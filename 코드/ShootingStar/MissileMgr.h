#pragma once
#include "pch.h"
#include "ObjectPool.h"

class Player;
class Missile;
//class Enemy;
class MissileMgr
{
private:
	ObjectPool<Missile*> m_missilePool;
	Player* m_player;

public:
	//void Init();
	void Init(Player* player);		
	void Release();		// �޸� ����
	void Update();		// ������ ���� ���� ���� ���� (������ ����)
	void Render(HDC hdc);	// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	void AddUnitMissile();
	void AddEnemyMissile();
	void SetMissileRegen(FPOINT unitPoint, int missileSort);
	void SetEnemyMissileRegen(FPOINT enemyPos, int missileSort);
	bool CheckColisionWithEnemy(FPOINT enemyPos, int enemySize);
	bool CheckColisionWithPlayer(FPOINT unitPos, int unitSize);
	
};

