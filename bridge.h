//
// Created by Luca on 31/01/2022.
//

#ifndef PROVACLION_BRIDGE_H
#define PROVACLION_BRIDGE_H

#include "mapObject.h"


class bridge: public mapObject {
public:
	olc::Pixel getColor() const override {
		const static auto color = olc::Pixel(143, 102, 20); // Kind of brown
		return color;
	}

	bool isTraversable() const override {
		return true;
	}

};


#endif //PROVACLION_BRIDGE_H
