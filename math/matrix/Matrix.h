/**
@file Matrix.h
@author Mike Lindstrom
@date May 2024
@version 5

@brief This gives a very simple implementation of a matrix class.

@details This works as a very elementary matrix class. There are few optimizations done besides enabling
move semantics, and memcpy for copying. Inversion is really slow using a naive Gaussian elimination and multiplication
follows the naive direct approach.
*/

#ifndef _BASIC_MATH__MATRIX_
#define _BASIC_MATH__MATRIX_

#include<utility>
#include<iomanip>
#include<iostream>
#include<initializer_list>
#include<stdexcept>
#include<memory>
#include<cstring>
#include<concepts>

// within the basic_math namespace, we define the matrix class
namespace basic_math {

	namespace {

		// allocator class for internal purposes only

		template<typename D>
		struct allocator {
			D* allocate(size_t N) const {
				return static_cast<D*>(operator new(N * sizeof(D)));
			}

			template<typename ... Types>
			void construct(D* p, Types&& ... vals)  const {
				new (p) D(std::forward<Types>(vals)...);
			}

			void destroy(D* p) const {
				p->~D();
			}

			void deallocate(D* p) const {
				operator delete(p);
			}
		};
	}

	/**
	@class matrix defines a rudimentary matrix class with a few
	key operations
	@tparam D the type of data stored, double by default, should be some floating point type (or complex)
	*/
	template<typename D = double>
	class matrix {
	public:
		using value_type = D; // standard typedef

	private:
		static constexpr int width = 6; // width of each entry (unless entry is too wide)
		size_t rows, cols; // its number of rows and columns
		D* values; // all of our data is layed out contiguously
		allocator<D> data_alloc; // allocator for data		

									  /**
									  Helper function to get index of an entry given row and col
									  @param row the row index from 0
									  @param col the column index from 0
									  @return the index from 0, counting left to right then top to bottom
									  */
		size_t entry_index(const size_t row, const size_t col) const {
			return row * cols + col;
		}

		/**
		Helper function to get the row index given an entry's index
		@param entry the index
		@return the row index, indexed from 0
		*/
		size_t row_index(const size_t entry) const {
			return entry / cols;
		}

		/**
		Helper function to get the column index given an entry's index
		@param entry the index
		@return the column index, indexed from 0
		*/
		size_t col_index(const size_t entry) const {
			return entry % cols;
		}

		/**
		Helper function to update all entries by an operator
		@tparam op the type of function object
		@param right matrix on the right
		@param fun the function to run
		*/
		template<typename op, typename = typename std::enable_if< std::is_function<op>::value >>
		void update(const matrix& right, const op& operation) {
			const size_t entries = rows * cols;
			for (size_t i = 0; i < entries; ++i) { // go through all elements and to this
				values[i] = operation(values[i], right.values[i]);
			}
		}

		/**
		Helper function removes the row i and col j from matrix
		@param i the row to remove
		@param j the col to remove
		@return a matrix without row i and col j
		*/
		[[nodiscard]] matrix without(size_t i, size_t j) const {
			matrix ret(rows - 1, cols - 1);
			for (size_t p = 0; p < i; ++p) { // top
				for (size_t q = 0; q < j; ++q) { // and left
					ret(p, q) = operator()(p, q);
				}
				for (size_t q = j+1; q < cols; ++q) { // and right
					ret(p, q-1) = operator()(p, q);
				}
			}
			for (size_t p = i+1; p < rows; ++p) { // bottom
				for (size_t q = 0; q < j; ++q) { // and left
					ret(p-1, q) = operator()(p, q);
				}
				for (size_t q = j + 1; q < cols; ++q) { // and right
					ret(p-1, q - 1) = operator()(p, q);
				}
			}
			return ret;
		}

	public:

		/**
		default constructor makes an empty size 0 matrix!
		*/
		matrix() : rows(0), cols(0), values(nullptr) {}

		/**
		constructor: makes a matrix with all zeros for the rows and columns
		@param _rows number of rows
		@param _cols number of columns
		*/
		matrix(const size_t _rows, const size_t _cols);

		/**
		constructor accepts an initializer list of rows, each being an initializer list of D's
		@param list an initilizer list of initializer lists
		*/
		matrix(const std::initializer_list< std::initializer_list<D> >& input);

		/**
		Copy constructor to copy the matrix elements
		@param other the other matrix
		*/
		matrix(const matrix& other);

		/**
		Function to swap two matrices
		@param first the first matrix
		@param second the second matrix
		*/
		friend void swap(matrix& first, matrix& second) {
			using std::swap; // enable ADL (not that we should need it here)
			swap(first.rows, second.rows);
			swap(first.cols, second.cols);
			swap(first.values, second.values);
			swap(first.data_alloc, second.data_alloc);
		}

