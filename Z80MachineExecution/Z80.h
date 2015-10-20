#pragma once
#include <vector>
#include <string>



class Z80{
public:
	Z80();
	~Z80();

private:
	struct opCode {
		enum class expectingType{
			NOTHING,			// NULL (no data)
			NUMBER_SINGLE,		// 1 byte number    
			NUMBER_DOUBLE,		// 2 byte number    
			REGISTER_SINGLE,	// 1 byte register  
			REGISTER_DOUBLE,	// 2 byte register  
			ADDRESS_SINGLE,		// address
			ADDRESS_DOUBLE,		// address and address + 1			
			CONDITION,			// condition		
			DISPLACEMENT		// displacement		
		};
		std::string nemo;
		std::string hex;
		expectingType expects;
	};
	std::vector< opCode >* opCodesList;



};