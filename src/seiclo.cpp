#include "plugin.hpp"

#define MAX_CHANNELS 16

struct Seiclo : Module {
	enum ParamId {
		CHANNELS_PARAM,
		RANDOMIZE_BTN_PARAM,
		RANGE_MIN_PARAM,
		RANGE_MAX_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		CLOCK_TRIG_INPUT,
		RESET_INPUT,
		RANDOMIZE_TRIG_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		SEQ_OUT_OUTPUT,
		POLY_OUT_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

    dsp::BooleanTrigger pushBoolean;
	dsp::SchmittTrigger pushSchmitt;
	dsp::SchmittTrigger clockSchmitt;
	dsp::SchmittTrigger resetSchmitt;

    int seqStep = 0;
    float fvals[MAX_CHANNELS];
    bool prevRndGate = 0;
    bool prevClock = 0;
    bool prevReset = 0;
    int prevChannels = 0;
    bool clk_transitioned_high = 0;
    bool rst_transitioned_high = 0;
    bool rnd_transitioned_high = 0;

	Seiclo() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configButton(RANDOMIZE_BTN_PARAM, "Randomize");
		configParam(CHANNELS_PARAM, 1.f, 16.f, 1.f, "Channels");
        paramQuantities[CHANNELS_PARAM]->snapEnabled = true;
		configParam(RANGE_MIN_PARAM, -10.f, 10.f, 0.f, "Range min");
		configParam(RANGE_MAX_PARAM, -10.f, 10.f, 10.f, "Range max");
		configInput(CLOCK_TRIG_INPUT, "Clock");
		configInput(RANDOMIZE_TRIG_INPUT, "Randomize");
		configInput(RESET_INPUT, "Reset");
		configOutput(SEQ_OUT_OUTPUT, "Seq out");
		configOutput(POLY_OUT_OUTPUT, "Poly out");
	}

	void process(const ProcessArgs& args) override {
        int channels = params[CHANNELS_PARAM].getValue();
        prevChannels = channels;
        float range_min = params[RANGE_MIN_PARAM].getValue();
        float range_max = params[RANGE_MAX_PARAM].getValue();

        bool reset = resetSchmitt.process(inputs[RESET_INPUT].getVoltage());

        if (!(prevReset > 0.f) && (reset > 0.f)){
            rst_transitioned_high = true;
        } else {
            rst_transitioned_high = false;
        }

        prevReset = reset;

        clockSchmitt.process(inputs[CLOCK_TRIG_INPUT].getVoltage(),0.1f,1.f);
        bool clock = clockSchmitt.isHigh();
        if (!(prevClock > 0.f) && (clock > 0.f)){
            clk_transitioned_high = true;
        } else {
            clk_transitioned_high = false;
        }
        prevClock = clock;

        bool push = params[RANDOMIZE_BTN_PARAM].getValue() > 0.f;
        pushSchmitt.process(inputs[RANDOMIZE_TRIG_INPUT].getVoltage(),0.1f,1.f);
        bool rnd_gate = push || pushSchmitt.isHigh();
        if (!(prevRndGate > 0.f) && (rnd_gate > 0.f)){
            rnd_transitioned_high = true;
        } else {
            rnd_transitioned_high = false;
        }
        if (rnd_transitioned_high){
            for (int i=0;i<channels;i++){
                fvals[i] = math::rescale(random::uniform(),0.f,1.f,range_min,range_max);
            }
            outputs[POLY_OUT_OUTPUT].setChannels(channels);
            outputs[POLY_OUT_OUTPUT].writeVoltages(fvals);
        }
        prevRndGate = rnd_gate;

        if (clk_transitioned_high){
            if (rst_transitioned_high){
                seqStep = 0;
            }
            seqStep = (seqStep + 1) % channels;
            outputs[SEQ_OUT_OUTPUT].setVoltage(fvals[seqStep]);
        }
	}
};


struct SeicloWidget : ModuleWidget {
	SeicloWidget(Seiclo* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/seiclo.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(5.08, 26.935)), module, Seiclo::CHANNELS_PARAM));
		addParam(createParamCentered<BefacoPush>(mm2px(Vec(5.08, 34.555)), module, Seiclo::RANDOMIZE_BTN_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(5.08, 72.655)), module, Seiclo::RANGE_MIN_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(5.08, 82.815)), module, Seiclo::RANGE_MAX_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.08, 6.615)), module, Seiclo::CLOCK_TRIG_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.08, 14.235)), module, Seiclo::RESET_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.08, 42.175)), module, Seiclo::RANDOMIZE_TRIG_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(5.08, 115.835)), module, Seiclo::SEQ_OUT_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(5.08, 123.455)), module, Seiclo::POLY_OUT_OUTPUT));
	}
};


Model* modelSeiclo = createModel<Seiclo, SeicloWidget>("seiclo");
