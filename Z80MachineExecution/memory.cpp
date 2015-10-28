#include "memory.h"

Memory::Memory(int hexSize) {
	heap.emplace_back(new int{ 0 }); // inc heap so index address starts at 01;
}

Memory::~Memory() {
	heap.clear();
}

void Memory::setMem(int loc, int val) {
	*(heap[loc]) = val;
}

void Memory::emplace(int val) {
	heap.emplace_back(new int{ val });
}
