#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "memory.h"

namespace iohandler {
	inline void pause() {
		std::cout << "\nPress any key to continue...";
		std::cin.ignore();
		std::cin.get();
	};

	inline void loadSnapshot(std::string fileName, std::shared_ptr<Memory> mem) {
		std::ifstream file(fileName);
		
		// catch file error
		try {
			if (!file.is_open())
				throw std::runtime_error("ERROR - could not open file: "+fileName);
		}
		catch (std::runtime_error e){
			std::cerr << e.what() << std::endl;
			pause();
			return;
		}

		std::string str;
		int hexVal;
		while (file) {
			file >> str;

			if (str.length() == 4) { // remove brackets
				str = str.substr(1, str.length() - 2);
				if (!str.compare("HL"))
					str = "41"; // set hex for HL
			}

			hexVal = std::stoi(str, 0, 16); // convert string to hex
			mem->emplace(hexVal);
		}
	};
}