#include "plugin.hpp"

#pragma GCC diagnostic ignored "-Warray-bounds"

struct Cyfeiriad : Module {
	enum ParamId {
		PARAMS_LEN
	};
	enum InputId {
		GATES_IN_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		ISEVEN_OUTPUT,
		LESSTHANTWO_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	Cyfeiriad() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configInput(GATES_IN_INPUT, "Polyphonic Gates");
		configOutput(ISEVEN_OUTPUT, "10V if number of active gates is even.");
		configOutput(LESSTHANTWO_OUTPUT, "10V if number of active gates is less than two.");
	}

	void process(const ProcessArgs& args) override {
        float even_out_val = 10.f;
        float lt2_out_val = 10.f;
        float gates_in_t[16] = {};
        int gatecount = 0;
        if (inputs[GATES_IN_INPUT].isConnected()){
            if (inputs[GATES_IN_INPUT].isPolyphonic()){
                inputs[GATES_IN_INPUT].readVoltages(gates_in_t);
            }
        }

        for (int i=0;i<PORT_MAX_CHANNELS;i++){
            if (gates_in_t[i] >= 5.f){
                gatecount++;
            }
        }
        if ((gatecount%2)==0){
            even_out_val = 10.f;
        }
        else {
            even_out_val = 0.f;
        }
        if (gatecount < 2){
            lt2_out_val = 10.f;
        }
        else {
            lt2_out_val = 0.f;
        }
        outputs[ISEVEN_OUTPUT].setChannels(1);
        outputs[ISEVEN_OUTPUT].setVoltage(even_out_val);
        outputs[LESSTHANTWO_OUTPUT].setChannels(1);
        outputs[LESSTHANTWO_OUTPUT].setVoltage(lt2_out_val);

	}
};


struct CyfeiriadWidget : ModuleWidget {
	CyfeiriadWidget(Cyfeiriad* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/cyfeiriad.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(10.16, 12.7)), module, Cyfeiriad::GATES_IN_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(10.16, 93.98)), module, Cyfeiriad::ISEVEN_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(10.16, 114.3)), module, Cyfeiriad::LESSTHANTWO_OUTPUT));
	}
};


Model* modelCyfeiriad = createModel<Cyfeiriad, CyfeiriadWidget>("cyfeiriad");
