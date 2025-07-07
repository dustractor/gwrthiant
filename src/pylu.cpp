#include "plugin.hpp"


struct Pylu : Module {
	enum ParamId {
		A_1_PARAM,
		B_1_PARAM,
		A_2_PARAM,
		B_2_PARAM,
		A_3_PARAM,
		B_3_PARAM,
		A_4_PARAM,
		B_4_PARAM,
		A_5_PARAM,
		B_5_PARAM,
		A_6_PARAM,
		B_6_PARAM,
		A_7_PARAM,
		B_7_PARAM,
		A_8_PARAM,
		B_8_PARAM,
		FADER_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		INPUTS_LEN
	};
	enum OutputId {
		O1_OUTPUT,
		O2_OUTPUT,
		O3_OUTPUT,
		O4_OUTPUT,
		O5_OUTPUT,
		O6_OUTPUT,
		O7_OUTPUT,
		O8_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	Pylu() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(A_1_PARAM, -10.f, 10.f, 0.f, "A1");
		configParam(A_2_PARAM, -10.f, 10.f, 0.f, "A2");
		configParam(A_3_PARAM, -10.f, 10.f, 0.f, "A3");
		configParam(A_4_PARAM, -10.f, 10.f, 0.f, "A4");
		configParam(A_5_PARAM, -10.f, 10.f, 0.f, "A5");
		configParam(A_6_PARAM, -10.f, 10.f, 0.f, "A6");
		configParam(A_7_PARAM, -10.f, 10.f, 0.f, "A7");
		configParam(A_8_PARAM, -10.f, 10.f, 0.f, "A8");

		configParam(B_1_PARAM, -10.f, 10.f, 0.f, "B1");
		configParam(B_2_PARAM, -10.f, 10.f, 0.f, "B2");
		configParam(B_3_PARAM, -10.f, 10.f, 0.f, "B3");
		configParam(B_4_PARAM, -10.f, 10.f, 0.f, "B4");
		configParam(B_5_PARAM, -10.f, 10.f, 0.f, "B5");
		configParam(B_6_PARAM, -10.f, 10.f, 0.f, "B6");
		configParam(B_7_PARAM, -10.f, 10.f, 0.f, "B7");
		configParam(B_8_PARAM, -10.f, 10.f, 0.f, "B8");

		configParam(FADER_PARAM, 0.f, 1.f, 0.f, "Fader");

		configOutput(O1_OUTPUT, "O1");
		configOutput(O2_OUTPUT, "O2");
		configOutput(O3_OUTPUT, "O3");
		configOutput(O4_OUTPUT, "O4");
		configOutput(O5_OUTPUT, "O5");
		configOutput(O6_OUTPUT, "O6");
		configOutput(O7_OUTPUT, "O7");
		configOutput(O8_OUTPUT, "O8");
	}

	void process(const ProcessArgs& args) override {
	}
};


struct PyluWidget : ModuleWidget {
	PyluWidget(Pylu* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/pylu.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<Rogan2PBlue>(mm2px(Vec(15.24, 12.7)), module, Pylu::A_1_PARAM));
		addParam(createParamCentered<Rogan2PBlue>(mm2px(Vec(15.24, 25.4)), module, Pylu::A_2_PARAM));
		addParam(createParamCentered<Rogan2PBlue>(mm2px(Vec(15.24, 38.1)), module, Pylu::A_3_PARAM));
		addParam(createParamCentered<Rogan2PBlue>(mm2px(Vec(15.24, 50.8)), module, Pylu::A_4_PARAM));
		addParam(createParamCentered<Rogan2PBlue>(mm2px(Vec(15.24, 63.5)), module, Pylu::A_5_PARAM));
		addParam(createParamCentered<Rogan2PBlue>(mm2px(Vec(15.24, 76.2)), module, Pylu::A_6_PARAM));
		addParam(createParamCentered<Rogan2PBlue>(mm2px(Vec(15.24, 88.9)), module, Pylu::A_7_PARAM));
		addParam(createParamCentered<Rogan2PBlue>(mm2px(Vec(15.24, 101.6)), module, Pylu::A_8_PARAM));

		addParam(createParamCentered<Rogan2PRed>(mm2px(Vec(30.48, 12.7)), module, Pylu::B_1_PARAM));
		addParam(createParamCentered<Rogan2PRed>(mm2px(Vec(30.48, 25.4)), module, Pylu::B_2_PARAM));
		addParam(createParamCentered<Rogan2PRed>(mm2px(Vec(30.48, 38.1)), module, Pylu::B_3_PARAM));
		addParam(createParamCentered<Rogan2PRed>(mm2px(Vec(30.48, 50.8)), module, Pylu::B_4_PARAM));
		addParam(createParamCentered<Rogan2PRed>(mm2px(Vec(30.48, 63.5)), module, Pylu::B_5_PARAM));
		addParam(createParamCentered<Rogan2PRed>(mm2px(Vec(30.48, 76.2)), module, Pylu::B_6_PARAM));
		addParam(createParamCentered<Rogan2PRed>(mm2px(Vec(30.48, 88.9)), module, Pylu::B_7_PARAM));
		addParam(createParamCentered<Rogan2PRed>(mm2px(Vec(30.48, 101.6)), module, Pylu::B_8_PARAM));

		addParam(createParamCentered<Crossfader>(mm2px(Vec(22.86, 116.84)), module, Pylu::FADER_PARAM));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(40.64, 12.7)), module, Pylu::O1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(40.64, 25.4)), module, Pylu::O2_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(40.64, 38.1)), module, Pylu::O3_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(40.64, 50.8)), module, Pylu::O4_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(40.64, 63.5)), module, Pylu::O5_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(40.64, 76.2)), module, Pylu::O6_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(40.64, 88.9)), module, Pylu::O7_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(40.64, 101.6)), module, Pylu::O8_OUTPUT));
	}
};


Model* modelPylu = createModel<Pylu, PyluWidget>("pylu");
