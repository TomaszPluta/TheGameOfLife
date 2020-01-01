#include <iostream>
#include <map>
#include <utility>




class Universe{
public:
	using point = std::pair<int, int> ;
	std::map<point, bool> grid;


	void play(){
		point currentPoint(2,2);
		int liveNeighbourCount = 0;

		if (grid[currentPoint] == false){
			std::cout<<"*"<<std::endl;
		}

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


	}
};





int main() {

	Universe u;
	u.play();

	return 0;
}
