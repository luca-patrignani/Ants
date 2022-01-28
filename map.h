#pragma once
#include <list>
#include <vector>
#include <memory>

#include "ant.h"
#include "olcPixelGameEngine.h"

enum land { PLAIN, HILL, WATER, BLACK, TOTAL_LAND };

class map {
private:
	std::vector<land> array;
	olc::PixelGameEngine* pge;

public:
	unsigned rows, cols;

	map() = default;
	map(unsigned _cols, unsigned _rows, olc::PixelGameEngine* _pge): rows(_rows), cols(_cols) {
		array = std::vector<land>(rows * cols);
		pge = _pge;
		for (auto& i : array)
			i = PLAIN;
	}

	land& operator()(unsigned x, unsigned y) {
		if (x < cols && y < rows)
			return array[y * cols + x];
		else
			throw std::out_of_range("Accessing Map outside bounds\n");
	}

	void print() {
		for (unsigned i = 0; i < cols; ++i)
			for (unsigned j = 0; j < rows; ++j) {
				olc::Pixel p;
				switch (operator()(i, j)) {
					case PLAIN: p = olc::DARK_GREEN; break;
					case HILL: p = olc::VERY_DARK_GREEN; break;
					case WATER: p = olc::BLUE; break;
					default: p = olc::BLACK;
				}
				pge->Draw(i, j, p);
			}
	}

	bool crossable(int x, int y) {
		land l;
		try {
			l = operator()(x, y);
		}
		catch(const std::out_of_range& _) { // We're out of bound,
			return false; // so it is not crossable.
		}

		switch (l) {
			case WATER: return false;
			default: return true;
		}
	}
};