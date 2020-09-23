#pragma once
#include "pch.h"
#include "Enemy.h"

class Image;
class Scurge : public Enemy
{
	//Image* m_idleImage;
	bool m_isFired;

public:
	virtual HRESULT Init(POINT regenPoint, MissileMgr* missileMgr);		// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();		// �޸� ����
	virtual void Update();		// ������ ���� ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);	// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)
	virtual void SetItemMgr(ItemMgr* itemMgr) { m_itemmgr = itemMgr; }
	void MovePatton();
	void SetRegen(bool isRegen) { m_isRegen = isRegen; }
	bool GetRegen() { return m_isRegen; }
	void Reset();
	void SetUnitPos(FPOINT* unitPos) { m_unitPos = unitPos; }
	void UpdateAniFrame();
	bool GetIsEnemyBoss() { return m_isEnemyBoss; }
};

