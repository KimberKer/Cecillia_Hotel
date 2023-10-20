//---------------------------------------------------------
// File:		Map.h
// 
// authors:		Rina Firdianna binte Raihan
// email:		rinafirdiana.b\@digipen.edu
//
// Brief:       This file declare the mapDataHandler class
//              and functions
//
// Copyright © 2023 DigiPen, All rights reserved.
//---------------------------------------------------------
#pragma once
#include <string>
#include <iostream>

namespace Duck {

    class MapDataHandler {
    private:
        int MapWidth{};
        int MapHeight{};
        std::string file = "";

        //temporary var
        std::string width, w;
        std::string height, h;

        int** MapData;
        int** CollisionData;

        const int COLLISION_LEFT = 0x00000001;
        const int COLLISION_RIGHT = 0x00000002;
        const int COLLISION_TOP = 0x00000004;
        const int COLLISION_BOTTOM = 0x00000008;

    public:

        MapDataHandler() : MapWidth(0), MapHeight(0), MapData{}, CollisionData{}, file{} {};
        int GetMapData(const std::string& filename);
        int UpdateCellData(const std::string& filename, int row, int column, int value);
        void FreeMapData();
        int GetCellValue(int X, int Y);
        std::string GetFile() const;
        int CheckInstanceBinaryMapCollision(float PosX, float PosY,
            float scaleX, float scaleY);
        int SnapToCellX(float cellSize, float x);
        int GetWidth() const;
        int GetHeight() const;
        float SnapToCellY(float cellSize, float y);
        void printMapData();
        void SetWidth(int value);
        void SetHeight(int value);
    };
}
