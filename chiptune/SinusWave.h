#include<Generator.h>
#include<SineWave.h>
#include <Envelope.h>
using namespace stk;
class SinusWave :public stk::Generator
{
public:
    //! Default constructor.
    SinusWave(void) {}

    //! Class destructor.
    ~SinusWave(void)=default;

    //! Clear output and reset time pointer to zero.
    void reset(void);

    void setRate(StkFloat rate)
    {
        sine_.setRate(rate);
        envelope_.setRate(rate);
    }

    void setFrequency(StkFloat frequency) { sine_.setFrequency(frequency); }

    void addTime(StkFloat time) { sine_.addTime(time); }

    void addPhase(StkFloat phase) { sine_.addPhase(phase); }

    void addPhaseOffset(StkFloat phaseOffset) { sine_.addPhaseOffset(phaseOffset); }

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
    SineWave sine_;
    Envelope envelope_;
};

inline StkFloat SinusWave::tick()
{
    return sine_.tick() * envelope_.tick();
}

inline StkFrames& SinusWave::tick(StkFrames& frames, unsigned channel)
{
    throw std::exception("not implemented");
    return frames;
}
