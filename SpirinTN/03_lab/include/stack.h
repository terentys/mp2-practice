#include <iostream>
#include <algorithm>
#include <stdexcept>

const size_t MAX_SIZE = 1000000;

template <typename T>
class TStack {
private:
	size_t maxSize;
	size_t topIdx;
	T* pMem;
public:
	TStack(size_t maxSize = 1) : maxSize(maxSize), topIdx(-1) {
		if (maxSize == 0 || maxSize > MAX_SIZE) {
			throw std::out_of_range("Incorrect stack size");
		}
		pMem = new T[maxSize];
	}

	TStack(const TStack& st) : maxSize(st.maxSize), topIdx(st.topIdx) {

	}
};