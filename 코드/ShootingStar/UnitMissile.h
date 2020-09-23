
#pragma once
#include "Missile.h"
#include "Image.h"


class UnitMissile : public Missile
{
private:

	Image m_missileSort1Image;
	Image m_missileSort2Image;
	Image m_missileSort3Image;

	int m_firepoint;
public:
	virtual HRESULT Init();		// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();		// �޸� ����
	virtual void Update();		// ������ ���� ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);	// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	virtual void SetIsFire(bool b) { m_isFire = b; }
	virtual bool GetIsFire() { return m_isFire; }
	virtual void SetRegen(bool isRegen) {
		m_isRegen = isRegen;
	}

	virtual void SetMissileSort(int missileSort) { m_missileSort = missileSort; }
	virtual void SetUnitPos(FPOINT unitPos) { m_ownerPos = unitPos; }
	virtual bool GetRegen() { return m_isRegen; }
	virtual void Reset();
	virtual void SetTargetPos(FPOINT targetPos) { m_targetpos = targetPos; }
	virtual FPOINT GetPos() { return m_pos; }
	virtual int GetSize() { return m_size; }

	virtual void SetFirePoint(int point) { m_firepoint = point; }
	virtual void SetAngle(float angle) { m_angle = angle; }
	void SetPos(FPOINT pos) { m_pos = pos; }
	void UpdateAniFrame();
};

