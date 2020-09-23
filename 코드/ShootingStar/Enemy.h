#pragma once
#include "pch.h"
#include "Image.h"

class ItemMgr;
class MissileMgr;
class Enemy
{
protected:
	MissileMgr* m_missileMgr;
	FPOINT m_pos;
	FPOINT m_regenPos;
	FPOINT* m_unitPos;
	ItemMgr* m_itemmgr;

	Image m_idleImage;
	bool m_isEnemyBoss = false;
	int m_maxHp;
	int m_hp;
	bool m_isGameClear;
	float m_speed;
	enum EnemyState
	{
		Idle,
		Die,
		Stop,
		Attacked
	};

	EnemyState m_enemyState;
	float m_attackSpeed;
	int m_attackDamage;
	int m_size;
	RECT m_rc;
	int m_currentKeyFrameX;
	int m_updateCount;
	int m_currentMovePatton;
	bool m_isRegen;
	float m_time;

	


	

public:
	virtual HRESULT Init(POINT regenPoint, MissileMgr* missileMgr) = 0;		// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release() = 0;		// �޸� ����
	virtual void Update() = 0 ;		// ������ ���� ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc) = 0;	// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	virtual void MovePatton() = 0;
	virtual void SetRegen(bool isRegen) = 0;
	virtual bool GetRegen() = 0;
	virtual void Reset() = 0;
	virtual void SetUnitPos(FPOINT* unitPos) = 0;
	virtual void SetItemMgr(ItemMgr* itemMgr) = 0;
	virtual bool GetIsGameClear() { return m_isGameClear; }
	virtual bool GetIsEnemyBoss() = 0;

	FPOINT GetPos() { return m_pos; }
	int GetHP() { return m_hp; }
	void SetHP(int hp) { m_hp = hp; }
	float GetAttackDamage() { return m_attackDamage; }
	RECT GetRect() { return m_rc; }
};

