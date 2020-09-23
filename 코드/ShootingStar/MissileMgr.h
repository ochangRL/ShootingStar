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
	void Release();		// 메모리 해제
	void Update();		// 프레임 단위 게임 로직 실행 (데이터 변경)
	void Render(HDC hdc);	// 프레임 단위 출력 (이미지, 텍스트 등)

	void AddUnitMissile();
	void AddEnemyMissile();
	void SetMissileRegen(FPOINT unitPoint, int missileSort);
	void SetEnemyMissileRegen(FPOINT enemyPos, int missileSort);
	bool CheckColisionWithEnemy(FPOINT enemyPos, int enemySize);
	bool CheckColisionWithPlayer(FPOINT unitPos, int unitSize);
	
};

