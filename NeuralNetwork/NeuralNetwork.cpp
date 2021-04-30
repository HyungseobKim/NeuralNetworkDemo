#include <cmath>

#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(int size)
	: dataSize(size), x_data(std::vector<double>(dataSize)), y_data(std::vector<double>(dataSize))
{
	InitializeNeurons();

	for (int i = 0; i < dataSize; ++i)
		x_data.push_back(i);

	for (int i = 0; i < dataSize; ++i)
		y_data.push_back(i*i);

	output.resize(dataSize);
}

void NeuralNetwork::Initialize()
{
	iteration = 0;
	InitializeNeurons();
}

void NeuralNetwork::InitializeNeurons()
{
	for (int i = 0; i < 30; ++i)
		layer[i] = Neuron(i / 30.0);
}

void NeuralNetwork::GetData(double* x_data, double* y_data)
{
	for (int i = 0; i < dataSize; ++i)
		x_data[i] = (this->x_data)[i];

	for (int i = 0; i < dataSize; ++i)
		y_data[i] = (this->y_data)[i];
}

int NeuralNetwork::GetResult(double* output)
{
	// Not finished yet
	if (iteration < 10000)
	{
		++iteration;

		ComputeOneStep();
		UpdateNeuron();
	}

	for (int i = 0; i < dataSize; ++i)
		output[i] = (this->output)[i];

	return iteration;
}

void NeuralNetwork::ComputeOneStep()
{
	for (int i = 0; i < dataSize; ++i)
	{
		const double x = x_data[i];
		double y = 0.0;

		for (int j = 0; j < 30; ++j)
			y += layer[j].Compute(x) * layer[j].Weight();

		output[i] = y;
	}
}

void NeuralNetwork::UpdateNeuron()
{
	for (int i = 0; i < 30; ++i)
	{
		auto& neuron = layer[i];
		double dEdw = 0.0;
		double dEda = 0.0;
		double dEdb = 0.0;

		for (int j = 0; j < dataSize; ++j)
		{
			const double x = x_data[j];
			const double error = output[j] - y_data[j];
			dEdw += error * neuron.Compute(x);

			const double new_dEdb = error * neuron.Weight() * neuron.ComputeDerivative(x);
			dEda += new_dEdb * x;
			dEdb += new_dEdb;
		}

		neuron.Update_w(learningRate * dEdw);
		neuron.Update_a(learningRate * dEda);
		neuron.Update_b(learningRate * dEdb);
	}
}