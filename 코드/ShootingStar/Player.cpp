#include "Player.h"
#include "Defiler.h"
#include "Mutalisk.h"
#include "Ultralisk.h"
#include "MissileMgr.h"
#include "ItemMgr.h"
#include "EnemyMgr.h"

HRESULT Player::Init(int charNum, MissileMgr* missileMgr, EnemyMgr* enemyMgr)
{
	m_enemyMgr = enemyMgr;
	m_selectNum = charNum;
	if (m_selectNum == 0) // 들어갈 조건문
	{
		m_unit = new Ultralisk();
		m_unit->SetItem(m_itemMgr);
		m_unit->Init(missileMgr, enemyMgr);
	}
	else if (m_selectNum == 1) // 들어갈 조건문
	{
		m_unit = new Mutalisk();
		m_unit->SetItem(m_itemMgr);
		m_unit->Init(missileMgr, enemyMgr);
	}
	else if (m_selectNum == 2) // 들어갈 조건문
	{
		m_unit = new Defiler();
		m_unit->SetItem(m_itemMgr);
		m_unit->Init(missileMgr, enemyMgr);
	}

	return S_OK;
}

void Player::Release()
{
	if (m_unit)
	{
		m_unit->Release();
		SAFE_DELETE(m_unit);
	}
}

void Player::Update()
{
	if (m_unit)
	{
		m_unit->Update();
		
	}
}

void Player::Render(HDC hdc)
{
	if (m_unit)
	{
		m_unit->Render(hdc);
	}
}

FPOINT * Player::GetUnitPos()
{
	if (m_unit)
	{
		return m_unit->GetPos();
	}
	return nullptr;
}

int Player::GetUnitHp()
{
	return m_unit->GetHP();
}

int Player::GetUnitMaxHP()
{
	return m_unit->GetMaxHP();
}

int Player::GetUnitLevel()
{
	return m_unit->GetLevel();
}

int Player::GetUnitKillCount()
{
	return m_unit->GetKillCount();
}

bool Player::GetBombDown()
{
	return m_unit->GetBombDown();
}

int Player::GetUnitBombCount()
{
	return m_unit->GetBombCount();
}

void Player::SetUnitSkill(bool isOn)
{
	return m_unit->SetSkill(isOn);
}

void Player::SetBombSkill(bool isOn)
{
	return m_unit->SetBombSkill(isOn);
}