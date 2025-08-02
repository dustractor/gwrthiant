#include "plugin.hpp"


#pragma GCC diagnostic ignored "-Warray-bounds"

struct Lithr : Module {
	enum ParamId {

		LIMITA_MIN_PARAM,
		LIMITA_MAX_PARAM,
		LIMITB_MIN_PARAM,
		LIMITB_MAX_PARAM,
		LIMITC_MIN_PARAM,
		LIMITC_MAX_PARAM,
		LIMITD_MIN_PARAM,
		LIMITD_MAX_PARAM,

		SLIDERA1_PARAM,
		SLIDERA2_PARAM,
		SLIDERA3_PARAM,
		SLIDERA4_PARAM,
		SLIDERA5_PARAM,
		SLIDERA6_PARAM,
		SLIDERA7_PARAM,
		SLIDERA8_PARAM,
		SLIDERA9_PARAM,
		SLIDERA10_PARAM,
		SLIDERA11_PARAM,
		SLIDERA12_PARAM,
		SLIDERA13_PARAM,
		SLIDERA14_PARAM,
		SLIDERA15_PARAM,
		SLIDERA16_PARAM,
		SLIDERB1_PARAM,
		SLIDERB2_PARAM,
		SLIDERB3_PARAM,
		SLIDERB4_PARAM,
		SLIDERB5_PARAM,
		SLIDERB6_PARAM,
		SLIDERB7_PARAM,
		SLIDERB8_PARAM,
		SLIDERB9_PARAM,
		SLIDERB10_PARAM,
		SLIDERB11_PARAM,
		SLIDERB12_PARAM,
		SLIDERB13_PARAM,
		SLIDERB14_PARAM,
		SLIDERB15_PARAM,
		SLIDERB16_PARAM,
		SLIDERC1_PARAM,
		SLIDERC2_PARAM,
		SLIDERC3_PARAM,
		SLIDERC4_PARAM,
		SLIDERC5_PARAM,
		SLIDERC6_PARAM,
		SLIDERC7_PARAM,
		SLIDERC8_PARAM,
		SLIDERC9_PARAM,
		SLIDERC10_PARAM,
		SLIDERC11_PARAM,
		SLIDERC12_PARAM,
		SLIDERC13_PARAM,
		SLIDERC14_PARAM,
		SLIDERC15_PARAM,
		SLIDERC16_PARAM,
		SLIDERD1_PARAM,
		SLIDERD2_PARAM,
		SLIDERD3_PARAM,
		SLIDERD4_PARAM,
		SLIDERD5_PARAM,
		SLIDERD6_PARAM,
		SLIDERD7_PARAM,
		SLIDERD8_PARAM,
		SLIDERD9_PARAM,
		SLIDERD10_PARAM,
		SLIDERD11_PARAM,
		SLIDERD12_PARAM,
		SLIDERD13_PARAM,
		SLIDERD14_PARAM,
		SLIDERD15_PARAM,
		SLIDERD16_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		INPUTS_LEN
	};
	enum OutputId {
		OUTPUTA_OUTPUT,
		OUTPUTB_OUTPUT,
		OUTPUTC_OUTPUT,
		OUTPUTD_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	Lithr() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);

		configParam(LIMITA_MIN_PARAM, -10.f, 10.f, -10.f, "Min A");
		configParam(LIMITA_MAX_PARAM, -10.f, 10.f, 10.f, "Max A");
		configParam(LIMITB_MIN_PARAM, -10.f, 10.f, -10.f, "Min B");
		configParam(LIMITB_MAX_PARAM, -10.f, 10.f, 10.f, "Max B");
		configParam(LIMITC_MIN_PARAM, -10.f, 10.f, -10.f, "Min C");
		configParam(LIMITC_MAX_PARAM, -10.f, 10.f, 10.f, "Max C");
		configParam(LIMITD_MIN_PARAM, -10.f, 10.f, -10.f, "Min D");
		configParam(LIMITD_MAX_PARAM, -10.f, 10.f, 10.f, "Max D");

