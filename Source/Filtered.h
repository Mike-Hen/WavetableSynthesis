
#pragma once
class Filtered {
public:
	enum FilterMode {
		FILTER_MODE_LOWPASS = 0,
		FILTER_MODE_HIGHPASS,
		FILTER_MODE_BANDPASS,
		kNumFilterModes
	};
	Filtered() :
		cutoff(0.99),
		resonance(0.0),
		mode(FILTER_MODE_HIGHPASS),
		buf0(0.0),
		buf1(0.0)
	{
		calculateFeedbackAmount();
	};
	double process(double inputValue, float cutoff, int selected_mode);
	inline void setCutoff(double newCutoff) { cutoff = newCutoff; calculateFeedbackAmount(); };
	inline void setResonance(double newResonance) { resonance = newResonance; calculateFeedbackAmount(); };
	inline void setFilterMode(FilterMode newMode) { mode = newMode; }

private:
	double cutoff;
	double resonance;
	FilterMode mode;
	double feedbackAmount;
	inline void calculateFeedbackAmount() { feedbackAmount = resonance + resonance / (1.0 - cutoff); }
	double buf0;
	double buf1;
};