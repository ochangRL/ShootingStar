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

	virtual HRESULT Init(int charNum);		// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();		// �޸� ����
	virtual void Update();		// ������ ���� ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);	// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)


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

