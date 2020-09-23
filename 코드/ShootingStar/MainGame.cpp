#include "MainGame.h"
#include "macroFunction.h"
#include "Image.h"
#include "BattleScene.h"
#include "UIBattle.h"
#include "SceneManager.h"
#include "Map.h"

Image* backBuffer;

HRESULT MainGame::Init()
{
	hdc = GetDC(g_hWnd);

	// backBuffer
	backBuffer = new Image();
	backBuffer->Init(WINSIZE_X, WINSIZE_Y);

	KeyManager::GetSingleton()->Init();
	ImageManager::GetSingleton()->Init();
	TimeManager::GetSingleton()->Init();
	SoundManager::GetSingleton()->Init();

	m_battleScene = new BattleScene();
	//m_battleScene->Init();

	m_sceneMgr = new SceneManager();
	m_sceneMgr->Init(m_battleScene);

	m_battleScene->SetSceneMgr(m_sceneMgr);

	m_uiBattle = new UIBattle();
	m_uiBattle->Init(m_battleScene);
	//hTimer = (HANDLE)SetTimer(g_hWnd, 0, 10, NULL);

	
	map = new Map;
	map->Init();

	//enemy = new Enemy[10];
	//for (int i = 0; i < 10; i++)
	//{
	//	enemy[i].Init(80 + (i % 5) * 100, 120 + (i / 5) * 80);
	//}

	// BG
	//SoundManager::GetSingleton()->AddSound("Dark Waltz.mp3", "Sound/Dark Waltz.mp3", true, true);*/

	//bg = new Image();
	//bg->Init("Image/background.bmp", WINSIZE_X, WINSIZE_Y);

	isInit = true;

	return S_OK;
}

void MainGame::Release()
{
	m_battleScene->Release();
	SAFE_DELETE(m_battleScene);

	m_uiBattle->Release();
	SAFE_DELETE(m_uiBattle);

	TimeManager::GetSingleton()->Release();
	TimeManager::GetSingleton()->ReleaseSingleton();

	ImageManager::GetSingleton()->Release();
	ImageManager::GetSingleton()->ReleaseSingleton();

	KeyManager::GetSingleton()->Release();
	KeyManager::GetSingleton()->ReleaseSingleton();

	map->Release();
	SAFE_DELETE(map);

	backBuffer->Release();
	delete backBuffer;

	ReleaseDC(g_hWnd, hdc);
}

void MainGame::Update()
{
	//SoundManager::GetSingleton()->Update();
	
	if (m_sceneMgr->GetCurrScene() < 2)
	{
		m_sceneMgr->Update();
	}
	else if (m_sceneMgr->GetCurrScene() == 2)
	{
		if (map)
		{
			map->Update();
		}
		m_battleScene->Update();
		m_uiBattle->Update();
	}
	else if (m_sceneMgr->GetCurrScene() == 3)
	{
		m_sceneMgr->Update();
	}

	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render()
{
	if (m_sceneMgr->GetCurrScene() < 2)
	{
		m_sceneMgr->Render(backBuffer->GetMemDC());
	}
	else if (m_sceneMgr->GetCurrScene() == 2)
	{
		if (map)
		{
			map->Render(backBuffer->GetMemDC());
		}
		m_battleScene->Render(backBuffer->GetMemDC());
		m_uiBattle->Render(backBuffer->GetMemDC());
	}
	else
	{
		m_sceneMgr->Render(backBuffer->GetMemDC());
	}

	TimeManager::GetSingleton()->Render(backBuffer->GetMemDC());

	backBuffer->Render(hdc, 0, 0);
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_TIMER:
		if (isInit)
			this->Update();
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		//if (isInit)
		//	this->Render(hdc);

		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_SPACE:
			//tank->Fire();
			break;
		case VK_LEFT:
			//tank->SetBarrelAngle(tank->GetBarrelAngle() + (PI / 180 * 1));
			break;
		case VK_RIGHT:
			//tank->SetBarrelAngle(tank->GetBarrelAngle() - (PI / 180 * 1));
			break;
		case VK_UP:
			break;
		case VK_DOWN:
			break;
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

float MainGame::GetAngle(float x1, float y1, float x2, float y2)
{
	/*
		tan (theta) = x / y;
					= (x2 - x1) / (y2 - y1);

					atan2( (y2 - y1), (x2 - x1) );
	*/

	return atan2((y2 - y1), (x2 - x1));
}

float MainGame::GetDistance(float x1, float y1, float x2, float y2)
{
	float x = x2 - x1;
	float y = y2 - y1;

	float dist = sqrtf((x * x) + (y * y));

	return dist;
}

//bool MainGame::CheckCollision(Missile * m1, Missile * m2)
//{
//	float halfSize1 = m1->GetSize() / 2;
//	float halfSize2 = m2->GetSize() / 2;
//	FPOINT pos1 = m1->GetPos();
//	FPOINT pos2 = m2->GetPos();
//
//	if ((halfSize1 + halfSize2) >=
//		GetDistance(pos1.x, pos1.y, pos2.x, pos2.y))
//	{
//		return true;
//	}
//
//	return false;
//}

MainGame::MainGame()
	: isInit(false)
{
}


MainGame::~MainGame()
{
}
