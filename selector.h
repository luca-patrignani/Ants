#ifndef PROVACLION_SELECTOR_H
#define PROVACLION_SELECTOR_H

#include "ant.h"
#include "map.h"
#include <set>
#include <algorithm>


// A class that handles ants' selection by the player.
class selector {
private:
	// The chief ant
	ant* a;
	std::set<ant*> selectedAnts;
public:
	explicit selector(ant* a) : a(a) {}

	// Returns const begin iterator of "selectedAnts"
	std::_Rb_tree_const_iterator<ant *> getSelectedAntsBegin();

	// Returns const end iterator of "selectedAnts"
	std::_Rb_tree_const_iterator<ant *> getSelectedAntsEnd();


	// Search an ant with the "x" "y" position.
	// Returns the pointer of the first found ant.
	ant* searchAnt(int x, int y);

	// Append or remove the ant positioned in "x" "y" position.
	// It's supposed to use the mouse position as input.
	// Returns none.
	void singleSelection(int x, int y);

	// Append or remove all the subordinate ant of the "chief" ant. If "chiefToo", then append or remove the "chief" too.
	// Returns none.
	void subSelection(ant* chief, bool chiefToo=false);

	// Set the goal of the selected ants to "goalX" "goalY". Every time it sets an ant's goal,
	// "goalX" is manipulated by the "f" function.
	// Returns none.
	void setGoal(int goalX, int goalY, const std::function<void(int&)>& f=[](int&) {});

	// Deselect all the ants in "selectedAnts".
	// Returns none.
	void deselectAll() { selectedAnts.clear(); }


private:
	// If "s" is not selected, then selects "s" too;
	// Else deselect "s".
	// returns none.
	void selectionAndRemoval(ant* s);
};

std::_Rb_tree_const_iterator<ant *> selector::getSelectedAntsBegin() {
	return selectedAnts.cbegin();
}


std::_Rb_tree_const_iterator<ant *> selector::getSelectedAntsEnd() {
	return selectedAnts.cend();
}

ant *selector::searchAnt(int x, int y) { return a->searchSub({x, y}); }

void selector::singleSelection(int x, int y) { // Single selection
	auto s = searchAnt(x, y);
	selectionAndRemoval(s);
}

void selector::subSelection(ant *chief, bool chiefToo) {
	if(chiefToo)
		selectionAndRemoval(chief);
	if(chief != nullptr)
		for(auto& i: chief->sub)
			selectionAndRemoval(&i);
}

void selector::setGoal(int goalX, int goalY, const std::function<void(int &)> &f) {
	for(auto i: selectedAnts) {
		i->goal = {goalX, goalY};
		f(goalX);
	}
}

void selector::selectionAndRemoval(ant *s) {
	if(s != nullptr) {
		if (selectedAnts.contains(s))
			selectedAnts.erase(s);
		else
			selectedAnts.insert(s);
	}
}


#endif //PROVACLION_SELECTOR_H
