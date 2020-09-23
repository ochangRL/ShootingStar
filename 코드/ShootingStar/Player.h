#pragma once
#include "pch.h"

class ItemMgr;
class MissileMgr;
class EnemyMgr;
class Unit;
class Player
{
	Unit* m_unit;
	int m_selectNum;
	ItemMgr* m_itemMgr;
	EnemyMgr* m_enemyMgr;


public:
	virtual HRESULT Init(int charNum, MissileMgr* missileMgr, EnemyMgr* enemyMgr);		// 멤버 변수 초기화, 메모리 할당
	virtual void Release();		// 메모리 해제
	virtual void Update();		// 프레임 단위 게임 로직 실행 (데이터 변경)
	virtual void Render(HDC hdc);	// 프레임 단위 출력 (이미지, 텍스트 등)

	FPOINT* GetUnitPos();
	int GetUnitHp();
	int GetUnitMaxHP();
	int GetUnitLevel();
	int GetUnitKillCount();
	int GetUnitBombCount();
	bool GetBombDown();

	void SetUnitSkill(bool isOn);
	void SetBombSkill(bool isOn);

	void SetItem(ItemMgr* itemmgr) { m_itemMgr = itemmgr; }
};

