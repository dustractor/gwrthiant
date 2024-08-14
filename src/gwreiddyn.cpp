// Gwreiddyn converts the note of a v/oct signal to an appropriate CV voltage
// for feeding into the root note parameter of various quantizer modules,
// namely Bidoo Dikt@t and several other quantizers.
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

#pragma GCC diagnostic ignored "-Warray-bounds"

struct Gwreiddyn : Module {
	enum ParamId {
		PARAMS_LEN
	};
	enum InputId {
		ROOT_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		THIRTEEN_STEP_OUTPUT,
		TWELVE_STEP_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	Gwreiddyn() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configInput(ROOT_INPUT, "");
		configOutput(THIRTEEN_STEP_OUTPUT, "");
		configOutput(TWELVE_STEP_OUTPUT, "");
	}

	void process(const ProcessArgs& args) override {
        double root_in = inputs[ROOT_INPUT].getVoltage();
        int t = (int)trunc(0.1+(std::fmod(10.f + root_in, 1.f) * 12)) % 12;
        float outv_13[12] = {
            1.0,        // C    6
            1.834,     // C#   7
            2.667,     // D    8
            3.5,       // D#   9
            4.334,     // E    10
            5.167,     // F    11
            6.0,        // F#   0
            6.834,     // G    1
            7.667,     // G#   2
            8.5,       // A    3
            9.334,     // A#   4
            10.167      // B    5
        };
        float outv_12[12] = {
            0.84,
            1.673,
            2.507,
            3.34,
            4.173,
            5.01,
            5.84,
            6.673,
            7.507,
            8.34,
            9.173,
            10.01
        };

        outputs[THIRTEEN_STEP_OUTPUT].setVoltage(outv_13[t],0);
        outputs[TWELVE_STEP_OUTPUT].setVoltage(outv_12[t],0);

        
	}
};


struct GwreiddynWidget : ModuleWidget {
	GwreiddynWidget(Gwreiddyn* module) {
		setModule(module);
		setPanel(createPanel(
                    asset::plugin(pluginInstance, "res/gwreiddyn.svg"),
                    asset::plugin(pluginInstance, "res/gwreiddyn-dark.svg")
                    ));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 12.7)), module, Gwreiddyn::ROOT_INPUT));

		addOutput(createOutputCentered<DarkPJ301MPort>(mm2px(Vec(7.62, 101.6)), module, Gwreiddyn::THIRTEEN_STEP_OUTPUT));
		addOutput(createOutputCentered<DarkPJ301MPort>(mm2px(Vec(7.62, 116.84)), module, Gwreiddyn::TWELVE_STEP_OUTPUT));

	}
};


Model* modelGwreiddyn = createModel<Gwreiddyn, GwreiddynWidget>("gwreiddyn");
