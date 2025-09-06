#include "plugin.hpp"


struct Cloren : Module {
	enum ParamId {
		CHANS_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		VOCT_INPUT,
		GATE_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		VOCTS_OUTPUT,
		GATES_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	Cloren() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(CHANS_PARAM, 1.f, 16.f, 16.f, "Channels");
		configInput(VOCT_INPUT, "");
		configInput(GATE_INPUT, "");
		configOutput(VOCTS_OUTPUT, "");
		configOutput(GATES_OUTPUT, "");
	}

	dsp::SchmittTrigger trigger;
	int last_channels = 0;
	int chan_ptr = 0;
	float voct[16] = { 0.f };

	float voct_delay[17] = { 0.f };
	float gate_delay[17] = { 0.f };
	void process(const ProcessArgs& args) override {

		int channels = clamp((int)(params[CHANS_PARAM].getValue()),1,16);
		if (channels < last_channels) {
			if (chan_ptr >= channels) {
				voct[0] = voct[chan_ptr];
				chan_ptr = 0;
			}
			for (int c = channels; c < last_channels; c++)
				voct[c] = 0.f;
		}
		last_channels = channels;
		for (int i = 16; i > 0; i--) {
			voct_delay[i] = voct_delay[i-1];
			gate_delay[i] = gate_delay[i-1];
		}
		voct_delay[0] = inputs[VOCT_INPUT].getVoltage();
		gate_delay[0] = inputs[GATE_INPUT].getVoltage();
        
        if (trigger.process(rescale(gate_delay[16], 0.1f, 2.f, 0.f, 1.f))) {
            chan_ptr = (chan_ptr + 1) % channels;
            voct[chan_ptr] = voct_delay[0];
        }

		outputs[VOCTS_OUTPUT].setChannels(channels);
		outputs[GATES_OUTPUT].setChannels(channels);
        
		for (int c = 0; c < channels; c++) {
			outputs[VOCTS_OUTPUT].setVoltage(voct[c], c);
			if (c == chan_ptr) {
                outputs[GATES_OUTPUT].setVoltage((trigger.isHigh() ? 10.f : 0.f), c);
			}
			else {
				outputs[GATES_OUTPUT].setVoltage(0.f, c);
            }
		}
	}
};


struct ClorenWidget : ModuleWidget {
	ClorenWidget(Cloren* module) {
		setModule(module);
		setPanel(createPanel(
                    asset::plugin(pluginInstance, "res/cloren.svg"),
                    asset::plugin(pluginInstance, "res/cloren-dark.svg")
                    ));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(7.62, 81.28)), module, Cloren::CHANS_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 40.64)), module, Cloren::VOCT_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 60.96)), module, Cloren::GATE_INPUT));

		addOutput(createOutputCentered<PJ3410Port>(mm2px(Vec(7.62, 50.8)), module, Cloren::VOCTS_OUTPUT));
		addOutput(createOutputCentered<PJ3410Port>(mm2px(Vec(7.62, 71.12)), module, Cloren::GATES_OUTPUT));
	}
};


Model* modelCloren = createModel<Cloren, ClorenWidget>("cloren");
