#pragma once

#include <random>
class Random {
public:
	Random(int min, int max) :
			gen(rd()), dis(min, max) {}

    int get() {
        return dis(gen);
    }

private:
	std::random_device rd;
	std::mt19937 gen;
	std::uniform_int_distribution<> dis;
};