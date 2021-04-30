/*!*******************************************************************
\headerfile   NeuralNetwork.h
\author       Kim Hyungseob
\par          email: hn02415 \@ gmail.com
\date         2021/04/13
\brief
			  Header file for NeuralNetwork class approximates x^cosx.
********************************************************************/
#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <vector>

#include "Neuron.h"

class NeuralNetwork
{
public:
	NeuralNetwork(int size);

	void Initialize();
	int GetResult(double* output);
	void GetData(double* x_data, double* y_data);

private:
	void ComputeOneStep();
	void UpdateNeuron();

	void InitializeNeurons();

private:
	std::vector<double> x_data;
	std::vector<double> y_data;
	std::vector<double> output;
	const int dataSize;

	Neuron layer[30];
	const double learningRate = 0.000005;

	int iteration = 0;
};

#endif // !NEURALNETWORK_H

