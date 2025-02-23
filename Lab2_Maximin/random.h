#ifndef RANDOM_H
#define RANDOM_H

#include <random>

namespace rnd
{
    extern std::mt19937 rng;

    void Init();
    int Randint(int up);
    int Randint(int bottom, int up);
    float RandFloat(float min, float max);
    float RandFloat(float max);
}


#endif // RANDOM_H