		/**
		Move constructor: steals from another matrix
		@param other an rvalue to steal from
		*/
		matrix(matrix&& other) noexcept : matrix() {
			swap(*this, other);
		}

		/**
		assignment operators
		@param that the matrix that overwrites the left side
		*/
		matrix& operator=(matrix that) { // will be copy or move constructed
			swap(*this, that);  // swap the two using friend swap
			return *this;  // return the new matrix
		}

		/**
		size function returns the size of a matrix either number of
		rows or number of columns - 1 indicates number of rows, 2 indicates number of columns
		@param i whether row number (i==0) or col number (i==1)
		@return the dimension
		*/
		[[nodiscard]] size_t size(const size_t i) const {
			return (0 <= i && i < 2) ?
				((i == 0) ? rows : cols) : throw std::logic_error("improper size parameter");
		}

		/**
		transpose operator makes the transpose
		@return the matrix transpose so the (ij) entry of the transpose is the (ji) entry of the original
		*/
		[[nodiscard]] matrix T() const {
			matrix transpose(cols, rows);
			for (size_t i = 0; i < rows; ++i) { // for each row of original
				for (size_t j = 0; j < cols; ++j) { // for each column of original
					transpose(j, i) = operator()(i, j); // flip over the diagonal
				}
			}
			return transpose;
		}

		/**
		trace operator
		@return the trace of the matrix
		*/
		[[nodiscard]] value_type tr() const {
			if (rows != cols) [[unlikely]] { // invalid
				throw std::logic_error("cannot compute trace of non-square matrix");
			}
			value_type tot{};
			for (size_t i = 0; i < rows; ++i) { // add along diagonal
				tot += operator()(i, i);
			}
			return tot;
		}

		/**
		Conversion operator: can convert a 1x1 matrix<D> to a D
		@return the scalar value stored in the 1x1 matrix
		*/
		operator value_type() const {
			if ((rows == 1) && (cols == 1)) { // then it is just a scalar
				return operator()(0, 0); // give its value
			}
			else { // but if not a scalar this makes no sense!
				throw std::logic_error("cannot convert matrix");
			}
		}

		/**
		Get the diagonal of a matrix
		@param col whether to return as column vector (otherwise row vector),
		default is true
		@return the diagonal as a column vector
		*/
		[[nodiscard]] matrix diag(bool col=true) const {
			if (rows != cols) { // invalid
				throw std::logic_error("cannot compute diagonal of non-square matrix");
			}
			if (col) [[likely]] { // get a column
				matrix d(rows, 1);
				for (size_t i = 0; i < rows; ++i) { // set values
					d(i, 0) = operator()(i, i);
				}
				return d;
			}
			else { // get a row
				matrix d(1, rows);
				for (size_t i = 0; i < rows; ++i) { // set values
					d(0, i) = operator()(i, i);
				}
				return d;
			}
		}

		/**
		select a submatrix
		@param row_low the lower row index to start at
		@param row_up the past-the-end row index
		@param row_stride the stride width for rows 
		@param col_low the lower col index to start at 
		@param col_up the past-the-end column index 
		@param col_stride the stride width for columns 
		@return a submatrix: indexing past the edges will not happen
		*/
		[[nodiscard]] matrix<D> select(size_t row_low, size_t row_up, size_t row_stride,
			size_t col_low, size_t col_up, size_t col_stride) const {

			// no stride width or bad order
			if (row_low > row_up || col_low > col_up || row_stride == 0 || col_stride == 0) { 
				throw std::logic_error("bad selection");
			}

			// empty selection get empty matrix
			if (row_low == row_up || col_low == col_up) {
				return {};
			}

			// row_up and col_up must both be > 0
			// set bounds on what past-the-end means
			const size_t max_row = (row_up > rows) ? rows : row_up;
			const size_t max_col = (col_up > cols) ? cols : col_up;

			// widest range is from row_low to max_row-1 inclusive
			// add 1 in case round to 0
			const size_t num_rows = 1+ (max_row-1 - row_low) / row_stride;
			const size_t num_cols = 1+ (max_col-1 - col_low) / col_stride;

			matrix<D> m(num_rows, num_cols);
			for (size_t i = 0; i < num_rows; ++i) {
				for (size_t j = 0; j < num_cols; ++j) {
					m(i, j) = operator()(row_low + i * row_stride, col_low + j * col_stride);
				}
			}

			return m;
		}

		/**
		computes the determinant very inefficiently with Laplace expansion
		@return the determinant
		*/
		[[nodiscard]] value_type det() const {
			if (rows != cols) { // not square
				throw std::logic_error("can only take determinant of square matrix");
			}

			if (rows == 1) { // base case
				return operator()(0, 0);
			}

			// sign
			int sgn = 1;
			value_type tot{}; // start at 0
			for (size_t i = 0; i < cols; ++i) { // run across row 0
				tot += operator()(0,i) * without(0, i).det() * sgn;
				sgn = -sgn;
			}
			return tot;
		}


