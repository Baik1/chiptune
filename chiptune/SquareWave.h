#pragma once

#include <Generator.h>
#include <SineWave.h>
#include <Envelope.h>

using namespace stk;

class SquareWave
{
    SineWave sine_;
    Envelope envelope_;

public:
    SquareWave(double frequency, double rate)
    {
        sine_.setFrequency(frequency);
        envelope_.setRate(rate);
    };

    //! Default constructor.
    SquareWave(void) = default;

    //! Class destructor.
    ~SquareWave(void) = default;

    //! Clear output and reset time pointer to zero.
    void reset(void)
    {
        sine_.reset();
    };

    void setRate(StkFloat rate)
    {
        envelope_.setRate(rate);
    }

    void setFrequency(StkFloat frequency)
    {
        sine_.setFrequency(frequency);
    }

    //! Set target = 1.
    void keyOn(void) { envelope_.setTarget(1.0); }

    //! Set target = 0.
    void keyOff(void) { envelope_.setTarget(0.0); }

    StkFloat tick(void)
    {
        return  0.5 * (sine_.tick() < 0.0 ? 0 : 1) * envelope_.tick();
    }
};