		configParam(SLIDERA1_PARAM,  -10.f, 10.f, 0.f, "A1");
		configParam(SLIDERA2_PARAM,  -10.f, 10.f, 0.f, "A2");
		configParam(SLIDERA3_PARAM,  -10.f, 10.f, 0.f, "A3");
		configParam(SLIDERA4_PARAM,  -10.f, 10.f, 0.f, "A4");
		configParam(SLIDERA5_PARAM,  -10.f, 10.f, 0.f, "A5");
		configParam(SLIDERA6_PARAM,  -10.f, 10.f, 0.f, "A6");
		configParam(SLIDERA7_PARAM,  -10.f, 10.f, 0.f, "A7");
		configParam(SLIDERA8_PARAM,  -10.f, 10.f, 0.f, "A8");
		configParam(SLIDERA9_PARAM,  -10.f, 10.f, 0.f, "A9");
		configParam(SLIDERA10_PARAM, -10.f, 10.f, 0.f, "A10");
		configParam(SLIDERA11_PARAM, -10.f, 10.f, 0.f, "A11");
		configParam(SLIDERA12_PARAM, -10.f, 10.f, 0.f, "A12");
		configParam(SLIDERA13_PARAM, -10.f, 10.f, 0.f, "A13");
		configParam(SLIDERA14_PARAM, -10.f, 10.f, 0.f, "A14");
		configParam(SLIDERA15_PARAM, -10.f, 10.f, 0.f, "A15");
		configParam(SLIDERA16_PARAM, -10.f, 10.f, 0.f, "A16");
		configParam(SLIDERB1_PARAM,  -10.f, 10.f, 0.f, "B1");
		configParam(SLIDERB2_PARAM,  -10.f, 10.f, 0.f, "B2");
		configParam(SLIDERB3_PARAM,  -10.f, 10.f, 0.f, "B3");
		configParam(SLIDERB4_PARAM,  -10.f, 10.f, 0.f, "B4");
		configParam(SLIDERB5_PARAM,  -10.f, 10.f, 0.f, "B5");
		configParam(SLIDERB6_PARAM,  -10.f, 10.f, 0.f, "B6");
		configParam(SLIDERB7_PARAM,  -10.f, 10.f, 0.f, "B7");
		configParam(SLIDERB8_PARAM,  -10.f, 10.f, 0.f, "B8");
		configParam(SLIDERB9_PARAM,  -10.f, 10.f, 0.f, "B9");
		configParam(SLIDERB10_PARAM, -10.f, 10.f, 0.f, "B10");
		configParam(SLIDERB11_PARAM, -10.f, 10.f, 0.f, "B11");
		configParam(SLIDERB12_PARAM, -10.f, 10.f, 0.f, "B12");
		configParam(SLIDERB13_PARAM, -10.f, 10.f, 0.f, "B13");
		configParam(SLIDERB14_PARAM, -10.f, 10.f, 0.f, "B14");
		configParam(SLIDERB15_PARAM, -10.f, 10.f, 0.f, "B15");
		configParam(SLIDERB16_PARAM, -10.f, 10.f, 0.f, "B16");
		configParam(SLIDERC1_PARAM,  -10.f, 10.f, 0.f, "C1");
		configParam(SLIDERC2_PARAM,  -10.f, 10.f, 0.f, "C2");
		configParam(SLIDERC3_PARAM,  -10.f, 10.f, 0.f, "C3");
		configParam(SLIDERC4_PARAM,  -10.f, 10.f, 0.f, "C4");
		configParam(SLIDERC5_PARAM,  -10.f, 10.f, 0.f, "C5");
		configParam(SLIDERC6_PARAM,  -10.f, 10.f, 0.f, "C6");
		configParam(SLIDERC7_PARAM,  -10.f, 10.f, 0.f, "C7");
		configParam(SLIDERC8_PARAM,  -10.f, 10.f, 0.f, "C8");
		configParam(SLIDERC9_PARAM,  -10.f, 10.f, 0.f, "C9");
		configParam(SLIDERC10_PARAM, -10.f, 10.f, 0.f, "C10");
		configParam(SLIDERC11_PARAM, -10.f, 10.f, 0.f, "C11");
		configParam(SLIDERC12_PARAM, -10.f, 10.f, 0.f, "C12");
		configParam(SLIDERC13_PARAM, -10.f, 10.f, 0.f, "C13");
		configParam(SLIDERC14_PARAM, -10.f, 10.f, 0.f, "C14");
		configParam(SLIDERC15_PARAM, -10.f, 10.f, 0.f, "C15");
		configParam(SLIDERC16_PARAM, -10.f, 10.f, 0.f, "C16");
		configParam(SLIDERD1_PARAM,  -10.f, 10.f, 0.f, "D1");
		configParam(SLIDERD2_PARAM,  -10.f, 10.f, 0.f, "D2");
		configParam(SLIDERD3_PARAM,  -10.f, 10.f, 0.f, "D3");
		configParam(SLIDERD4_PARAM,  -10.f, 10.f, 0.f, "D4");
		configParam(SLIDERD5_PARAM,  -10.f, 10.f, 0.f, "D5");
		configParam(SLIDERD6_PARAM,  -10.f, 10.f, 0.f, "D6");
		configParam(SLIDERD7_PARAM,  -10.f, 10.f, 0.f, "D7");
		configParam(SLIDERD8_PARAM,  -10.f, 10.f, 0.f, "D8");
		configParam(SLIDERD9_PARAM,  -10.f, 10.f, 0.f, "D9");
		configParam(SLIDERD10_PARAM, -10.f, 10.f, 0.f, "D10");
		configParam(SLIDERD11_PARAM, -10.f, 10.f, 0.f, "D11");
		configParam(SLIDERD12_PARAM, -10.f, 10.f, 0.f, "D12");
		configParam(SLIDERD13_PARAM, -10.f, 10.f, 0.f, "D13");
		configParam(SLIDERD14_PARAM, -10.f, 10.f, 0.f, "D14");
		configParam(SLIDERD15_PARAM, -10.f, 10.f, 0.f, "D15");
		configParam(SLIDERD16_PARAM, -10.f, 10.f, 0.f, "D16");
		configOutput(OUTPUTA_OUTPUT, "A");
		configOutput(OUTPUTB_OUTPUT, "B");
		configOutput(OUTPUTC_OUTPUT, "C");
		configOutput(OUTPUTD_OUTPUT, "D");
	}

	void process(const ProcessArgs& args) override {
        outputs[OUTPUTA_OUTPUT].setChannels(16);
        outputs[OUTPUTB_OUTPUT].setChannels(16);
        outputs[OUTPUTC_OUTPUT].setChannels(16);
        outputs[OUTPUTD_OUTPUT].setChannels(16);

        float limit_a_min = params[LIMITA_MIN_PARAM].getValue();
        float limit_a_max = params[LIMITA_MAX_PARAM].getValue();
        float limit_b_min = params[LIMITB_MIN_PARAM].getValue();
        float limit_b_max = params[LIMITB_MAX_PARAM].getValue();
        float limit_c_min = params[LIMITC_MIN_PARAM].getValue();
        float limit_c_max = params[LIMITC_MAX_PARAM].getValue();
        float limit_d_min = params[LIMITD_MIN_PARAM].getValue();
        float limit_d_max = params[LIMITD_MAX_PARAM].getValue();

        outputs[OUTPUTA_OUTPUT].setVoltage(math::rescale(params[SLIDERA1_PARAM].getValue(),-10.0f,10.0f,limit_a_min,limit_a_max),0);
        outputs[OUTPUTA_OUTPUT].setVoltage(math::rescale(params[SLIDERA2_PARAM].getValue(),-10.0f,10.0f,limit_a_min,limit_a_max),1);
        outputs[OUTPUTA_OUTPUT].setVoltage(math::rescale(params[SLIDERA3_PARAM].getValue(),-10.0f,10.0f,limit_a_min,limit_a_max),2);
        outputs[OUTPUTA_OUTPUT].setVoltage(math::rescale(params[SLIDERA4_PARAM].getValue(),-10.0f,10.0f,limit_a_min,limit_a_max),3);
        outputs[OUTPUTA_OUTPUT].setVoltage(math::rescale(params[SLIDERA5_PARAM].getValue(),-10.0f,10.0f,limit_a_min,limit_a_max),4);
        outputs[OUTPUTA_OUTPUT].setVoltage(math::rescale(params[SLIDERA6_PARAM].getValue(),-10.0f,10.0f,limit_a_min,limit_a_max),5);
        outputs[OUTPUTA_OUTPUT].setVoltage(math::rescale(params[SLIDERA7_PARAM].getValue(),-10.0f,10.0f,limit_a_min,limit_a_max),6);
        outputs[OUTPUTA_OUTPUT].setVoltage(math::rescale(params[SLIDERA8_PARAM].getValue(),-10.0f,10.0f,limit_a_min,limit_a_max),7);
        outputs[OUTPUTA_OUTPUT].setVoltage(math::rescale(params[SLIDERA9_PARAM].getValue(),-10.0f,10.0f,limit_a_min,limit_a_max),8);
        outputs[OUTPUTA_OUTPUT].setVoltage(math::rescale(params[SLIDERA10_PARAM].getValue(),-10.0f,10.0f,limit_a_min,limit_a_max),9);
        outputs[OUTPUTA_OUTPUT].setVoltage(math::rescale(params[SLIDERA11_PARAM].getValue(),-10.0f,10.0f,limit_a_min,limit_a_max),10);
        outputs[OUTPUTA_OUTPUT].setVoltage(math::rescale(params[SLIDERA12_PARAM].getValue(),-10.0f,10.0f,limit_a_min,limit_a_max),11);
        outputs[OUTPUTA_OUTPUT].setVoltage(math::rescale(params[SLIDERA13_PARAM].getValue(),-10.0f,10.0f,limit_a_min,limit_a_max),12);
        outputs[OUTPUTA_OUTPUT].setVoltage(math::rescale(params[SLIDERA14_PARAM].getValue(),-10.0f,10.0f,limit_a_min,limit_a_max),13);
        outputs[OUTPUTA_OUTPUT].setVoltage(math::rescale(params[SLIDERA15_PARAM].getValue(),-10.0f,10.0f,limit_a_min,limit_a_max),14);
        outputs[OUTPUTA_OUTPUT].setVoltage(math::rescale(params[SLIDERA16_PARAM].getValue(),-10.0f,10.0f,limit_a_min,limit_a_max),15);

        outputs[OUTPUTB_OUTPUT].setVoltage(math::rescale(params[SLIDERB1_PARAM].getValue(),-10.0f,10.0f,limit_b_min,limit_b_max),0);
        outputs[OUTPUTB_OUTPUT].setVoltage(math::rescale(params[SLIDERB2_PARAM].getValue(),-10.0f,10.0f,limit_b_min,limit_b_max),1);
        outputs[OUTPUTB_OUTPUT].setVoltage(math::rescale(params[SLIDERB3_PARAM].getValue(),-10.0f,10.0f,limit_b_min,limit_b_max),2);
        outputs[OUTPUTB_OUTPUT].setVoltage(math::rescale(params[SLIDERB4_PARAM].getValue(),-10.0f,10.0f,limit_b_min,limit_b_max),3);
        outputs[OUTPUTB_OUTPUT].setVoltage(math::rescale(params[SLIDERB5_PARAM].getValue(),-10.0f,10.0f,limit_b_min,limit_b_max),4);
        outputs[OUTPUTB_OUTPUT].setVoltage(math::rescale(params[SLIDERB6_PARAM].getValue(),-10.0f,10.0f,limit_b_min,limit_b_max),5);
        outputs[OUTPUTB_OUTPUT].setVoltage(math::rescale(params[SLIDERB7_PARAM].getValue(),-10.0f,10.0f,limit_b_min,limit_b_max),6);
        outputs[OUTPUTB_OUTPUT].setVoltage(math::rescale(params[SLIDERB8_PARAM].getValue(),-10.0f,10.0f,limit_b_min,limit_b_max),7);
        outputs[OUTPUTB_OUTPUT].setVoltage(math::rescale(params[SLIDERB9_PARAM].getValue(),-10.0f,10.0f,limit_b_min,limit_b_max),8);
        outputs[OUTPUTB_OUTPUT].setVoltage(math::rescale(params[SLIDERB10_PARAM].getValue(),-10.0f,10.0f,limit_b_min,limit_b_max),9);
        outputs[OUTPUTB_OUTPUT].setVoltage(math::rescale(params[SLIDERB11_PARAM].getValue(),-10.0f,10.0f,limit_b_min,limit_b_max),10);
        outputs[OUTPUTB_OUTPUT].setVoltage(math::rescale(params[SLIDERB12_PARAM].getValue(),-10.0f,10.0f,limit_b_min,limit_b_max),11);
        outputs[OUTPUTB_OUTPUT].setVoltage(math::rescale(params[SLIDERB13_PARAM].getValue(),-10.0f,10.0f,limit_b_min,limit_b_max),12);
        outputs[OUTPUTB_OUTPUT].setVoltage(math::rescale(params[SLIDERB14_PARAM].getValue(),-10.0f,10.0f,limit_b_min,limit_b_max),13);
        outputs[OUTPUTB_OUTPUT].setVoltage(math::rescale(params[SLIDERB15_PARAM].getValue(),-10.0f,10.0f,limit_b_min,limit_b_max),14);
        outputs[OUTPUTB_OUTPUT].setVoltage(math::rescale(params[SLIDERB16_PARAM].getValue(),-10.0f,10.0f,limit_b_min,limit_b_max),15);

        outputs[OUTPUTC_OUTPUT].setVoltage(math::rescale(params[SLIDERC1_PARAM].getValue(),-10.0f,10.0f,limit_c_min,limit_c_max),0);
        outputs[OUTPUTC_OUTPUT].setVoltage(math::rescale(params[SLIDERC2_PARAM].getValue(),-10.0f,10.0f,limit_c_min,limit_c_max),1);
        outputs[OUTPUTC_OUTPUT].setVoltage(math::rescale(params[SLIDERC3_PARAM].getValue(),-10.0f,10.0f,limit_c_min,limit_c_max),2);
        outputs[OUTPUTC_OUTPUT].setVoltage(math::rescale(params[SLIDERC4_PARAM].getValue(),-10.0f,10.0f,limit_c_min,limit_c_max),3);
        outputs[OUTPUTC_OUTPUT].setVoltage(math::rescale(params[SLIDERC5_PARAM].getValue(),-10.0f,10.0f,limit_c_min,limit_c_max),4);
        outputs[OUTPUTC_OUTPUT].setVoltage(math::rescale(params[SLIDERC6_PARAM].getValue(),-10.0f,10.0f,limit_c_min,limit_c_max),5);
        outputs[OUTPUTC_OUTPUT].setVoltage(math::rescale(params[SLIDERC7_PARAM].getValue(),-10.0f,10.0f,limit_c_min,limit_c_max),6);
        outputs[OUTPUTC_OUTPUT].setVoltage(math::rescale(params[SLIDERC8_PARAM].getValue(),-10.0f,10.0f,limit_c_min,limit_c_max),7);
        outputs[OUTPUTC_OUTPUT].setVoltage(math::rescale(params[SLIDERC9_PARAM].getValue(),-10.0f,10.0f,limit_c_min,limit_c_max),8);
        outputs[OUTPUTC_OUTPUT].setVoltage(math::rescale(params[SLIDERC10_PARAM].getValue(),-10.0f,10.0f,limit_c_min,limit_c_max),9);
        outputs[OUTPUTC_OUTPUT].setVoltage(math::rescale(params[SLIDERC11_PARAM].getValue(),-10.0f,10.0f,limit_c_min,limit_c_max),10);
        outputs[OUTPUTC_OUTPUT].setVoltage(math::rescale(params[SLIDERC12_PARAM].getValue(),-10.0f,10.0f,limit_c_min,limit_c_max),11);
        outputs[OUTPUTC_OUTPUT].setVoltage(math::rescale(params[SLIDERC13_PARAM].getValue(),-10.0f,10.0f,limit_c_min,limit_c_max),12);
        outputs[OUTPUTC_OUTPUT].setVoltage(math::rescale(params[SLIDERC14_PARAM].getValue(),-10.0f,10.0f,limit_c_min,limit_c_max),13);
        outputs[OUTPUTC_OUTPUT].setVoltage(math::rescale(params[SLIDERC15_PARAM].getValue(),-10.0f,10.0f,limit_c_min,limit_c_max),14);
        outputs[OUTPUTC_OUTPUT].setVoltage(math::rescale(params[SLIDERC16_PARAM].getValue(),-10.0f,10.0f,limit_c_min,limit_c_max),15);

        outputs[OUTPUTD_OUTPUT].setVoltage(math::rescale(params[SLIDERD1_PARAM].getValue(),-10.0f,10.0f,limit_d_min,limit_d_max),0);
        outputs[OUTPUTD_OUTPUT].setVoltage(math::rescale(params[SLIDERD2_PARAM].getValue(),-10.0f,10.0f,limit_d_min,limit_d_max),1);
        outputs[OUTPUTD_OUTPUT].setVoltage(math::rescale(params[SLIDERD3_PARAM].getValue(),-10.0f,10.0f,limit_d_min,limit_d_max),2);
        outputs[OUTPUTD_OUTPUT].setVoltage(math::rescale(params[SLIDERD4_PARAM].getValue(),-10.0f,10.0f,limit_d_min,limit_d_max),3);
        outputs[OUTPUTD_OUTPUT].setVoltage(math::rescale(params[SLIDERD5_PARAM].getValue(),-10.0f,10.0f,limit_d_min,limit_d_max),4);
        outputs[OUTPUTD_OUTPUT].setVoltage(math::rescale(params[SLIDERD6_PARAM].getValue(),-10.0f,10.0f,limit_d_min,limit_d_max),5);
        outputs[OUTPUTD_OUTPUT].setVoltage(math::rescale(params[SLIDERD7_PARAM].getValue(),-10.0f,10.0f,limit_d_min,limit_d_max),6);
        outputs[OUTPUTD_OUTPUT].setVoltage(math::rescale(params[SLIDERD8_PARAM].getValue(),-10.0f,10.0f,limit_d_min,limit_d_max),7);
        outputs[OUTPUTD_OUTPUT].setVoltage(math::rescale(params[SLIDERD9_PARAM].getValue(),-10.0f,10.0f,limit_d_min,limit_d_max),8);
        outputs[OUTPUTD_OUTPUT].setVoltage(math::rescale(params[SLIDERD10_PARAM].getValue(),-10.0f,10.0f,limit_d_min,limit_d_max),9);
        outputs[OUTPUTD_OUTPUT].setVoltage(math::rescale(params[SLIDERD11_PARAM].getValue(),-10.0f,10.0f,limit_d_min,limit_d_max),10);
        outputs[OUTPUTD_OUTPUT].setVoltage(math::rescale(params[SLIDERD12_PARAM].getValue(),-10.0f,10.0f,limit_d_min,limit_d_max),11);
        outputs[OUTPUTD_OUTPUT].setVoltage(math::rescale(params[SLIDERD13_PARAM].getValue(),-10.0f,10.0f,limit_d_min,limit_d_max),12);
        outputs[OUTPUTD_OUTPUT].setVoltage(math::rescale(params[SLIDERD14_PARAM].getValue(),-10.0f,10.0f,limit_d_min,limit_d_max),13);
        outputs[OUTPUTD_OUTPUT].setVoltage(math::rescale(params[SLIDERD15_PARAM].getValue(),-10.0f,10.0f,limit_d_min,limit_d_max),14);
        outputs[OUTPUTD_OUTPUT].setVoltage(math::rescale(params[SLIDERD16_PARAM].getValue(),-10.0f,10.0f,limit_d_min,limit_d_max),15);
	}
};


