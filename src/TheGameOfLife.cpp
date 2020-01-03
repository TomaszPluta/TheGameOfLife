#include <iostream>
#include <map>
#include <utility>
#include <random>


using point = std::pair<int, int>;
//using cell = std::pair<point, bool>;

constexpr int MIN_LIVE_NEIGHBOURS_TO_SURVIVE = 2;
constexpr int MAX_LIVE_NEIGHBOURS_TO_SURVIVE = 3;
constexpr int LIVE_NEIGHBOURS_TO_ALIVE = 3;

constexpr int GRID_SIZE_X = 10;
constexpr int GRID_SIZE_Y = 10;

class Universe{
	int sizeX_;
	int sizeY_;
	std::map<point, bool> wordGrid;

	bool isOutsideGrid(point point){
		return ((point.first < 0) || (point.first > sizeX_) || (point.second < 0) || (point.second > sizeY_));
	}

	int getLiveNeighbours(point currentPoint){
		int liveNeighbourCount = 0;
		for (int x =-1; x <=1; x++){
			for (int y =-1; y <=1; y++){
				point neighbour = std::make_pair(currentPoint.first+ x, currentPoint.second + y);
				if ((neighbour == currentPoint) || isOutsideGrid(neighbour)){
					continue;
				}

//				std::cout<<(currentPoint.first+ x)<<":"<<(currentPoint.second + y)<<std::endl;
				if (wordGrid[neighbour]){
					liveNeighbourCount++;
					std::cout<<"*"<<std::endl;
				}
			}
		}
		return liveNeighbourCount;
	}
	bool isAlive(point currentPoint){
		return wordGrid[ std::make_pair(currentPoint.first, currentPoint.second)];
	}

	void die(point currentPoint){
		wordGrid[ std::make_pair(currentPoint.first, currentPoint.second)] = false;
	}

	void live(point currentPoint){
		wordGrid[ std::make_pair(currentPoint.first, currentPoint.second)] = true;
	}


	void liveOrDie(point currentPoint, int liveNeighbourCount){
		if (isAlive(currentPoint)){
			if (liveNeighbourCount >= MIN_LIVE_NEIGHBOURS_TO_SURVIVE || liveNeighbourCount <= MAX_LIVE_NEIGHBOURS_TO_SURVIVE){
				live(currentPoint);
				std::cout<<(currentPoint.first)<<":"<<(currentPoint.second)<<" alive live!"<<std::endl;
				return;
			}
		}
		if (!isAlive(currentPoint)){
			if (liveNeighbourCount == LIVE_NEIGHBOURS_TO_ALIVE){
				std::cout<<(currentPoint.first)<<":"<<(currentPoint.second)<<" died live!"<<std::endl;
				live(currentPoint);
				return;
			}
		}

		std::cout<<(currentPoint.first)<<":"<<(currentPoint.second)<<" is dead"<<std::endl;
		die(currentPoint);
	}

public:

	void reset(int maxX, int maxY){
			for (int x = 0; x <  maxX; x++){
				for (int y = 0; y <  maxY; y++){
					point newpoint(x,y);
					wordGrid[newpoint] = false;
				}
			}
		}

	Universe(int sizeX, int sizeY) : sizeX_{sizeX}, sizeY_{sizeY} {
		reset(sizeX_, sizeY_);
	}


	void randomizeCells(){
		  std::random_device rd;
		  //TODO:: ...
	}

	void play(void){
		randomizeCells();
		for (const auto & [point, state] : wordGrid){
				liveOrDie(point, getLiveNeighbours(point));
		}
	}

};





int main() {

	Universe u(GRID_SIZE_X, GRID_SIZE_Y);
	u.play();

	return 0;
}
