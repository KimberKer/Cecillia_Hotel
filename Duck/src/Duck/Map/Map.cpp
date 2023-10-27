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

	void MapDataHandler::InitializeMap(std::vector<std::shared_ptr<GameObject>> &objectlist, std::shared_ptr<GameObject> m_gameobjList, std::shared_ptr<Duck::GameObject>& p_player) {
		// Reset any game-related variables to their initial values

		// Clear the object list and re-create objects based on the map
		objectlist.clear();

		for (int i = 0; i < MapHeight; i++) {
			for (int j = 0; j < MapWidth; j++) {
				int cellValue = MapData[j][i];
		
				switch (cellValue) {
				case 0:
					objectlist.push_back(m_gameobjList->CreateObj(j, i, STATE_NONE, OBJ_EMPTY));
					break;
				case 1:
					objectlist.push_back(m_gameobjList->CreateObj(j, i, STATE_NONE, OBJ_PLAYER));
					break;
				case 2:
					objectlist.push_back(m_gameobjList->CreateObj(j, i, STATE_NONE, OBJ_OBJ));
					break;
				case 3:
					objectlist.push_back(m_gameobjList->CreateObj(i, j, STATE_NONE, OBJ_GHOST));
					break;
				default:
					break;
				}
			}
		}

		for (int i{}; i < objectlist.size(); i++) {
			if (objectlist[i]->getObj() == OBJ_PLAYER) {
				p_player = objectlist[i];
			}
		}
	}


	MapDataHandler::MapDataHandler(const std::string& filepath){
		filePath = filepath;
		GetMapData();
	}


	/******************************************************************************/
	/*!
		This function reads the map from txt file.
	 */
	 /******************************************************************************/
	int MapDataHandler::GetMapData()
	{
		//file = filename;
		//const std::string path = "../txtfiles/" + filename;
		std::ifstream file(filePath);

		if (!file.is_open()) {
			DUCK_CORE_ERROR("Error: Can't open file");
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
			}
			catch (const std::invalid_argument& e) {
				DUCK_CORE_ERROR("Error: Failed to convert width or height to integer.");
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
			bool foundFirstOne = false;
			//read map
			for (int i = 0; i < MapHeight; i++) {
				for (int j = 0; j < MapWidth; j++) {
					file >> MapData[j][i];
					//checks if there is more than 1 main character
					
				}
			}

			//apply binary collision
			//for (int i = 0; i < MapHeight; i++) {
			//	for (int j = 0; j < MapWidth; j++) {
			//		if (MapData[j][i] == 1) { //wall
			//			CollisionData[j][i] = 1;
			//		}
			//		else {
			//			CollisionData[j][i] = 0;
			//		}

			//	}
			//}
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
		return filePath;
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
				std::cout << MapData[j][i] << " ";
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
	int MapDataHandler::UpdateCellData(int row, int column, int value) {
		std::ifstream inputFile(filePath);
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
				if (j == row && i == column) {
					MapData[j][i] = value;
				}
				file << MapData[j][i] << ' ';
			}
			file << std::endl;
		}

		inputFile.close();
		file.close();
		if (std::remove(filePath.c_str()) != 0) {
			std::cerr << "Error removing original file" << std::endl;
			return 0;
		}
		if (std::rename("../txtfiles/temp.txt", filePath.c_str()) != 0) {
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
			for (int j = 0; j < MapHeight; j++) {
				if (MapData[j][i] == objType) {
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

	int MapIndex = 0;

	const int& GetMapIndex() { return MapIndex; }
	void SetMapIndex(int i) { MapIndex = i; }

}