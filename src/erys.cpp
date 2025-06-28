#include "plugin.hpp"

#include <cmath>
#include <algorithm>

#pragma GCC diagnostic ignored "-Warray-bounds"

struct Erys : Module {
	enum ParamId {
		PARAMS_LEN
	};
	enum InputId {
		INPUT_A_INPUT,
		INPUT_B_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		OUTPUT_MOD_AB_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	Erys() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configInput(INPUT_A_INPUT, "CV A (poly)");
		configInput(INPUT_B_INPUT, "CV B (mono)");
		configOutput(OUTPUT_MOD_AB_OUTPUT, "A modulo B (poly)");
	}

	void process(const ProcessArgs& args) override {
        int channels = std::max(1, inputs[INPUT_A_INPUT].getChannels());
        float a[channels];
        float b[channels];
        float ab[channels];
        inputs[INPUT_A_INPUT].readVoltages(a);

        float b_t = inputs[INPUT_B_INPUT].getNormalVoltage(0.5f);
        std::fill_n(b,channels,b_t);

        for(int i=0;i<channels;i++){
            ab[i] = fmod(a[i],b[i]==0.0?0.001:b[i]);
        }

        outputs[OUTPUT_MOD_AB_OUTPUT].setChannels(channels);
        outputs[OUTPUT_MOD_AB_OUTPUT].writeVoltages(ab);
	}
};


struct ErysWidget : ModuleWidget {
	ErysWidget(Erys* module) {
		setModule(module);

		setPanel(createPanel(
                    asset::plugin(pluginInstance, "res/erys.svg"),
                    asset::plugin(pluginInstance, "res/erys-dark.svg")
                    ));


		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.0, 10.0)), module, Erys::INPUT_A_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.0, 24.0)), module, Erys::INPUT_B_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(5.0, 116.0)), module, Erys::OUTPUT_MOD_AB_OUTPUT));
	}
};


Model* modelErys = createModel<Erys, ErysWidget>("erys");
