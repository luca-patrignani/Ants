#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "ant.h"
#include "map.h"

// Override base class with your custom functionality
class Example : public olc::PixelGameEngine
{
public:
	int width, height;
	map m;
	ant a;
	Example(int _width, int _height): width(_width), height(_height), m(width, height, this), a(10, 10, 10, this)
	{
		// Name your application
		sAppName = "Example";
		a.addNSub(5);
		a.front().addNSub(4);

	}

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		
		//m(1, 1) = HILL;
		m.print();
		a.print();
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// Called once per frame, draws random coloured pixels
		
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