		/**
		Destructor to free resources
		*/
		~matrix();

		/**
		@class row a class to represent a row of a non-const matrix
		*/
		class row; // nested row class

				   /**
				   @class const_row a class to represent a row of a const matrix
				   */
		class const_row; // nested const row class

						 /**
						 @class column a class to represent a column of a non-const matrix
						 */
		class column; // nested column class

					  /**
					  @class const_column a class to represent a column of a const matrix
					  */
		class const_column; // nested const column class

							/**
							subscript returns a row, index from 0
							@param i the row index
							@return the ith row
							*/
		row operator[](const size_t i);

		/**
		subscript returns a const row, index from 0
		@param i the row index
		@return the const ith row
		*/
		const_row operator[](const size_t i) const;

		/**
		returns a column, index from 0
		@param i the column index
		@return the ith column
		*/
		column get_col(const size_t i);

		/**
		returns a const column, index from 0
		@param i the column index
		@return the ith column
		*/
		const_column get_col(const size_t i) const;

		/**
		call operator - non const version, indexed from 0
		@param i row index
		@param j the column index
		@return reference to element
		*/
		value_type& operator()(const size_t i, const size_t j) {
			if ((i < rows) && (j < cols)) { // if valid indices then just return the value
				return values[entry_index(i, j)];
			}
			else { // otherwise, throw exception
				throw std::logic_error("bad call indices for matrix");
			}
		}

		/**
		call operator - const version, indexed from 0
		@param i row index
		@param j the column index
		@return reference to element
		*/
		const value_type& operator()(const size_t i, const size_t j) const {
			if ((i < rows) && (j < cols)) { // if valid indices then just return the value
				return values[entry_index(i, j)];
			}
			else { // otherwise, throw exception
				std::cerr << i << ", " << j << " - bad call indices for matrix";
				throw std::logic_error("bad call indices for matrix");
			}
		}

		/**
		addition to update left matrix
		@param right matrix on the right
		@return the left plus right, returned as reference to left
		*/
		matrix& operator+=(const matrix& right) {

			if ((rows != right.rows) || (cols != right.cols)) { // if not same size cannot add
				throw std::logic_error("can only add matrices of the same size!");
			}

			// call the update function with +
			update(right, [](value_type x, value_type y)->value_type { return x + y; });

			return *this;
		}

		/**
		subtraction to update left matrix
		@param right matrix on the right
		@return the left minus right, returned as reference to left
		*/
		matrix& operator-=(const matrix& right) {
			if ((rows != right.rows) || (cols != right.cols)) { // if not same size cannot minus them
				throw std::logic_error("can only subtract matrices of the same size!");
			}

			// call the update function with -
			update(right, [](value_type x, value_type y)->value_type { return x - y; });

			return *this;
		}

		/**
		elementwise multiplication to update left matrix
		@param right matrix on the right
		@return the left elementwise multiplied by right, returned as reference to left
		*/
		matrix& operator%=(const matrix& right) {
			if ((rows != right.rows) || (cols != right.cols)) { // if not same size cannot minus them
				throw std::logic_error("can only subtract matrices of the same size!");
			}

			// call the update function with *
			update(right, [](value_type x, value_type y)->value_type { return x * y; });

			return *this;
		}

		/**
		elementwise add scalar
		@param _scalar scalar on the right
		@return the right values added to all of the left, returned as reference to left
		*/
		matrix& operator+=(const value_type& _scalar) {
			for (size_t i = 0; i < rows; ++i) { // for each row
				for (size_t j = 0; j < cols; ++j) {  // and column
					(*this)(i, j) += _scalar; // update the value
				}
			}
			return *this;
		}

		/**
		elementwise subtract scalar
		@param _scalar scalar on the right
		@return the right values subtracted from to all of the left, returned as reference to left
		*/
		matrix& operator-=(const value_type& _scalar) {
			for (size_t i = 0; i < rows; ++i) { // for each row
				for (size_t j = 0; j < cols; ++j) {  // and column
					(*this)(i, j) -= _scalar; // update the value
				}
			}
			return *this;
		}

		/**
		multiply matrix by scalar
		@param _scalar scalar on the right
		@return the left times right, returned as reference to left
		*/
		matrix& operator*=(const value_type& _scalar) {
			for (size_t i = 0; i < rows; ++i) { // for each row
				for (size_t j = 0; j < cols; ++j) {  // and column
					(*this)(i, j) *= _scalar; // update the value
				}
			}
			return *this;
		}

		/**
		matrix multiplcation *= to update left
		@param right right matrix
		@return new left matrix
		*/
		matrix& operator*=(const matrix& right);

		/**
		return a copy with +
		@return a copy
		*/
		[[nodiscard]] matrix operator+() const { return *this; }

