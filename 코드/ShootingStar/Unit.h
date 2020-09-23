#pragma once
#include "pch.h"

//class Mutalisk;
class EnemyMgr;
class ItemMgr;
class MissileMgr;
class Unit
{
protected:
	FPOINT m_pos;
	int m_maxHp;
	int m_hp;
	float m_speed;
	enum UnitState
	{
		Idle,
		Die,
		Attack
	};
	UnitState m_unitState;
	float m_attackSpeed;
	int m_attackDamage;
	int m_size;
	RECT m_rc;
	int m_currentKeyFrameX;
	int m_updateCount;
	int m_level;
	int m_KillCount;
	bool m_isSkillOn = false;
	bool m_isBombSkillOn = false;
	bool m_isBombDown = false;
	int m_firepoint[3];
	MissileMgr* m_missileMgr;
	ItemMgr* m_itemmgr;
	EnemyMgr* m_enemyMgr;
	int m_time = 0;
	int m_BombCount;
	bool m_isNoDamage;
	int m_currKeyfameX;



public:
	virtual HRESULT Init(MissileMgr* missileMgr, EnemyMgr* enemyMgr) = 0;		// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release() = 0;		// �޸� ����
	virtual void Update() = 0 ;		// ������ ���� ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc) = 0;	// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	virtual int GetHP() = 0;
	virtual int GetMaxHP() = 0;
	virtual int GetLevel() = 0;
	virtual int GetKillCount() = 0;
	virtual bool GetSkill() = 0;
	virtual void SetSkill(bool isOn) = 0;
	virtual void SetBombSkill(bool isOn) = 0;
	virtual int GetBombCount() = 0;
	virtual void SetItem(ItemMgr* itemmgr) = 0;
	virtual bool GetBombDown() = 0;

	FPOINT* GetPos() { return &m_pos; }
	void SetHP(int hp) { m_hp = hp; }
	float GetAttackDamage() { return m_attackDamage; }
	RECT GetRect() { return m_rc; }
};

