//
// Created by Luca on 31/01/2022.
//

#ifndef PROVACLION_MAPOBJECT_H
#define PROVACLION_MAPOBJECT_H

#include <map>

#include "olcPixelGameEngine.h"
typedef olc::vi2d position;


// An object that can be built and destroyed by an ant.
class mapObject {
public:
	// Returns the color of the maoObject that will appear on screen.
	virtual olc::Pixel getColor() const {}

	// Returns if the mapOject is traversable by an ant
	virtual bool isTraversable() const {}

};


#endif //PROVACLION_MAPOBJECT_H