		/**
		return a negated copy with -
		@return the negative
		*/
		[[nodiscard]] matrix operator-() const {
			matrix negated(rows, cols); // start at all 0's
			return negated -= *this; // subtract off this matrix
		}

		/**
		operator to print the matrices
		@param out the output stream
		@param mat the matrix to print
		*/
		friend std::ostream& operator<<(std::ostream& out, const matrix<D>& mat) {

			for (size_t i = 0; i < mat.rows; ++i) { // go over rows
				out << "[";
				for (size_t j = 0; j < mat.cols; ++j) {  // and colunns
					out << std::setw(width) << mat[i][j] << " "; // print with given width
				}
				out << "]" << '\n'; // and new line
			}

			return out; // return the stream
		}

	};

	/**
	deduction guide for matrix, always deduct to default type
	@tparam ... Types the types used
	@param ... vals the arguments
	*/
	template<typename ... Types>
	matrix(Types&& ... vals)->matrix<>;

	
	/**
	computes matrix inverse: very costly operation, beware!
	@param X the matrix to invert
	@return its inverse, or throws an exception if there is no inverse
	*/
	template<typename D>
	[[nodiscard]] matrix<D> inverse(matrix<D> X);

	/**
	operator+ to add two matrices
	@tparam D the data type
	@param left left matrix
	@param right right matrix
	@return their sum
	*/
	template<typename D>
	[[nodiscard]] matrix<D> operator+(matrix<D> left, const matrix<D>& right);

	/**
	operator- to subtract two matrices
	@tparam D the data type
	@param left left matrix
	@param right right matrix
	@return their difference
	*/
	template<typename D>
	[[nodiscard]] matrix<D> operator-(matrix<D> left, const matrix<D>& right);

	/**
	regular matrix multiplication provided the inner dimensions agree
	@tparam D the data stored in the matrices
	@param left the left matrix
	@param right the right matrix
	@return their product
	*/
	template<typename D>
	[[nodiscard]] matrix<D> operator*(matrix<D> left, const matrix<D>& right);

	/**
	matrix elementwise multiplication when dimensions directly match
	@param left the left matrix
	@param right the right hand matrix
	@return the elementwise multiplication
	*/
	template<typename D>
	[[nodiscard]] matrix<D> operator%(matrix<D> left, const matrix<D>& right);

	/**
	convert matrix(vector) to diagonal matrix
	@tparam D the type of vector data
	@param v the vector
	@return a diagonal matrix from v
	*/
	template<typename D>
	[[nodiscard]] matrix<D> diag(const matrix<D>& v);

	/**
	make a diagonal matrix with a repeated value
	@tparam D the type of data
	@param N the matrix size
	@param v the value to repeat
	@return a diagonal matrix with v along the diagonal
	*/
	template<typename D>
	[[nodiscard]] matrix<D> diag(size_t N, D v);

	/**
	to perform an operation on each element of a matrix
	@tparam Functor the type of functor to use
	@tparam D the type of matrix data
	@param f the function
	@param m the matrix
	@return a matrix from f acting on each element of M
	*/
	template<typename Functor, typename D>
	[[nodiscard]] matrix<D> apply_to(Functor&& f, matrix<D> m);

	/**
	to perform an operation on each element of a matrix
	@tparam Functor the type of functor to use
	@tparam D the type of matrix data
	@param f the function
	@param m the matrix
	@return a matrix from f acting on each element of M
	*/
	template<typename Functor, typename D>
	[[nodiscard]] matrix<D> operator%(Functor&& f, matrix<D> m);

	/**
	to multiply a column with a row
	@tparam D the type of matrix the row and column matrices belong to
	@param _col the column
	@param _row the row
	@return the resulting matrix
	*/
	template<typename D>
	[[nodiscard]] matrix<D> col_times_row(const typename matrix<D>::const_column& _col,
		const typename matrix<D>::const_row& _row);



	/**
	a utility function to make an identity matrix
	@tparam D the data type
	@param dim the dimension
	*/
	template<typename D>
	[[nodiscard]] matrix<D> make_identity(const size_t dim) {
		matrix<D> id(dim, dim);
		for (size_t i = 0; i < dim; ++i) { // place 1's on diagonal
			id(i, i) = 1;
		}
		return id;
	}


	/**
	to add scalar to matrix
	@tparam S the type of the scalar
	@tparam D the type of data in the matrix
	@param _mat the matrix to add to
	@param _scalar the scalar value
	@return the matrix plus the scalar
	*/
	template<typename S, typename D>
	[[nodiscard]] matrix<D> operator+(const S& _scalar, matrix<D> _mat);

	/**
	to add scalar to matrix
	@tparam D the type of data in the matrix
	@tparam S the type of the scalar
	@param _mat the matrix to add to
	@param _scalar the scalar value
	@return the matrix plus the scalar
	*/
	template<typename D, typename S>
	[[nodiscard]] matrix<D> operator+(matrix<D> _mat, const S& _scalar);


