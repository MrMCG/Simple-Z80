#include "Z80cloud.h"

Z80Cloud::Z80Cloud() {
	theCloud = new std::vector<std::unique_ptr<Z80>>(numOfZ80);

	for (int i = 0; i < numOfZ80; i++) {	
		theCloud->emplace_back(new Z80());
		utility::loadSnapshot(theCloud->back()->getRam(), utility::cloudFile);
	}
}

Z80Cloud::~Z80Cloud() {
	theCloud->clear();
	delete theCloud;
}