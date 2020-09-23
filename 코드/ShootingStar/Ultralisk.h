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
	virtual HRESULT Init(MissileMgr* missileMgr, EnemyMgr* enemyMgr);		// 멤버 변수 초기화, 메모리 할당
	virtual void Release();		// 메모리 해제
	virtual void Update();		// 프레임 단위 게임 로직 실행 (데이터 변경)
	virtual void Render(HDC hdc);	// 프레임 단위 출력 (이미지, 텍스트 등)

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

