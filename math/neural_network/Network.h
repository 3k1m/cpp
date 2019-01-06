/**
@file Network.h
@author Mike Lindstrom
@version 3

@brief This file defines the network_manager class that a user can directly work with to learn with a neural network.
The nested inner classes neural_network and network_policies are also defined here.

@details To use this neural network, one constructs a network_manager class with appropriate parameters. This class
stores within it a neural_network (bare bones weight matrices and bias vectors) and network_policies (how the neural
network is supposed to operate/learn)
*/
#ifndef _BASIC_NETWORK__NETWORK_
#define _BASIC_NETWORK__NETWORK_

#include<cmath>
#include<vector>
#include<ctime>
#include<cstdlib>
#include<random>
#include<memory>
#include<deque>
#include<fstream>
#include<string>
#include<set>
#include<utility>
#include<type_traits>
#include<algorithm>

#include "Matrix.h"
#include "Network_Components.h"

namespace basic_network {

	/**
	@class network_manager can be used directly by a user to learn with a neural network
	@tparam T the type of data used, double by defaut but could in principle be any floating point type.
	*/
	template<typename T = double>
	class network_manager {
		static constexpr size_t print_epoch = 50; // how often to print

		using matrix_type = basic_math::matrix<T>; // just to avoid having to write basic_math::matrix_type everywhere!

	private:
		std::string parameter_out_file; // file to write parameters to
		std::string testing_out_file; // file to write test data to

									  /**
									  @class neural_network a neural network class that obeys the network_manager
									  */
		class neural_network; // nested class: this is the neural network

							  /**
							  @class network_policies a class that records how the neural network should operate
							  */
		class network_policies; // nested class: this sets policies for the network

		neural_network the_network; // network it manages
		network_policies policies; // its policies

		std::vector< in_out<T> > all_data; // the input and output vectors

		T fraction; // fraction of data used for training

					/**
					checks the stream is in a valid state for reading and throws and exception if not
					@param _in the input stream to test
					*/
		void check_stream(const std::istream& _in) {
			if (!_in) { // if not in a valid state
				std::cerr << "failed to open file or process data" << std::flush;
				throw std::runtime_error("stream failed");
			}
		}

		/**
		reads the data from a given file
		@param _data_file the data file to use
		@param _input_size number of inputs used
		@param _output_size number of output nodes
		*/
		void read_data(const std::string& _data_file, const size_t _input_size, const size_t _output_size);

		/**
		reads the node data
		@param _node_data the file to use to assign nodes to layers
		*/
		void read_nodes(const std::string& _node_data);

		/**
		gives data about the network that has been set up
		*/
		void display_info() const {
			std::cout << "Network has " << all_data.size() << " pieces of data." << '\n';			
		}

	public:
		/**
		The network manager can receive multiple arguments at the end to specify its policies.
		To construct a network manager, need
		@tparam Types the various types of data used to set policies
		@param _input_size number of inputs to receive
		@param _output_size number of outputs to give
		@param _data_file file containing the input data and output (not formatted necessarily)
		@param _node_file file contaiing number of nodes in each level
		@param _parameter_out_file file to write the parameters to
		@param _testing_out_file file to write testing data to
		@param _rate initial learning rate
		@param _decay geometric decrease in learning rate between epochs
		@param _momentum fractional amount of previous direction to include in new direction
		@param _fraction fraction to use for training
		@param _cost the const function to use
		@param _binning the way the binning is to be done, for example whether to represent the value 20 as a bucketed vector
		<0,0,1,0> (BUCKET), just as 20 (SINGLE), etc.
		@param _hidden_activations the activation function to be used at hidden layers
		@param _output_activations the activation to be used for output
		@param _values the setup values required for the binning for outputs
		the values within these parameters are given first as setup parameters and then as binning parameters
		if the binning calls for buckets, an initializer list of T's representing the cutoffs
		*/
		template<typename ... Types>
		network_manager(const size_t _input_size, const size_t _output_size, std::string _data_file,
			std::string _node_file, std::string _parameter_out_file, std::string _testing_out_file,
			const T& _rate, const T& _decay, const T& _momentum, const T& _fraction, const NETWORK_COST _cost,
			const NETWORK_BINNING _binning, const NETWORK_HIDDEN_ACTIVATIONS _hidden_activations,
			const NETWORK_OUTPUT_ACTIVATIONS _output_activations,
			Types&&... _values);

		/**
		run the neural network to learn
		@param _iterations number of iterations to run
		@param _sample the size of the sample data
		*/
		void run(const size_t _iterations, const size_t _sample) {

			for (size_t i = 0; i < _iterations; ++i) { // for each iteration
				the_network.learn(policies.get_rate(), _sample); // make it learn
				if (i % print_epoch == 0) {
					std::cout << "itertion " << i << ", error: " << the_network.average_cost() << '\n'; // print the average cost
				}

				policies.get_rate() *= policies.get_decay(); // make the rate a bit lower
			}

			the_network.save(); // and save the results!
		}

