// Pysgota starts with a range of 16 evenly spaced values determined by its
// start and end parameters or inputs, applies the function sin(x*y) to each
// where y is the (possibly polyphonic) freq mult parameter, applies an offset
// and a scale to the resulting value and then applies a modulo operation
// v = A modulo B where B is taken from the (possibly polyphonic) modulus
// parameter or input and the resulting 16 values are output polyphonically.
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
#include <algorithm>

#pragma GCC diagnostic ignored "-Warray-bounds"

struct Pysgota : Module {
	enum ParamId {
		START_VOLTAGE_KNOB_PARAM,
		END_VOLTAGE_KNOB_PARAM,
		SCALE_Y_KNOB_PARAM,
		OFFSET_KNOB_PARAM,
		SCALE_KNOB_PARAM,
		MODULUS_KNOB_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		START_VOLTAGE_SOCKET_INPUT,
		END_VOLTAGE_SOCKET_INPUT,
		SCALE_Y_SOCKET_INPUT,
		OFFSET_SOCKET_INPUT,
		SCALE_SOCKET_INPUT,
		MODULUS_SOCKET_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		POLYPHONIC_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	Pysgota() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(START_VOLTAGE_KNOB_PARAM, -10.f, 10.f, -1.f, "Voltage Range Start");
		configParam(END_VOLTAGE_KNOB_PARAM, -10.f, 10.f, 1.f, "Voltage Range End");
		configParam(SCALE_Y_KNOB_PARAM, -10.f, 10.f, 1.f, "Scale Y");
		configParam(OFFSET_KNOB_PARAM, -10.f, 10.f, 0.f, "Offset");
		configParam(SCALE_KNOB_PARAM, -10.f, 10.f, 1.f, "Scale");
		configParam(MODULUS_KNOB_PARAM, 0.f, 10.f, 1.f, "Modulus");
		configInput(START_VOLTAGE_SOCKET_INPUT, "Voltage Range Start");
		configInput(END_VOLTAGE_SOCKET_INPUT, "Voltage Range End");
		configInput(SCALE_Y_SOCKET_INPUT, "Scale Y");
		configInput(OFFSET_SOCKET_INPUT, "Offset");
		configInput(SCALE_SOCKET_INPUT, "Scale");
		configInput(MODULUS_SOCKET_INPUT, "Modulus");
		configOutput(POLYPHONIC_OUTPUT, "Polyphonic");
	}

	void process(const ProcessArgs& args) override {
        float vstart = params[START_VOLTAGE_KNOB_PARAM].getValue();
        if (inputs[START_VOLTAGE_SOCKET_INPUT].isConnected()){
            vstart = inputs[START_VOLTAGE_SOCKET_INPUT].getVoltage();
        }
        float vend = params[END_VOLTAGE_KNOB_PARAM].getValue();
        if (inputs[END_VOLTAGE_SOCKET_INPUT].isConnected()){
            vend = inputs[END_VOLTAGE_SOCKET_INPUT].getVoltage();
        }
        float scale_y_t = params[SCALE_Y_KNOB_PARAM].getValue();
        float scale_y[16] = {};
        if (inputs[SCALE_Y_SOCKET_INPUT].isConnected()){
            if (inputs[SCALE_Y_SOCKET_INPUT].isPolyphonic()){
                inputs[SCALE_Y_SOCKET_INPUT].readVoltages(scale_y);
            }
            else {
                scale_y_t = inputs[SCALE_Y_SOCKET_INPUT].getVoltage();
                std::fill_n(scale_y,16,scale_y_t);
            }
        }
        else {
            std::fill_n(scale_y,16,scale_y_t);
        }
        float offset = params[OFFSET_KNOB_PARAM].getValue();
        if (inputs[OFFSET_SOCKET_INPUT].isConnected()){
            offset = inputs[OFFSET_SOCKET_INPUT].getVoltage();
        }
        float scale = params[SCALE_KNOB_PARAM].getValue();
        if (inputs[SCALE_SOCKET_INPUT].isConnected()){
            scale = inputs[SCALE_SOCKET_INPUT].getVoltage();
        }
        float modulus_t = params[MODULUS_KNOB_PARAM].getValue();
        float modulus[16] = {};
        if (inputs[MODULUS_SOCKET_INPUT].isConnected()){
            if (inputs[MODULUS_SOCKET_INPUT].isPolyphonic()){
                inputs[MODULUS_SOCKET_INPUT].readVoltages(modulus);
            }
            else {
                modulus_t = inputs[MODULUS_SOCKET_INPUT].getVoltage();
                std::fill_n(modulus,16,modulus_t);
            }
        }
        else {
            std::fill_n(modulus,16,modulus_t);
        }
        float increment = (vend - vstart) / (PORT_MAX_CHANNELS - 1);
        float range[PORT_MAX_CHANNELS];
        if (!(scale == 0)){
            for (int i=0; i<PORT_MAX_CHANNELS; i++){
                range[i] = fmod((offset + sin(scale_y[i] * (vstart + increment * i))) * scale, (modulus[i]==0?0.001:modulus[i]));
            }
        }
        outputs[POLYPHONIC_OUTPUT].setChannels(PORT_MAX_CHANNELS);
        outputs[POLYPHONIC_OUTPUT].writeVoltages(range);
	}
};


struct PysgotaWidget : ModuleWidget {
	PysgotaWidget(Pysgota* module) {
		setModule(module);
		setPanel(createPanel(
                    asset::plugin(pluginInstance, "res/pysgota.svg"),
                    asset::plugin(pluginInstance, "res/pysgota-dark.svg")
                    ));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(10.16, 10.16)), module, Pysgota::START_VOLTAGE_KNOB_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(20.32, 10.16)), module, Pysgota::END_VOLTAGE_KNOB_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(15.24, 35.56)), module, Pysgota::SCALE_Y_KNOB_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(10.16, 60.96)), module, Pysgota::OFFSET_KNOB_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(20.32, 60.96)), module, Pysgota::SCALE_KNOB_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(15.24, 86.36)), module, Pysgota::MODULUS_KNOB_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(10.16, 22.86)), module, Pysgota::START_VOLTAGE_SOCKET_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(20.32, 22.811)), module, Pysgota::END_VOLTAGE_SOCKET_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(15.24, 48.26)), module, Pysgota::SCALE_Y_SOCKET_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(10.16, 73.66)), module, Pysgota::OFFSET_SOCKET_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(20.32, 73.66)), module, Pysgota::SCALE_SOCKET_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(15.24, 99.06)), module, Pysgota::MODULUS_SOCKET_INPUT));

		addOutput(createOutputCentered<DarkPJ301MPort>(mm2px(Vec(15.24, 116.84)), module, Pysgota::POLYPHONIC_OUTPUT));
	}
};


Model* modelPysgota = createModel<Pysgota, PysgotaWidget>("pysgota");
