#include <iostream>
#include <map>
#include <utility>



using point = std::pair<int, int>;
//using cell = std::pair<point, bool>;

class Universe{
	std::map<point, bool> grid;

	int getLiveNeighbours(point currentPoint){
		int liveNeighbourCount = 0;
		for (int x =-1; x <=1; x++){
			for (int y =-1; y <=1; y++){
				point neighbour = std::make_pair(currentPoint.first+ x, currentPoint.second + y);
				if (neighbour == currentPoint){
					continue;
				}
				std::cout<<(currentPoint.first+ x)<<":"<<(currentPoint.second + y)<<std::endl;
				if (grid[neighbour]){
					liveNeighbourCount++;
					std::cout<<"*"<<std::endl;
				}
			}
		}
		return liveNeighbourCount;
	}
	bool isAlive(point currentPoint){
		return grid[ std::make_pair(currentPoint.first, currentPoint.second)];
	}

	void die(point currentPoint){
		grid[ std::make_pair(currentPoint.first, currentPoint.second)] = false;
	}

	void live(point currentPoint){
		grid[ std::make_pair(currentPoint.first, currentPoint.second)] = true;
	}


	void liveOrDie(point currentPoint, int liveNeighbourCount){
		if (isAlive(currentPoint)){
			if (liveNeighbourCount == 2 || liveNeighbourCount == 3){
				live(currentPoint);
				return;
			}
		}
		if (!isAlive(currentPoint)){
			if (liveNeighbourCount == 3){
				live(currentPoint);
				return;
			}
		}
		die(currentPoint);
	}

public:

	void play(){
		point currentPoint(2,2);
		int liveNeighbourCount = getLiveNeighbours(currentPoint);

	}

};





int main() {

	Universe u;
	u.play();

	return 0;
}
