#include "Terrains.h"
#include "GameConstants.h"



Terrains::Terrains() {
	_numOfTerrains = 1;
	_maps = 0;
	_maps = new int **[MAP_COLUMS];

	for (int i = 0; i < MAP_COLUMS; i++) {
		_maps[i] = new int*[MAP_ROWS];
		for (int j = 0; j < MAP_ROWS; j++) {
			_maps[i][j] = new int[_numOfTerrains];
			_maps[i][j][_numOfTerrains] = SPRITE_TERRAIN_ROAD_HOROZONTAL;
		}

	}
}

Terrains::~Terrains() {}

void Terrains::setNewTerrain(int ** newTerrain) {
	_numOfTerrains++;

	for (int i = 0; i < MAP_COLUMS; i++) {
		_maps[i] = new int*[MAP_ROWS];
		for (int j = 0; j < MAP_ROWS; j++) {
			_maps[i][j] = new int[_numOfTerrains];
			_maps[i][j][_numOfTerrains] = newTerrain[i][j];
		}
	}
}
