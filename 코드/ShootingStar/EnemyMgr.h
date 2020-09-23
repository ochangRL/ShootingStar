#pragma once
#include "pch.h"
#include "ObjectPool.h"

class ItemMgr;
class MissileMgr;
class Enemy;
class EnemyMgr
{
private:
	ItemMgr* m_itemMgr;
	ObjectPool<Enemy*> m_enemyPool;
	POINT m_regenPointArray[3];
	MissileMgr* m_missileMgr;
	FPOINT m_pos;

public:

	virtual HRESULT Init(FPOINT* unitPos, MissileMgr* missileMgr);		// 멤버 변수 초기화, 메모리 할당
	virtual void Release();		// 메모리 해제
	virtual void Update();		// 프레임 단위 게임 로직 실행 (데이터 변경)
	virtual void Render(HDC hdc);	// 프레임 단위 출력 (이미지, 텍스트 등)

	void AddWraithEnemy(FPOINT* unitPos);
	void AddScurgeEnemy(FPOINT* unitPos);
	void AddBattleCruiserEnemy(FPOINT* unitPos);
	void AddDragoonEnemy(FPOINT* unitPos);
	void AddGuardianEnemy(FPOINT* unitPos);
	void AddQueenEnemy(FPOINT* unitPos);
	void AddKerriganEnemy(FPOINT* unitPos);
	void AddProtossEnemy(FPOINT* unitPoss);
	bool CheckBossDead();
	void ActivateBomb();

	void SetItem(ItemMgr* itemmgr) { m_itemMgr = itemmgr; }
};