		/**
		tests the network and displays results
		*/
		void test() const {

			std::cout << "training complete. testing now\n";

			// to write to the file
			std::ofstream fout(testing_out_file);
			fout << "TRAINING: prediction/actual/cost\n\n";

			const size_t dataset_size = all_data.size();

			size_t num_tested = 0;
			T total_cost = 0;

			for (size_t i = 0, max_test = static_cast<size_t>(fraction * dataset_size); i < max_test; ++i) { // for i in range of traing data
				auto unthresholded = the_network.predict(all_data[i].input); // compute the prediction
				
				auto err = policies.get_error(all_data[i].output, unthresholded); // compute the error
				std::cout << "Prediction: " << unthresholded.T() << "\nExact: " <<
					all_data[i].output.T() << "\nCost: " << err << '\n'; // and display

				for (size_t j = 0, length = unthresholded.size(1); j < length; ++j) { // print values in prediction
					fout << unthresholded(j, 0) << '\t';
				}
				for (size_t j = 0, length = all_data[i].output.size(1); j < length; ++j) { // print values in actual
					fout << all_data[i].output(j, 0) << '\t';
				}
				fout << "\n\n";

				++num_tested;
				total_cost += err;
			}

			// give the average cost
			fout << "Average cost: " << total_cost / num_tested << "\n\n";

			// reset and now do for testing
			num_tested = 0;
			total_cost = 0;

			fout << "TESTING: prediction/actual/cost\n\n";

			for (size_t i = static_cast<size_t>(fraction * dataset_size) + 1; i < dataset_size; ++i) { // for i in range of testing data
				auto unthresholded = the_network.predict(all_data[i].input); // compute the prediction
				
				auto err = policies.get_error(all_data[i].output, unthresholded); // compute the error
				std::cout << "Prediction: " << unthresholded.T() << "\nExact: " <<
					all_data[i].output.T() << "\nCost: " << err << '\n'; // and display

				for (size_t j = 0, length = unthresholded.size(1); j < length; ++j) { // print values in prediction
					fout << unthresholded(j, 0) << '\t';
				}
				for (size_t j = 0, length = all_data[i].output.size(1); j < length; ++j) { // print values in actual
					fout << all_data[i].output(j, 0) << '\t';
				}
				fout << "\n\n";

				// and update running totals
				++num_tested;
				total_cost += err;
			}

			// give the average cost
			fout << "Average cost: " << total_cost / num_tested;

			fout.close();

		}

	};


	/**
	the policies class has all the policies necessary for the neural network to function
	@tparam T the floating type of the network_manager
	*/
	template<typename T>
	class network_manager<T>::network_policies {

		T norm; // the normalization constant, not including the batch size
		T rate; // learning rate
		T decay; // rate that learning rate decays
		T momentum; // momentum term

		std::function<matrix_type(const T&)> out; // output function for data of type T to matrix_type
		std::function<matrix_type(matrix_type)> thresh; // theseholded output: may make results 0 or 1 if necessary

		std::function<T(const matrix_type&, const matrix_type&)> error; // the error of a single trial (not including any normalization)
		std::function<matrix_type(const matrix_type&, const matrix_type&)> error_times_prime; // error times derivative of error vector with respect to activation

		std::function<matrix_type(const matrix_type&)> z_to_a_hidden; // how to take z-s to activations in hidden layer
		std::function<matrix_type(const matrix_type&)> z_to_dadz_hidden; // given z, what are dadz values in hidden layer
		std::function<matrix_type(const matrix_type&, const matrix_type&)> zw_to_dada_hidden; // given z and w values, how layer changes with respect to prior layer in hidden layer
		std::function<matrix_type(const matrix_type&)> z_to_dadb_hidden; // given z, how activation changes with respect to the biases in hidden layer
		std::function< std::vector< matrix_type>(const matrix_type&, const matrix_type&)> za_to_dadW_hidden; // the tensor derivative of a wrt to weights in hidden layer

		std::function<matrix_type(const matrix_type&)> z_to_a_output; // how to take z-s to activations in output layer
		std::function<matrix_type(const matrix_type&)> z_to_dadz_output; // given z, what are dadz values in output layer
		std::function<matrix_type(const matrix_type&, const matrix_type&)> zw_to_dada_output; // given z and w values, how layer changes with respect to prior layer in output layer
		std::function<matrix_type(const matrix_type&)> z_to_dadb_output; // given z, how activation changes with respect to the biases in output layer
		std::function< std::vector< matrix_type>(const matrix_type&, const matrix_type&)> za_to_dadW_output; // the tensor derivative of a wrt to weights in output layer

