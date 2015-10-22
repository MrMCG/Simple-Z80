#pragma once
#include <map>

class Register {
public:
	enum regName{ PC, A, B, C, D, E, F, H, L, NUM_OF_REG };

	Register();
	~Register();

	void set(regName reg, int num);
	void set(regName regSet, regName regData);
	void setDeref(regName reg, int regHexVal);

private:
	struct regCombined {
		regName first;
		regName second;
	};

	void incPositionCounter();
	void initMap();
	std::map<int, regCombined>* registerMap;

	int* registerList[NUM_OF_REG];

};