	/**
	to subtract matrix from scalar elementwise
	@tparam S the type of the scalar
	@tparam D the type of data in the matrix
	@param _mat the matrix being subtracted elementwise
	@param _scalar the scalar value
	@return the scalar minus matrix elementwise
	*/
	template<typename S, typename D>
	[[nodiscard]] matrix<D> operator-(const S& _scalar, matrix<D> _mat);

	/**
	to subtract scalar from matrix elementwise
	@tparam D the type of data in the matrix
	@tparam S the type of the scalar
	@param _mat the matrix to add to
	@param _scalar the scalar value
	@return the matrix minus the scalar elementwise
	*/
	template<typename D, typename S>
	[[nodiscard]] matrix<D> operator-(matrix<D> _mat, const S& _scalar);


	/**
	to multiply a matrix by a scalar
	@tparam S the type of the scalar
	@tparam D the type of data in the matrix
	@param _mat the matrix to multiply
	@param _scalar the scalar value
	@return the matrix times the scalar
	*/
	template<typename S, typename D>
	[[nodiscard]] matrix<D> operator*(const S& _scalar, matrix<D> _mat);

	/**
	to multiply a matrix by a scalar
	@tparam S the type of the scalar
	@tparam D the type of data in the matrix
	@param _mat the matrix to multiply
	@param _scalar the scalar value
	@return the matrix times the scalar
	*/
	template<typename D, typename S>
	[[nodiscard]] matrix<D> operator*(matrix<D> _mat, const S& _scalar);

	/**
	to divide a matrix by a scalar value
	@tparam D the data type of the matrix
	@tparam S the data type of the scalar to be turned into T
	@param mat the matrix
	@param scalar the scalar value
	@return the matrix divided by the scalar
	*/
	template<typename D, typename S>
	[[nodiscard]] matrix<D> operator/(matrix<D> mat, const S& scalar);

	/**
	to divide a scalar by matrix elementwise
	@tparam S the data type of the scalar to be turned into T
	@tparam D the data type of the matrix
	@param scalar the scalar value
	@param mat the matrix
	@return the matrix divided by the scalar
	*/
	template<typename S, typename D>
	[[nodiscard]] matrix<D> operator/(const S& scalar, matrix<D> mat);

	/**
	to make a linear space
	@tparam D the type of data
	@param low the lower bound
	@param up the upper bound 
	@param N the number of interval points
	@param col whether to make a column vector, true by default 
	@return vector with N points, uniformly spaced from low to up
	*/
	template<typename D>
	[[nodiscard]] matrix<D> linspace(D low, D up, size_t N, bool col = true);


	/* DEFINITIONS */

	// construct zeros by size

	template<typename D>
	matrix<D>::matrix(const size_t _rows, const size_t _cols) : rows(_rows), cols(_cols), values(nullptr) { // start as null

		const size_t entries = rows * cols;

		values = data_alloc.allocate(entries); // allocate space for all entries

		for (size_t i = 0; i < entries; ++i) { // go through every entry
			try { // and try to place an element there				
				data_alloc.construct(values + i);
			}
			catch (...) { // if we fail
				for (size_t j = 0; j < i; ++j) { // destroy all created items up to but not i where failed
					data_alloc.destroy(values + j);
				}
				data_alloc.destroy(values);
				throw; // throw onwards
			}
		}

	} // end constructor body

	  // constructor accepting lists
	template<typename D>
	matrix<D>::matrix(const std::initializer_list< std::initializer_list<D> >& input) : rows(input.size()),
		cols(input.begin()->size()), values(nullptr) { // start as null
		const size_t entries = rows * cols;

		auto row_list_iter = input.begin(); // iterator starts at first initializer list

		values = data_alloc.allocate(entries); // allocate space for all entries

		for (size_t i = 0; i < rows; ++i) { // for each row

			size_t j = 0;

			try { // try to allocate space
				auto col_list_iter = row_list_iter->begin(); // start at beginning of the list

				if (row_list_iter->size() != cols) { // if a row doesn't have the same size as the rest, that's bad.
					throw std::logic_error("not all rows same size");
				}

				for (j = 0; j < cols; ++j) { // for each col place in that row
					data_alloc.construct(values + entry_index(i, j), *(col_list_iter++)); // make the value the proper col value from the list
				}

				++row_list_iter; // advance to the initializer list of the next row
			}
			catch (...) { // if a row failed on ith
				size_t last = entry_index(i, j);
				for (size_t k = 0; k < last; ++k) { // go over all successful rows and destroy them
					data_alloc.destroy(values + k);
				}
				data_alloc.deallocate(values, entries); // and free up the memory  
				throw;
			}
		}
	} // end initializer list constructor body


