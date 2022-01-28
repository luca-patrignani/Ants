#pragma once
#include <list>
#include <vector>
#include <memory>

#include "ant.h"
#include "olcPixelGameEngine.h"

enum land { PLAIN, HILL, WATER, TOTAL_LAND };

class map {
private:
	std::vector<land> array;
	olc::PixelGameEngine* pge;

	void init(int _cols, int _rows, olc::PixelGameEngine* _pge);

public:
	int rows, cols;

	map() = default;
	map(int _cols, int _rows, olc::PixelGameEngine* _pge);

	explicit map(const std::string& filename, olc::PixelGameEngine* _pge);

	void save(const std::string& outPath);

	land& operator()(int x, int y);

	void print();

	bool crossable(int x, int y);
};

bool map::crossable(int x, int y) {
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

map::map(int _cols, int _rows, olc::PixelGameEngine *_pge) {
	init(_cols, _rows, _pge);
	for (auto& i : array)
		i = PLAIN;
}

map::map(const std::string &filename, olc::PixelGameEngine *_pge) {
	auto stream = std::fstream(filename, std::fstream::in);
	int _cols, _rows;
	stream >> _cols >> _rows;
	init(_cols, _rows, _pge);
	for(auto &i: array) {
		int l;
		stream >> l;
		i = (land)l;
	}
}

void map::save(const std::string &outPath) {
	auto stream = std::fstream(outPath, std::fstream::out);
	stream << cols << " " << rows;
	for(auto& i: array)
		stream << " " << (int)i;
}

land &map::operator()(int x, int y) {
	if (x < cols && y < rows)
		return array[y * cols + x];
	else
		throw std::out_of_range("Accessing Map outside bounds\n");
}

void map::print() {
	for (int i = 0; i < cols; ++i)
		for (int j = 0; j < rows; ++j) {
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

void map::init(int _cols, int _rows, olc::PixelGameEngine *_pge) {
	cols = _cols;
	rows = _rows;
	array = std::vector<land>(rows * cols);
	pge = _pge;
}
