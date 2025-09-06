#include "plugin.hpp"


struct Brofen : Module {
	enum ParamId {
		PARAMS_LEN
	};
	enum InputId {
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
            float tx = 0.0f;
            float ty = 0.0f;
            int tr = 0;
            for (int i=0;i<channels;i++){
                float v = module->inputs[Brofen::A_INPUT].getVoltage(i);
                nvgBeginPath(args.vg);
                tx = ((b.size.x/20.0f)*v)+ct.x;
                ty = (i*h)+hh;
                nvgCircle(args.vg,tx,ty,5.0);
                tr = (int)(tx+100);
                INFO("%f %d",tx,tr);
                nvgFillColor(args.vg,nvgRGBA(tr,0,tr,255));
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

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 7.62)), module, Brofen::A_INPUT));

	}
};


Model* modelBrofen = createModel<Brofen, BrofenWidget>("brofen");
