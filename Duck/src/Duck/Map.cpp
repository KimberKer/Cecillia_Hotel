#include "Map.h"
#include <iostream>
#include <fstream>

static int MapWidth = 1000;
static int MapHeight = 1000;

static int** MapData;


/******************************************************************************/
/*!
	This function reads the map from txt file.

	NOTE: cannot read the collision binary yet.
 */
 /******************************************************************************/
int MapDatas::GetMapData(const char* filename) {
	std::ifstream file(filename);

	if (!file.is_open()) {
		return 0;
	}
	else {
		//allocate Map
		MapData = new int* [MapHeight];
		for (int i{}; i < MapHeight; i++) {

			MapData[i] = new int[MapWidth];
		}
		//read map
		for (int i = 0; i < MapHeight; i++) {
			for (int j = 0; j < MapWidth; j++) {
				file >> MapData[i][j];
			}
		}
	}
	file.close(); //close file
	return 1;

}

int MapDatas::UpdateMapData(const char* filename) {
	std::ofstream file(filename);

	if (!file.is_open()) {
		return 0;
	}
	for (int i = 0; i < MapHeight; i++) {
		for (int j = 0; j < MapWidth; j++) {
			file << MapData[i][j] << ' ';
		}
		file << '\n';
	}

	file.close();
	return 1;


}
/******************************************************************************/
/*!
	This function free the allocated memory for MapData
 */
 /******************************************************************************/
void MapDatas::FreeMapData(void)
{
	for (int i{}; i < MapHeight; i++) {
		//delete rows
		delete[] MapData[i];
	}

	//delete whole thing
	delete[] MapData;
}


void MapDatas::SnapToCell(float* Coordinate)
{
	*Coordinate = static_cast<int>(*Coordinate) + 0.5f;
}

