#include "plugin.hpp"


struct Cama : Module {
	enum ParamId {
		NUMERATOR_PARAM,
		DENOMINATOR_PARAM,
		MODEQ_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		CLOCK_INPUT,
		RESET_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		GATE_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	Cama() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);

		configParam(NUMERATOR_PARAM, 1.f, 1024.f, 1.f, "Numerator");
		configParam(DENOMINATOR_PARAM, 1.f, 1024.f, 1.f, "Denominator");
		configParam(MODEQ_PARAM, 2.f, 9.f, 2.f, "Modeq");

        paramQuantities[NUMERATOR_PARAM]->snapEnabled = true;
        paramQuantities[DENOMINATOR_PARAM]->snapEnabled = true;
        paramQuantities[MODEQ_PARAM]->snapEnabled = true;

		configInput(CLOCK_INPUT, "Clock");
		configInput(RESET_INPUT, "Reset");
		configOutput(GATE_OUTPUT, "Gate");
	}
    dsp::SchmittTrigger clockSchmitt;
    dsp::SchmittTrigger resetSchmitt;
    int state;
    int prevClock;
    int prevReset;
    int num,denom,modeq;
    int t_num = 1;
    bool clk_transitioned_high;

	void process(const ProcessArgs& args) override {
        num = params[NUMERATOR_PARAM].getValue();
        denom = params[DENOMINATOR_PARAM].getValue();
        modeq = params[MODEQ_PARAM].getValue();

        bool reset = resetSchmitt.process(inputs[RESET_INPUT].getVoltage());
        if (!(prevReset > 0.f) && (reset > 0.f)){
            t_num = num;
        }
        bool clock = resetSchmitt.process(inputs[CLOCK_INPUT].getVoltage(),0.1f,1.f);
        if (!(prevClock > 0.f) && (clock > 0.f)){
            clk_transitioned_high = true;
        } else {
            clk_transitioned_high = false;
        }
        prevClock = clock;
        if (clk_transitioned_high){
            t_num %= denom;
            t_num *= 10;
            state = ((t_num/denom) % modeq) == 0;
            outputs[GATE_OUTPUT].setVoltage(state*10.f);
            if (t_num == 0){
                t_num = num;
            }
        }

	}
};


struct CamaWidget : ModuleWidget {
	CamaWidget(Cama* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/cama.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(10.16, 17.78)), module, Cama::NUMERATOR_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(10.16, 33.02)), module, Cama::DENOMINATOR_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(10.16, 48.26)), module, Cama::MODEQ_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(10.16, 93.98)), module, Cama::CLOCK_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(10.16, 104.14)), module, Cama::RESET_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(10.16, 116.84)), module, Cama::GATE_OUTPUT));
	}
};


Model* modelCama = createModel<Cama, CamaWidget>("cama");
