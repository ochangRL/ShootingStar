#pragma once
#include "pch.h"
#include "Enemy.h"

class Image;
class Protoss : public Enemy
{
	int m_moveDirection;
	float m_angle;
	bool m_Protoss_Effect = false;
	int m_direction;
	int m_pattonTime;
	int m_turnCount;
public:
	virtual HRESULT Init(POINT regenPoint, MissileMgr* missileMgr);		// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();		// �޸� ����
	virtual void Update();		// ������ ���� ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);	// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	void MovePatton();
	void SetRegen(bool isRegen) { m_isRegen = isRegen; }
	bool GetRegen() { return m_isRegen; }
	virtual void SetItemMgr(ItemMgr* itemMgr) { m_itemmgr = itemMgr; }
	void Reset();
	void SetUnitPos(FPOINT* unitPos) { m_unitPos = unitPos; }
	void UpdateAniFrame();
};

