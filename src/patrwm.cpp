#include "plugin.hpp"
#include <cmath>

struct Patrwm : Module {
	enum ParamId {
		PARAMS_LEN
	};
	enum InputId {
		CV_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		PATTERN_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	Patrwm() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configInput(CV_INPUT, "");
		configOutput(PATTERN_OUTPUT, "");
	}

	void process(const ProcessArgs& args) override {
        float cv = -3.f;
        if (inputs[CV_INPUT].isConnected()){
            cv = inputs[CV_INPUT].getVoltage();
        }
        cv = std::min(5.25f,cv);
        cv = std::max(-3.f,cv);
        float t = round(((cv + 3.f) * 12.f) + 0.01f) * 0.1f;
        outputs[PATTERN_OUTPUT].setChannels(1);
        outputs[PATTERN_OUTPUT].setVoltage(t);
	}
};


struct PatrwmWidget : ModuleWidget {
	PatrwmWidget(Patrwm* module) {
		setModule(module);
		setPanel(createPanel(
                    asset::plugin(pluginInstance, "res/patrwm.svg"),
                    asset::plugin(pluginInstance, "res/patrwm-dark.svg")
                    ));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 12.7)), module, Patrwm::CV_INPUT));

		addOutput(createOutputCentered<DarkPJ301MPort>(mm2px(Vec(7.62, 116.84)), module, Patrwm::PATTERN_OUTPUT));
	}
};


Model* modelPatrwm = createModel<Patrwm, PatrwmWidget>("patrwm");

