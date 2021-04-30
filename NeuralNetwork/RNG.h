#ifndef RNG_H
#define RNG_H

#include <random>

class RNG
{
private:
	RNG();
	RNG(const RNG&);
	RNG& operator=(const RNG&);

public:
	static RNG* GetInstance();

	int GetRandomInt(int min, int max);
	double GetRandomDouble(double min, double max);
	

private:
	std::mt19937 mt;
};

#endif // !RNG_H