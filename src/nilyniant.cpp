// Nilyniant converts notes C4-D#5 of a v/oct signal to CV voltages values
// which can be used to select patterns 1-16 of Impromptu's PhraseSeq16
// or notes C4-G6 to values which select patterns 1-32 of either
// Impromptu's PhraseSeq32 or GateSeq64.
//
// Copyright (C) 2024 Shams Kitz
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "plugin.hpp"
#include <cmath>


struct Nilyniant : Module {
	enum ParamId {
		PARAMS_LEN
	};
	enum InputId {
		CV_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		SEQ16_OUTPUT,
		SEQ3264_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	Nilyniant() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configInput(CV_INPUT, "v/oct");
		configOutput(SEQ16_OUTPUT, "to phraseSeq16 seq#");
		configOutput(SEQ3264_OUTPUT, "to phraseSeq32 or gateSeq64 seq#");
	}

	void process(const ProcessArgs& args) override {
        float cv = 0.f;
        if (inputs[CV_INPUT].isConnected()){
            cv = inputs[CV_INPUT].getVoltage();
        }

        float t16 = (cv * 12) * (2.f/3.f);
        t16 = std::max(t16,0.f);
        t16 = std::min(t16,10.f);

        float t32 = ((cv * 12) * (1.f/3.f)) - 0.171f;
        t32 = std::max(t32,0.f);
        t32 = std::min(t32,10.f);

        outputs[SEQ16_OUTPUT].setChannels(1);
        outputs[SEQ3264_OUTPUT].setChannels(1);

        outputs[SEQ16_OUTPUT].setVoltage(t16);
        outputs[SEQ3264_OUTPUT].setVoltage(t32);
	}
};


struct NilyniantWidget : ModuleWidget {
	NilyniantWidget(Nilyniant* module) {
		setModule(module);
		setPanel(createPanel(
                    asset::plugin(pluginInstance, "res/nilyniant.svg"),
                    asset::plugin(pluginInstance, "res/nilyniant-dark.svg")
                    ));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 15.24)), module, Nilyniant::CV_INPUT));

		addOutput(createOutputCentered<DarkPJ301MPort>(mm2px(Vec(7.62, 93.98)), module, Nilyniant::SEQ16_OUTPUT));
		addOutput(createOutputCentered<DarkPJ301MPort>(mm2px(Vec(7.62, 111.76)), module, Nilyniant::SEQ3264_OUTPUT));
	}
};


Model* modelNilyniant = createModel<Nilyniant, NilyniantWidget>("nilyniant");
