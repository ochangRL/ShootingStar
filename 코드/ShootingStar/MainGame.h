#pragma once
#include "pch.h"

class Image;
class BattleScene;
class UIBattle;
class SceneManager;
class Map;
class MainGame
{
private:
	HDC hdc;
	bool isInit;
	HANDLE hTimer;

	HPEN hPen, hOldPen;
	HBRUSH hBrush, hOldBrush;


	SceneManager* m_sceneMgr;
	BattleScene* m_battleScene;
	UIBattle* m_uiBattle;
	Image* bg;
	Map* map;
	

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	LRESULT MainProc(HWND hWnd, UINT iMessage,
		WPARAM wParam, LPARAM lParam);

	float GetAngle(float x1, float y1, float x2, float y2);
	float GetDistance(float x1, float y1, float x2, float y2);
	//bool CheckCollision(Missile* m1, Missile* m2);

	MainGame();
	~MainGame();
};

