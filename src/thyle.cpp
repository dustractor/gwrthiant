#include "plugin.hpp"


struct Thyle : Module {
	enum ParamId {
		LENGTH_A_PARAM,
		LENGTH_B_PARAM,
		HITS_A_PARAM,
		HITS_B_PARAM,
		OFFSET_A_PARAM,
		OFFSET_B_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		CLOCK_INPUT,
		RESET_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		GATE_A_OUTPUT,
		GATE_B_OUTPUT,
		GATE_X_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	Thyle() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);

		configParam(LENGTH_A_PARAM, 1.f, 128.f, 8.f, "Length A");
		configParam(LENGTH_B_PARAM, 1.f, 128.f, 8.f, "Length B");
		configParam(HITS_A_PARAM, 1.f, 128.f, 4.f, "Hits A");
		configParam(HITS_B_PARAM, 1.f, 128.f, 4.f, "Hits B");
		configParam(OFFSET_A_PARAM, 0.f, 127.f, 0.f, "Offset A");
		configParam(OFFSET_B_PARAM, 0.f, 127.f, 0.f, "Offset B");

        paramQuantities[LENGTH_A_PARAM]->snapEnabled = true;
        paramQuantities[LENGTH_B_PARAM]->snapEnabled = true;
        paramQuantities[HITS_A_PARAM]->snapEnabled = true;
        paramQuantities[HITS_B_PARAM]->snapEnabled = true;
        paramQuantities[OFFSET_A_PARAM]->snapEnabled = true;
        paramQuantities[OFFSET_B_PARAM]->snapEnabled = true;

		configInput(CLOCK_INPUT, "Clock");
		configInput(RESET_INPUT, "Reset");

		configOutput(GATE_A_OUTPUT, "Gate A");
		configOutput(GATE_B_OUTPUT, "Gate B");
		configOutput(GATE_X_OUTPUT, "Gate X");
	}
    dsp::SchmittTrigger clockSchmitt;
    dsp::SchmittTrigger resetSchmitt;
    int step = 0;
    bool clk_transitioned_high = 0;
    bool prevclock,prevreset;
    float length_A,length_B,hits_A,hits_B,offset_A,offset_B;
    float lastlength_A,lastlength_B,lasthits_A,lasthits_B,lastoffset_A,lastoffset_B;
    int step_A,step_B;
    int cells_A[128];
    int cells_B[128];
    bool swap;
    int getstep_A(){
        return (step + (int)offset_A) % (int)length_A;
    }
    int getstep_B(){
        return (step + (int)offset_B) % (int)length_B;
    }
    
	void process(const ProcessArgs& args) override {
        length_A = params[LENGTH_A_PARAM].getValue();
        length_B = params[LENGTH_B_PARAM].getValue();
        hits_A = params[HITS_A_PARAM].getValue();
        hits_B = params[HITS_B_PARAM].getValue();
        offset_A = params[OFFSET_A_PARAM].getValue();
        offset_B = params[OFFSET_B_PARAM].getValue();
        int cur;
        int prev;
        if ((length_A!=lastlength_A)||(hits_A!=lasthits_A)||(offset_A!=lastoffset_A)){
            float slope = hits_A / length_A;
            prev = -1;
            for (int i=0;i<length_A;i++){
                cur = (int)floor(i*slope);
                if (cur!=prev){
                    cells_A[i] = 1;
                } else {
                    cells_A[i] = 0;
                }
                prev = cur;
            }
        }

        lastlength_A = length_A;
        lasthits_A = hits_A;
        lastoffset_A = offset_A;

        if ((length_B!=lastlength_B)||(hits_B!=lasthits_B)||(offset_B!=lastoffset_B)){
            float slope = hits_B / length_B;
            prev = -1;
            for (int i=0;i<length_B;i++){
                cur = (int)floor(i*slope);
                if (cur!=prev){
                    cells_B[i] = 1;
                } else {
                    cells_B[i] = 0;
                }
                prev = cur;
            }
        }

        lastlength_B = length_B;
        lasthits_B = hits_B;
        lastoffset_B = offset_B;

        bool reset = resetSchmitt.process(inputs[RESET_INPUT].getVoltage());
        if (!(prevreset > 0.f) && (reset > 0.f)){
            step = 0;
        }
        prevreset = reset;
        clockSchmitt.process(inputs[CLOCK_INPUT].getVoltage(),0.1f,1.f);
        bool clock = clockSchmitt.isHigh();
        if (!(prevclock > 0.f) && (clock > 0.f)){
            clk_transitioned_high = true;
        } else {
            clk_transitioned_high = false;
        }
        prevclock = clock;
        if (clk_transitioned_high){
            step += 1;
            int sa = getstep_A();
            int sb = getstep_B();
            int ca = cells_A[sa]*10.f;
            int cb = cells_B[sb]*10.f;
            outputs[GATE_A_OUTPUT].setVoltage(ca);
            outputs[GATE_B_OUTPUT].setVoltage(cb);
            if (((swap==0)&&(sa==0))||((swap==1)&&(sb==0))){
                swap ^= 1;
            }
            outputs[GATE_X_OUTPUT].setVoltage(swap?ca:cb);
        }

	}
};


