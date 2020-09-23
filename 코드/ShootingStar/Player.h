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
	virtual HRESULT Init(int charNum, MissileMgr* missileMgr, EnemyMgr* enemyMgr);		// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();		// �޸� ����
	virtual void Update();		// ������ ���� ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);	// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

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