																											 /**
																											 This function initializes the functions when SOFT_MAX and BUCKET are selected, only works if correct
																											 number of arguments are given and correct type
																											 @param _num_out the number of output nodes																											 
																											 */
		template<typename _bucket_list>
		typename std::enable_if< std::is_convertible<_bucket_list,
			std::vector<T>>::value >::type
			process_bins(_bucket_list&& _bins) {

			std::vector<T> cutoffs(std::forward<_bucket_list>(_bins));

			size_t num_out = cutoffs.size() + 1; // number of bins

			out = [num_out, cutoffs](const T& _in)->matrix_type {
				matrix_type ret(num_out, 1); // return matrix

					// count how many thresholds it exceeds
				size_t bin = std::count_if(std::begin(cutoffs), std::end(cutoffs), [_in](const T& cut)->bool {
					return cut < _in;
				});
				ret(bin, 0) = 1;
				return ret;
			};
		}

		/* never used */
		template<typename _bucket_list>
		typename std::enable_if< !(std::is_convertible<_bucket_list,
			std::vector<T>>::value ) >::type
			process_bins(_bucket_list&& _bins) {
			throw std::logic_error("Incorrect bucketing arguments");
		}

		/* never used */
		template<typename ... Types>
		typename std::enable_if< !(sizeof...(Types) == 1) >::type
			process_bins(Types&&... vals) {
			throw std::logic_error("Incorrect number of bucketing arguments");
		}

		/* never used */
		template<typename ... Types>
		typename std::enable_if< !(sizeof...(Types) == 0) >::type
			finish_initialization(Types&&... vals) {
			throw std::logic_error("Too many arguments given");
		}

		/**
		Function should do nothing here when no arguments are given
		*/
		void finish_initialization() {
			
			out = [](const T& _in)->matrix_type { // single element matrix
				return { { _in } };
			};

		}




	public:

		/**
		constructor accepts the basic policies plus arbitrary list of arguments used for the policies
		@tparam Types the data types used in policy: must be consistent in type and quantity to set the appropriate setup/binning properties
		@param setup the setup chosen for layers
		@param binning the way output data are managed
		@param num_out number of output nodes
		@param _rate the learning rate
		@param _decay rate of decay for learning rate
		@param _momentum the momentum of previous term to keep
		@param values the values used in the policies
		*/
		template<typename... Types>
		network_policies(const NETWORK_COST _cost, const NETWORK_BINNING _binning,
			const NETWORK_HIDDEN_ACTIVATIONS _hidden_activations,
			const NETWORK_OUTPUT_ACTIVATIONS _output_activations, const size_t num_out, const T& _rate,
			const T& _decay, const T& _momentum,
			Types&& ... values);

		/**
		given an input of type T, gives the output vector
		@param _in the input
		@return the output data vector
		*/
		matrix_type get_output(const T& _in) const {
			return out(_in);
		}

		
		/**
		given a vector describing the error in each component, returns a possibly scaled vector indicative of the true error
		@param _in the input
		@return the error vector
		*/
		T get_error(const matrix_type& _y, const matrix_type& _a) const {
			assert_column(_y);
			assert_column(_a);
			return error(_y, _a);
		}

		/**
		computes the derivative of the error vector components with respect to activations
		@param _in the input
		@return the error vector derivative with respect to activations
		*/
		matrix_type dCda(const matrix_type& _y, const matrix_type& _a) const {
			assert_column(_y);
			assert_column(_a);
			return error_times_prime(_y, _a);
		}

		/**
		computes the transform of z hidden values
		@param _in the input
		@return the activations
		*/
		matrix_type transform_hidden(const matrix_type& _in) const {
			assert_column(_in);
			return z_to_a_hidden(_in);
		}

		/**
		computes the derivative of the activations with respect to the zvalues in the hidden layers
		@param _in the input
		@return the derivatives, a matrix, of a with respect to z at a fixed layer
		*/
		matrix_type dadz_hidden(const matrix_type& _in) const {
			assert_column(_in);
			return z_to_dadz_hidden(_in);
		}

		/**
		computes derivative of one layer of activations with rspect to the prior in the hidden layers
		@param _z the z-values of a given lavel
		@param _W the weights at that level
		@return da^ell/da(ell-1)
		*/
		matrix_type dada_hidden(const matrix_type& _z, const matrix_type& _W) const {

			assert_column(_z);
			return zw_to_dada_hidden(_z, _W);
		}

		/**
		computes derivative of one layer of activations with rspect to their biases in the hidden layers
		@param _z the z-values of a given lavel
		@return da/db
		*/
		matrix_type dadb_hidden(const matrix_type& _z) const {
			assert_column(_z);
			return z_to_dadb_hidden(_z);
		}


		/**
		computes derivative of one layer of activations with respect to their weights in the hidden layers
		@param _z the z-values of a layer
		@param _a the activations of the prior layer
		@return a tensor whose ith component is a matrix: the rate of change of the ith activtion with respect to each weight
		*/
		std::vector< matrix_type > dadW_hidden(const matrix_type& _z, const matrix_type& _a) const {
			assert_column(_z);
			assert_column(_a);
			return za_to_dadW_hidden(_z, _a);
		}

		/**
		computes the transform of z output values
		@param _in the input
		@return the activations
		*/
		matrix_type transform_output(const matrix_type& _in) const {
			assert_column(_in);
			return z_to_a_output(_in);
		}

