#pragma once
#include <vector>

class Register {
public:
	enum regName{ BC, DE, HL, NUM_OF_REG };
	struct reg {
		int lowOrder;
		int highOrder;
	};

	Register();
	~Register();

	void setAccu(int num);
	int getAccu() const { return accu; };

	void set(regName reg, int num);
	void set(regName regSet, regName regData);
	reg* get(regName reg) const { return registerList[reg]; };

private:
	

	int accu;
	bool flagC, flagZ;
	reg* registerList[NUM_OF_REG];

};