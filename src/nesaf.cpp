#include "plugin.hpp"

using simd::float_4;
using simd::int32_4;


struct Nesaf : Module {
	enum ParamId {
		LENGTH_A_PARAM,
		DENSITY_A_PARAM,
		OFFSET_A_PARAM,
		LENGTH_B_PARAM,
		DENSITY_B_PARAM,
		OFFSET_B_PARAM,
		LENGTH_C_PARAM,
		DENSITY_C_PARAM,
		OFFSET_C_PARAM,
		LENGTH_D_PARAM,
		DENSITY_D_PARAM,
		OFFSET_D_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		CLOCK_INPUT,
		RESET_INPUT,
		LENGTH_CV_A_INPUT,
		DENSITY_CV_A_INPUT,
		OFFSET_CV_A_INPUT,
		LENGTH_CV_B_INPUT,
		DENSITY_CV_B_INPUT,
		OFFSET_CV_B_INPUT,
		LENGTH_CV_C_INPUT,
		DENSITY_CV_C_INPUT,
		OFFSET_CV_C_INPUT,
		LENGTH_CV_D_INPUT,
		DENSITY_CV_D_INPUT,
		OFFSET_CV_D_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		EOC_A_OUTPUT,
		EOC_B_OUTPUT,
		EOC_C_OUTPUT,
		EOC_D_OUTPUT,
		GATE_A_OUTPUT,
		GATE_B_OUTPUT,
		GATE_C_OUTPUT,
		GATE_D_OUTPUT,
		GATE_X_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	Nesaf() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(LENGTH_A_PARAM,  2.f, 128.f, 16.f, "Length A");
		configParam(LENGTH_B_PARAM,  2.f, 128.f, 16.f, "Length B");
		configParam(LENGTH_C_PARAM,  2.f, 128.f, 16.f, "Length C");
		configParam(LENGTH_D_PARAM,  2.f, 128.f, 16.f, "Length D");

		configParam(DENSITY_A_PARAM, 0.f, 100.f, 50.f, "Density A");
		configParam(DENSITY_B_PARAM, 0.f, 100.f, 50.f, "Density B");
		configParam(DENSITY_C_PARAM, 0.f, 100.f, 50.f, "Density C");
		configParam(DENSITY_D_PARAM, 0.f, 100.f, 50.f, "Density D");

		configParam(OFFSET_A_PARAM,  0.f, 128.f, 0.f, "Offset A");
		configParam(OFFSET_B_PARAM,  0.f, 128.f, 0.f, "Offset B");
		configParam(OFFSET_C_PARAM,  0.f, 128.f, 0.f, "Offset C");
		configParam(OFFSET_D_PARAM,  0.f, 128.f, 0.f, "Offset D");

        paramQuantities[LENGTH_A_PARAM]->snapEnabled = true;
        paramQuantities[LENGTH_B_PARAM]->snapEnabled = true;
        paramQuantities[LENGTH_C_PARAM]->snapEnabled = true;
        paramQuantities[LENGTH_D_PARAM]->snapEnabled = true;

        paramQuantities[OFFSET_A_PARAM]->snapEnabled = true;
        paramQuantities[OFFSET_B_PARAM]->snapEnabled = true;
        paramQuantities[OFFSET_C_PARAM]->snapEnabled = true;
        paramQuantities[OFFSET_D_PARAM]->snapEnabled = true;

		configInput(CLOCK_INPUT, "Clock");
		configInput(RESET_INPUT, "Reset");

		configInput(LENGTH_CV_A_INPUT, "Length CV A");
		configInput(LENGTH_CV_B_INPUT, "Length CV B");
		configInput(LENGTH_CV_C_INPUT, "Length CV C");
		configInput(LENGTH_CV_D_INPUT, "Length CV D");

		configInput(DENSITY_CV_A_INPUT, "Density CV A");
		configInput(DENSITY_CV_B_INPUT, "Density CV B");
		configInput(DENSITY_CV_C_INPUT, "Density CV C");
		configInput(DENSITY_CV_D_INPUT, "Density CV D");

		configInput(OFFSET_CV_A_INPUT, "Offset CV A");
		configInput(OFFSET_CV_B_INPUT, "Offset CV B");
		configInput(OFFSET_CV_C_INPUT, "Offset CV C");
		configInput(OFFSET_CV_D_INPUT, "Offset CV D");

