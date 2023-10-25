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
// Copyright   2023 DigiPen, All rights reserved.
//---------------------------------------------------------
#include "duckpch.h"
#include "Map.h"

namespace Duck {


	/*MapDataHandler::MapDataHandler() {
		MapWidth = 0;
		MapHeight = 0;
		MapData = nullptr;
		CollisionData = nullptr;
	}*/

	/******************************************************************************/
	/*!
		This function reads the map from txt file.
	 */
	 /******************************************************************************/
	int MapDataHandler::GetMapData(const std::string& filename)
	{
		file = filename;
		//const std::string path = "../txtfiles/" + filename;
		std::ifstream file(filename);

		if (!file.is_open()) {
			perror(filename.c_str());
			return 0;
		}
		else {
			std::string width, w;
			std::string height, h;
			file >> width >> w;
			file >> height >> h;

			try {
				SetWidth(std::stoi(w));
				SetHeight(std::stoi(h));
				std::cout << MapWidth << std::endl;
			}
			catch (const std::invalid_argument& e) {
				std::cerr << "Error: Failed to convert width or height to integer." << std::endl;
				file.close(); // Close the file
				return 0;
			}


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
		This function gets the width
	 */
	 /******************************************************************************/
	int MapDataHandler::GetWidth() const{
		return MapWidth;
	}

	/******************************************************************************/
	/*!
		This function returns file
	 */
	 /******************************************************************************/
	std::string MapDataHandler::GetFile() const {
		return file;
	}

	/******************************************************************************/
	/*!
		This function gets the width
	 */
	 /******************************************************************************/
	int MapDataHandler::GetWidth() const {
		return MapWidth;
	}

	/******************************************************************************/
	/*!
		This function returns file
	 */
	 /******************************************************************************/
	std::string MapDataHandler::GetFile() const {
		return file;
	}

	/******************************************************************************/
	/*!
		This function gets the height
	 */
	 /******************************************************************************/
	int MapDataHandler::GetHeight() const {
		return MapHeight;
	}

	/******************************************************************************/
	/*!
		This function prints the map
	 */
	 /******************************************************************************/
	void MapDataHandler::printMapData() {

		std::cout << "-----------------MAP--------------" << std::endl;
		std::cout << "Width : " << MapWidth << std::endl;
		std::cout << "Height : " << MapHeight << std::endl;
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
	int MapDataHandler::UpdateCellData(const std::string& filename, int row, int column, int value) {
		std::ifstream inputFile(filename);
		std::ofstream file("../txtfiles/temp.txt");

		if (!inputFile.is_open() || !file.is_open()) {
			DUCK_CORE_ERROR("Failed to open file: 1 ");;
			return 0;
		}

		if (row >= MapHeight || column >= MapWidth) {
			DUCK_CORE_ERROR("Row or column out of range");
			file.close();
			inputFile.close();
			return 0;
		}

		// Update the specific cell and write it to the file

		file << "Width: " << MapWidth << std::endl;
		file << "Height: " << MapHeight << std::endl;
		file << std::endl;
		for (int i = 0; i < MapHeight; i++) {
			for (int j = 0; j < MapWidth; j++) {
				if (i == row && j == column) {
					MapData[i][j] = value;
				}
				file << MapData[i][j] << ' ';
			}
			file << std::endl;
		}

		inputFile.close();
		file.close();
		if (std::remove(filename.c_str()) != 0) {
			std::cerr << "Error removing original file" << std::endl;
			return 0;
		}
		if (std::rename("../txtfiles/temp.txt", filename.c_str()) != 0) {
			DUCK_CORE_ERROR("Error renaming file");
			return 0;
		}
		return 1;
	}


	/******************************************************************************/
	/*!
		This function free the allocated memory for MapData
	 */
	 /******************************************************************************/
	void MapDataHandler::FreeMapData()
	{
		//for (int i{}; i < MapHeight; i++) {
		//	//delete rows
		//	delete[] MapData[i];
		//}

		////delete whole thing
		//delete[] MapData;
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
			return MapData[Y][X];
		}
	}
	int MapDataHandler::GetNumberOfObjects(int objType) {
		int count{};
		for (int i = 0; i < MapHeight; i++) {
			for (int j = 0; j < MapWidth; j++) {
				if (MapData[i][j] == objType) {
					count++;
				}
			}
		}
		return count;
	}
	/******************************************************************************/
	/*!
		These functions snap to Cell
	 */
	 /******************************************************************************/
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

	void MapDataHandler::SetWidth(int value)
	{
		MapWidth = value;
	}
	void MapDataHandler::SetHeight(int value)
	{
		MapHeight = value;
	}
}