#include <iostream>
#include <map>
#include <utility>
#include <random>
#include <algorithm>
#include <vector>
#include <iterator>
#include <queue>
#include <sstream>
#include <thread>

using point = std::pair<int, int>;
//using cell = std::pair<point, bool>;

constexpr int MIN_LIVE_NEIGHBOURS_TO_SURVIVE = 2;
constexpr int MAX_LIVE_NEIGHBOURS_TO_SURVIVE = 3;
constexpr int LIVE_NEIGHBOURS_TO_ALIVE = 3;

constexpr int GRID_SIZE_X = 10;
constexpr int GRID_SIZE_Y = 10;


   static inline std::string clrscr(void)
      {

	   enum ANSI : char { ESC = 27 };
         std::stringstream ss;
         ss << static_cast<char>(ESC) << "[H"   // home
            << static_cast<char>(ESC) << "[2J"; // clrbos
         return(ss.str());
      }

   //              r/c are 0 based------v------v------0 based



class Universe{
	int sizeX_;
	int sizeY_;
	std::map<point, bool> worldGrid;
	std::vector<std::deque<bool>> historicalData;


	bool isOutsideGrid(point point){
		return ((point.first < 0) || (point.first > sizeX_) || (point.second < 0) || (point.second > sizeY_));
	}

	int getLiveNeighbours(point currentPoint){
		int liveNeighbourCount = 0;
		for (int x =-1; x <=1; x++){
			for (int y =-1; y <=1; y++){
				point neighbour = {currentPoint.first+ x, currentPoint.second + y};
				if ((neighbour == currentPoint) || isOutsideGrid(neighbour)){
					continue;
				}
				if (worldGrid[neighbour]){
					liveNeighbourCount++;
				}
			}
		}
		return liveNeighbourCount;
	}
	bool isAlive(point currentPoint){
		return worldGrid[ {currentPoint.first, currentPoint.second}];
	}

	void die(point currentPoint){
		worldGrid[ {currentPoint.first, currentPoint.second}] = false;
	}

	void live(point currentPoint){
		worldGrid[ {currentPoint.first, currentPoint.second}] = true;
	}


	void liveOrDie(point currentPoint, int liveNeighbourCount){
		if (isAlive(currentPoint)){
			if (liveNeighbourCount >= MIN_LIVE_NEIGHBOURS_TO_SURVIVE && liveNeighbourCount <= MAX_LIVE_NEIGHBOURS_TO_SURVIVE){
				live(currentPoint);
				return;
			}
		}
		if (!isAlive(currentPoint)){
			if (liveNeighbourCount == LIVE_NEIGHBOURS_TO_ALIVE){
				live(currentPoint);
				return;
			}
		}

		if (isAlive(currentPoint)){
				std::cout<<currentPoint.first<< "," << currentPoint.second<<std::endl;
		}
		die(currentPoint);
	}

	bool generateRandomCellState(double probability = 0.5){
		std::random_device rd;
		std::default_random_engine gen(rd());
		std::bernoulli_distribution distr(probability);
		return distr(rd);
	}

	void randomizeCells(){
		for (auto & [point, state] : worldGrid){
			state = generateRandomCellState();
		}
	}

	void print (){ //poc
		for (auto & [point, state] : worldGrid){
			if (state){
				std::cout<<"*";
			} else {
				std::cout<<" ";
			}
			if (point.second == sizeY_){
				std::cout<<std::endl;
			}
		}
		std::cout<<std::endl;

	}

public:

	void reset(int maxX, int maxY){
		randomizeCells();
	}

	Universe(int sizeX, int sizeY) : sizeX_{sizeX}, sizeY_{sizeY} {
		reset(sizeX_, sizeY_);
		for (int x = 0; x <  sizeX_; x++){
			for (int y = 0; y <  sizeY_; y++){
				point newpoint(x,y);
				worldGrid[newpoint] = generateRandomCellState();
			}
		}
	}


	void play(int iteration){
		randomizeCells();
		while (iteration--){
			for (const auto & [point, state] : worldGrid){
				liveOrDie(point, getLiveNeighbours(point));
			}

			std::cout << clrscr() << std::flush; // clears the screen


			print();
			saveStage();

			std::this_thread::sleep_for(std::chrono::milliseconds(400));
		}
	}



	std::vector<std::pair<point, bool>> getWorldAsLinear(){
		std::vector<std::pair<point, bool>> v (worldGrid.begin(), worldGrid.end());
		return v;
	}



	void saveStage (void){
		std::vector<std::pair<point, bool>> serializedCells = getWorldAsLinear();
		std::deque<bool> cellsStatus;
		cellsStatus.resize(serializedCells.size());

		std::transform(serializedCells.begin(), serializedCells.end(), cellsStatus.begin(),
				[](std::pair<point, bool> cell){

			//debug print
		//	std::cout<<cell.second;
			return cell.second;
		});
		//debug print
		std::cout<<std::endl;
		std::cout<<std::endl;

		historicalData.resize(serializedCells.size());
		std::deque<bool>::iterator fromIter = cellsStatus.begin();
		for (std::vector<std::deque<bool>>::iterator toIt = historicalData.begin(); toIt !=historicalData.end(); toIt++){
			(*toIt).push_back(*fromIter++);
		}
	}

	void printCellHistory(int cellNumber){
		std::copy(historicalData[cellNumber].begin(), historicalData[cellNumber].end(), std::ostream_iterator<bool> {std::cout, ","});
		std::cout<<std::endl;
	}



};





int main() {


	Universe u(GRID_SIZE_X, GRID_SIZE_Y);
	u.play(10);
	std::cout<<std::endl;

	u.printCellHistory(0);
	u.printCellHistory(1);
	u.printCellHistory(2);
	u.printCellHistory(3);
	u.printCellHistory(4);
	u.printCellHistory(5);
	u.printCellHistory(6);
	u.printCellHistory(7);
	u.printCellHistory(8);
	u.printCellHistory(9);
	return 0;
}
