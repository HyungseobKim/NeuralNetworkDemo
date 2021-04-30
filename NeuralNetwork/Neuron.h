/*!*******************************************************************
\headerfile   Neuron.h
\author       Kim Hyungseob
\par          email: hn02415 \@ gmail.com
\date         2021/04/13
\brief
			  Header file for Neuron class having sigmoid function as 
			  activation function.
********************************************************************/
#ifndef NEURON_H
#define NEURON_H

class RNG;

class Neuron
{
public:
	Neuron();
	Neuron(double b);

	double Compute(double input) const;
	double ComputeDerivative(double input) const;

	void Update_a(double amount);
	void Update_b(double amount);
	void Update_w(double amount);

	double Weight() const;

private:
	double a;
	double b;
	double w;
};

#endif // !NEURON_H