struct LithrWidget : ModuleWidget {
	LithrWidget(Lithr* module) {
		setModule(module);
		setPanel(createPanel(
                    asset::plugin(pluginInstance, "res/lithr.svg"),
                    asset::plugin(pluginInstance, "res/lithr-dark.svg")
                    ));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(134.62, 7.62)), module, Lithr::LIMITA_MIN_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(134.62, 27.94)), module, Lithr::LIMITA_MAX_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(134.62, 38.1)), module, Lithr::LIMITB_MIN_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(134.62, 58.42)), module, Lithr::LIMITB_MAX_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(134.62, 68.58)), module, Lithr::LIMITC_MIN_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(134.62, 88.9)), module, Lithr::LIMITC_MAX_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(134.62, 99.06)), module, Lithr::LIMITD_MIN_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(134.62, 119.38)), module, Lithr::LIMITD_MAX_PARAM));

		addParam(createParamCentered<LEDSliderBlue>(mm2px(Vec(10.16, 17.78)), module, Lithr::SLIDERA1_PARAM));
		addParam(createParamCentered<LEDSliderBlue>(mm2px(Vec(17.78, 17.78)), module, Lithr::SLIDERA2_PARAM));
		addParam(createParamCentered<LEDSliderBlue>(mm2px(Vec(25.4, 17.78)), module, Lithr::SLIDERA3_PARAM));
		addParam(createParamCentered<LEDSliderBlue>(mm2px(Vec(33.02, 17.78)), module, Lithr::SLIDERA4_PARAM));
		addParam(createParamCentered<LEDSliderRed>(mm2px(Vec(40.64, 17.78)), module, Lithr::SLIDERA5_PARAM));
		addParam(createParamCentered<LEDSliderRed>(mm2px(Vec(48.26, 17.78)), module, Lithr::SLIDERA6_PARAM));
		addParam(createParamCentered<LEDSliderRed>(mm2px(Vec(55.88, 17.78)), module, Lithr::SLIDERA7_PARAM));
		addParam(createParamCentered<LEDSliderRed>(mm2px(Vec(63.5, 17.78)), module, Lithr::SLIDERA8_PARAM));
		addParam(createParamCentered<LEDSliderBlue>(mm2px(Vec(71.12, 17.78)), module, Lithr::SLIDERA9_PARAM));
		addParam(createParamCentered<LEDSliderBlue>(mm2px(Vec(78.74, 17.78)), module, Lithr::SLIDERA10_PARAM));
		addParam(createParamCentered<LEDSliderBlue>(mm2px(Vec(86.36, 17.78)), module, Lithr::SLIDERA11_PARAM));
		addParam(createParamCentered<LEDSliderBlue>(mm2px(Vec(93.98, 17.78)), module, Lithr::SLIDERA12_PARAM));
		addParam(createParamCentered<LEDSliderRed>(mm2px(Vec(101.6, 17.78)), module, Lithr::SLIDERA13_PARAM));
		addParam(createParamCentered<LEDSliderRed>(mm2px(Vec(109.22, 17.78)), module, Lithr::SLIDERA14_PARAM));
		addParam(createParamCentered<LEDSliderRed>(mm2px(Vec(116.84, 17.78)), module, Lithr::SLIDERA15_PARAM));
		addParam(createParamCentered<LEDSliderRed>(mm2px(Vec(124.46, 17.78)), module, Lithr::SLIDERA16_PARAM));

		addParam(createParamCentered<LEDSliderRed>(mm2px(Vec(10.16, 48.26)), module, Lithr::SLIDERB1_PARAM));
		addParam(createParamCentered<LEDSliderRed>(mm2px(Vec(17.78, 48.26)), module, Lithr::SLIDERB2_PARAM));
		addParam(createParamCentered<LEDSliderRed>(mm2px(Vec(25.4, 48.26)), module, Lithr::SLIDERB3_PARAM));
		addParam(createParamCentered<LEDSliderRed>(mm2px(Vec(33.02, 48.26)), module, Lithr::SLIDERB4_PARAM));
		addParam(createParamCentered<LEDSliderBlue>(mm2px(Vec(40.64, 48.26)), module, Lithr::SLIDERB5_PARAM));
		addParam(createParamCentered<LEDSliderBlue>(mm2px(Vec(48.26, 48.26)), module, Lithr::SLIDERB6_PARAM));
		addParam(createParamCentered<LEDSliderBlue>(mm2px(Vec(55.88, 48.26)), module, Lithr::SLIDERB7_PARAM));
		addParam(createParamCentered<LEDSliderBlue>(mm2px(Vec(63.5, 48.26)), module, Lithr::SLIDERB8_PARAM));
		addParam(createParamCentered<LEDSliderRed>(mm2px(Vec(71.12, 48.26)), module, Lithr::SLIDERB9_PARAM));
		addParam(createParamCentered<LEDSliderRed>(mm2px(Vec(78.74, 48.26)), module, Lithr::SLIDERB10_PARAM));
		addParam(createParamCentered<LEDSliderRed>(mm2px(Vec(86.36, 48.26)), module, Lithr::SLIDERB11_PARAM));
		addParam(createParamCentered<LEDSliderRed>(mm2px(Vec(93.98, 48.26)), module, Lithr::SLIDERB12_PARAM));
		addParam(createParamCentered<LEDSliderBlue>(mm2px(Vec(101.6, 48.26)), module, Lithr::SLIDERB13_PARAM));
		addParam(createParamCentered<LEDSliderBlue>(mm2px(Vec(109.22, 48.26)), module, Lithr::SLIDERB14_PARAM));
		addParam(createParamCentered<LEDSliderBlue>(mm2px(Vec(116.84, 48.26)), module, Lithr::SLIDERB15_PARAM));
		addParam(createParamCentered<LEDSliderBlue>(mm2px(Vec(124.46, 48.26)), module, Lithr::SLIDERB16_PARAM));

		addParam(createParamCentered<LEDSliderGreen>(mm2px(Vec(10.16, 78.74)), module, Lithr::SLIDERC1_PARAM));
		addParam(createParamCentered<LEDSliderGreen>(mm2px(Vec(17.78, 78.74)), module, Lithr::SLIDERC2_PARAM));
		addParam(createParamCentered<LEDSliderGreen>(mm2px(Vec(25.4, 78.74)), module, Lithr::SLIDERC3_PARAM));
		addParam(createParamCentered<LEDSliderGreen>(mm2px(Vec(33.02, 78.74)), module, Lithr::SLIDERC4_PARAM));
		addParam(createParamCentered<LEDSliderRed>(mm2px(Vec(40.64, 78.74)), module, Lithr::SLIDERC5_PARAM));
		addParam(createParamCentered<LEDSliderRed>(mm2px(Vec(48.26, 78.74)), module, Lithr::SLIDERC6_PARAM));
		addParam(createParamCentered<LEDSliderRed>(mm2px(Vec(55.88, 78.74)), module, Lithr::SLIDERC7_PARAM));
		addParam(createParamCentered<LEDSliderRed>(mm2px(Vec(63.5, 78.74)), module, Lithr::SLIDERC8_PARAM));
		addParam(createParamCentered<LEDSliderGreen>(mm2px(Vec(71.12, 78.74)), module, Lithr::SLIDERC9_PARAM));
		addParam(createParamCentered<LEDSliderGreen>(mm2px(Vec(78.74, 78.74)), module, Lithr::SLIDERC10_PARAM));
		addParam(createParamCentered<LEDSliderGreen>(mm2px(Vec(86.36, 78.74)), module, Lithr::SLIDERC11_PARAM));
		addParam(createParamCentered<LEDSliderGreen>(mm2px(Vec(93.98, 78.74)), module, Lithr::SLIDERC12_PARAM));
		addParam(createParamCentered<LEDSliderRed>(mm2px(Vec(101.6, 78.74)), module, Lithr::SLIDERC13_PARAM));
		addParam(createParamCentered<LEDSliderRed>(mm2px(Vec(109.22, 78.74)), module, Lithr::SLIDERC14_PARAM));
		addParam(createParamCentered<LEDSliderRed>(mm2px(Vec(116.84, 78.74)), module, Lithr::SLIDERC15_PARAM));
		addParam(createParamCentered<LEDSliderRed>(mm2px(Vec(124.46, 78.74)), module, Lithr::SLIDERC16_PARAM));

		addParam(createParamCentered<LEDSliderRed>(mm2px(Vec(10.16, 109.22)), module, Lithr::SLIDERD1_PARAM));
		addParam(createParamCentered<LEDSliderRed>(mm2px(Vec(17.78, 109.22)), module, Lithr::SLIDERD2_PARAM));
		addParam(createParamCentered<LEDSliderRed>(mm2px(Vec(25.4, 109.22)), module, Lithr::SLIDERD3_PARAM));
		addParam(createParamCentered<LEDSliderRed>(mm2px(Vec(33.02, 109.22)), module, Lithr::SLIDERD4_PARAM));
		addParam(createParamCentered<LEDSliderGreen>(mm2px(Vec(40.64, 109.22)), module, Lithr::SLIDERD5_PARAM));
		addParam(createParamCentered<LEDSliderGreen>(mm2px(Vec(48.26, 109.22)), module, Lithr::SLIDERD6_PARAM));
		addParam(createParamCentered<LEDSliderGreen>(mm2px(Vec(55.88, 109.22)), module, Lithr::SLIDERD7_PARAM));
		addParam(createParamCentered<LEDSliderGreen>(mm2px(Vec(63.5, 109.22)), module, Lithr::SLIDERD8_PARAM));
		addParam(createParamCentered<LEDSliderRed>(mm2px(Vec(71.12, 109.22)), module, Lithr::SLIDERD9_PARAM));
		addParam(createParamCentered<LEDSliderRed>(mm2px(Vec(78.74, 109.22)), module, Lithr::SLIDERD10_PARAM));
		addParam(createParamCentered<LEDSliderRed>(mm2px(Vec(86.36, 109.22)), module, Lithr::SLIDERD11_PARAM));
		addParam(createParamCentered<LEDSliderRed>(mm2px(Vec(93.98, 109.22)), module, Lithr::SLIDERD12_PARAM));
		addParam(createParamCentered<LEDSliderGreen>(mm2px(Vec(101.6, 109.22)), module, Lithr::SLIDERD13_PARAM));
		addParam(createParamCentered<LEDSliderGreen>(mm2px(Vec(109.22, 109.22)), module, Lithr::SLIDERD14_PARAM));
		addParam(createParamCentered<LEDSliderGreen>(mm2px(Vec(116.84, 109.22)), module, Lithr::SLIDERD15_PARAM));
		addParam(createParamCentered<LEDSliderGreen>(mm2px(Vec(124.46, 109.22)), module, Lithr::SLIDERD16_PARAM));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(134.62, 17.78)), module, Lithr::OUTPUTA_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(134.62, 48.26)), module, Lithr::OUTPUTB_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(134.62, 78.74)), module, Lithr::OUTPUTC_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(134.62, 109.22)), module, Lithr::OUTPUTD_OUTPUT));
	}
};


Model* modelLithr = createModel<Lithr, LithrWidget>("lithr");