	  // copy constructor
	template<typename D>
	matrix<D>::matrix(const matrix& other) : rows(other.rows), cols(other.cols), values(nullptr) { // start as null
		const size_t entries = rows * cols;

		values = data_alloc.allocate(entries); // allocate space for rows

											   // copy into values space from other, need to tract sizeof the data type and number of entries for bytes moved
		std::memcpy(values, other.values, sizeof(value_type) * entries);

	} // end copy body

	  // destructor
	template<typename D>
	matrix<D>::~matrix() {
		if (!values) { // if the values pointer is null then do nothing!
			return;
		}
		else { // assuming not null, clean up
			const size_t entries = rows * cols;

			for (size_t i = 0; i < entries; ++i) { // go through all entries and destroy
				data_alloc.destroy(values + i);
			}

			data_alloc.deallocate(values);

			values = nullptr;
		}
	}




	// the row class!
	template<typename D>
	class matrix<D>::row {
		friend matrix; // matrix needs to create rows and manipulate them

	private:
		matrix* owner; // matrix it belongs to
		size_t offset; // the row offset value

					   /**
					   row constructor has a row offset and a matrix it references
					   @param _offset the row number
					   @param _owner its matrix
					   */
		row(const size_t _offset, matrix* _owner) : owner(_owner), offset(_offset) {}

	public:

		/**
		subscript operator returns the value of the ith colunn of that row as const
		@param i the column being examined
		@return the value
		*/
		const value_type& operator[](const size_t i) const {
			return (*owner)(offset, i);
		}

		/**
		subscript operator returns the value of the ith colunn of that row
		@param i the column being examined
		@return the value
		*/
		value_type& operator[](const size_t i) {
			return (*owner)(offset, i);
		}

		/**
		turns a row into a const_row
		@return a const_row
		*/
		operator const_row() const {
			return const_row(offset, owner);
		}

	};

	// the const row class!
	template<typename D>
	class matrix<D>::const_row {
		friend matrix;
		friend row; // so row can be converted to const_row

		friend matrix<D> col_times_row<D>(const typename matrix<D>::const_column& _col,
			const typename matrix<D>::const_row& _row);

	private:
		const matrix* owner; // matrix it belongs to
		size_t offset; // the row offset value

					   /**
					   row constructor has a row offset and a matrix it references
					   @param _offset the row number
					   @param _owner its matrix
					   */
		const_row(const size_t _offset, const matrix* _owner) : owner(_owner), offset(_offset) {}

	public:

		/**
		subscript operator returns the value of the ith colunn of that row as const
		@param i the column being examined
		@return the value
		*/
		const value_type& operator[](size_t i) const {
			return (*owner)(offset, i);
		}

	};


	// the column class
	template<typename D>
	class matrix<D>::column {
		friend matrix;

	private:
		matrix* owner; // matrix it belongs to
		size_t offset; // the row offset value

					   /**
					   row constructor has a row offset and a matrix it references
					   @param _offset the row number
					   @param _owner its matrix
					   */
		column(const size_t _offset, matrix* _owner) : owner(_owner), offset(_offset) {}

	public:

		/**
		subscript operator returns the value of the ith colunn of that row as const
		@param i the column being examined
		@return the value
		*/
		const value_type& operator[](size_t i) const {
			return (*owner)(i, offset);
		}

		/**
		subscript operator returns the value of the ith colunn of that row
		@param i the column being examined
		@return the value
		*/
		value_type& operator[](const size_t i) {
			return (*owner)(i, offset);
		}

		/**
		turns the column into a const_column
		@return a const_column
		*/
		operator const_column() const {
			return const_column(offset, owner);
		}

	};

	// the const column class
	template<typename D>
	class matrix<D>::const_column {

		friend matrix;
		friend column; // so column can be made to const_column

		friend matrix<D> col_times_row<D>(const typename matrix<D>::const_column& _col,
			const typename matrix<D>::const_row& _row);

	private:
		const matrix* owner; // matrix it belongs to
		size_t offset; // the row offset value

					   /**
					   row constructor has a row offset and a matrix it references
					   @param _offset the row number
					   @param _owner its matrix
					   */
		const_column(const size_t _offset, const matrix* _owner) : owner(_owner), offset(_offset) {}

	public:

		/**
		subscript operator returns the value of the ith colunn of that row as const
		@param i the column being examined
		@return the value
		*/
		const value_type& operator[](const size_t i) const {
			return (*owner)(i, offset);
		}

	};

	// subscript operators

	template<typename D>
	typename matrix<D>::const_row matrix<D>::operator[](const size_t i) const {
		return (i < rows) ? const_row(i, this) : throw std::logic_error("index past rows"); // make a row of the data
	}

	template<typename D>
	typename matrix<D>::row matrix<D>::operator[](const size_t i) {
		return (i < rows) ? row(i, this) : throw std::logic_error("index past rows"); // make a row of the data
	}

