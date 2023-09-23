#include "duckpch.h"
#include "Map.h"


MapDataHandler::MapDataHandler() {
	MapWidth =0;
	MapHeight =0;
	MapData = nullptr;
	CollisionData = nullptr;
}

/******************************************************************************/
/*!
	This function reads the map from txt file.
 */
 /******************************************************************************/
int MapDataHandler::GetMapData(const char* FileName)
{
	std::ifstream file(FileName);

	if (!file.is_open()) {
		return 0;
	}
	else {
		file >> width >> MapWidth;
		file >> height >> MapHeight;


		//allocate map
		MapData = new int* [MapHeight];
		for (int i{}; i < MapHeight; i++) {

			MapData[i] = new int[MapWidth];
		}

		//alocate binary
		CollisionData = new int* [MapHeight];
		for (int i{}; i < MapHeight; i++) {

			CollisionData[i] = new int[MapWidth];
		}

		//read map
		for (int i = 0; i < MapHeight; i++) {
			for (int j = 0; j < MapWidth; j++) {
				file >> MapData[i][j];
			}
		}

		//apply binary collision
		for (int i = 0; i < MapHeight; i++) {
			for (int j = 0; j < MapWidth; j++) {
				if (MapData[i][j] == 1) { //wall
					CollisionData[i][j] > 1;
				}
				else {
					CollisionData[i][j] = 0;
				}

			}
		}
	}

	file.close(); //close file
	return 1;

}



void MapDataHandler::printMapData() {
	std::cout << "-----------------MAP--------------" << std::endl;
	std::cout << width<<" : " << MapWidth << std::endl;
	std::cout << height<<" : " << MapHeight << std::endl;
	for (int i{}; i < MapHeight; i++) {
		for (int j{}; j < MapWidth; j++) {
			std::cout << MapData[i][j]<< " ";
		}
		std::cout << std::endl;
	} 
	std::cout << "------------------------------------" << std::endl;
}



int MapDataHandler::UpdateCellData(const char* filename , int row, int column, int value) {
	std::ofstream file(filename);

	if (!file.is_open()) {
		std::cerr << "Failed to open file: " << strerror(errno) << std::endl;
		return 0;
	}

	if (row > MapHeight-1 && row < MapHeight-1) {
		std::cerr << "height out of range" << std::endl;
		return 0;
	}
	else if (column > MapWidth-1 && column < MapWidth-1) {
		std::cerr << "width out of range" << std::endl;
		return 0;
	}

	for (int i = 0; i < MapHeight; i++) {
		for (int j = 0; j < MapWidth; j++) {
			MapData[row][column] = value;
			file << MapData[i][j] << ' ';
		}
		file << std::endl;
	}

	file.close();
	return 1;


}


/******************************************************************************/
/*!
	This function free the allocated memory for MapData
 */
 /******************************************************************************/
void MapDataHandler::FreeMapData(void)
{
	for (int i{}; i < MapHeight; i++) {
		//delete rows
		delete[] MapData[i];
	}

	//delete whole thing
	delete[] MapData;
}


void MapDataHandler::SnapToCell(float* Coordinate)
{
	*Coordinate = static_cast<int>(*Coordinate) + 0.5f;
}

int MapDataHandler::GetCellValue(int X, int Y)
{
	/*UNREFERENCED_PARAMETER(X);
	UNREFERENCED_PARAMETER(Y); */
	if (X < 0 || X >= MapWidth || Y < 0 || Y >= MapHeight) {
		return 0;
	}
	else {
		return CollisionData[Y][X];
	}
}

int MapDataHandler::CheckInstanceBinaryMapCollision(float PosX, float PosY,
	float scaleX, float scaleY)
{
	int Flag{};
	float x1, x2, y1, y2;

	//right side
	x1 = PosX + scaleX / 2;
	y1 = PosY + scaleY / 4;

	x2 = PosX + scaleX / 2;
	y2 = PosY - scaleY / 4;

	if (GetCellValue(static_cast<int>(x1), static_cast<int>(y1)) || GetCellValue(static_cast<int>(x2), static_cast<int>(y2)))
	{
		Flag |= COLLISION_RIGHT;
	}

	//left side
	x1 = PosX - scaleX / 2;
	y1 = PosY - scaleY / 4;

	x2 = PosX - scaleX / 2;
	y2 = PosY + scaleY / 4;


	if (GetCellValue(static_cast<int>(x1), static_cast<int>(y1)) || GetCellValue(static_cast<int>(x2), static_cast<int>(y2)))
	{
		Flag |= COLLISION_LEFT;
	}

	//top side
	x1 = PosX - scaleX / 4;
	y1 = PosY + scaleY / 2;

	x2 = PosX + scaleX / 4;
	y2 = PosY + scaleY / 2;


	if (GetCellValue(static_cast<int>(x1), static_cast<int>(y1)) || GetCellValue(static_cast<int>(x2), static_cast<int>(y2))) {
		Flag |= COLLISION_TOP;
	}

	//BOTTOM side
	x1 = PosX + scaleX / 4;
	y1 = PosY - scaleY / 2;

	x2 = PosX - scaleX / 4;
	y2 = PosY - scaleY / 2;


	if (GetCellValue(static_cast<int>(x1), static_cast<int>(y1)) || GetCellValue(static_cast<int>(x2), static_cast<int>(y2))) {
		Flag |= COLLISION_BOTTOM;
	}
	return Flag;
}


/*
void CheckCollision() {
	pInst->gridCollisionFlag = CheckInstanceBinaryMapCollision(pInst->posCurr.x, pInst->posCurr.y, pInst->scale.x, pInst->scale.y);

	//collision from bottom
	if (pInst->gridCollisionFlag & COLLISION_BOTTOM) {
		//snap to cell
		SnapToCell(&pInst->posCurr.y);
		//Velocity y=0
		pInst->velCurr.y = 0;
	}

	//collsion top
	if (pInst->gridCollisionFlag & COLLISION_TOP) {
		//snap to cell
		SnapToCell(&pInst->posCurr.y);
		//Velocity y=0
		pInst->velCurr.y = 0;
	}
	//collsion left
	if (pInst->gridCollisionFlag & COLLISION_LEFT) {
		//snap to cell
		SnapToCell(&pInst->posCurr.x);
		//velocity x =0 
		pInst->velCurr.x = 0;
	}
	//collsion right
	if (pInst->gridCollisionFlag & COLLISION_RIGHT) {
		//snap to cell
		SnapToCell(&pInst->posCurr.x);
		//velocity x =0 
		pInst->velCurr.x = 0;
	}
}
*/
