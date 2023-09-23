#include <iostream>
#include <fstream>


class MapDataHandler {
private: 
    int MapWidth;
    int MapHeight;

    //temporary var
    std::string width;
    std::string height;

    int** MapData ;
    int** CollisionData;

    const int COLLISION_LEFT        = 0x00000001;
    const int COLLISION_RIGHT       = 0x00000002;
    const int COLLISION_TOP         = 0x00000004;
    const int COLLISION_BOTTOM      = 0x00000008;

public:

    MapDataHandler();
    int GetMapData(const char* File);
    int UpdateCellData(const char* filename, int row, int column, int value);
    void FreeMapData();
    void SnapToCell(float* Coordinate);
    int GetCellValue(int X, int Y);
    int CheckInstanceBinaryMapCollision(float PosX, float PosY,
    float scaleX, float scaleY);
    void printMapData();
};
