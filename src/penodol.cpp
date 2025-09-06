#include "plugin.hpp"


struct Penodol : Module {
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

		E_C_PARAM,
		E_CS_PARAM,
		E_D_PARAM,
		E_DS_PARAM,
		E_E_PARAM,
		E_F_PARAM,
		E_FS_PARAM,
		E_G_PARAM,
		E_GS_PARAM,
		E_A_PARAM,
		E_AS_PARAM,
		E_B_PARAM,

		F_C_PARAM,
		F_CS_PARAM,
		F_D_PARAM,
		F_DS_PARAM,
		F_E_PARAM,
		F_F_PARAM,
		F_FS_PARAM,
		F_G_PARAM,
		F_GS_PARAM,
		F_A_PARAM,
		F_AS_PARAM,
		F_B_PARAM,

		G_C_PARAM,
		G_CS_PARAM,
		G_D_PARAM,
		G_DS_PARAM,
		G_E_PARAM,
		G_F_PARAM,
		G_FS_PARAM,
		G_G_PARAM,
		G_GS_PARAM,
		G_A_PARAM,
		G_AS_PARAM,
		G_B_PARAM,

		H_C_PARAM,
		H_CS_PARAM,
		H_D_PARAM,
		H_DS_PARAM,
		H_E_PARAM,
		H_F_PARAM,
		H_FS_PARAM,
		H_G_PARAM,
		H_GS_PARAM,
		H_A_PARAM,
		H_AS_PARAM,
		H_B_PARAM,

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
		E_OUTPUT,
		F_OUTPUT,
		G_OUTPUT,
		H_OUTPUT,
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

