#pragma once
#include "Missile.h"

class Image;
class Enemy;
class EnemyMissile : public Missile
{
private:
	int m_firepoint;
	bool m_isReachedPlayer = false;
	float m_savedAngle;
	float m_size; //추후생각
public:
	virtual HRESULT Init();		// 멤버 변수 초기화, 메모리 할당
	virtual void Release();		// 메모리 해제
	virtual void Update();		// 프레임 단위 게임 로직 실행 (데이터 변경)
	virtual void Render(HDC hdc);	// 프레임 단위 출력 (이미지, 텍스트 등)

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

	void MissileToUnitPatton();
	void MissileToUnitPatton1();
	void MissileToUnitPatton2();
	

	EnemyMissile();
	~EnemyMissile();
};