	template<typename D>
	typename matrix<D>::const_column matrix<D>::get_col(const size_t i) const {
		return (i < cols) ? const_column(i, this) : throw std::logic_error("index past columns"); // make a row of the data
	}

	template<typename D>
	typename matrix<D>::column matrix<D>::get_col(const size_t i) {
		return (i < cols) ? column(i, this) : throw std::logic_error("index past columns"); // make a row of the data
	}

	// outer product

	template<typename D>
	matrix<D> col_times_row(const typename matrix<D>::const_column& _col, const typename matrix<D>::const_row& _row) {
		matrix<D> res(_col.owner->size(0), _row.owner->size(1)); // the resulting matrix
		for (size_t i = 0, col_height = res.size(0); i < col_height; ++i) { // loop over the entries of _col
			for (size_t j = 0, row_width = res.size(1); j < row_width; ++j) { // and the entries of _row
				res(i, j) = _col[i] * _row[j]; // multiply to generate the rank 1 outer product
			}
		}
		return res;
	}


	// plain operator+
	template<typename D>
	matrix<D> operator+(matrix<D> left, const matrix<D>& right) { // left by value, right ref to const
		return std::move(left += right); // define + by +=
	}

	// plain operator-
	template<typename D>
	matrix<D> operator-(matrix<D> left, const matrix<D>& right) { // left by value, right ref to const
		return std::move(left -= right); // define - by -=
	}

	// plain operator%
	template<typename D>
	matrix<D> operator%(matrix<D> left, const matrix<D>& right) {
		return std::move(left %= right); // defined by %=
	}

	template<typename D>
	matrix<D> diag(const matrix<D>& v) {
		if (v.size(0) != 1 && v.size(1) != 1) { // not a vector
			throw std::logic_error("require a vector with one dimension of 1 to make diagonal matrix");
		}
		if (v.size(0) == 1) { // a row vector
			const size_t N = v.size(1);
			matrix<D> d(N, N);
			for (size_t i = 0; i < N; ++i) { // set values across the row
				d(i, i) = v(0, i);
			}
			return d;
		}
		// must be a column vector
		const size_t N = v.size(0); 
		matrix<D> d(N, N);
		for (size_t i = 0; i < N; ++i) { // set values down the column
			d(i, i) = v(i,0);
		}
		return d;
	}

	template<typename D>
	matrix<D> diag(size_t N, D v) {
		return make_identity<D>(N) * v;
	}

	template<typename D>
	matrix<D>& matrix<D>::operator*=(const matrix& right) {
		if (size(1) != right.size(0)) { // if inner dimension mismatch
			throw std::logic_error("inner matrix dimensions must agree");
		}

		size_t num_rows = size(0);
		size_t num_cols = right.size(1);

		matrix product(num_rows, num_cols);

		for (size_t i = 0, num_rows = size(0); i < num_rows; ++i) { // set ith row of product
			for (size_t j = 0, right_cols = right.size(1); j < right_cols; ++j) { // and jth column of product
				for (size_t k = 0, inner_dim = size(1); k < inner_dim; ++k) { // loop over their inner parts
					product(i, j) += (*this)(i, k) * right(k, j);
				}
			}
		}
		return *this = product; // return result that's updated
	}


	// times operator
	template<typename D>
	matrix<D> operator*(matrix<D> left, const matrix<D>& right) {
		return std::move(left *= right); // use *= to define *
	}


	template<typename S, typename D>
	matrix<D> operator+(const S& _scalar, matrix<D> _mat) {
		return std::move(_mat += static_cast<D>(_scalar));
	}

	template<typename D, typename S>
	matrix<D> operator+(matrix<D> _mat, const S& _scalar) {
		return std::move(_mat += static_cast<D>(_scalar));
	}


	template<typename S, typename D>
	matrix<D> operator-(const S& _scalar, matrix<D> _mat) {
		return -(_mat -= static_cast<D>(_scalar));
	}

	template<typename D, typename S>
	matrix<D> operator-(matrix<D> _mat, const S& _scalar) {
		return std::move(_mat += static_cast<D>(-_scalar));
	}


	template<typename S, typename D>
	matrix<D> operator*(const S& _scalar, matrix<D> _mat) {
		return std::move(_mat *= static_cast<D>(_scalar));
	}


	template<typename D, typename S>
	matrix<D> operator*(matrix<D> _mat, const S& _scalar) {
		return std::move(_mat *= static_cast<D>(_scalar));
	}

	template<typename D, typename S>
	matrix<D> operator/(matrix<D> mat, const S& scalar) {
		return std::move(mat *= (1 / static_cast<D>(scalar)));
	}