	Penodol() {
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

		configParam(E_C_PARAM,   -10.f, 10.f, 0.f, "C");
		configParam(E_CS_PARAM,  -10.f, 10.f, 0.f, "C#");
		configParam(E_D_PARAM,   -10.f, 10.f, 0.f, "D");
		configParam(E_DS_PARAM,  -10.f, 10.f, 0.f, "D#");
		configParam(E_E_PARAM,   -10.f, 10.f, 0.f, "E");
		configParam(E_F_PARAM,   -10.f, 10.f, 0.f, "F");
		configParam(E_FS_PARAM,  -10.f, 10.f, 0.f, "F#");
		configParam(E_G_PARAM,   -10.f, 10.f, 0.f, "G");
		configParam(E_GS_PARAM,  -10.f, 10.f, 0.f, "G#");
		configParam(E_A_PARAM,   -10.f, 10.f, 0.f, "A");
		configParam(E_AS_PARAM,  -10.f, 10.f, 0.f, "A#");
		configParam(E_B_PARAM,   -10.f, 10.f, 0.f, "B");

		configParam(F_C_PARAM,   -10.f, 10.f, 0.f, "C");
		configParam(F_CS_PARAM,  -10.f, 10.f, 0.f, "C#");
		configParam(F_D_PARAM,   -10.f, 10.f, 0.f, "D");
		configParam(F_DS_PARAM,  -10.f, 10.f, 0.f, "D#");
		configParam(F_E_PARAM,   -10.f, 10.f, 0.f, "E");
		configParam(F_F_PARAM,   -10.f, 10.f, 0.f, "F");
		configParam(F_FS_PARAM,  -10.f, 10.f, 0.f, "F#");
		configParam(F_G_PARAM,   -10.f, 10.f, 0.f, "G");
		configParam(F_GS_PARAM,  -10.f, 10.f, 0.f, "G#");
		configParam(F_A_PARAM,   -10.f, 10.f, 0.f, "A");
		configParam(F_AS_PARAM,  -10.f, 10.f, 0.f, "A#");
		configParam(F_B_PARAM,   -10.f, 10.f, 0.f, "B");

		configParam(G_C_PARAM,   -10.f, 10.f, 0.f, "C");
		configParam(G_CS_PARAM,  -10.f, 10.f, 0.f, "C#");
		configParam(G_D_PARAM,   -10.f, 10.f, 0.f, "D");
		configParam(G_DS_PARAM,  -10.f, 10.f, 0.f, "D#");
		configParam(G_E_PARAM,   -10.f, 10.f, 0.f, "E");
		configParam(G_F_PARAM,   -10.f, 10.f, 0.f, "F");
		configParam(G_FS_PARAM,  -10.f, 10.f, 0.f, "F#");
		configParam(G_G_PARAM,   -10.f, 10.f, 0.f, "G");
		configParam(G_GS_PARAM,  -10.f, 10.f, 0.f, "G#");
		configParam(G_A_PARAM,   -10.f, 10.f, 0.f, "A");
		configParam(G_AS_PARAM,  -10.f, 10.f, 0.f, "A#");
		configParam(G_B_PARAM,   -10.f, 10.f, 0.f, "B");

		configParam(H_C_PARAM,   -10.f, 10.f, 0.f, "C");
		configParam(H_CS_PARAM,  -10.f, 10.f, 0.f, "C#");
		configParam(H_D_PARAM,   -10.f, 10.f, 0.f, "D");
		configParam(H_DS_PARAM,  -10.f, 10.f, 0.f, "D#");
		configParam(H_E_PARAM,   -10.f, 10.f, 0.f, "E");
		configParam(H_F_PARAM,   -10.f, 10.f, 0.f, "F");
		configParam(H_FS_PARAM,  -10.f, 10.f, 0.f, "F#");
		configParam(H_G_PARAM,   -10.f, 10.f, 0.f, "G");
		configParam(H_GS_PARAM,  -10.f, 10.f, 0.f, "G#");
		configParam(H_A_PARAM,   -10.f, 10.f, 0.f, "A");
		configParam(H_AS_PARAM,  -10.f, 10.f, 0.f, "A#");
		configParam(H_B_PARAM,   -10.f, 10.f, 0.f, "B");

		configInput(CV_INPUT, "CV");

		configOutput(A_OUTPUT, "A");
		configOutput(B_OUTPUT, "B");
		configOutput(C_OUTPUT, "C");
		configOutput(D_OUTPUT, "D");
		configOutput(E_OUTPUT, "E");
		configOutput(F_OUTPUT, "F");
		configOutput(G_OUTPUT, "G");
		configOutput(H_OUTPUT, "H");
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
                outputs[E_OUTPUT].setVoltage(params[E_C_PARAM].getValue());
                outputs[F_OUTPUT].setVoltage(params[F_C_PARAM].getValue());
                outputs[G_OUTPUT].setVoltage(params[G_C_PARAM].getValue());
                outputs[H_OUTPUT].setVoltage(params[H_C_PARAM].getValue());
                break;
            case 1:
                outputs[A_OUTPUT].setVoltage(params[A_CS_PARAM].getValue());
                outputs[B_OUTPUT].setVoltage(params[B_CS_PARAM].getValue());
                outputs[C_OUTPUT].setVoltage(params[C_CS_PARAM].getValue());
                outputs[D_OUTPUT].setVoltage(params[D_CS_PARAM].getValue());
                outputs[E_OUTPUT].setVoltage(params[E_CS_PARAM].getValue());
                outputs[F_OUTPUT].setVoltage(params[F_CS_PARAM].getValue());
                outputs[G_OUTPUT].setVoltage(params[G_CS_PARAM].getValue());
                outputs[H_OUTPUT].setVoltage(params[H_CS_PARAM].getValue());
                break;
            case 2:
                outputs[A_OUTPUT].setVoltage(params[A_D_PARAM].getValue());
                outputs[B_OUTPUT].setVoltage(params[B_D_PARAM].getValue());
                outputs[C_OUTPUT].setVoltage(params[C_D_PARAM].getValue());
                outputs[D_OUTPUT].setVoltage(params[D_D_PARAM].getValue());
                outputs[E_OUTPUT].setVoltage(params[E_D_PARAM].getValue());
                outputs[F_OUTPUT].setVoltage(params[F_D_PARAM].getValue());
                outputs[G_OUTPUT].setVoltage(params[G_D_PARAM].getValue());
                outputs[H_OUTPUT].setVoltage(params[H_D_PARAM].getValue());
                break;
            case 3:
                outputs[A_OUTPUT].setVoltage(params[A_DS_PARAM].getValue());
                outputs[B_OUTPUT].setVoltage(params[B_DS_PARAM].getValue());
                outputs[C_OUTPUT].setVoltage(params[C_DS_PARAM].getValue());
                outputs[D_OUTPUT].setVoltage(params[D_DS_PARAM].getValue());
                outputs[E_OUTPUT].setVoltage(params[E_DS_PARAM].getValue());
                outputs[F_OUTPUT].setVoltage(params[F_DS_PARAM].getValue());
                outputs[G_OUTPUT].setVoltage(params[G_DS_PARAM].getValue());
                outputs[H_OUTPUT].setVoltage(params[H_DS_PARAM].getValue());
                break;
            case 4:
                outputs[A_OUTPUT].setVoltage(params[A_E_PARAM].getValue());
                outputs[B_OUTPUT].setVoltage(params[B_E_PARAM].getValue());
                outputs[C_OUTPUT].setVoltage(params[C_E_PARAM].getValue());
                outputs[D_OUTPUT].setVoltage(params[D_E_PARAM].getValue());
                outputs[E_OUTPUT].setVoltage(params[E_E_PARAM].getValue());
                outputs[F_OUTPUT].setVoltage(params[F_E_PARAM].getValue());
                outputs[G_OUTPUT].setVoltage(params[G_E_PARAM].getValue());
                outputs[H_OUTPUT].setVoltage(params[H_E_PARAM].getValue());
                break;
            case 5:
                outputs[A_OUTPUT].setVoltage(params[A_F_PARAM].getValue());
                outputs[B_OUTPUT].setVoltage(params[B_F_PARAM].getValue());
                outputs[C_OUTPUT].setVoltage(params[C_F_PARAM].getValue());
                outputs[D_OUTPUT].setVoltage(params[D_F_PARAM].getValue());
                outputs[E_OUTPUT].setVoltage(params[E_F_PARAM].getValue());
                outputs[F_OUTPUT].setVoltage(params[F_F_PARAM].getValue());
                outputs[G_OUTPUT].setVoltage(params[G_F_PARAM].getValue());
                outputs[H_OUTPUT].setVoltage(params[H_F_PARAM].getValue());
                break;
            case 6:
                outputs[A_OUTPUT].setVoltage(params[A_FS_PARAM].getValue());
                outputs[B_OUTPUT].setVoltage(params[B_FS_PARAM].getValue());
                outputs[C_OUTPUT].setVoltage(params[C_FS_PARAM].getValue());
                outputs[D_OUTPUT].setVoltage(params[D_FS_PARAM].getValue());
                outputs[E_OUTPUT].setVoltage(params[E_FS_PARAM].getValue());
                outputs[F_OUTPUT].setVoltage(params[F_FS_PARAM].getValue());
                outputs[G_OUTPUT].setVoltage(params[G_FS_PARAM].getValue());
                outputs[H_OUTPUT].setVoltage(params[H_FS_PARAM].getValue());
                break;
            case 7:
                outputs[A_OUTPUT].setVoltage(params[A_G_PARAM].getValue());
                outputs[B_OUTPUT].setVoltage(params[B_G_PARAM].getValue());
                outputs[C_OUTPUT].setVoltage(params[C_G_PARAM].getValue());
                outputs[D_OUTPUT].setVoltage(params[D_G_PARAM].getValue());
                outputs[E_OUTPUT].setVoltage(params[E_G_PARAM].getValue());
                outputs[F_OUTPUT].setVoltage(params[F_G_PARAM].getValue());
                outputs[G_OUTPUT].setVoltage(params[G_G_PARAM].getValue());
                outputs[H_OUTPUT].setVoltage(params[H_G_PARAM].getValue());
                break;
            case 8:
                outputs[A_OUTPUT].setVoltage(params[A_GS_PARAM].getValue());
                outputs[B_OUTPUT].setVoltage(params[B_GS_PARAM].getValue());
                outputs[C_OUTPUT].setVoltage(params[C_GS_PARAM].getValue());
                outputs[D_OUTPUT].setVoltage(params[D_GS_PARAM].getValue());
                outputs[E_OUTPUT].setVoltage(params[E_GS_PARAM].getValue());
                outputs[F_OUTPUT].setVoltage(params[F_GS_PARAM].getValue());
                outputs[G_OUTPUT].setVoltage(params[G_GS_PARAM].getValue());
                outputs[H_OUTPUT].setVoltage(params[H_GS_PARAM].getValue());
                break;
            case 9:
                outputs[A_OUTPUT].setVoltage(params[A_A_PARAM].getValue());
                outputs[B_OUTPUT].setVoltage(params[B_A_PARAM].getValue());
                outputs[C_OUTPUT].setVoltage(params[C_A_PARAM].getValue());
                outputs[D_OUTPUT].setVoltage(params[D_A_PARAM].getValue());
                outputs[E_OUTPUT].setVoltage(params[E_A_PARAM].getValue());
                outputs[F_OUTPUT].setVoltage(params[F_A_PARAM].getValue());
                outputs[G_OUTPUT].setVoltage(params[G_A_PARAM].getValue());
                outputs[H_OUTPUT].setVoltage(params[H_A_PARAM].getValue());
                break;
            case 10:
                outputs[A_OUTPUT].setVoltage(params[A_AS_PARAM].getValue());
                outputs[B_OUTPUT].setVoltage(params[B_AS_PARAM].getValue());
                outputs[C_OUTPUT].setVoltage(params[C_AS_PARAM].getValue());
                outputs[D_OUTPUT].setVoltage(params[D_AS_PARAM].getValue());
                outputs[E_OUTPUT].setVoltage(params[E_AS_PARAM].getValue());
                outputs[F_OUTPUT].setVoltage(params[F_AS_PARAM].getValue());
                outputs[G_OUTPUT].setVoltage(params[G_AS_PARAM].getValue());
                outputs[H_OUTPUT].setVoltage(params[H_AS_PARAM].getValue());
                break;
            case 11:
                outputs[A_OUTPUT].setVoltage(params[A_B_PARAM].getValue());
                outputs[B_OUTPUT].setVoltage(params[B_B_PARAM].getValue());
                outputs[C_OUTPUT].setVoltage(params[C_B_PARAM].getValue());
                outputs[D_OUTPUT].setVoltage(params[D_B_PARAM].getValue());
                outputs[E_OUTPUT].setVoltage(params[E_B_PARAM].getValue());
                outputs[F_OUTPUT].setVoltage(params[F_B_PARAM].getValue());
                outputs[G_OUTPUT].setVoltage(params[G_B_PARAM].getValue());
                outputs[H_OUTPUT].setVoltage(params[H_B_PARAM].getValue());
                break;
        }
	}
};


