#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "ant.h"
#include "map.h"
#include "MapDrawer.h"
#include "inputHandler.h"
#include <set>

// Override base class with your custom functionality
class Example : public olc::PixelGameEngine
{
public:
	int width, height;
	map m;
	ant a;
	std::set<ant*> selectedAnts;
	float timePassed = 0.0;
	inputHandler ih;

	Example(int _width, int _height): width(_width), height(_height), m(width, height, this), ih(&a)
	{
		// Name your application
		sAppName = "Example";
		a = ant(50, 10, 10, this, &m);
		a.addNSub(5);
		a.front().addNSub(4);
		ih = inputHandler(&a);
	}

public:
	void paintAround(const olc::vi2d& pos, const olc::Pixel& color) {
		static const std::set<olc::vi2d> positionsAround = {
				{-1, -1}, {0, -1}, {1, -1},
				{-1, 0},                {1, 0},
				{-1, 1},  {0, 1},  {1, 1}
		};
		//static const auto d = olc::Decal();
		for(const auto& v: positionsAround)
			Draw(pos + v, color);
	}

	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		
		//m(1, 1) = HILL;
		m.print();
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		/* Input handling */
		if(GetMouse(olc::Mouse::RIGHT).bPressed)
			ih.singleSelection(GetMouseX(), GetMouseY());
		if(GetMouse(olc::Mouse::LEFT).bPressed)
			ih.subSelection(ih.selectAnt(GetMouseX(), GetMouseY()), !GetKey(olc::CTRL).bHeld);
		if(GetKey(olc::G).bPressed)
			ih.setGoal(GetMouseX(), GetMouseY(), [](int& x){x += 5;});
		if(GetKey(olc::DEL).bPressed)
			ih.deselectAll();

		timePassed += fElapsedTime;
		if(timePassed >= 0.08) {
			timePassed = 0.0;

			/* Move phase */
			a.moveToGoal(true);

			/* Print phase */
			m.print();
			//Draw(a.goal, olc::RED);
			for (auto i = ih.getSelectedAntsBegin(); i != ih.getSelectedAntsEnd(); ++i)
				paintAround((*i)->pos, olc::DARK_YELLOW);
			a.print(true);
		}
		return true;
	}
};

int main()
{
	constexpr int width = 200, height = 200;
	std::string filename = "../maps/firstMap.map";
	//MapDrawer demo(filename);
	Example demo(width, height); demo.m = map(filename, &demo);
	if (demo.Construct(width, height, 8, 8))
		demo.Start();
	return 0;
}