struct ThyleDisplay : LedDisplay {
    Thyle* module;
    ModuleWidget* moduleWidget;

    void drawLayer(const DrawArgs& args, int layer) override {
        if (layer != 1) {
            return;
        }
        if (module) {
            if (!module->inputs[Thyle::CLOCK_INPUT].isConnected()) {
                return;
            }
            Rect b = box.zeroPos();
            int lenA = (int) module->length_A;
            int lenB = (int) module->length_B;
            nvgScissor(args.vg,b.pos.x,b.pos.y,b.size.x,b.size.y);
            float cell_H_A = b.size.y / lenA;
            float cell_H_B = b.size.y / lenB;
            float halfwidth = b.size.x / 2;
            float tx = 0.0f;
            float ty = 0.0f;
            int sa = module->getstep_A();
            int sb = module->getstep_B();
            for (int i=0;i<lenA;i++) {
                int s = module->cells_A[i]*127;
                nvgBeginPath(args.vg);
                ty = i * cell_H_A;
                nvgRect(args.vg,tx,ty,halfwidth,cell_H_A);
                if (module->swap){
                    nvgFillColor(args.vg,nvgRGBA( (127*(sa==i))+s, s, s, 255));
                } else {
                    nvgFillColor(args.vg,nvgRGBA( s, (127*(sa==i))+s, s, 255));
                }
                nvgFill(args.vg);
                nvgClosePath(args.vg);
            }
            tx = halfwidth;

            for (int i=0;i<lenB;i++) {
                int s = module->cells_B[i]*127;
                nvgBeginPath(args.vg);
                ty = i * cell_H_B;
                nvgRect(args.vg,tx,ty,halfwidth,cell_H_B);
                if (!module->swap) {
                    nvgFillColor(args.vg,nvgRGBA( (127*(sb==i))+s, s, s, 255));
                } else {
                    nvgFillColor(args.vg,nvgRGBA( s, (127*(sb==i))+s, s, 255));
                }
                nvgFill(args.vg);
                nvgClosePath(args.vg);
            }
        }
    }
};


struct ThyleWidget : ModuleWidget {
	ThyleWidget(Thyle* module) {
		setModule(module);
		setPanel(createPanel(
                    asset::plugin(pluginInstance, "res/thyle.svg"),
                    asset::plugin(pluginInstance, "res/thyle-dark.svg")
                    ));

        ThyleDisplay* display = createWidget<ThyleDisplay>(mm2px(Vec(15.24,0.0)));
        display->box.size = mm2px(Vec(15.24,128.5));
        display->module = module;
        display->moduleWidget = this;
        addChild(display);

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(8.89, 11.43)), module, Thyle::LENGTH_A_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(36.83, 11.43)), module, Thyle::LENGTH_B_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(8.89, 24.13)), module, Thyle::HITS_A_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(36.83, 24.13)), module, Thyle::HITS_B_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(8.89, 36.83)), module, Thyle::OFFSET_A_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(36.83, 36.83)), module, Thyle::OFFSET_B_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(8.89, 74.93)), module, Thyle::CLOCK_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(8.89, 87.63)), module, Thyle::RESET_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(8.89, 105.41)), module, Thyle::GATE_A_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(36.83, 105.41)), module, Thyle::GATE_B_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(36.83, 118.11)), module, Thyle::GATE_X_OUTPUT));

	}
};


Model* modelThyle = createModel<Thyle, ThyleWidget>("thyle");
