#include "plugin.hpp"
#include <cmath>


struct Graddfa : Module {
	enum ParamId {
		PARAMS_LEN
	};
	enum InputId {
		CV_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		MODE_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	Graddfa() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configInput(CV_INPUT, "");
		configOutput(MODE_OUTPUT, "");
	}

	void process(const ProcessArgs& args) override {
        float cv = 0.f;
        if (inputs[CV_INPUT].isConnected()){
            cv = inputs[CV_INPUT].getVoltage();
        }
        float t = ((cv * 12) * (10.f / 45.f)) + ((2.f * (1.f / 12.f)) / 10.f);

        t = std::max(t,0.f);
        t = std::min(t,10.f);

        outputs[MODE_OUTPUT].setChannels(1);
        outputs[MODE_OUTPUT].setVoltage(t);
	}
};


struct GraddfaWidget : ModuleWidget {
	GraddfaWidget(Graddfa* module) {
		setModule(module);
		setPanel(createPanel(
                    asset::plugin(pluginInstance, "res/graddfa.svg"),
                    asset::plugin(pluginInstance, "res/graddfa-dark.svg")
                    ));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 17.78)), module, Graddfa::CV_INPUT));

		addOutput(createOutputCentered<DarkPJ301MPort>(mm2px(Vec(7.62, 111.76)), module, Graddfa::MODE_OUTPUT));
	}
};


Model* modelGraddfa = createModel<Graddfa, GraddfaWidget>("graddfa");
