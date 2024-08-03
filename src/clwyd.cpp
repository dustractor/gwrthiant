#include "plugin.hpp"


struct Clwyd : Module {
	enum ParamId {
		ANALOG_VALUE_PARAM,
		SHIFT_VALUE_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		ANALOG_CV_INPUT,
		SHIFT_CV_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		GATES_POLY_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LITE_1_LIGHT,
		LITE_2_LIGHT,
		LITE_3_LIGHT,
		LITE_4_LIGHT,
		LITE_5_LIGHT,
		LITE_6_LIGHT,
		LITE_7_LIGHT,
		LITE_8_LIGHT,
		LITE_9_LIGHT,
		LITE_10_LIGHT,
		LITE_11_LIGHT,
		LITE_12_LIGHT,
		LITE_13_LIGHT,
		LITE_14_LIGHT,
		LITE_15_LIGHT,
		LITE_16_LIGHT,
		LIGHTS_LEN
	};

	Clwyd() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(ANALOG_VALUE_PARAM, 0.f, 10.f, 0.f, "Analog Value");
		configParam(SHIFT_VALUE_PARAM, -10.f, 10.f, 0.f, "Shift Value");
		configInput(ANALOG_CV_INPUT, "Analog CV 0-10");
		configInput(SHIFT_CV_INPUT, "Shift CV");
		configOutput(GATES_POLY_OUTPUT, "Polyphonic Gates");
	}

	void process(const ProcessArgs& args) override {

        float val = params[ANALOG_VALUE_PARAM].getValue();
        if (inputs[ANALOG_CV_INPUT].isConnected()){
            val = inputs[ANALOG_CV_INPUT].getVoltage();
        }

        float shift_f = params[SHIFT_VALUE_PARAM].getValue();
        if (inputs[SHIFT_CV_INPUT].isConnected()){
            shift_f = inputs[SHIFT_CV_INPUT].getVoltage();
        }

        int ival = (int)(val * 6553.6f);
        int s = (int)(shift_f * 16.f);

        int x = 0x01;

        float gates[16] = { // {{{1
            10.f * (ival & x<<((s+0)%16)),
            10.f * (ival & x<<((s+1)%16)),
            10.f * (ival & x<<((s+2)%16)),
            10.f * (ival & x<<((s+3)%16)),

            10.f * (ival & x<<((s+4)%16)),
            10.f * (ival & x<<((s+5)%16)),
            10.f * (ival & x<<((s+6)%16)),
            10.f * (ival & x<<((s+7)%16)),

            10.f * (ival & x<<((s+8)%16)),
            10.f * (ival & x<<((s+9)%16)),
            10.f * (ival & x<<((s+10)%16)),
            10.f * (ival & x<<((s+11)%16)),

            10.f * (ival & x<<((s+12)%16)),
            10.f * (ival & x<<((s+13)%16)),
            10.f * (ival & x<<((s+14)%16)),
            10.f * (ival & x<<((s+15)%16)),
        }; // }}}1
        lights[LITE_1_LIGHT].setBrightness(gates[0]/10.f);
        lights[LITE_2_LIGHT].setBrightness(gates[1]/10.f);
        lights[LITE_3_LIGHT].setBrightness(gates[2]/10.f);
        lights[LITE_4_LIGHT].setBrightness(gates[3]/10.f);

        lights[LITE_5_LIGHT].setBrightness(gates[4]/10.f);
        lights[LITE_6_LIGHT].setBrightness(gates[5]/10.f);
        lights[LITE_7_LIGHT].setBrightness(gates[6]/10.f);
        lights[LITE_8_LIGHT].setBrightness(gates[7]/10.f);

        lights[LITE_9_LIGHT].setBrightness(gates[8]/10.f);
        lights[LITE_10_LIGHT].setBrightness(gates[9]/10.f);
        lights[LITE_11_LIGHT].setBrightness(gates[10]/10.f);
        lights[LITE_12_LIGHT].setBrightness(gates[11]/10.f);

        lights[LITE_13_LIGHT].setBrightness(gates[12]/10.f);
        lights[LITE_14_LIGHT].setBrightness(gates[13]/10.f);
        lights[LITE_15_LIGHT].setBrightness(gates[14]/10.f);
        lights[LITE_16_LIGHT].setBrightness(gates[15]/10.f);

        outputs[GATES_POLY_OUTPUT].setChannels(16);
        outputs[GATES_POLY_OUTPUT].writeVoltages(gates);
	}
};


struct ClwydWidget : ModuleWidget {
	ClwydWidget(Clwyd* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/clwyd.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(6.35, 8.89)), module, Clwyd::ANALOG_VALUE_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(6.35, 31.75)), module, Clwyd::SHIFT_VALUE_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(6.35, 19.05)), module, Clwyd::ANALOG_CV_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(6.35, 41.91)), module, Clwyd::SHIFT_CV_INPUT));

		addOutput(createOutputCentered<DarkPJ301MPort>(mm2px(Vec(6.35, 120.65)), module, Clwyd::GATES_POLY_OUTPUT));

		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(15.24, 5.08)), module, Clwyd::LITE_1_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(15.24, 12.7)), module, Clwyd::LITE_2_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(15.24, 20.32)), module, Clwyd::LITE_3_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(15.24, 27.94)), module, Clwyd::LITE_4_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(15.24, 35.56)), module, Clwyd::LITE_5_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(15.24, 43.18)), module, Clwyd::LITE_6_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(15.24, 50.8)), module, Clwyd::LITE_7_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(15.24, 58.42)), module, Clwyd::LITE_8_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(15.24, 66.04)), module, Clwyd::LITE_9_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(15.24, 73.66)), module, Clwyd::LITE_10_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(15.24, 81.28)), module, Clwyd::LITE_11_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(15.24, 88.9)), module, Clwyd::LITE_12_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(15.24, 96.52)), module, Clwyd::LITE_13_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(15.24, 104.14)), module, Clwyd::LITE_14_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(15.24, 111.76)), module, Clwyd::LITE_15_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(15.24, 119.38)), module, Clwyd::LITE_16_LIGHT));
	}
};


Model* modelClwyd = createModel<Clwyd, ClwydWidget>("clwyd");
