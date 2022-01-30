#ifndef PROVACLION_INPUTHANDLER_H
#define PROVACLION_INPUTHANDLER_H

#include "ant.h"
#include "map.h"
#include <set>
#include <algorithm>

class inputHandler {
private:
	// The chief ant
	ant* a;
	std::set<ant*> selectedAnts;
public:
	std::_Rb_tree_const_iterator<ant *> getSelectedAntsBegin();
	std::_Rb_tree_const_iterator<ant *> getSelectedAntsEnd();

private:
	void selectionAndRemoval(ant* s) {
		if(s != nullptr) {
			if (selectedAnts.contains(s))
				selectedAnts.erase(s);
			else
				selectedAnts.insert(s);
		}
	}



public:
	//inputHandler(ant a, map m) : a(std::move(a)), m(std::move(m)) {}

	explicit inputHandler(ant* a) : a(a) {}

	ant* selectAnt(int x, int y) { return a->searchSub({x, y}); }

	void singleSelection(int mouseX, int mouseY) { // Single selection
		ant* s = selectAnt(mouseX, mouseY);
		selectionAndRemoval(s);
	}

	void subSelection(ant* chief, bool chiefToo=false) {
		if(chiefToo)
			selectionAndRemoval(chief);
		if(chief != nullptr)
			for(auto& i: chief->sub)
				selectionAndRemoval(&i);
	}

	void subSelectionChiefAnt(bool chiefToo=false) {
		subSelection(a, chiefToo);
	}

	// Set the goal of the selectedAnt and if "subToo" set the subs' goal too.
	void setGoal(int goalX, int goalY, const std::function<void(int&)>& f=[](int&) {}) {
		for(auto i: selectedAnts) {
			i->goal = {goalX, goalY};
			f(goalX);
		}
	}

	void deselectAll() {
		selectedAnts.clear();
	}
};

std::_Rb_tree_const_iterator<ant *> inputHandler::getSelectedAntsBegin() {
	return selectedAnts.cbegin();
}


std::_Rb_tree_const_iterator<ant *> inputHandler::getSelectedAntsEnd() {
	return selectedAnts.cend();
}


#endif //PROVACLION_INPUTHANDLER_H
