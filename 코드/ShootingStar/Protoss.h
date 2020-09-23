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
	virtual HRESULT Init(POINT regenPoint, MissileMgr* missileMgr);		// 멤버 변수 초기화, 메모리 할당
	virtual void Release();		// 메모리 해제
	virtual void Update();		// 프레임 단위 게임 로직 실행 (데이터 변경)
	virtual void Render(HDC hdc);	// 프레임 단위 출력 (이미지, 텍스트 등)

	void MovePatton();
	void SetRegen(bool isRegen) { m_isRegen = isRegen; }
	bool GetRegen() { return m_isRegen; }
	virtual void SetItemMgr(ItemMgr* itemMgr) { m_itemmgr = itemMgr; }
	void Reset();
	void SetUnitPos(FPOINT* unitPos) { m_unitPos = unitPos; }
	void UpdateAniFrame();
};

