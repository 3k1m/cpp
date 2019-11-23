/**
@file kmeans.h
@author Mike Lindstrom
@version 1
@date November 2019

@brief the kmeans algorithm is an unspervised learning algorithm to place points
into groups called clusters
*/

#ifndef _BASIC_MATH__KMEANS_
#define _BASIC_MATH__KMEANS_

#include<vector>
#include<cmath>
#include<numeric>
#include<stdexcept>

#include "ArrayVector.h"

#include<cstdlib>


namespace basic_math {

	/**
	@class kmeans does a kmeans clustering algorithm on points
	@tparam k the number of clusters sought
	@tparam N the dimension of the points being clustered
	@tparam precision the floating point precision sought
	*/
	template<size_t k, size_t N, typename precision = double>
	class kmeans {
	public:

		// useful typedef for points we use
		using point_type = array_vector<N, precision>;

	private:

		struct point;
		
		/**
		@struct cluster represents a cluster.
		A cluster has a centroid and an id
		*/
		struct cluster {
			point_type centroid;
			std::vector<point*> points;
			size_t id;
		};

		/**
		@struct point represents a point to be clustered.
		A point has a location and a cluster it belongs to
		*/
		struct point {
			const point_type x;
			cluster* owner;
			/**
			constructor for point, assigns location and gives no owner
			@param _x its location
			*/
			point(const point_type& _x) : x(_x), owner(nullptr) {}
		};
				
		cluster clusters[k]; // store an array of clusters
		std::vector<point> points; // and vector of points since we don't know how many points there will be
		bool valid_for_printing; // whether it's okay to print the results
		
		/**
		Function computes the Euclidean distance between two points
		@param x a first point
		@param y a second point
		@return the square root of the sum of squared differences of the components
		*/
		precision dist(const point_type& x, const point_type& y) const {
			auto diff = x - y;
			return std::sqrt(std::accumulate(std::begin(diff), std::end(diff), precision{},
				[](precision L, const precision& R)->precision {
				return L += R*R;
			}));
		}

		/**
		This function assigns each point to a cluster in an
		approximately uniform way initially
		*/
		void initial_assign_clusters() {
			size_t count = 0;
			for (auto& p : points) { // assign each point to a cluster, equally distributed
				p.owner = &clusters[count % k];
				++count;
			}
		}

		/**
		This function assigns each point to a cluster based on
		its proximity to their centroids
		*/
		void assign_clusters() {

			for (auto& c : clusters) { // reset all points in a cluster
				c.points.clear();
			}

			for (auto& p : points) { // for each point
				size_t best = 0; // current best index
				double min_dist = std::numeric_limits<double>::max(); // best distance

				for (size_t i = 0; i < k; ++i) { // look at every cluster
					if (dist(clusters[i].centroid, p.x) < min_dist) { // if point-cluster distance is smaller
						best = i; // update best
						min_dist = dist(clusters[i].centroid, p.x);
					}
				}
				p.owner = &clusters[best]; // set the owner
				clusters[best].points.push_back(&p); // add point as part of the cluster
			}

		}

		/**
		This function computes the centroids of each cluster given
		the points that belong to it
		*/
		void set_centroids() {
			size_t in_clusters[k]{}; // start the counts at 0

			for (auto& c : clusters) { // set all centroids to 0
				c.centroid = point_type{};
			}

			for (const auto& p : points) { // add to each point's cluster and increase point count per cluster
				p.owner->centroid += p.x;
				++in_clusters[p.owner->id];
			}

			for (auto& c : clusters) { // compute the centroid: divide by points in cluster
				c.centroid /= in_clusters[c.id];
			}
			
		}

	public:
		/**
		Constructor for kmeans: places each
		cluster centroid at the origin initially and
		gives the clusters indices 0 to k-1
		*/
		kmeans() : valid_for_printing(false) {
			for (size_t i = 0; i < k; ++i) {
				clusters[i] = cluster{ point_type{},{}, i };
			}
		}

		/**
		Function adds a point to the collection of points
		@param p the point
		*/
		void add_point(point_type p) {
			points.emplace_back(std::move(p));
			valid_for_printing = false; // added a point so need to recluster
		}

		/**
		Performs the clustering a given number of iterations
		@param num_its the number of iterations to run
		*/
		void do_clustering(int num_its) {
			initial_assign_clusters();

			for (int i = 0; i < num_its; ++i) { // do num_its times

				// algorithm entails computing cluster centroids then
				// shifting point ownership around, repeatedly

				set_centroids();
				assign_clusters();
			}

			valid_for_printing = true; // safe to print
		}

		/**
		This function prints all clusters with their centroids and
		lists the points that belong to each cluster
		*/
		void print_clusters() const {

			if (valid_for_printing) { // only do stats if clustering has been done

				for (const auto& cluster : clusters) { // go cluster by cluster

					if (cluster.points.size() > 0) { // cluster has some points

						// Give its statistics
						std::cout << "Cluster id " << cluster.id << " with centroid at " << cluster.centroid << "\n";

						for (const auto& p : cluster.points) { // print every point in the cluster
							std::cout << p->x << ' ';
						}
					}
					else { // no points in the cluster
						
						std::cout << "Cluster id " << cluster.id << " has no points.";
					}

					std::cout << '\n';
				}
			}
			else { // bad here, throw error
				throw std::logic_error("Clustering Has Not Been Done!");
			}
		}		

	};


}
#endif
