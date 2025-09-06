#include "plugin.hpp"


struct Penodol4 : Module {
	enum ParamId {

		A_C_PARAM,
		A_CS_PARAM,
		A_D_PARAM,
		A_DS_PARAM,
		A_E_PARAM,
		A_F_PARAM,
		A_FS_PARAM,
		A_G_PARAM,
		A_GS_PARAM,
		A_A_PARAM,
		A_AS_PARAM,
		A_B_PARAM,

		B_C_PARAM,
		B_CS_PARAM,
		B_D_PARAM,
		B_DS_PARAM,
		B_E_PARAM,
		B_F_PARAM,
		B_FS_PARAM,
		B_G_PARAM,
		B_GS_PARAM,
		B_A_PARAM,
		B_AS_PARAM,
		B_B_PARAM,

		C_C_PARAM,
		C_CS_PARAM,
		C_D_PARAM,
		C_DS_PARAM,
		C_E_PARAM,
		C_F_PARAM,
		C_FS_PARAM,
		C_G_PARAM,
		C_GS_PARAM,
		C_A_PARAM,
		C_AS_PARAM,
		C_B_PARAM,

		D_C_PARAM,
		D_CS_PARAM,
		D_D_PARAM,
		D_DS_PARAM,
		D_E_PARAM,
		D_F_PARAM,
		D_FS_PARAM,
		D_G_PARAM,
		D_GS_PARAM,
		D_A_PARAM,
		D_AS_PARAM,
		D_B_PARAM,

		PARAMS_LEN
	};
	enum InputId {
		CV_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		A_OUTPUT,
		B_OUTPUT,
		C_OUTPUT,
		D_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		NOTE_C_LIGHT,
		NOTE_CS_LIGHT,
		NOTE_D_LIGHT,
		NOTE_DS_LIGHT,
		NOTE_E_LIGHT,
		NOTE_F_LIGHT,
		NOTE_FS_LIGHT,
		NOTE_G_LIGHT,
		NOTE_GS_LIGHT,
		NOTE_A_LIGHT,
		NOTE_AS_LIGHT,
		NOTE_B_LIGHT,
		LIGHTS_LEN
	};

