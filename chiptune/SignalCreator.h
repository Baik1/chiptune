#pragma once
#include <cmath>
#include "PianoUI.h"

const double PI = 2.0 * acos(0.0);

struct base_signal
{
    virtual ~base_signal() = default;
    virtual float operator()(float t) const { return 0; };
    virtual base_signal& operator=(const base_signal& other) = default;
};

struct  sinus :base_signal
{
    float A;
    float F;

    sinus(float A, float F) :A{ A }, F{ F }{}

    virtual sinus& operator=(const sinus& other)
    {
        A = other.A;
        F = other.F;
    }
    float operator()(float t) const override
    {
        return (A / 2) * sin(2 * PI * F * t) + (A / 2);
    }
};