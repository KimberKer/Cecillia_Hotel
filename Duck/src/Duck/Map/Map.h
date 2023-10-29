//---------------------------------------------------------
// File:		Map.h
// 
// authors:		Rina Firdianna binte Raihan
// email:		rinafirdiana.b\@digipen.edu
//
// Brief:       This file declare the mapDataHandler class
//              and functions
//
// Copyright   2023 DigiPen, All rights reserved.
//---------------------------------------------------------
#pragma once
#include <string>
#include <iostream>
#include "../De-serialize/GameObject.h"
#include "Duck/Log.h"
#include "../Ghost/AI.h"
#include "../Math/Vector2D.h"

namespace Duck {

    class MapDataHandler {
    private:
        Duck::AABB aabb;
        int MapWidth{};
        int MapHeight{};
        std::string filePath;
        //temporary var
        std::string width, w;
        std::string height, h;
        float ghost_x, ghost_y;


        int** MapData;
        int** CollisionData;

        const int COLLISION_LEFT = 0x00000001;
        const int COLLISION_RIGHT = 0x00000002;
        const int COLLISION_TOP = 0x00000004;
        const int COLLISION_BOTTOM = 0x00000008;



    public:
        
        MapDataHandler(const std::string& filePath);
        int GetMapData();
        int UpdateCellData(int row, int column, int value);
        void FreeMapData();
        int GetCellValue(int X, int Y);
        std::string GetFile() const;
        int CheckInstanceBinaryMapCollision(float PosX, float PosY,
            float scaleX, float scaleY);
        int SnapToCellX(float cellSize, float x);
        int GetWidth() const;
        int GetNumberOfObjects(int getType);
        int GetHeight() const;
        float SnapToCellY(float cellSize, float y);
        void printMapData();
        void SetWidth(int value);
        void SetHeight(int value);
        void InitializeMap(std::vector<std::shared_ptr<GameObject>>& objectlist, std::shared_ptr<GameObject> m_gameobjList, std::shared_ptr<Duck::GameObject>& p_player, Ghost ghost, uint32_t image[]);
        float GetGhostPositionX();
        float GetGhostPositionY();
    };

    const int& GetMapIndex();
    void SetMapIndex(int i);

}
