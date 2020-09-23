#pragma once
#include "Unit.h"

class MissileMgr;
class Image;
class Ultralisk : public Unit
{
private:
	Image* m_Ultralisk_idleAni;
	bool m_attacked;
public:
	virtual HRESULT Init(MissileMgr* missileMgr, EnemyMgr* enemyMgr);		// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();		// �޸� ����
	virtual void Update();		// ������ ���� ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);	// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	virtual int GetHP() { return m_hp; }
	virtual int GetMaxHP() { return m_maxHp; }
	virtual int GetLevel() { return m_level; }
	virtual bool GetSkill() { return m_isSkillOn; }
	virtual int GetKillCount() { return m_KillCount; }
	virtual int GetBombCount() { return m_BombCount; }
	virtual void SetItem(ItemMgr* itemmgr) { m_itemmgr = itemmgr; }
	virtual bool GetBombDown() { return m_isBombDown; }

	void SetSkill(bool isOn) { m_isSkillOn = isOn; }
	void SetBombSkill(bool isOn) { m_isBombSkillOn = isOn; }
	void UpdateAniFrame();
	void SetPosition();

};

