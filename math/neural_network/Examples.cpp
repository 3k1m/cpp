/**
@file Examples.cpp
@author Mike Lindstrom

@brief there are two examples to illustrate how the neural network works. It is NOT fast

@details there is a continuous prediction example using forest fire data and a discrete example using an
abridged part of the mnist data set

to test this, you need all of the files:
fire_data.txt
fire_nodes.txt
mnist.txt
mnist_nodes.txt

The fire data requires the citation below:

P. Cortez and A. Morais. A Data Mining Approach to Predict Forest Fires using Meteorological Data.
In J. Neves, M. F. Santos and J. Machado Eds., New Trends in Artificial Intelligence,
Proceedings of the 13th EPIA 2007 - Portuguese Conference on Artificial Intelligence, December,
Guimaraes, Portugal, pp. 512-523, 2007. APPIA, ISBN-13 978-989-95618-0-9.
Available at: http://www.dsi.uminho.pt/~pcortez/fires.pdf

The columns/info used were: FFMC	DMC	DC	ISI	temp	RH	wind	rain	area

In general, data should be normalized before being fed into the neural network. The last column should be
the ground truth. It seems the mnist is fine without being first normalized, at least here...

One winter break I thought it would be fun to write a neural network from scratch to help myself learn. This
was never designed to be super fast, just to get the job done.
*/

#include "Network.h"

#include<iostream>

int main() {
	// our many hyperparameters
	constexpr long double rate = 1.e-3; // the learning rate
	constexpr long double decay = 0.9995; // geometric rate that learning decays between epochs
	constexpr long double momentum = 0.8; // momentum term
	
	// network setup parameters
	constexpr long double fraction = 0.7; // fraction to train on
	constexpr size_t epochs = 1000; // number of epochs
	constexpr size_t batch_size = 40; // how many per mini-batch for stochastic gradient descent

	// some of the topology of our data sets
	constexpr size_t fire_in_nodes = 8; // input nodes for forest fire problem
	constexpr size_t fire_out_nodes = 1; // only one output for forest fire
	constexpr char* fire_data_file = "fire_data.txt"; // flat file of data, last column = output
	constexpr char* fire_node_file = "fire_nodes.txt"; // file that has node structure
	constexpr char* fire_param_file = "fire_params.txt"; // where to write the parameters
	constexpr char* fire_test_file = "fire_test.txt"; // where to give training/testing results

	constexpr size_t mnist_in_nodes = 784; // input nodes for mnist dataset
	constexpr size_t mnist_out_nodes = 10; // 10 digits to classify
	constexpr char* mnist_data_file = "mnist.txt"; // flat file of data, last column = output
	constexpr char* mnist_node_file = "mnist_nodes.txt"; // file that has node structure
	constexpr char* mnist_param_file = "mnist_params.txt"; // where to write the parameters
	constexpr char* mnist_test_file = "mnist_test.txt"; // where to give training/testing results
	// 0 < 0.5 < 1 < 1.5 < ... ensures numbers are placed in proper bucket
	std::vector<long double> cutoffs{ 0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5 };

	basic_network::network_manager<long double> mgr_fire(fire_in_nodes, fire_out_nodes, fire_data_file,
		fire_node_file, fire_param_file, fire_test_file,
		rate, decay, momentum, fraction,
		basic_network::NETWORK_COST::L2,
		basic_network::NETWORK_BINNING::SINGLE,
		basic_network::NETWORK_HIDDEN_ACTIVATIONS::RELU,
		basic_network::NETWORK_OUTPUT_ACTIVATIONS::IDENTITY);

	mgr_fire.run(epochs, batch_size);
	mgr_fire.test();

	basic_network::network_manager<long double> mgr_mnist(mnist_in_nodes, mnist_out_nodes, mnist_data_file,
		mnist_node_file, mnist_param_file, mnist_test_file,
		rate, decay, momentum, fraction,
		basic_network::NETWORK_COST::CROSS_ENTROPY,
		basic_network::NETWORK_BINNING::BUCKET,
		basic_network::NETWORK_HIDDEN_ACTIVATIONS::RELU,
		basic_network::NETWORK_OUTPUT_ACTIVATIONS::SOFT, cutoffs);

	mgr_mnist.run(epochs, batch_size);
	mgr_mnist.test();
	
	std::cin.get();

	return 0;

}