	Penodol4() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);

		configParam(A_C_PARAM,   -10.f, 10.f, 0.f, "C");
		configParam(A_CS_PARAM,  -10.f, 10.f, 0.f, "C#");
		configParam(A_D_PARAM,   -10.f, 10.f, 0.f, "D");
		configParam(A_DS_PARAM,  -10.f, 10.f, 0.f, "D#");
		configParam(A_E_PARAM,   -10.f, 10.f, 0.f, "E");
		configParam(A_F_PARAM,   -10.f, 10.f, 0.f, "F");
		configParam(A_FS_PARAM,  -10.f, 10.f, 0.f, "F#");
		configParam(A_G_PARAM,   -10.f, 10.f, 0.f, "G");
		configParam(A_GS_PARAM,  -10.f, 10.f, 0.f, "G#");
		configParam(A_A_PARAM,   -10.f, 10.f, 0.f, "A");
		configParam(A_AS_PARAM,  -10.f, 10.f, 0.f, "A#");
		configParam(A_B_PARAM,   -10.f, 10.f, 0.f, "B");

		configParam(B_C_PARAM,   -10.f, 10.f, 0.f, "C");
		configParam(B_CS_PARAM,  -10.f, 10.f, 0.f, "C#");
		configParam(B_D_PARAM,   -10.f, 10.f, 0.f, "D");
		configParam(B_DS_PARAM,  -10.f, 10.f, 0.f, "D#");
		configParam(B_E_PARAM,   -10.f, 10.f, 0.f, "E");
		configParam(B_F_PARAM,   -10.f, 10.f, 0.f, "F");
		configParam(B_FS_PARAM,  -10.f, 10.f, 0.f, "F#");
		configParam(B_G_PARAM,   -10.f, 10.f, 0.f, "G");
		configParam(B_GS_PARAM,  -10.f, 10.f, 0.f, "G#");
		configParam(B_A_PARAM,   -10.f, 10.f, 0.f, "A");
		configParam(B_AS_PARAM,  -10.f, 10.f, 0.f, "A#");
		configParam(B_B_PARAM,   -10.f, 10.f, 0.f, "B");

		configParam(C_C_PARAM,   -10.f, 10.f, 0.f, "C");
		configParam(C_CS_PARAM,  -10.f, 10.f, 0.f, "C#");
		configParam(C_D_PARAM,   -10.f, 10.f, 0.f, "D");
		configParam(C_DS_PARAM,  -10.f, 10.f, 0.f, "D#");
		configParam(C_E_PARAM,   -10.f, 10.f, 0.f, "E");
		configParam(C_F_PARAM,   -10.f, 10.f, 0.f, "F");
		configParam(C_FS_PARAM,  -10.f, 10.f, 0.f, "F#");
		configParam(C_G_PARAM,   -10.f, 10.f, 0.f, "G");
		configParam(C_GS_PARAM,  -10.f, 10.f, 0.f, "G#");
		configParam(C_A_PARAM,   -10.f, 10.f, 0.f, "A");
		configParam(C_AS_PARAM,  -10.f, 10.f, 0.f, "A#");
		configParam(C_B_PARAM,   -10.f, 10.f, 0.f, "B");

		configParam(D_C_PARAM,   -10.f, 10.f, 0.f, "C");
		configParam(D_CS_PARAM,  -10.f, 10.f, 0.f, "C#");
		configParam(D_D_PARAM,   -10.f, 10.f, 0.f, "D");
		configParam(D_DS_PARAM,  -10.f, 10.f, 0.f, "D#");
		configParam(D_E_PARAM,   -10.f, 10.f, 0.f, "E");
		configParam(D_F_PARAM,   -10.f, 10.f, 0.f, "F");
		configParam(D_FS_PARAM,  -10.f, 10.f, 0.f, "F#");
		configParam(D_G_PARAM,   -10.f, 10.f, 0.f, "G");
		configParam(D_GS_PARAM,  -10.f, 10.f, 0.f, "G#");
		configParam(D_A_PARAM,   -10.f, 10.f, 0.f, "A");
		configParam(D_AS_PARAM,  -10.f, 10.f, 0.f, "A#");
		configParam(D_B_PARAM,   -10.f, 10.f, 0.f, "B");

		configInput(CV_INPUT, "CV");

		configOutput(A_OUTPUT, "A");
		configOutput(B_OUTPUT, "B");
		configOutput(C_OUTPUT, "C");
		configOutput(D_OUTPUT, "D");
	}

	void process(const ProcessArgs& args) override {
        float cv = 0.f;
        if (inputs[CV_INPUT].isConnected()){
            cv = inputs[CV_INPUT].getVoltage();
        }
        float r = std::fmod(10.0f+cv,1.0f);
        int note = (int)(0.5f+r*12)%12;
        lights[NOTE_C_LIGHT].setBrightness((float)(note==0));
        lights[NOTE_CS_LIGHT].setBrightness((float)(note==1));
        lights[NOTE_D_LIGHT].setBrightness((float)(note==2));
        lights[NOTE_DS_LIGHT].setBrightness((float)(note==3));
        lights[NOTE_E_LIGHT].setBrightness((float)(note==4));
        lights[NOTE_F_LIGHT].setBrightness((float)(note==5));
        lights[NOTE_FS_LIGHT].setBrightness((float)(note==6));
        lights[NOTE_G_LIGHT].setBrightness((float)(note==7));
        lights[NOTE_GS_LIGHT].setBrightness((float)(note==8));
        lights[NOTE_A_LIGHT].setBrightness((float)(note==9));
        lights[NOTE_AS_LIGHT].setBrightness((float)(note==10));
        lights[NOTE_B_LIGHT].setBrightness((float)(note==11));

        switch (note){
            case 0:
                outputs[A_OUTPUT].setVoltage(params[A_C_PARAM].getValue());
                outputs[B_OUTPUT].setVoltage(params[B_C_PARAM].getValue());
                outputs[C_OUTPUT].setVoltage(params[C_C_PARAM].getValue());
                outputs[D_OUTPUT].setVoltage(params[D_C_PARAM].getValue());
                break;
            case 1:
                outputs[A_OUTPUT].setVoltage(params[A_CS_PARAM].getValue());
                outputs[B_OUTPUT].setVoltage(params[B_CS_PARAM].getValue());
                outputs[C_OUTPUT].setVoltage(params[C_CS_PARAM].getValue());
                outputs[D_OUTPUT].setVoltage(params[D_CS_PARAM].getValue());
                break;
            case 2:
                outputs[A_OUTPUT].setVoltage(params[A_D_PARAM].getValue());
                outputs[B_OUTPUT].setVoltage(params[B_D_PARAM].getValue());
                outputs[C_OUTPUT].setVoltage(params[C_D_PARAM].getValue());
                outputs[D_OUTPUT].setVoltage(params[D_D_PARAM].getValue());
                break;
            case 3:
                outputs[A_OUTPUT].setVoltage(params[A_DS_PARAM].getValue());
                outputs[B_OUTPUT].setVoltage(params[B_DS_PARAM].getValue());
                outputs[C_OUTPUT].setVoltage(params[C_DS_PARAM].getValue());
                outputs[D_OUTPUT].setVoltage(params[D_DS_PARAM].getValue());
                break;
            case 4:
                outputs[A_OUTPUT].setVoltage(params[A_E_PARAM].getValue());
                outputs[B_OUTPUT].setVoltage(params[B_E_PARAM].getValue());
                outputs[C_OUTPUT].setVoltage(params[C_E_PARAM].getValue());
                outputs[D_OUTPUT].setVoltage(params[D_E_PARAM].getValue());
                break;
            case 5:
                outputs[A_OUTPUT].setVoltage(params[A_F_PARAM].getValue());
                outputs[B_OUTPUT].setVoltage(params[B_F_PARAM].getValue());
                outputs[C_OUTPUT].setVoltage(params[C_F_PARAM].getValue());
                outputs[D_OUTPUT].setVoltage(params[D_F_PARAM].getValue());
                break;
            case 6:
                outputs[A_OUTPUT].setVoltage(params[A_FS_PARAM].getValue());
                outputs[B_OUTPUT].setVoltage(params[B_FS_PARAM].getValue());
                outputs[C_OUTPUT].setVoltage(params[C_FS_PARAM].getValue());
                outputs[D_OUTPUT].setVoltage(params[D_FS_PARAM].getValue());
                break;
            case 7:
                outputs[A_OUTPUT].setVoltage(params[A_G_PARAM].getValue());
                outputs[B_OUTPUT].setVoltage(params[B_G_PARAM].getValue());
                outputs[C_OUTPUT].setVoltage(params[C_G_PARAM].getValue());
                outputs[D_OUTPUT].setVoltage(params[D_G_PARAM].getValue());
                break;
            case 8:
                outputs[A_OUTPUT].setVoltage(params[A_GS_PARAM].getValue());
                outputs[B_OUTPUT].setVoltage(params[B_GS_PARAM].getValue());
                outputs[C_OUTPUT].setVoltage(params[C_GS_PARAM].getValue());
                outputs[D_OUTPUT].setVoltage(params[D_GS_PARAM].getValue());
                break;
            case 9:
                outputs[A_OUTPUT].setVoltage(params[A_A_PARAM].getValue());
                outputs[B_OUTPUT].setVoltage(params[B_A_PARAM].getValue());
                outputs[C_OUTPUT].setVoltage(params[C_A_PARAM].getValue());
                outputs[D_OUTPUT].setVoltage(params[D_A_PARAM].getValue());
                break;
            case 10:
                outputs[A_OUTPUT].setVoltage(params[A_AS_PARAM].getValue());
                outputs[B_OUTPUT].setVoltage(params[B_AS_PARAM].getValue());
                outputs[C_OUTPUT].setVoltage(params[C_AS_PARAM].getValue());
                outputs[D_OUTPUT].setVoltage(params[D_AS_PARAM].getValue());
                break;
            case 11:
                outputs[A_OUTPUT].setVoltage(params[A_B_PARAM].getValue());
                outputs[B_OUTPUT].setVoltage(params[B_B_PARAM].getValue());
                outputs[C_OUTPUT].setVoltage(params[C_B_PARAM].getValue());
                outputs[D_OUTPUT].setVoltage(params[D_B_PARAM].getValue());
                break;
        }
	}
};


