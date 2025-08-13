#include "plugin.hpp"


struct Brofen : Module {
	enum ParamId {
		PARAMS_LEN
	};
	enum InputId {
		B_INPUT,
		A_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	Brofen() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configInput(B_INPUT, "");
		configInput(A_INPUT, "");
	}

	void process(const ProcessArgs& args) override {
	}
};

struct TestDisplay : LedDisplay {
    Brofen* module;
    ModuleWidget* moduleWidget;

    void drawLayer(const DrawArgs& args, int layer) override {
        if (layer != 1) {
            return;
        }
        if (module){
            if (!module->inputs[Brofen::A_INPUT].isConnected()){
                return;
            }

            Rect b = box.zeroPos();
            Vec ct = b.getCenter();

            int channels =  module->inputs[Brofen::A_INPUT].getChannels();

            nvgScissor(args.vg,b.pos.x,b.pos.y,b.size.x,b.size.y);


            float h = b.size.y / channels;
            float hh = h / 2;

            for (int i=0;i<channels;i++){
                float v = module->inputs[Brofen::A_INPUT].getVoltage(i);
                INFO("ch: %d | h: %f | i: %d | v: %f",channels,h,i,v);
                nvgBeginPath(args.vg);
                nvgCircle(args.vg,((b.size.x/10)*v)+ct.x,(i*h)+hh,10.0);
                nvgFillColor(args.vg,nvgRGBA(255,255,255,255));
                nvgFill(args.vg);
                nvgClosePath(args.vg);
            }

            
        }
    }

};


struct BrofenWidget : ModuleWidget {
	BrofenWidget(Brofen* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/brofen.svg")));

        TestDisplay* display = createWidget<TestDisplay>(mm2px(Vec(0.0,0.0)));
        display->box.size = mm2px(Vec(50.8,128.5));
        display->module = module;
        display->moduleWidget = this;
        addChild(display);

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 7.62)), module, Brofen::B_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 17.78)), module, Brofen::A_INPUT));

	}
};


Model* modelBrofen = createModel<Brofen, BrofenWidget>("brofen");
