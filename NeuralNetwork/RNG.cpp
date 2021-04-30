#include "RNG.h"

RNG::RNG()
	: mt((std::random_device())())
{
}

RNG* RNG::GetInstance()
{
	static RNG instance;

	return &instance;
}

int RNG::GetRandomInt(int min, int max)
{
	std::uniform_int_distribution<> dist(min, max);

	return dist(mt);
}

double RNG::GetRandomDouble(double min, double max)
{
	std::uniform_real_distribution<> dist(min, max);
	
	return dist(mt);
}