struct Penodol4Widget : ModuleWidget {
	Penodol4Widget(Penodol4* module) {
		setModule(module);
		setPanel(createPanel(
                    asset::plugin(pluginInstance, "res/penodol4.svg"),
                    asset::plugin(pluginInstance, "res/penodol4-dark.svg")
                    ));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(21.59, 8.89)), module, Penodol4::A_C_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(33.201, 8.89)), module, Penodol4::B_C_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(44.813, 8.89)), module, Penodol4::C_C_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(56.424, 8.89)), module, Penodol4::D_C_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(21.59, 17.895)), module, Penodol4::A_CS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(33.201, 17.895)), module, Penodol4::B_CS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(44.813, 17.895)), module, Penodol4::C_CS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(56.424, 17.895)), module, Penodol4::D_CS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(21.59, 26.901)), module, Penodol4::A_D_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(33.201, 26.901)), module, Penodol4::B_D_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(44.813, 26.901)), module, Penodol4::C_D_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(56.424, 26.901)), module, Penodol4::D_D_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(21.59, 35.906)), module, Penodol4::A_DS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(33.201, 35.906)), module, Penodol4::B_DS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(44.813, 35.906)), module, Penodol4::C_DS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(56.424, 35.906)), module, Penodol4::D_DS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(21.59, 44.912)), module, Penodol4::A_E_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(33.201, 44.912)), module, Penodol4::B_E_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(44.813, 44.912)), module, Penodol4::C_E_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(56.424, 44.912)), module, Penodol4::D_E_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(21.59, 53.917)), module, Penodol4::A_F_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(33.201, 53.917)), module, Penodol4::B_F_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(44.813, 53.917)), module, Penodol4::C_F_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(56.424, 53.917)), module, Penodol4::D_F_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(21.59, 62.923)), module, Penodol4::A_FS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(33.201, 62.923)), module, Penodol4::B_FS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(44.813, 62.923)), module, Penodol4::C_FS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(56.424, 62.923)), module, Penodol4::D_FS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(21.59, 71.928)), module, Penodol4::A_G_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(33.201, 71.928)), module, Penodol4::B_G_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(44.813, 71.928)), module, Penodol4::C_G_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(56.424, 71.928)), module, Penodol4::D_G_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(21.59, 80.934)), module, Penodol4::A_GS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(33.201, 80.934)), module, Penodol4::B_GS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(44.813, 80.934)), module, Penodol4::C_GS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(56.424, 80.934)), module, Penodol4::D_GS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(21.59, 89.939)), module, Penodol4::A_A_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(33.201, 89.939)), module, Penodol4::B_A_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(44.813, 89.939)), module, Penodol4::C_A_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(56.424, 89.939)), module, Penodol4::D_A_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(21.59, 98.945)), module, Penodol4::A_AS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(33.201, 98.945)), module, Penodol4::B_AS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(44.813, 98.945)), module, Penodol4::C_AS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(56.424, 98.945)), module, Penodol4::D_AS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(21.59, 107.95)), module, Penodol4::A_B_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(33.201, 107.95)), module, Penodol4::B_B_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(44.813, 107.95)), module, Penodol4::C_B_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(56.424, 107.95)), module, Penodol4::D_B_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(8.89, 120.65)), module, Penodol4::CV_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(21.59, 120.65)), module, Penodol4::A_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(33.201, 120.65)), module, Penodol4::B_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(44.813, 120.65)), module, Penodol4::C_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(56.424, 120.65)), module, Penodol4::D_OUTPUT));

		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(8.834, 8.89)), module, Penodol4::NOTE_C_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(8.834, 17.895)), module, Penodol4::NOTE_CS_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(8.834, 26.901)), module, Penodol4::NOTE_D_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(8.834, 35.906)), module, Penodol4::NOTE_DS_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(8.834, 44.912)), module, Penodol4::NOTE_E_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(8.834, 53.917)), module, Penodol4::NOTE_F_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(8.834, 62.923)), module, Penodol4::NOTE_FS_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(8.834, 71.928)), module, Penodol4::NOTE_G_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(8.834, 80.934)), module, Penodol4::NOTE_GS_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(8.834, 89.939)), module, Penodol4::NOTE_A_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(8.834, 98.945)), module, Penodol4::NOTE_AS_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(8.834, 107.95)), module, Penodol4::NOTE_B_LIGHT));
	}
};


Model* modelPenodol4 = createModel<Penodol4, Penodol4Widget>("penodol4");
