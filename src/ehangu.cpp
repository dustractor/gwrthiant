#include "plugin.hpp"


struct Ehangu : Module {
	enum ParamId {
		LENGTH_PARAM,
		OFFSET_PARAM,
		NUMERATOR_PARAM,
		DENOMINATOR_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		CLOCK_INPUT,
		RESET_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		GATE_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	Ehangu() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(LENGTH_PARAM, 1.f, 128.f, 16.f, "Length");
		configParam(OFFSET_PARAM, 0.f, 128.f, 0.f, "Offset");
		configParam(NUMERATOR_PARAM, 1.f, 1024.f, 1.f, "Numerator");
		configParam(DENOMINATOR_PARAM, 1.f, 1024.f, 1.f, "Denominator");
		configInput(CLOCK_INPUT, "Clock");
		configInput(RESET_INPUT, "Reset");
		configOutput(GATE_OUTPUT, "Gate");
        paramQuantities[LENGTH_PARAM]->snapEnabled = true;
        paramQuantities[OFFSET_PARAM]->snapEnabled = true;
        paramQuantities[NUMERATOR_PARAM]->snapEnabled = true;
        paramQuantities[DENOMINATOR_PARAM]->snapEnabled = true;

	}
    int gates[1024] = {0};
    int lastlength,lastnum,lastdenom;
    dsp::SchmittTrigger clockSchmitt;
    dsp::SchmittTrigger resetSchmitt;
    int seqStep = 0;
    bool prevClock = 0;
    bool prevReset = 0;
    bool clk_transitioned_high = 0;
    int length,offset,num,denom;

	void process(const ProcessArgs& args) override {
        length = params[LENGTH_PARAM].getValue();
        offset = params[OFFSET_PARAM].getValue();
        num = params[NUMERATOR_PARAM].getValue();
        denom = params[DENOMINATOR_PARAM].getValue();

        if ((length!=lastlength)||(num!=lastnum)||(denom!=lastdenom)){
            num %= denom;
            for (int i=0;i<length;++i){
                num *= 10;
                gates[i] = ((num/denom) % 2) == 0;
                num %= denom;
                if (num==0){
                    break;
                }
            }
            lastlength = length;
            lastnum = num;
            lastdenom = denom;
        }
        bool reset = resetSchmitt.process(inputs[RESET_INPUT].getVoltage());

        if (!(prevReset > 0.f) && (reset > 0.f)){
            seqStep = offset;
        }

        prevReset = reset;

        clockSchmitt.process(inputs[CLOCK_INPUT].getVoltage(),0.1f,1.f);
        bool clock = clockSchmitt.isHigh();
        if (!(prevClock > 0.f) && (clock > 0.f)){
            clk_transitioned_high = true;
        } else {
            clk_transitioned_high = false;
        }
        prevClock = clock;

        if (clk_transitioned_high){
            seqStep = (seqStep + 1) % length;
            outputs[GATE_OUTPUT].setVoltage(gates[seqStep]*10.f);
        }
	}
};


struct GateDisplay : LedDisplay {
    Ehangu* module;
    ModuleWidget* moduleWidget;
    void drawLayer(const DrawArgs& args, int layer) override {
        if (layer != 1) {
            return;
        }
        if (module) {
            Rect b = box.zeroPos();
            nvgScissor(args.vg,b.pos.x,b.pos.y,b.size.x,b.size.y);
            float h = b.size.y / module->length;
            float tx = 0.0f;
            float ty = 0.0f;
            for (int i=0;i<module->length;i++) {
                int s = module->gates[i]*127;
                nvgBeginPath(args.vg);
                ty = i*h;
                nvgRect(args.vg,tx,ty,b.size.x,h);
                nvgFillColor(args.vg,nvgRGBA(s,s+((((module->offset+module->seqStep)%module->length)==i)*127),s,255));
                nvgFill(args.vg);
                nvgClosePath(args.vg);
            }
        }
    }
};


struct EhanguWidget : ModuleWidget {
	EhanguWidget(Ehangu* module) {
		setModule(module);
		setPanel(createPanel(
                    asset::plugin(pluginInstance, "res/ehangu.svg"),
                    asset::plugin(pluginInstance, "res/ehangu-dark.svg")
                    ));

        GateDisplay* display = createWidget<GateDisplay>(mm2px(Vec(15.0,0.0)));
        display->box.size = mm2px(Vec(10.0f,128.5f));
        display->module = module;
        display->moduleWidget = this;
        addChild(display);

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(7.62, 7.62)), module, Ehangu::LENGTH_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(7.62, 17.78)), module, Ehangu::OFFSET_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(7.62, 27.94)), module, Ehangu::NUMERATOR_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(7.62, 38.1)), module, Ehangu::DENOMINATOR_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 96.52)), module, Ehangu::CLOCK_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 106.68)), module, Ehangu::RESET_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.62, 121.92)), module, Ehangu::GATE_OUTPUT));
	}
};


Model* modelEhangu = createModel<Ehangu, EhanguWidget>("ehangu");
