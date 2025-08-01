#include "plugin.hpp"
#include <cmath>

struct Nodiadau : Module {
	enum ParamId {
		PARAMS_LEN
	};
	enum InputId {
		SCALE_INPUT,
		MODE_INPUT,
		CVS_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		NOTES_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		C_LIGHT,
		CS_LIGHT,
		IONIAN_LIGHT,
		D_LIGHT,
		DORIAN_LIGHT,
		DS_LIGHT,
		E_LIGHT,
		PHRYGIAN_LIGHT,
		F_LIGHT,
		LYDIAN_LIGHT,
		FS_LIGHT,
		MIXOLYDIAN_LIGHT,
		G_LIGHT,
		GS_LIGHT,
		AEOLIAN_LIGHT,
		A_LIGHT,
		LOCRIAN_LIGHT,
		AS_LIGHT,
		B_LIGHT,
		LIGHTS_LEN
	};


    int ionian[7] =     {0,2,4,5,7,9,11};
    int dorian[7] =     {0,2,3,5,7,9,10};
    int phrygian[7] =   {0,1,3,5,7,8,10};
    int lydian[7] =     {0,2,4,6,7,9,11};
    int mixolydian[7] = {0,2,4,5,7,9,10};
    int aeolian[7] =    {0,2,3,5,7,8,10};
    int locrian[7] =    {0,1,3,5,6,8,10};

	Nodiadau() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configInput(SCALE_INPUT, "Scale");
		configInput(MODE_INPUT, "Mode");
		configInput(CVS_INPUT, "CV (poly)");
		configOutput(NOTES_OUTPUT, "Notes (poly)");
	}

	void process(const ProcessArgs& args) override {
        float root_cv = 0.f;
        if (inputs[SCALE_INPUT].isConnected()){
            root_cv = inputs[SCALE_INPUT].getVoltage();
        }
        float r = std::fmod(10.0f+root_cv, 1.0f);
        int note = (int)(0.5f+r*12) % 12;
        
        lights[C_LIGHT].setBrightness((float)(note==0));
        lights[CS_LIGHT].setBrightness((float)(note==1));
        lights[D_LIGHT].setBrightness((float)(note==2));
        lights[DS_LIGHT].setBrightness((float)(note==3));
        lights[E_LIGHT].setBrightness((float)(note==4));
        lights[F_LIGHT].setBrightness((float)(note==5));
        lights[FS_LIGHT].setBrightness((float)(note==6));
        lights[G_LIGHT].setBrightness((float)(note==7));
        lights[GS_LIGHT].setBrightness((float)(note==8));
        lights[A_LIGHT].setBrightness((float)(note==9));
        lights[AS_LIGHT].setBrightness((float)(note==10));
        lights[B_LIGHT].setBrightness((float)(note==11));

        float mode_cv = 0;
        if (inputs[MODE_INPUT].isConnected()){
            mode_cv = inputs[MODE_INPUT].getVoltage();
        }
        float m = std::fmod(10.0f+mode_cv,1.0f);
        int mode = (int)(0.5f+m*12)%12;
        lights[IONIAN_LIGHT    ].setBrightness((float)((mode==0)||(mode==1)));
        lights[DORIAN_LIGHT    ].setBrightness((float)((mode==2)||(mode==3)));
        lights[PHRYGIAN_LIGHT  ].setBrightness((float)(mode==4));
        lights[LYDIAN_LIGHT    ].setBrightness((float)((mode==5)||(mode==6)));
        lights[MIXOLYDIAN_LIGHT].setBrightness((float)((mode==7)||(mode==8)));
        lights[AEOLIAN_LIGHT   ].setBrightness((float)((mode==9)||(mode==10)));
        lights[LOCRIAN_LIGHT   ].setBrightness((float)(mode==11));
        int *scale = ionian;
        switch (mode){
            case 0:
                scale = ionian;
                break;
            case 1:
                scale = ionian;
                break;
            case 2:
                scale = dorian;
                break;
            case 3:
                scale = dorian;
                break;
            case 4:
                scale = phrygian;
                break;
            case 5:
                scale = lydian;
                break;
            case 6:
                scale = lydian;
                break;
            case 7:
                scale = mixolydian;
                break;
            case 8:
                scale = mixolydian;
                break;
            case 9:
                scale = aeolian;
                break;
            case 10:
                scale = aeolian;
                break;
            case 11:
                scale = locrian;
                break;
        }

        int channels = std::max(inputs[CVS_INPUT].getChannels(),1);
        outputs[NOTES_OUTPUT].setChannels(channels);

        for (int channel=0;channel<channels;channel++){
            float pitch = inputs[CVS_INPUT].getVoltage(channel);
            float closest_value = 0.0f;
            float closest_distance = 100.0f;
            float note_in_volts = 0.0f;
            float distance = 0.0f;
            int octave = int(floorf(pitch));
            float volts_minus_octave = pitch - octave;
            for (int i=0;i<7;i++){
                note_in_volts = (scale[i] + note) % 12 / 12.0f;
                distance = fabsf(volts_minus_octave - note_in_volts);
                if (distance < closest_distance){
                    closest_distance = distance;
                    closest_value = note_in_volts;
                }
            }
            outputs[NOTES_OUTPUT].setVoltage(closest_value + octave, channel);
        }
	}
};


struct NodiadauWidget : ModuleWidget {
	NodiadauWidget(Nodiadau* module) {
		setModule(module);
		setPanel(createPanel(
                    asset::plugin(pluginInstance, "res/nodiadau.svg"),
                    asset::plugin(pluginInstance, "res/nodiadau-dark.svg")
                    ));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(6.35, 11.43)), module, Nodiadau::SCALE_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(18.99, 11.43)), module, Nodiadau::MODE_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(6.35, 118.11)), module, Nodiadau::CVS_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(19.05, 118.11)), module, Nodiadau::NOTES_OUTPUT));

		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(5.08, 22.86)), module, Nodiadau::C_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(5.08, 30.48)), module, Nodiadau::CS_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(20.399, 34.29)), module, Nodiadau::IONIAN_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(5.08, 38.1)), module, Nodiadau::D_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(20.399, 44.45)), module, Nodiadau::DORIAN_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(5.08, 45.869)), module, Nodiadau::DS_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(5.08, 53.34)), module, Nodiadau::E_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(20.399, 54.61)), module, Nodiadau::PHRYGIAN_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(5.08, 60.96)), module, Nodiadau::F_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(20.399, 64.77)), module, Nodiadau::LYDIAN_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(5.08, 68.58)), module, Nodiadau::FS_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(20.399, 74.93)), module, Nodiadau::MIXOLYDIAN_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(5.08, 76.2)), module, Nodiadau::G_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(5.08, 83.82)), module, Nodiadau::GS_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(20.399, 85.09)), module, Nodiadau::AEOLIAN_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(5.08, 91.44)), module, Nodiadau::A_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(20.399, 95.25)), module, Nodiadau::LOCRIAN_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(5.08, 99.06)), module, Nodiadau::AS_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(5.08, 106.68)), module, Nodiadau::B_LIGHT));
	}
};


Model* modelNodiadau = createModel<Nodiadau, NodiadauWidget>("nodiadau");