		configOutput(EOC_A_OUTPUT, "EOC A");
		configOutput(EOC_B_OUTPUT, "EOC B");
		configOutput(EOC_C_OUTPUT, "EOC C");
		configOutput(EOC_D_OUTPUT, "EOC D");

		configOutput(GATE_A_OUTPUT, "Gate A");
		configOutput(GATE_B_OUTPUT, "Gate B");
		configOutput(GATE_C_OUTPUT, "Gate C");
		configOutput(GATE_D_OUTPUT, "Gate D");

		configOutput(GATE_X_OUTPUT, "Gate X");
	}
    
    float_4 length_v = {};
    float_4 density_v = {};
    float_4 offset_v = {};
    float_4 lastlength_v = {};
    float_4 lastdensity_v = {};
    float_4 lastoffset_v = {};

    dsp::SchmittTrigger clockSchmitt;
    dsp::SchmittTrigger resetSchmitt;
    bool clk_transitioned_high = 0;
    bool prevclock,prevreset;

    int length_A,length_B,length_C,length_D;
    float density_A,density_B,density_C,density_D;
    int offset_A,offset_B,offset_C,offset_D;

    int lastlength_A,lastlength_B,lastlength_C,lastlength_D;
    float lastdensity_A,lastdensity_B,lastdensity_C,lastdensity_D;
    int lastoffset_A,lastoffset_B,lastoffset_C,lastoffset_D;

    int step = 0;
    int cells_A[128];
    int cells_B[128];
    int cells_C[128];
    int cells_D[128];

    int32_4 cells_v[128] = {};

    void calccells(){
        
    }

    void calccells(int (&cells)[128], int len, float dens){
        int hits = (int)(len * dens * 0.01f);
        float slope = (float)hits / (float)len;
        INFO("hits:%d slope:%f len:%d dens:%f",hits,slope,len,dens);
        int prev = -1;
        for (int i=0;i<len;i++){
            int cur = (int)floor(i*slope);
            if (cur!=prev){
                cells[i] = 1;
            } else {
                cells[i] = 0;
            }
            prev = cur;
        }
    }

    int getstep_A(){
        return (step + (int)offset_A) % (int)length_A;
    }
    int getstep_B(){
        return (step + (int)offset_B) % (int)length_B;
    }
    int getstep_C(){
        return (step + (int)offset_C) % (int)length_C;
    }
    int getstep_D(){
        return (step + (int)offset_D) % (int)length_D;
    }