struct PenodolWidget : ModuleWidget {
	PenodolWidget(Penodol* module) {
		setModule(module);
		setPanel(createPanel(
                    asset::plugin(pluginInstance, "res/penodol.svg"),
                    asset::plugin(pluginInstance, "res/penodol-dark.svg")
                    ));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(21.59, 8.89)), module, Penodol::A_C_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(33.201, 8.89)), module, Penodol::B_C_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(44.813, 8.89)), module, Penodol::C_C_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(56.424, 8.89)), module, Penodol::D_C_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(68.036, 8.89)), module, Penodol::E_C_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(79.647, 8.89)), module, Penodol::F_C_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(91.259, 8.89)), module, Penodol::G_C_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(102.87, 8.89)), module, Penodol::H_C_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(21.59, 17.895)), module, Penodol::A_CS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(33.201, 17.895)), module, Penodol::B_CS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(44.813, 17.895)), module, Penodol::C_CS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(56.424, 17.895)), module, Penodol::D_CS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(68.036, 17.895)), module, Penodol::E_CS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(79.647, 17.895)), module, Penodol::F_CS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(91.259, 17.895)), module, Penodol::G_CS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(102.87, 17.895)), module, Penodol::H_CS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(21.59, 26.901)), module, Penodol::A_D_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(33.201, 26.901)), module, Penodol::B_D_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(44.813, 26.901)), module, Penodol::C_D_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(56.424, 26.901)), module, Penodol::D_D_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(68.036, 26.901)), module, Penodol::E_D_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(79.647, 26.901)), module, Penodol::F_D_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(91.259, 26.901)), module, Penodol::G_D_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(102.87, 26.901)), module, Penodol::H_D_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(21.59, 35.906)), module, Penodol::A_DS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(33.201, 35.906)), module, Penodol::B_DS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(44.813, 35.906)), module, Penodol::C_DS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(56.424, 35.906)), module, Penodol::D_DS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(68.036, 35.906)), module, Penodol::E_DS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(79.647, 35.906)), module, Penodol::F_DS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(91.259, 35.906)), module, Penodol::G_DS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(102.87, 35.906)), module, Penodol::H_DS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(21.59, 44.912)), module, Penodol::A_E_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(33.201, 44.912)), module, Penodol::B_E_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(44.813, 44.912)), module, Penodol::C_E_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(56.424, 44.912)), module, Penodol::D_E_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(68.036, 44.912)), module, Penodol::E_E_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(79.647, 44.912)), module, Penodol::F_E_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(91.259, 44.912)), module, Penodol::G_E_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(102.87, 44.912)), module, Penodol::H_E_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(21.59, 53.917)), module, Penodol::A_F_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(33.201, 53.917)), module, Penodol::B_F_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(44.813, 53.917)), module, Penodol::C_F_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(56.424, 53.917)), module, Penodol::D_F_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(68.036, 53.917)), module, Penodol::E_F_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(79.647, 53.917)), module, Penodol::F_F_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(91.259, 53.917)), module, Penodol::G_F_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(102.87, 53.917)), module, Penodol::H_F_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(21.59, 62.923)), module, Penodol::A_FS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(33.201, 62.923)), module, Penodol::B_FS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(44.813, 62.923)), module, Penodol::C_FS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(56.424, 62.923)), module, Penodol::D_FS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(68.036, 62.923)), module, Penodol::E_FS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(79.647, 62.923)), module, Penodol::F_FS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(91.259, 62.923)), module, Penodol::G_FS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(102.87, 62.923)), module, Penodol::H_FS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(21.59, 71.928)), module, Penodol::A_G_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(33.201, 71.928)), module, Penodol::B_G_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(44.813, 71.928)), module, Penodol::C_G_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(56.424, 71.928)), module, Penodol::D_G_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(68.036, 71.928)), module, Penodol::E_G_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(79.647, 71.928)), module, Penodol::F_G_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(91.259, 71.928)), module, Penodol::G_G_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(102.87, 71.928)), module, Penodol::H_G_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(21.59, 80.934)), module, Penodol::A_GS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(33.201, 80.934)), module, Penodol::B_GS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(44.813, 80.934)), module, Penodol::C_GS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(56.424, 80.934)), module, Penodol::D_GS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(68.036, 80.934)), module, Penodol::E_GS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(79.647, 80.934)), module, Penodol::F_GS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(91.259, 80.934)), module, Penodol::G_GS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(102.87, 80.934)), module, Penodol::H_GS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(21.59, 89.939)), module, Penodol::A_A_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(33.201, 89.939)), module, Penodol::B_A_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(44.813, 89.939)), module, Penodol::C_A_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(56.424, 89.939)), module, Penodol::D_A_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(68.036, 89.939)), module, Penodol::E_A_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(79.647, 89.939)), module, Penodol::F_A_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(91.259, 89.939)), module, Penodol::G_A_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(102.87, 89.939)), module, Penodol::H_A_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(21.59, 98.945)), module, Penodol::A_AS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(33.201, 98.945)), module, Penodol::B_AS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(44.813, 98.945)), module, Penodol::C_AS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(56.424, 98.945)), module, Penodol::D_AS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(68.036, 98.945)), module, Penodol::E_AS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(79.647, 98.945)), module, Penodol::F_AS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(91.259, 98.945)), module, Penodol::G_AS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(102.87, 98.945)), module, Penodol::H_AS_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(21.59, 107.95)), module, Penodol::A_B_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(33.201, 107.95)), module, Penodol::B_B_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(44.813, 107.95)), module, Penodol::C_B_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(56.424, 107.95)), module, Penodol::D_B_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(68.036, 107.95)), module, Penodol::E_B_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(79.647, 107.95)), module, Penodol::F_B_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(91.259, 107.95)), module, Penodol::G_B_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(102.87, 107.95)), module, Penodol::H_B_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(8.89, 120.65)), module, Penodol::CV_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(21.59, 120.65)), module, Penodol::A_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(33.201, 120.65)), module, Penodol::B_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(44.813, 120.65)), module, Penodol::C_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(56.424, 120.65)), module, Penodol::D_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(68.036, 120.65)), module, Penodol::E_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(79.647, 120.65)), module, Penodol::F_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(91.259, 120.65)), module, Penodol::G_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(102.87, 120.65)), module, Penodol::H_OUTPUT));

		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(8.834, 8.89)), module, Penodol::NOTE_C_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(8.834, 17.895)), module, Penodol::NOTE_CS_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(8.834, 26.901)), module, Penodol::NOTE_D_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(8.834, 35.906)), module, Penodol::NOTE_DS_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(8.834, 44.912)), module, Penodol::NOTE_E_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(8.834, 53.917)), module, Penodol::NOTE_F_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(8.834, 62.923)), module, Penodol::NOTE_FS_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(8.834, 71.928)), module, Penodol::NOTE_G_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(8.834, 80.934)), module, Penodol::NOTE_GS_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(8.834, 89.939)), module, Penodol::NOTE_A_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(8.834, 98.945)), module, Penodol::NOTE_AS_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(8.834, 107.95)), module, Penodol::NOTE_B_LIGHT));
	}
};


Model* modelPenodol = createModel<Penodol, PenodolWidget>("penodol");
