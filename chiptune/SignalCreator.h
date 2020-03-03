#pragma once
#include <cmath>

float PI = 3.14159;

struct  sinus
{
    float A;
    float F;

    sinus(float A, float F) :A{ A }, F{ F }{}

    float operator()(float t) const
    {
        return (A / 2) * sin(2 * PI * F * t) + (A / 2);
    }
};