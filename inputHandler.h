#ifndef PROVACLION_INPUTHANDLER_H
#define PROVACLION_INPUTHANDLER_H

#include "ant.h"
#include "map.h"
#include <set>
#include <utility>

class inputHandler {
private:
	// The chief ant
	ant* a;
	std::set<ant*> selectedAnts;
public:
	const std::set<ant*> &getSelectedAnts() const;

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
		for(auto& i: chief->sub)
			selectionAndRemoval(&i);
	}

	void subSelectionChiefAnt(bool chiefToo=false) {
		subSelection(a, chiefToo);
	}

};

const std::set<ant*>& inputHandler::getSelectedAnts() const {
	return selectedAnts;
}


#endif //PROVACLION_INPUTHANDLER_H
