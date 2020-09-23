#pragma once
#include "pch.h"
#include "Enemy.h"

class MissileMgr;
class Kerrigan : public Enemy
{
	float m_angle;
	bool m_isposx, m_isposy;
	bool m_y, m_x;
	int m_time;

public:
	virtual HRESULT Init(POINT regenPoint, MissileMgr* missileMgr);		// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();		// �޸� ����
	virtual void Update();		// ������ ���� ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);	// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)
	void MovePatton();
	void SetRegen(bool isRegen) { m_isRegen = isRegen; }
	bool GetRegen() { return m_isRegen; }
	void Reset();
	void SetUnitPos(FPOINT* unitPos) { m_unitPos = unitPos; }
	virtual void SetItemMgr(ItemMgr* itemMgr) { m_itemmgr = itemMgr; }
	void UpdateAniFrame();
	bool GetIsEnemyBoss() { return m_isEnemyBoss; }
};

