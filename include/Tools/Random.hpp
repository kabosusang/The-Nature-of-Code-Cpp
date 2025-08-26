#pragma once

#include <random>


class Random {
public:
	Random(double min, double max) :
			gen(rd()), dis(min, max) {}

    double get() {
        return dis(gen);
    }


private:
	std::random_device rd;
	std::mt19937 gen;
	std::uniform_real_distribution<> dis;
};


//正态分布
class NormalRandom{
public:
	NormalRandom(double min, double max) :
			gen(rd()), dis(min, max) {}

    double get() {
        return dis(gen);
    }


private:
	std::random_device rd;
	std::mt19937 gen;
	std::normal_distribution<> dis;
};