	void process(const ProcessArgs& args) override {
        length_A = std::min(128,std::max(2,(int)(params[LENGTH_A_PARAM].getValue() + inputs[LENGTH_CV_A_INPUT].getVoltage())));
        length_B = std::min(128,std::max(2,(int)(params[LENGTH_B_PARAM].getValue() + inputs[LENGTH_CV_B_INPUT].getVoltage())));
        length_C = std::min(128,std::max(2,(int)(params[LENGTH_C_PARAM].getValue() + inputs[LENGTH_CV_C_INPUT].getVoltage())));
        length_D = std::min(128,std::max(2,(int)(params[LENGTH_D_PARAM].getValue() + inputs[LENGTH_CV_D_INPUT].getVoltage())));
        density_A = std::min(100,std::max(0,(int)(params[DENSITY_A_PARAM].getValue() + inputs[DENSITY_CV_A_INPUT].getVoltage())));
        density_B = std::min(100,std::max(0,(int)(params[DENSITY_B_PARAM].getValue() + inputs[DENSITY_CV_B_INPUT].getVoltage())));
        density_C = std::min(100,std::max(0,(int)(params[DENSITY_C_PARAM].getValue() + inputs[DENSITY_CV_C_INPUT].getVoltage())));
        density_D = std::min(100,std::max(0,(int)(params[DENSITY_D_PARAM].getValue() + inputs[DENSITY_CV_D_INPUT].getVoltage())));
        offset_A = std::min(128,std::max(0,(int)(params[OFFSET_A_PARAM].getValue() + inputs[OFFSET_CV_A_INPUT].getVoltage())));
        offset_B = std::min(128,std::max(0,(int)(params[OFFSET_B_PARAM].getValue() + inputs[OFFSET_CV_B_INPUT].getVoltage())));
        offset_C = std::min(128,std::max(0,(int)(params[OFFSET_C_PARAM].getValue() + inputs[OFFSET_CV_C_INPUT].getVoltage())));
        offset_D = std::min(128,std::max(0,(int)(params[OFFSET_D_PARAM].getValue() + inputs[OFFSET_CV_D_INPUT].getVoltage())));
        INFO("length_A: %d density_A: %f offset_A: %d",length_A,density_A,offset_A);
        if ((length_A!=lastlength_A)||(density_A!=lastdensity_A)){
            calccells(cells_A,length_A,density_A);
            lastlength_A = length_A;
            lastdensity_A = density_A;
        }
        if ((length_B!=lastlength_B)||(density_B!=lastdensity_B)){
            calccells(cells_B,length_B,density_B);
            lastlength_B = length_B;
            lastdensity_B = density_B;
        }
        if ((length_C!=lastlength_C)||(density_C!=lastdensity_C)){
            calccells(cells_C,length_C,density_C);
            lastlength_C = length_C;
            lastdensity_C = density_C;
        }
        if ((length_D!=lastlength_D)||(density_D!=lastdensity_D)){
            calccells(cells_D,length_D,density_D);
            lastlength_D = length_D;
            lastdensity_D = density_D;
        }

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
            int sc = getstep_C();
            int sd = getstep_D();
            int ca = cells_A[sa];
            int cb = cells_B[sb];
            int cc = cells_C[sc];
            int cd = cells_D[sd];
            int ea = sa == offset_A;
            int eb = sb == offset_B;
            int ec = sc == offset_C;
            int ed = sd == offset_D;
            outputs[GATE_A_OUTPUT].setVoltage(ca*10.f);
            outputs[GATE_B_OUTPUT].setVoltage(cb*10.f);
            outputs[GATE_C_OUTPUT].setVoltage(cc*10.f);
            outputs[GATE_D_OUTPUT].setVoltage(cd*10.f);
            outputs[EOC_A_OUTPUT].setVoltage(ea*10.f);
            outputs[EOC_B_OUTPUT].setVoltage(eb*10.f);
            outputs[EOC_C_OUTPUT].setVoltage(ec*10.f);
            outputs[EOC_D_OUTPUT].setVoltage(ed*10.f);
            outputs[GATE_X_OUTPUT].setVoltage((ea||eb||ec||ed)*10.f);
        }

	}
};



struct NesafDisplay : LedDisplay {
    Nesaf* module;
    ModuleWidget* moduleWidget;
    
    void drawLayer(const DrawArgs& args, int layer) override {
        if (layer != 1) {
            return;
        }

        if (module) {
            if (!module->inputs[Nesaf::CLOCK_INPUT].isConnected()){
                return;
            }
            Rect b = box.zeroPos();
            int lenA = (int) module->length_A;
            int lenB = (int) module->length_B;
            int lenC = (int) module->length_C;
            int lenD = (int) module->length_D;
            nvgScissor(args.vg,b.pos.x,b.pos.y,b.size.x,b.size.y);
            float cell_H_A = b.size.y / lenA;
            float cell_H_B = b.size.y / lenB;
            float cell_H_C = b.size.y / lenC;
            float cell_H_D = b.size.y / lenD;
            float colwidth = b.size.x / 4;
            float tx = 0.f;
            float ty = 0.f;
            int sa = module->getstep_A();
            int sb = module->getstep_B();
            int sc = module->getstep_C();
            int sd = module->getstep_D();
            for (int i=0;i<lenA;i++){
                int s = module->cells_A[i]*127;
                nvgBeginPath(args.vg);
                ty = i * cell_H_A;
                nvgRect(args.vg,tx,ty,colwidth,cell_H_A);
                nvgFillColor(args.vg,nvgRGBA( (127*(sa==i))+s,s,s,255));
                nvgFill(args.vg);
                nvgClosePath(args.vg);
            }
            tx += colwidth;
            for (int i=0;i<lenB;i++){
                int s = module->cells_B[i]*127;
                nvgBeginPath(args.vg);
                ty = i * cell_H_B;
                nvgRect(args.vg,tx,ty,colwidth,cell_H_B);
                nvgFillColor(args.vg,nvgRGBA( (127*(sb==i))+s,s,s,255));
                nvgFill(args.vg);
                nvgClosePath(args.vg);
            }
            tx += colwidth;
            for (int i=0;i<lenC;i++){
                int s = module->cells_C[i]*127;
                nvgBeginPath(args.vg);
                ty = i * cell_H_C;
                nvgRect(args.vg,tx,ty,colwidth,cell_H_C);
                nvgFillColor(args.vg,nvgRGBA( (127*(sc==i))+s,s,s,255));
                nvgFill(args.vg);
                nvgClosePath(args.vg);
            }
            tx += colwidth;
            for (int i=0;i<lenD;i++){
                int s = module->cells_D[i]*127;
                nvgBeginPath(args.vg);
                ty = i * cell_H_D;
                nvgRect(args.vg,tx,ty,colwidth,cell_H_D);
                nvgFillColor(args.vg,nvgRGBA( (127*(sd==i))+s,s,s,255));
                nvgFill(args.vg);
                nvgClosePath(args.vg);
            }
        }
    }
};


