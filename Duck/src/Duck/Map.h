
#include <iostream>
#include <fstream>


namespace MapDatas {
	int GetMapData(const char* File);
	int UpdateMapData(const char* filename);
	void FreeMapData(void);
	void SnapToCell(float* Coordinate);
}