		/**
		computes the derivative of the activations with respect to the zvalues in the output layer
		@param _in the input
		@return the derivatives, a matrix, of a with respect to z at a fixed layer
		*/
		matrix_type dadz_output(const matrix_type& _in) const {
			assert_column(_in);
			return z_to_dadz_output(_in);
		}

		/**
		computes derivative of one layer of activations with rspect to the prior in the output layer
		@param _z the z-values of a given lavel
		@param _W the weights at that level
		@return da^ell/da(ell-1)
		*/
		matrix_type dada_output(const matrix_type& _z, const matrix_type& _W) const {
			assert_column(_z);
			return zw_to_dada_output(_z, _W);
		}

		/**
		computes derivative of one layer of activations with rspect to their biases in the output layer
		@param _z the z-values of a given lavel
		@return da/db
		*/
		matrix_type dadb_output(const matrix_type& _z) const {
			assert_column(_z);
			return z_to_dadb_output(_z);
		}

		/**
		computes derivative of one layer of activations with respect to their weights in the hidden layers
		@param _z the z-values of a layer
		@param _a the activations of the prior layer
		@return a tensor whose ith component is a matrix: the rate of change of the ith activtion with respect to each weight
		*/
		std::vector< matrix_type > dadW_output(const matrix_type& _z, const matrix_type& _a) const {
			assert_column(_z);
			assert_column(_a);
			return za_to_dadW_output(_z, _a);
		}

		/**
		returns the norm scaling
		@return the prefactor in the norm (not with the sample size)
		*/
		const T& get_norm() const {
			return norm;
		}

		/**
		returns the rate to (possibly) be modified
		@return the learning rate
		*/
		T& get_rate() {
			return rate;
		}

		/**
		returns the decay
		@return the geometric decrease in learning rate between epochs
		*/
		const T& get_decay() const {
			return decay;
		}

		/**
		returns the momentum
		@return the amount of weighting to give to previous descent direction in new direction
		*/
		const T& get_momentum() const {
			return momentum;
		}

	};


	/**
	The neural network class stores layers and derivatives and costs
	@tparam T the type of floating point used by the network_manager
	*/
	template<typename T>
	class network_manager<T>::neural_network {
	private:
		const network_manager* manager; // its network manager

		static std::default_random_engine default_rand; // a default random generator
		static std::uniform_real_distribution<T> unif_real; // a random generator to produce uniform randoms from 0 to 1

		std::vector< in_out<T> > training_data; // the training data, subset of all data given
		std::set< size_t > indices_used; // indices used from the training data, based on the sampling

		std::deque< layer<T> > layers; // all the layers of the neural network: from the first layer to receive inputs through the final layer yielding the network's prediction

		std::deque< matrix_type > dCdas; // derivative of cost with respect to activations at the output

		std::deque< matrix_type > dCostdBiases; // derivatives with respect to biases
		std::deque< matrix_type > dCostdWeights; // derivatives with respect to weight matrices

		std::deque< matrix_type > stepBiases; // step taken for biases
		std::deque< matrix_type > stepdWeights; // step taken for weights

		std::deque< matrix_type > dCostdBiasesSamples; // collection of derivative of cost with respect to biases for each indvidual sample
		std::deque< matrix_type > dCostdWeightsSamples; // collection of derivative of cost with respect to weights for each indvidual sample

		std::vector< std::deque< matrix_type > > zvalues; // the pure z-values, un-transformed by the layers transform function, for each sample
		std::vector< std::deque< matrix_type > > avalues; // the activations for each sample

		T cost; // the total cost

	public:
		/**
		The neural network constructor
		@param _mgr its network manager
		*/
		neural_network(const network_manager* _mgr) : manager(_mgr), cost(std::numeric_limits<T>::max()) {} // give it an owner, let error begin at max possible

																											/**
																											function inserts a layer to the neural network
																											@param _nodes nodes of the given layer
																											@param _left_nodes nodes to its left (layer closer to input)
																											*/
		void insert_layer(const size_t _nodes, const size_t _left_nodes) {
			layers.emplace_front(_left_nodes, _nodes); // add a new layer of prescribed size to front
			dCostdBiases.emplace_front(_nodes, 1); // add all 0's vector for bias derivatives
			dCostdWeights.emplace_front(_nodes, _left_nodes); // add all 0's matrix for weights derivatives  

															  // and to hold past history
			stepBiases.emplace_front(_nodes, 1); // all 0's
			stepdWeights.emplace_front(_nodes, _left_nodes); // all 0's
		}

		/**
		function inserts a layer to the neural network
		@tparam call a callable class used to transfer between levels
		@param _nodes nodes of the given layer
		@param _left_nodes nodes to its left
		@param _transfer a transfer function
		*/
		template<typename call>
		void insert_layer(const size_t _nodes, const size_t _left_nodes, const call& _transfer) {
			layers.emplace_front(_left_nodes, _nodes, _transfer); // add a new layer of prescribed size to front
			dCostdBiases.emplace_front(_nodes, 1); // add all 0's vector for bias derivatives
			dCostdWeights.emplace_front(_nodes, _left_nodes); // add all 0's matrix for weights derivatives     
		}