struct NesafWidget : ModuleWidget {
	NesafWidget(Nesaf* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/nesaf.svg")));

		// mm2px(Vec(27.94, 128.5))
		// addChild(createWidget<Widget>(mm2px(Vec(40.64, 0.0))));

        NesafDisplay* display = createWidget<NesafDisplay>(mm2px(Vec(40.64,0.0)));
        display->box.size = mm2px(Vec(15.24,128.5));
        display->module = module;
        display->moduleWidget = this;
        addChild(display);

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(6.35, 16.51)), module, Nesaf::LENGTH_A_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(19.05, 16.51)), module, Nesaf::DENSITY_A_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(31.75, 16.51)), module, Nesaf::OFFSET_A_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(6.35, 44.45)), module, Nesaf::LENGTH_B_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(19.05, 44.45)), module, Nesaf::DENSITY_B_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(31.75, 44.45)), module, Nesaf::OFFSET_B_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(6.35, 72.39)), module, Nesaf::LENGTH_C_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(19.05, 72.39)), module, Nesaf::DENSITY_C_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(31.75, 72.39)), module, Nesaf::OFFSET_C_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(6.35, 100.33)), module, Nesaf::LENGTH_D_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(19.05, 100.33)), module, Nesaf::DENSITY_D_PARAM));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(31.75, 100.33)), module, Nesaf::OFFSET_D_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(74.93, 8.89)), module, Nesaf::CLOCK_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(74.93, 21.59)), module, Nesaf::RESET_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(6.35, 29.21)), module, Nesaf::LENGTH_CV_A_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(19.05, 29.21)), module, Nesaf::DENSITY_CV_A_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(31.75, 29.21)), module, Nesaf::OFFSET_CV_A_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(6.35, 57.15)), module, Nesaf::LENGTH_CV_B_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(19.05, 57.15)), module, Nesaf::DENSITY_CV_B_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(31.75, 57.15)), module, Nesaf::OFFSET_CV_B_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(6.35, 85.09)), module, Nesaf::LENGTH_CV_C_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(19.05, 85.09)), module, Nesaf::DENSITY_CV_C_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(31.75, 85.09)), module, Nesaf::OFFSET_CV_C_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(6.35, 113.03)), module, Nesaf::LENGTH_CV_D_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(19.05, 113.03)), module, Nesaf::DENSITY_CV_D_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(31.75, 113.03)), module, Nesaf::OFFSET_CV_D_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(74.93, 34.29)), module, Nesaf::EOC_A_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(74.93, 44.45)), module, Nesaf::EOC_B_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(74.93, 54.61)), module, Nesaf::EOC_C_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(74.93, 64.77)), module, Nesaf::EOC_D_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(74.93, 77.47)), module, Nesaf::GATE_A_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(74.93, 87.63)), module, Nesaf::GATE_B_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(74.93, 97.79)), module, Nesaf::GATE_C_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(74.93, 107.95)), module, Nesaf::GATE_D_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(74.93, 120.65)), module, Nesaf::GATE_X_OUTPUT));

	}
};


Model* modelNesaf = createModel<Nesaf, NesafWidget>("nesaf");
