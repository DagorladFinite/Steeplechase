
class Terrains {
private:
	int _numOfTerrains;
	int * * * _maps;

public:
	Terrains();
	~Terrains();

	void setNewTerrain(int * * newTerrain);
	inline int** getTerrain(int pos){ return _maps[pos]; }

};
