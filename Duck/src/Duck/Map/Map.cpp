//---------------------------------------------------------
// File:		Map.cpp
// 
// authors:		Rina Firdianna binte Raihan
// email:		rinafirdiana.b\@digipen.edu
//
// Brief:       This file reads map data from a text file,
//				generates binary collision data, and can print 
//				the map data.
//
// Copyright © 2023 DigiPen, All rights reserved.
//---------------------------------------------------------
#include "duckpch.h"
#include "Map.h"

namespace Duck {
	MapDataHandler::MapDataHandler() {
		MapWidth = 0;
		MapHeight = 0;
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
						CollisionData[i][j] = 1;
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


	/******************************************************************************/
	/*!
		This function prints the map
	 */
	 /******************************************************************************/
	void MapDataHandler::printMapData() {
		std::cout << "-----------------MAP--------------" << std::endl;
		std::cout << width << " : " << MapWidth << std::endl;
		std::cout << height << " : " << MapHeight << std::endl;
		for (int i{}; i < MapHeight; i++) {
			for (int j{}; j < MapWidth; j++) {
				std::cout << MapData[i][j] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << "------------------------------------" << std::endl;
	}



	/******************************************************************************/
	/*!
		This function updates the map data
	 */
	 /******************************************************************************/
	int MapDataHandler::UpdateCellData(const char* filename, int row, int column, int value) {
		std::ofstream file(filename);

		if (!file.is_open()) {
			std::cerr << "Failed to open file: " << strerror(errno) << std::endl;
			return 0;
		}

		if (row > MapHeight - 1 && row < MapHeight - 1) {
			std::cerr << "height out of range" << std::endl;
			return 0;
		}
		else if (column > MapWidth - 1 && column < MapWidth - 1) {
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

	/******************************************************************************/
	/*!
		This function gets the cell value
	 */
	 /******************************************************************************/
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
	int MapDataHandler::SnapToCellX(float cellSize, float x) {
		// Calculate the new x and y positions based on the cell size
		x = static_cast<float>(std::round(x / cellSize));
		return static_cast<int>(x);
	}
	float MapDataHandler::SnapToCellY(float cellSize, float y) {
		// Calculate the new x and y positions based on the cell size
		y = std::round((y / cellSize));
		return y;
	}

	/******************************************************************************/
	/*!
		This check the instance of the collision map
	 */
	 /******************************************************************************/
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

}
