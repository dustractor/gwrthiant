// Gwrthiant is a VCV Rack plugin containing modules written by dustractor.
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


Plugin* pluginInstance;


void init(Plugin* p) {
	pluginInstance = p;

	// Add modules here
	// p->addModel(modelMyModule);
p->addModel(modelPysgota);
p->addModel(modelGwreiddyn);
p->addModel(modelClwyd);
p->addModel(modelPatrwm);
p->addModel(modelNilyniant);
p->addModel(modelGraddfa);
p->addModel(modelCyfeiriad);
p->addModel(modelSeiclo);
p->addModel(modelErys);
p->addModel(modelNodiadau);
p->addModel(modelPylu);
p->addModel(modelLithr);
p->addModel(modelBrofen);
p->addModel(modelPenodol);
p->addModel(modelPenodol4);
p->addModel(modelCloren);
p->addModel(modelEhangu);
	// Any other plugin initialization may go here.
	// As an alternative, consider lazy-loading assets and lookup tables when your module is created to reduce startup times of Rack.
}