		/**
		adds training data
		@param begin_data the training data beginning, some position in a vector of in_out
		@param end_data past the end of the training data, just past the end of the data range, a position in a vector of in_out
		*/
		void add_training_data(const typename std::vector< in_out<T> >::iterator begin_data,
			const typename std::vector< in_out<T> >::iterator end_data) {
			training_data.insert(std::end(training_data), begin_data, end_data); // just include all of it
		}

		/**
		gives the total cost
		@return the average cost
		*/
		const T& average_cost() const { return cost; }

		/**
		get a random number 0 to 1, useful for seeding and other utilities
		@return a random number from 0 to 1
		*/
		T static get_random() { return unif_real(default_rand); }

		/**
		randomly seeds weights and biases
		*/
		void random_seed();

		/**
		selects a random subset of indices to use for the stochastic gradient
		@param _sample the number of samples to use
		*/
		void choose_sample(const size_t _sample);

		/**
		computes the gradients from the sampled data
		*/
		void compute_gradient();

		/**
		steps in the negative gradient direction, also updating the cost!
		@param _rate the learning rate
		*/
		void step(const T& _rate);


		/**
		computes the total average cost associated with the network
		@return the total cost
		*/
		const T& get_cost() const { return cost; }

		/**
		learn from the learning rate and calculated gradient
		@param _rate the rate of learning
		@param _sample the sample size to use
		*/
		void learn(const T& _rate, const size_t _sample) {
			choose_sample(_sample); // select a sample
			compute_gradient(); // and find the stochastic gradient
			step(_rate); // then step forward to decrease the average cost, also updating the average cost			

		}

		/**
		computes prediction of given input
		@param _val the input value
		@return the output
		*/
		auto predict(matrix_type _val) const {

			const size_t output_layer_index = layers.size() - 1;

			for (size_t i = 0; i < output_layer_index; ++i) { // move through each hidden layer
				_val = manager->policies.transform_hidden(layers[i].linear(_val)); // linear transform plus nonlinear transformation 
			}
			_val = manager->policies.transform_output(layers[output_layer_index].linear(_val)); // and the last

			return _val;
		}

		/**
		saves the data to a file
		*/
		void save() const {

			std::ofstream out(manager->parameter_out_file); // open file to save to

			for (size_t i = 0, num_layers = layers.size(); i < num_layers; ++i) { // go through every layer

				out << "Biases " << i << ":" << '\n' << layers[i].get_biases() << '\n'; // print the biases
				out << "Weights " << i << ":" << '\n' << layers[i].get_weights() << '\n'; // and weights
			}

			out.close(); //free file

			std::cout << "\nWriting complete";
		}
	};

	/* DEFINITIONS */

	// use time to seed default random, and specify uniform to take values 0 to 1

	template<typename T>
	std::default_random_engine network_manager<T>::neural_network::default_rand
		= std::default_random_engine(std::time(nullptr));

	template<typename T>
	std::uniform_real_distribution<T> network_manager<T>::neural_network::unif_real
		= std::uniform_real_distribution<T>(0, 1);

	// how seed random

	template<typename T>
	void network_manager<T>::neural_network::random_seed() {

		for (auto itr = layers.rbegin(), before_begin = layers.rend(); itr != before_begin; ++itr) { // go from end back
			for (size_t i = 0, biases_size = itr->biases_size(); i < biases_size; ++i) { // for each bias index			
				itr->operator()(i) = get_random(); // assign it a random number 0 to 1
			}
			for (size_t i = 0, weights_rows = itr->weights_size().first; i < weights_rows; ++i) { // for each weight row
				for (size_t j = 0, weights_cols = itr->weights_size().second; j < weights_cols; ++j) { // and col
					itr->operator()(i, j) = get_random(); // assign the element a random number 0 to 1
				}
			}
		}


	}

	// sample selection

	template<typename T>
	void network_manager<T>::neural_network::choose_sample(const size_t sample) {

		indices_used.clear(); // set to store sample indices starts empty

		while (indices_used.size() < sample) { // while not enough in the sample
			indices_used.insert(min_size(unif_real(default_rand) * training_data.size(), training_data.size() - 1)); // insert in range 0 to size-1 uniquely
		}

	}

	// stepping forward after derivatives found

	template<typename T>
	void network_manager<T>::neural_network::step(const T& _rate) {

		for (size_t i = 0; i < layers.size(); ++i) { // go over every layer
													 // and step weights and biases in negative gradient direction at learning rate
			stepBiases[i] = manager->policies.get_momentum()*stepBiases[i] - dCostdBiases[i] * _rate;
			stepdWeights[i] = manager->policies.get_momentum()*stepdWeights[i] - dCostdWeights[i] * _rate;
		}

		for (size_t i = 0; i < layers.size(); ++i) { // go over every layer
			layers[i].add_biases(stepBiases[i]); // and step weights and biases in negative gradient direction at learning rate
			layers[i].add_weights(stepdWeights[i]);
		}

		cost = 0; // start at 0 cost

		for (auto i : indices_used) { // over the data set used
			auto y = training_data[i].output; // store the correct value
			auto a = predict(training_data[i].input); // find the prediction

			cost += manager->policies.get_error(y, a);   // increase error
		}

		cost /= (manager->policies.get_norm() * indices_used.size()); // and average

	}

