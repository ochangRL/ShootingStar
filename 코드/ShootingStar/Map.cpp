#include "Map.h"
#include "Image.h"

void Map::Init()
{
	image = ImageManager::GetSingleton()->AddImage("First", "Map/backGround2.bmp", 800, 1000);
}

void Map::Release()
{
}

void Map::Update()
{

}

void Map::Render(HDC hdc)
{
	if (image)
	{
		image->ScrollRender(hdc, 1000);
	}
}
