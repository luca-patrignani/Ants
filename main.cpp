#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "ant.h"
#include "map.h"
#include <ctime>

// Override base class with your custom functionality
class Example : public olc::PixelGameEngine
{
public:
	int width, height;
	map m;
	ant a;
	float timePassed = 0.0;

	Example(int _width, int _height): width(_width), height(_height), m(width, height, this)
	{
		// Name your application
		sAppName = "Example";
		a = ant(30, 10, 10, this);
		a.addNSub(5);
		a.front().addNSub(4);
	}

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		
		//m(1, 1) = HILL;
		m.print();
		a.goal = position(20, 20);
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// Called once per frame, draws random coloured pixels
		timePassed += fElapsedTime;
		if(timePassed < 1.0)
			return true;
		timePassed = 0.0;

		a.moveToGoal();
		m.print();
		a.print(false);
		return true;
	}
};

int main()
{
	constexpr int width = 200, height = 200;
	Example demo(width, height);
	if (demo.Construct(width, height, 8, 8))
		demo.Start();
	return 0;
}
