#pragma once
#include "pch.h"
#include "Image.h"

//class UnitPattern;
//class EnemyPattern;
class Missile
{
protected:

	Image m_img;
	FPOINT m_pos;
	FPOINT m_targetpos;
	FPOINT m_ownerPos;
	float m_speed;
	float m_size;
	bool m_isFire;
	bool m_isRegen;
	float m_angle;
	int m_missileSort;
	int m_currFrameX, m_currFrameY;
	int m_updateCount;
public:
	virtual HRESULT Init() = 0;		// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release() = 0;		// �޸� ����
	virtual void Update() = 0;		// ������ ���� ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc) = 0;	// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	virtual void SetRegen(bool isRegen) = 0;
	virtual void SetMissileSort(int missileSort) = 0;
	virtual bool GetRegen() = 0;
	virtual void Reset() = 0;
	virtual void SetIsFire(bool b) = 0;
	virtual bool GetIsFire() = 0;
	virtual void SetUnitPos(FPOINT unitPos) = 0;
	virtual FPOINT GetPos() = 0;
	virtual int GetSize() = 0;
	virtual void SetTargetPos(FPOINT targetPos) = 0;

	virtual void SetFirePoint(int point) = 0;
	virtual void SetAngle(float angle) = 0;
	virtual void SetPos(FPOINT pos) { m_pos = pos; }
	virtual void SetEnemyPos(FPOINT pos) { m_targetpos = pos; }
};