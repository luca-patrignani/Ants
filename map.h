#pragma once
#include <list>
#include <utility>
#include <vector>
#include <map>

#include "mapObject.h"
#include "ant.h"
#include "olcPixelGameEngine.h"

enum land { PLAIN, HILL, WATER, TOTAL_LAND };

// The map
class map {
private:
	std::vector<land> array;
	int rows, cols;
	std::map<position, mapObject> mapObjects;
	olc::PixelGameEngine* pge;

	void init(int _cols, int _rows, olc::PixelGameEngine* _pge);

public:


	map() = default;
	map(int _cols, int _rows, olc::PixelGameEngine* _pge);
	map(const std::string& filename, olc::PixelGameEngine* _pge);

	// Save the map into a .map file at the "outPath" location.
	// Returns none.
	void save(const std::string& outPath);

	// Access the map at the "x" "y" position.
	// Returns the reference to the underlying land,
	land& operator()(int x, int y);

	// Print the map into the olc::pge screen
	// Returns none.
	void print();

	// Check if the undelrying "x" "y" land is traversable by an ant.
	// Out of bounds' locations are considered non-traversable.
	// Returns true if is traversable, else false.
	bool traversable(int x, int y);

	// Add a mapObject "mo" to the map at position "pos".
	// Returns none.
	void addMapObject(mapObject mo, position pos);
};





bool map::traversable(int x, int y) {
	land l;
	try {
		l = operator()(x, y);
	}
	catch(const std::out_of_range& _) { // We're out of bound,
		return false; // so it is not traversable.
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
			if(mapObjects.contains({i, j}))
				p = mapObjects[{i, j}].getColor();
			else {
				switch (operator()(i, j)) {
					case PLAIN: p = olc::DARK_GREEN; break;
					case HILL: p = olc::VERY_DARK_GREEN; break;
					case WATER: p = olc::BLUE; break;
					default: p = olc::BLACK;
				}
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

void map::addMapObject(mapObject mo, position pos) {
	mapObjects[pos] = mo;
}