	template<typename S, typename D>
	matrix<D> operator/(const S& scalar, matrix<D> mat) {
		for (size_t i = 0, rows = mat.size(0); i < rows; ++i) {
			for (size_t j = 0, cols = mat.size(1); j < cols; ++j) {
				mat(i, j) = scalar / mat(i, j);
			}
		}
		return mat;
	}

	template<typename D>
	matrix<D> linspace(D low, D up, size_t N, bool col) {
		auto dx = (up - low) / (N - 1);
		if (col) { // column vector
			matrix<D> m(N, 1);
			for (size_t i = 0; i < N; ++i) { // uniform space
				m(i, 0) = low + i * dx;
			}
			return m;
		}
		// row vector
		matrix<D> m(1,N);
		for (size_t i = 0; i < N; ++i) {
			m(0,i) = low + i * dx;
		}
		return m;
	}

	template<typename Functor, typename D>
	matrix<D> apply_to(Functor&& f, matrix<D> m) {
		for (size_t i = 0, rows = m.size(0); i < rows; ++i) {
			for (size_t j = 0, cols = m.size(1); j < cols; ++j) {
				m(i, j) = f(m(i, j));
			}
		}
		return m;
	}

	template<typename Functor, typename D>
	matrix<D> operator%(Functor&& f, matrix<D> m) {
		for (size_t i = 0, rows = m.size(0); i < rows; ++i) {
			for (size_t j = 0, cols = m.size(1); j < cols; ++j) {
				m(i, j) = f(m(i, j));
			}
		}
		return m;
	}

	namespace {

		/**
		function to make X lower triangular and update its inverse
		@param X the matrix to invert
		@param Xinv its inverse being computed
		*/

		template<typename D>
		void make_lower(matrix<D>& X, matrix<D>& Xinv) {
			using std::swap;

			const size_t rows = X.size(0);
			const size_t cols = X.size(1);

			size_t curr = cols - 1; // current column we are working on, start with last

			while (curr > 0) { // while not made it to top row
				if (X(curr, curr) == 0) { // no pivot to use 
					size_t look = curr - 1; // where we look for a nonzero
					for (; look != static_cast<size_t>(-1); --look) { // go looking for nonzero at higher rows
						if (X(look, curr) != 0) { // break out we found our match
							break;
						}
					}
					if (look != static_cast<size_t>(-1)) { // then just need to swap two rows 
						for (size_t col = 0; col < cols; ++col) { // column by column swap values
							swap(X(look, col), X(curr, col));
							swap(Xinv(look, col), Xinv(curr, col));
						}
					}
					else { // all zeros then, bad
						throw std::runtime_error("matrix is not invertible");
					}
				}

				// now we have a safe pivot
				size_t row = curr - 1;
				for (; row != static_cast<size_t>(-1); --row) { // move up from row above curr
					D factor = X(row, curr) / X(curr, curr);
					for (size_t col = 0; col < cols; ++col) { // column by column do the operation
						X(row, col) -= factor * X(curr, col);
						Xinv(row, col) -= factor * Xinv(curr, col);
					}
				}

				--curr; // move back a column
			}
		}

		/**
		function to make X diagonal and update its inverse
		@param X the matrix to invert
		@param Xinv its inverse being computed
		*/
		template<typename D>
		void make_diagonal(matrix<D>& X, matrix<D>& Xinv) {
			using std::swap;

			const size_t rows = X.size(0);
			const size_t cols = X.size(1);

			// now we have a lower triangular matrix X and we solve via forward substitution
			size_t curr = 0; // start at left column

			while (curr < cols - 1) { // while not cleared all the columns
				size_t row = curr + 1; // row we need to clear
				for (; row <= rows - 1; ++row) {
					D factor = X(row, curr) / X(curr, curr);
					X(row, curr) -= factor * X(curr, curr);
					for (size_t col = 0; col < cols; ++col) { // update all entries in the given row					
						Xinv(row, col) -= factor * Xinv(curr, col);
					}
				}
				++curr; // move to next column
			}
		}

	}

	// lengthy inverse computation
	template<typename D>
	matrix<D> inverse(matrix<D> X) {

		const size_t rows = X.size(0);
		const size_t cols = X.size(1);

		if ((rows != cols) || rows == 0 || cols == 0) { // ensure matrix has a positive size and is square
			throw std::logic_error("matrix is not square");
		}

		auto Xinv = make_identity<D>(rows); // identity matrix

											// we will try to make X lower triangular
		make_lower(X, Xinv);

		// now make X diagonal
		make_diagonal(X, Xinv);

		// now make X into identity and update its inverse

		// make diagonal all 1's
		for (size_t i = 0; i < cols; ++i) { // range over diagonal entries (i,i) of X
			for (size_t col = 0; col < cols; ++col) { // and divide each entry of that row by X(i,i)
				Xinv(i, col) /= X(i, i);
			}
			X(i, i) = 1; // will have normalized to 1
		}

		return Xinv;
	}




} // end namespace



#endif