	// computing derivatives

	template<typename T>
	void network_manager<T>::neural_network::compute_gradient() {

		for (size_t i = 0, num_layers = layers.size(); i < num_layers; ++i) { // for each layer, reset its derivatives
			dCostdBiases[i] *= 0;
			dCostdWeights[i] *= 0;
		}

		// both should have as many rows as there are sample paths, each path either being the number of layers or that plus 1 in the case of avalues since avalues initially are the input nodes
		avalues = std::vector< std::deque< matrix_type > >(indices_used.size(), std::deque< matrix_type >(layers.size() + 1));
		zvalues = std::vector< std::deque< matrix_type > >(indices_used.size(), std::deque< matrix_type >(layers.size()));

		// for a given sample, we have the derivatives at each set of biases and layers
		dCostdBiasesSamples = std::deque< matrix_type >(layers.size());
		dCostdWeightsSamples = std::deque< matrix_type >(layers.size());

		auto used_itr = indices_used.begin(); // start at first index used

		const size_t num_indices_used = indices_used.size(); // how many indices were select in the batch
		const size_t num_layers = layers.size();
		const size_t output_layer_index = num_layers - 1;

		for (size_t i = 0; i < num_indices_used; ++i) { // for each sample, set the initial activations
			avalues[i][0] = training_data[*used_itr++].input; // use the given index by dereferencing the iterator and incrementing it   
		}

		for (size_t i = 0; i < num_indices_used; ++i) { // for each path found by using a training index
			for (size_t j = 0; j < num_layers; ++j) { // for each layer

				if (j == output_layer_index) { // output layer
					zvalues[i][j] = layers[j].linear(avalues[i][j]); // the z is the linear map of the activations
					avalues[i][j + 1] = manager->policies.transform_output(zvalues[i][j]); // the activation is the layer's transform of the z
				}

				else { // hidden layer
					zvalues[i][j] = layers[j].linear(avalues[i][j]); // the z is the linear map of the activations
					avalues[i][j + 1] = manager->policies.transform_hidden(zvalues[i][j]); // the activation is the layer's transform of the z

				}

			}
		}

		size_t sample_index = 0; // the sample we are using

		for (auto i : indices_used) { // for each index used

			dCdas = std::deque< matrix_type >(indices_used.size(),
				matrix_type(training_data[0].output.size(1), training_data[0].output.size(2))); // start it off at all 0's

																								// first loop here computes the dCdas for each layer from the final to the first, back propagation

			for (size_t j = output_layer_index; j != static_cast<size_t>(-1); --j) { // go from end to start

				if (j == output_layer_index) { // if at the end, special case
					auto y = training_data[i].output; // the correct value
					auto a = avalues[sample_index][num_layers]; // predicted
					dCdas[j] = manager->policies.dCda(y, a).T() / (manager->policies.get_norm() * indices_used.size());
				}
				else {  // then somewhere in the middle of the chain
					dCdas[j] = dCdas[j + 1] * manager->policies.dada_hidden(zvalues[sample_index][j + 1], layers[j + 1].get_weights()); // make the layer derivative and multiply it by the rest on the left         
				}
			}


			for (size_t j = 0; j <= output_layer_index; ++j) { // now we compute the bias and weight derivatives for each layer

				const auto& dCda = dCdas[j]; // store the value dCda

				if (j == output_layer_index) { // if it's the output layer

					auto dadb = manager->policies.dadb_output(zvalues[sample_index][j]); // a matrix whose (row,col) entry is rate of change of activation row with respect to b-value col
					auto dadW = manager->policies.dadW_output(zvalues[sample_index][j], avalues[sample_index][j]);

					dCostdBiasesSamples[j] = (dCda * dadb).T();
					dCostdWeightsSamples[j] = 0 * layers[j].get_weights(); // start as 0's matrix, ij position signifies derivative of cost with respect to weight ij

					for (size_t a_index = 0, dCdasize2 = dCda.size(2); a_index < dCdasize2; ++a_index) { // for each rate of change of cost with respect to given activation
						dCostdWeightsSamples[j] += dCda(0, a_index)*dadW[a_index]; // just adding matrices
					}

					dCostdBiases[j] += dCostdBiasesSamples[j]; // add to cumulative total cost derivatives
					dCostdWeights[j] += dCostdWeightsSamples[j];

				}

				else { // then a hidden layer

					auto dadb = manager->policies.dadb_hidden(zvalues[sample_index][j]); // a matrix whose (row,col) entry is rate of change of activation row with respect to b-value col

																						 // tensor with indices ijk, say, where entry is derivative of activation i with respect to weight jk
					auto dadW = manager->policies.dadW_hidden(zvalues[sample_index][j], avalues[sample_index][j]);

					dCostdBiasesSamples[j] = (dCda * dadb).T();
					dCostdWeightsSamples[j] = 0 * layers[j].get_weights(); // start as 0's matrix, ij position signifies derivative of cost with respect to weight ij

					for (size_t a_index = 0, dCdasize2 = dCda.size(2); a_index < dCdasize2; ++a_index) { // for each rate of change of cost with respect to given activation
						dCostdWeightsSamples[j] += dCda(0, a_index)*dadW[a_index]; // just adding matrices
					}

					dCostdBiases[j] += dCostdBiasesSamples[j]; // add to cumulative total cost derivatives .......
					dCostdWeights[j] += dCostdWeightsSamples[j];
				}
			}

			++sample_index; // go to next sample for a's and z's
		}

	}

