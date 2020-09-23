#include "BattleScene.h"
#include "Player.h"
#include "EnemyMgr.h"
#include "MissileMgr.h"
#include "SceneManager.h"
#include "ItemMgr.h"

HRESULT BattleScene::Init(int charNum)
{
	TimeManager::GetSingleton()->ResetWorldTime();

	srand((unsigned int)time(NULL));
	m_itemmgr = new ItemMgr();
	m_itemmgr->Init();
	m_missileMgr = new MissileMgr();
	m_player = new Player();
	m_player->SetItem(m_itemmgr);
	m_enemyMgr = new EnemyMgr();


	m_missileMgr->Init(m_player);
	m_player->Init(charNum, m_missileMgr, m_enemyMgr);
	m_enemyMgr->SetItem(m_itemmgr);
	m_enemyMgr->Init(m_player->GetUnitPos(), m_missileMgr);
	SoundManager::GetSingleton()->Stop("IntroSound");

	SoundManager::GetSingleton()->AddSound("BattleSound", "BGM/BattleBGM.mp3", true, true);
	SoundManager::GetSingleton()->Play("BattleSound");
	return S_OK;
}

void BattleScene::Release()
{
	if (m_player)
	{
		m_player->Release();
		SAFE_DELETE(m_player);
	}
	if (m_enemyMgr)
	{
		m_enemyMgr->Release();
		SAFE_DELETE(m_enemyMgr);
	}
	if (m_missileMgr)
	{
		m_missileMgr->Release();
		SAFE_DELETE(m_missileMgr);
	}
}

void BattleScene::Update()
{
	if (m_player)
	{
		if (m_player->GetUnitHp() <= 0)
		{
			m_sceneMgr->SetCurrScene(3);

		}
		m_player->Update();
	}
	if (m_enemyMgr)
	{
		m_enemyMgr->Update();
		if (m_enemyMgr->CheckBossDead())
		{
			m_sceneMgr->SetCurrScene(3);
			m_sceneMgr->SetIsStageClear(true);
		}
	}
	if (m_missileMgr)
	{
		m_missileMgr->Update();
	}

	if (m_itemmgr)
	{
		m_itemmgr->Update();
	}
}

void BattleScene::Render(HDC hdc)
{
	if (m_player)
	{
		m_player->Render(hdc);
	}

	if (m_enemyMgr)
	{
		m_enemyMgr->Render(hdc);
	}
	if (m_missileMgr)
	{
		m_missileMgr->Render(hdc);
	}

	if (m_itemmgr)
	{
		m_itemmgr->Render(hdc);
	}
}

int BattleScene::GetPlayerHp()
{
	return m_player->GetUnitHp();
}

int BattleScene::GetPlayerMaxHP()
{
	return m_player->GetUnitMaxHP();
}

int BattleScene::GetPlayerLevel()
{
	return m_player->GetUnitLevel();
}

int BattleScene::GetPlayerKillCount()
{
	return m_player->GetUnitKillCount();
}

int BattleScene::GetPlayerBombCount()
{
	return m_player->GetUnitBombCount();
}

void BattleScene::SetPlayerSkill(bool isOn)
{
	m_player->SetUnitSkill(isOn);
}

bool BattleScene::GetPlayerBombDown()
{
	return m_player->GetBombDown();
}


void BattleScene::SetBombSkill(bool isOn)
{
	m_player->SetBombSkill(isOn);
}