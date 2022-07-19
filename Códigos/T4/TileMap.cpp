#include <fstream>
#include <string>
#include <sstream>
#include "TileMap.h"
#include "Camera.h"

TileMap::TileMap(GameObject& associated, std::string file, TileSet* tileSet) : Component(associated) {
	this->tileSet = tileSet;
	Load(file);
}

TileMap::~TileMap() {

}

void TileMap::Load(std::string file) {
	std::string linha;
	std::string elemento;
	std::ifstream texto(file);
	int indice = 0;

	if (!texto.is_open()) {
		SDL_Log("Unable to load TileMap");
		std::abort();
	}

	while (getline(texto, linha)) {
		std::stringstream line;
		line.str(linha);
		while (getline(line, elemento, ',')) {
			switch (indice) {
				case 0: mapWidth = std::stoi(elemento); indice++; break;
				case 1: mapHeight = std::stoi(elemento); indice++; break;
				case 2: mapDepth = std::stoi(elemento); indice++; break;
				default: tileMatrix.push_back(std::stoi(elemento)-1); break;
			}
		}
	}

	texto.close();
}

void TileMap::SetTileSet(TileSet* tileSet) {
	this->tileSet = tileSet;
}

int& TileMap::At(int x, int y, int z) {
	return tileMatrix.at(x+y*mapWidth+z*mapWidth*mapHeight);
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
	int elementoInicial = layer*mapWidth*mapHeight;
	int elementoFinal = (layer+1)*mapWidth*mapHeight;
	float parallaxX = Camera::pos.x * 0.5f * layer;
	float parallaxY = Camera::pos.y * 0.5f * layer;

	for (int i = elementoInicial; i < elementoFinal; i++) {
		int qualTile = tileMatrix[i];
		int posX = (i%mapWidth)*tileSet->GetTileWidth() + associated.box.x + cameraX;
		int compensacaoY = (i/mapWidth - mapHeight*layer)*tileSet->GetTileHeight();
		int posY = compensacaoY + associated.box.y + cameraY;

		tileSet->RenderTile(qualTile, posX + parallaxX, posY + parallaxY);
	}
}

void TileMap::Render() {
	for (int i = 0; i < mapDepth; i++) {
		RenderLayer(i);
	}
}

int TileMap::GetWidth() {
	return mapWidth;
}

int TileMap::GetHeight() {
	return mapHeight;
}

int TileMap::GetDepth() {
	return mapDepth;
}

void TileMap::Update(float dt) {

}

bool TileMap::Is(std::string type) {
	if (type == "TileMap" || type == "tilemap" || type == "Tilemap" || type == "tileMap") {
		return true;
	} else {
		return false;
	}
}