	// reading in the data file

	template<typename T>
	void network_manager<T>::read_data(const std::string& _data_file,
		const size_t _input_size, const size_t _output_size) {

		std::ifstream in_data(_data_file); // open the stream to read
		check_stream(in_data); // make sure that file is available!		

		while (!in_data.eof()) { // while more data in the file
			matrix_type input(_input_size, 1); // make matrix for the inputs

			for (size_t i = 0; i < _input_size; ++i) {
				in_data >> input(i, 0); // read in each value
			}

			T last_value{}; // value initialize last_value and then hopefully set it
			in_data >> last_value;

			if (in_data.good()) { // if stream still happy

				auto output = policies.get_output(last_value); // use policies to format	

				all_data.emplace_back(input, output); // add the piece of data
			}

		}



		in_data.close(); // free the resource

						 // randomly shuffle
		for (size_t i = 0, total_size = all_data.size(); i < total_size; ++i) { // go through each element and give chance to swap it with another
			size_t rand_index = min_size(the_network.get_random() * all_data.size(), all_data.size() - 1); // pick random from 0 to size-1
			std::swap(all_data[i], all_data[rand_index]); // swap two elements at random
		}

		size_t end_training = static_cast<size_t>(fraction * all_data.size()); // where the training indices end

		the_network.add_training_data(std::begin(all_data), std::begin(all_data) + end_training); // add stuff for training

	}

	template<typename T>
	void network_manager<T>::read_nodes(const std::string& _node_file) {

		std::ifstream in_node(_node_file); // open file to read number of nodes at each level

		check_stream(in_node); // ensure connection made

		std::vector<size_t> num_nodes;

		size_t nodes_in_layer = std::numeric_limits<size_t>::max();

		while (in_node >> nodes_in_layer) { // while still more to read
			num_nodes.push_back(nodes_in_layer); // and include it in the list
		}

		in_node.close(); // free resource

						 // now we add a bunch of layers: there must be at least 2 entries in the vector

		for (size_t i = num_nodes.size() - 1; i > 0; --i) { // moving from right to left      
			the_network.insert_layer(num_nodes[i], num_nodes[i - 1]); // give current nodes and nodes left
		}

	}

	// constructor of network_manager

	template<typename T>
	template<typename ... Types>
	network_manager<T>::network_manager(const size_t input_size, const size_t output_size, std::string _data_file,
		std::string _node_file, std::string _parameter_out_file, std::string _testing_out_file,
		const T& _rate, const T& _decay, const T& _momentum, const T& _fraction, const NETWORK_COST _cost,
		const NETWORK_BINNING _binning, const NETWORK_HIDDEN_ACTIVATIONS _hidden_activations,
		const NETWORK_OUTPUT_ACTIVATIONS _output_activations,
		Types&&... values) : parameter_out_file(std::move(_parameter_out_file)),
		testing_out_file(std::move(_testing_out_file)),
		the_network(this),
		policies(_cost, _binning, _hidden_activations, _output_activations,
			output_size, _rate, _decay, _momentum, std::forward<Types>(values)...), fraction(_fraction) {

		read_data(_data_file, input_size, output_size); // read in all the precious data

		read_nodes(_node_file);  // and determine the node arrangement         

		the_network.random_seed(); // randomly seed for gradient descent

		display_info(); // show network information
	}

	// constructor of network_policies

