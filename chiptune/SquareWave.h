#include <vector>
#include <Generator.h>
#include <SineWave.h>
#include <Envelope.h>

using namespace stk;

class SquareWave :public stk::Generator
{
public:
    //! Default constructor.
    SquareWave(void)
    {
        sines_.resize(200);
    }

    //! Class destructor.
    ~SquareWave(void) = default;

    //! Clear output and reset time pointer to zero.
    void reset(void);

    void setSinusRate(StkFloat rate)
    {
        for (auto& sine : sines_)
            sine.setRate(rate);
    }

    void setEnvelopeRate(StkFloat rate)
    {
        envelope_.setRate(rate);
    }

    void setFrequency(StkFloat frequency)
    {
        for (auto i = 0; i < sines_.size(); i++)
            sines_[i].setFrequency((2 * i + 1) * frequency);
    }

    void addTime(StkFloat time)
    {
        for (auto& sine : sines_)
            sine.addTime(time);
    }

    void addPhase(StkFloat phase) {
        for (auto& sine : sines_)
            sine.addPhase(phase);
    }

    void addPhaseOffset(StkFloat phaseOffset) {
        for (auto& sine : sines_)
            sine.addPhaseOffset(phaseOffset);
    }

    //! Return the last computed output value.
    StkFloat lastOut(void) const { return lastFrame_[0]; }

    //! Set target = 1.
    void keyOn(void) { this->setTarget(1.0); }

    //! Set target = 0.
    void keyOff(void) { this->setTarget(0.0); }

    //! Set the \e rate based on a positive time duration (seconds).
    /*!
      The \e rate is calculated such that the envelope will ramp from
      a value of 0.0 to 1.0 in the specified time duration.
     */
    void setTime(StkFloat time) { envelope_.setTime(time); }

    //! Set the target value.
    void setTarget(StkFloat target) { envelope_.setTarget(target); }

    //! Set current and target values to \e value.
    void setValue(StkFloat value);

    //! Return the current envelope \e state (0 = at target, 1 otherwise).
    int getState(void) const { return envelope_.getState(); };

    //! Compute and return one output sample.
    StkFloat tick(void);

    //! Fill a channel of the StkFrames object with computed outputs.
    /*!
      The \c channel argument must be less than the number of
      channels in the StkFrames argument (the first channel is specified
      by 0).  However, range checking is only performed if _STK_DEBUG_
      is defined during compilation, in which case an out-of-range value
      will trigger an StkError exception.
    */
    StkFrames& tick(StkFrames& frames, unsigned int channel = 0) override;

protected:
    std::vector<SineWave> sines_;
    Envelope envelope_;
};

inline StkFloat SquareWave::tick()
{
    /*double tick = 0.0;
    for(auto i=0; i< sines_.size(); i++)
        tick += (sines_[i].tick()) / (2 * i + 1);
    return (4 / PI) * tick * envelope_.tick();*/
    return 0.5*(sines_[0].tick() < 0.5 ? 0 : 1) * envelope_.tick();
    //return (sines_[0].tick() < 0 ? 0 : 1) * envelope_.tick();
    //return sines_[0].tick() * envelope_.tick();
}

inline StkFrames& SquareWave::tick(StkFrames& frames, unsigned channel)
{
    throw std::exception("not implemented");
    return frames;
}
