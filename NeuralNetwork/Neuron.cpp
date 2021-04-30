#include <cmath>

#include "Neuron.h"

#include "RNG.h"

Neuron::Neuron()
{
	a = 1.0;
	b = RNG::GetInstance()->GetRandomDouble(-1.0, 1.0);
	w = RNG::GetInstance()->GetRandomDouble(-1.0, 1.0);
}

Neuron::Neuron(double b)
{
	a = 1.0;
	this->b = b;
	w = RNG::GetInstance()->GetRandomDouble(-1.0, 1.0);
}

double Neuron::Compute(double input) const
{
	input = a * input + b;
	return 1 / (1 + exp(-input));
}

double Neuron::ComputeDerivative(double input) const
{
	input = a * input + b;
	const double e_to_the_negative_x = exp(-input);
	return (1 / ((1 + e_to_the_negative_x) * (1 + e_to_the_negative_x))) * e_to_the_negative_x;
}

void Neuron::Update_a(double amount)
{
	a -= amount;
}

void Neuron::Update_b(double amount)
{
	b -= amount;
}

void Neuron::Update_w(double amount)
{
	w -= amount;
}

double Neuron::Weight() const
{
	return w;
}