	template<typename T>
	template<typename... Types>
	network_manager<T>::network_policies::network_policies(const NETWORK_COST _cost, const NETWORK_BINNING _binning,
		const NETWORK_HIDDEN_ACTIVATIONS _hidden_activations,
		const NETWORK_OUTPUT_ACTIVATIONS _output_activations, const size_t num_out,
		const T& _rate, const T& _decay, const T& _momentum,
		Types&& ... values) : rate(_rate), decay(_decay), momentum(_momentum), out{}, thresh{}, error{}, error_times_prime{},
		z_to_a_hidden{}, z_to_dadz_hidden{}, zw_to_dada_hidden{}, z_to_dadb_hidden{}, za_to_dadW_hidden{},
		z_to_a_output{}, z_to_dadz_output{}, zw_to_dada_output{}, z_to_dadb_output{}, za_to_dadW_output{},
		norm(std::numeric_limits<T>::max()) {

		if (_hidden_activations == NETWORK_HIDDEN_ACTIVATIONS::IDENTITY) { // do identity
			z_to_a_hidden = identity<T>::transform;
			z_to_dadz_hidden = identity<T>::dadz;
			zw_to_dada_hidden = identity<T>::dada;
			z_to_dadb_hidden = identity<T>::dadb;
			za_to_dadW_hidden = identity<T>::dadW;
		}
		else if (_hidden_activations == NETWORK_HIDDEN_ACTIVATIONS::LOG) { // do log
			z_to_a_hidden = slow_log<T>::transform;
			z_to_dadz_hidden = slow_log<T>::dadz;
			zw_to_dada_hidden = slow_log<T>::dada;
			z_to_dadb_hidden = slow_log<T>::dadb;
			za_to_dadW_hidden = slow_log<T>::dadW;
		}
		else if (_hidden_activations == NETWORK_HIDDEN_ACTIVATIONS::RELU) { // do relu
			z_to_a_hidden = relu<T>::transform;
			z_to_dadz_hidden = relu<T>::dadz;
			zw_to_dada_hidden = relu<T>::dada;
			z_to_dadb_hidden = relu<T>::dadb;
			za_to_dadW_hidden = relu<T>::dadW;
		}
		else if (_hidden_activations == NETWORK_HIDDEN_ACTIVATIONS::SOFT) { // do soft_max
			z_to_a_hidden = soft_max<T>::transform;
			z_to_dadz_hidden = soft_max<T>::dadz;
			zw_to_dada_hidden = soft_max<T>::dada;
			z_to_dadb_hidden = soft_max<T>::dadb;
			za_to_dadW_hidden = soft_max<T>::dadW;
		}
		else { // shouldn't get here...
			throw std::logic_error("Bad Hidden Activation Branch");
		}

		if (_output_activations == NETWORK_OUTPUT_ACTIVATIONS::IDENTITY) { // do identity
			z_to_a_output = identity<T>::transform;
			z_to_dadz_output = identity<T>::dadz;
			zw_to_dada_output = identity<T>::dada;
			z_to_dadb_output = identity<T>::dadb;
			za_to_dadW_output = identity<T>::dadW;
		}
		else if (_output_activations == NETWORK_OUTPUT_ACTIVATIONS::LOG) { // do log
			z_to_a_output = slow_log<T>::transform;
			z_to_dadz_output = slow_log<T>::dadz;
			zw_to_dada_output = slow_log<T>::dada;
			z_to_dadb_output = slow_log<T>::dadb;
			za_to_dadW_output = slow_log<T>::dadW;
		}
		else if (_output_activations == NETWORK_OUTPUT_ACTIVATIONS::RELU) { // do relu
			z_to_a_output = relu<T>::transform;
			z_to_dadz_output = relu<T>::dadz;
			zw_to_dada_output = relu<T>::dada;
			z_to_dadb_output = relu<T>::dadb;
			za_to_dadW_output = relu<T>::dadW;
		}
		else if (_output_activations == NETWORK_OUTPUT_ACTIVATIONS::SOFT) { // do soft_max
			z_to_a_output = soft_max<T>::transform;
			z_to_dadz_output = soft_max<T>::dadz;
			zw_to_dada_output = soft_max<T>::dada;
			z_to_dadb_output = soft_max<T>::dadb;
			za_to_dadW_output = soft_max<T>::dadW;
		}
		else if (_output_activations == NETWORK_OUTPUT_ACTIVATIONS::X_ABS_X) { // do soft_max
			z_to_a_output = x_abs_x<T>::transform;
			z_to_dadz_output = x_abs_x<T>::dadz;
			zw_to_dada_output = x_abs_x<T>::dada;
			z_to_dadb_output = x_abs_x<T>::dadb;
			za_to_dadW_output = x_abs_x<T>::dadW;
		}
		else { // shouldn't get here...
			throw std::logic_error("Bad Output Activation Branch");
		}

		if (_cost == NETWORK_COST::CROSS_ENTROPY) { // if cross entropy cost - only suitable for multiple output nodes
			norm = 1;
			error = log_cost<T>::cost;
			error_times_prime = log_cost<T>::dCda;
		}
		else if (_cost == NETWORK_COST::L2) { // classic quadratic
			norm = 2;
			error = quadratic_cost<T>::cost;
			error_times_prime = quadratic_cost<T>::dCda;
		}
		else if (_cost == NETWORK_COST::L1) { // can do L1 as sum of abs values
			norm = 1;
			error = L1_cost<T>::cost;
			error_times_prime = L1_cost<T>::dCda;
		}
		else { // should not apply
			throw std::logic_error("Bad Cost");
		}

		// for a softmax output activation with a bucket
		if (_binning == NETWORK_BINNING::BUCKET) {
			process_bins(std::forward<Types>(values)...);
		}
		else { // in this case the parameter pack better be empty
			finish_initialization(std::forward<Types>(values)...);
		}

	}

}

#endif