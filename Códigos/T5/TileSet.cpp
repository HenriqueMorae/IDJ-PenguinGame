#include "TileSet.h"
#include "GameObject.h"

TileSet::TileSet(int tileWidth, int tileHeight, std::string file) {
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;

	GameObject* go = new GameObject();
	tileSet = new Sprite(*go, file);

	if(tileSet->IsOpen()) {
		columns = tileSet->GetWidth()/tileWidth;
		rows = tileSet->GetHeight()/tileHeight;
	} else {
		columns = 0;
		rows = 0;
	}
}

void TileSet::RenderTile(unsigned index, float x, float y) {
	unsigned int numeroTiles = columns*rows;

	if (index >= 0 && index < numeroTiles) {
		int linhaOndeEsta = index/columns;
		int colunaOndeEsta = index%columns;

		tileSet->SetClip(colunaOndeEsta*tileWidth, linhaOndeEsta*tileHeight, tileWidth, tileHeight);
		tileSet->Render(x, y);
	}
}

int TileSet::GetTileWidth() {
	return tileWidth;
}

int TileSet::GetTileHeight() {
	return tileHeight;
}
