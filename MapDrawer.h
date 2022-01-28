//
// Created by Luca on 28/01/2022.
//

#ifndef PROVACLION_MAPDRAWER_H
#define PROVACLION_MAPDRAWER_H

#include "olcPixelGameEngine.h"
#include "map.h"
#include <iostream>

class MapDrawer: public olc::PixelGameEngine {
public:
	map m;

	MapDrawer(const int cols, const int rows): m(cols, rows, this) {}

	explicit MapDrawer(const std::string& pathIn) {
		auto stream = std::fstream(pathIn, std::fstream::in);
		int cols, rows;
		stream >> cols >> rows;
		m = map(cols, rows, this);
		for(int x = 0; x < m.cols; ++x)
			for(int y = 0; y < m.rows; ++y) {
				int l;
				stream >> l;
				m(x, y) = (land)l;
			}
	}

private:
	void save(const std::string& outPath) {
		auto stream = std::fstream(outPath, std::fstream::out);
		stream << m.cols << " " << m.rows;
		for(int x = 0; x < m.cols; ++x)
			for(int y = 0; y < m.rows; ++y)
				stream << " " << (int)m(x, y);
	}


	bool OnUserCreate() override {
		m.print();
		save("../maps/firstMap.map");
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {
		return true;
	}
};


#endif //PROVACLION_MAPDRAWER_H
