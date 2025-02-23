#include "random.h"

namespace rnd
{
    std::mt19937 rng;

    void Init()
    {
        rng.seed(std::random_device{}());
    }

    int Randint(int up)
    {
        std::uniform_int_distribution<> distr(0, up);
        return distr(rng);
    }

    int Randint(int bottom, int up)
    {
        std::uniform_int_distribution<> distr(bottom, up);
        return distr(rng);
    }

    float RandFloat(float min, float max)
    {
        std::uniform_real_distribution<float> distr(min, max);
        return distr(rng);
    }

    float RandFloat(float max)
    {
        std::uniform_real_distribution<float> distr(0, max);
        return distr(rng);
    }
}
