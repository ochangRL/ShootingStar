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
	virtual HRESULT Init() = 0;		// 멤버 변수 초기화, 메모리 할당
	virtual void Release() = 0;		// 메모리 해제
	virtual void Update() = 0;		// 프레임 단위 게임 로직 실행 (데이터 변경)
	virtual void Render(HDC hdc) = 0;	// 프레임 단위 출력 (이미지, 텍스트 등)

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