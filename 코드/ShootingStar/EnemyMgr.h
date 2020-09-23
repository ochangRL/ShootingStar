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

	virtual HRESULT Init(FPOINT* unitPos, MissileMgr* missileMgr);		// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();		// �޸� ����
	virtual void Update();		// ������ ���� ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);	// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

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

