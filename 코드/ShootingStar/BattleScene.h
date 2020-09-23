#pragma once
#include "pch.h"

class Player;
class EnemyMgr;
class MissileMgr;
class SceneManager;
class ItemMgr;
class BattleScene
{
	Player* m_player;
	EnemyMgr* m_enemyMgr;
	MissileMgr* m_missileMgr;
	SceneManager* m_sceneMgr;
	ItemMgr* m_itemmgr;

public:

	virtual HRESULT Init(int charNum);		// 멤버 변수 초기화, 메모리 할당
	virtual void Release();		// 메모리 해제
	virtual void Update();		// 프레임 단위 게임 로직 실행 (데이터 변경)
	virtual void Render(HDC hdc);	// 프레임 단위 출력 (이미지, 텍스트 등)


	void SetSceneMgr(SceneManager* sceneMgr) { m_sceneMgr = sceneMgr; };
	int GetPlayerHp();
	int GetPlayerMaxHP();
	int GetPlayerLevel();
	int GetPlayerKillCount();
	int GetPlayerBombCount();
	bool GetPlayerBombDown();
	void SetPlayerSkill(bool isOn);
	void SetBombSkill(bool isOn);
};

