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
	std::string filename = "";
	land color = WATER;

	MapDrawer(const int cols, const int rows): m(cols, rows, this) {}

	explicit MapDrawer(const std::string& pathIn): m(pathIn, this) {
		filename = pathIn;
	}

private:

	bool OnUserCreate() override {
		m.print();
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {
		bool changes = false;
		if(GetMouse(olc::Mouse::LEFT).bHeld) {
			m(GetMouseX(), GetMouseY()) = WATER;
			changes = true;
		} else
			if(GetMouse(olc::Mouse::RIGHT).bHeld) {
				m(GetMouseX(), GetMouseY()) = PLAIN;
				changes = true;
			}
		if(changes)
			m.print();

		if(GetKey(olc::CTRL).bHeld && GetKey(olc::S).bPressed)
			m.save(filename);
		if(GetKey(olc::ESCAPE).bPressed)
			return false;
		return true;
	}
};


#endif //PROVACLION_MAPDRAWER_H
