#include "EnemyMgr.h"
#include "MissileMgr.h"
#include "ObjectPool.h"
#include "Wraith.h"
#include "Scurge.h"
#include "Dragoon.h"
#include "BattleCruiser.h"
#include "Guardian.h"
#include "Queen.h"
#include "Enemy.h"
#include "ItemMgr.h"
#include "Kerrigan.h"
#include "Protoss.h"

HRESULT EnemyMgr::Init(FPOINT* unitPos, MissileMgr* missileMgr)
{
	m_missileMgr = missileMgr;
	AddDragoonEnemy(unitPos);
	AddBattleCruiserEnemy(unitPos);
	AddWraithEnemy(unitPos);
	AddScurgeEnemy(unitPos);
	AddGuardianEnemy(unitPos);
	AddQueenEnemy(unitPos);
	AddKerriganEnemy(unitPos);
	//AddProtossEnemy(unitPos);

	m_pos.x = 0;
	m_pos.y = 0;
	ImageManager::GetSingleton()->AddImage("Missile_Effect", "Effect/aa.bmp", m_pos.x, m_pos.y, 170, 29, 7, 1, true, RGB(255, 255, 255));
	return S_OK;
}

void EnemyMgr::Release()
{

}

void EnemyMgr::Update()
{
	int time = (int)(TimeManager::GetSingleton()->GetWorldTime());
	
	
	if (time < 150)
	{
		if (time % 10 == 9)
		{
			if(m_enemyPool.CheckElementRegen("1Dragoon"))
			m_enemyPool.SetElementRegenTrue("1Dragoon");
		}
		if (time % 20 == 19)
		{
			if (m_enemyPool.CheckElementRegen("2BattleCruiser"))
			m_enemyPool.SetElementRegenTrue("2BattleCruiser");
		}
		if (time % 17 == 16)
		{
			if (m_enemyPool.CheckElementRegen("3Wraith"))
			m_enemyPool.SetElementRegenTrue("3Wraith");
		}

		if (time % 5 == 4)
		{
			if (m_enemyPool.CheckElementRegen("4Scurge"))
			m_enemyPool.SetElementRegenTrue("4Scurge");
		}

		if (time % 15== 13)
		{
			if (m_enemyPool.CheckElementRegen("5Guardian"))
			m_enemyPool.SetElementRegenTrue("5Guardian");
		}

		if (time % 25== 24)
		{
			if (m_enemyPool.CheckElementRegen("6Queen"))
			m_enemyPool.SetElementRegenTrue("6Queen");
		}
		
		/*if (time % 39 == 38)
		{
			if (m_enemyPool.CheckElementRegen("1Protoss"))
			m_enemyPool.SetElementRegenTrue("1Protoss");
		}*/
	}
	else
	{
		if (m_enemyPool.CheckElementRegen("1Kerrigan"))
		m_enemyPool.SetElementRegenTrue("1Kerrigan");

		if (time % 100 == 9)
		{
			if (m_enemyPool.CheckElementRegen("4Scurge"))
				m_enemyPool.SetElementRegenTrue("4Scurge");
		}
	}

	// 배열 전체 업데이트
	if (m_enemyPool.GetPoolSize() != 0)
	{
		m_enemyPool.UpdateObj();
	}
}

void EnemyMgr::Render(HDC hdc)
{
	if (m_enemyPool.GetPoolSize() != 0)
	{
		m_enemyPool.RenderObj(hdc);
	}
}

void EnemyMgr::AddWraithEnemy(FPOINT* unitPos)
{
	m_regenPointArray[0].x = WINSIZE_X / 2;
	m_regenPointArray[0].y = -100;

	m_regenPointArray[1].x = WINSIZE_X / 2 + 100;
	m_regenPointArray[1].y = -100;

	m_regenPointArray[2].x = WINSIZE_X / 2 + 200;
	m_regenPointArray[2].y = -100;


	for (int i = 0; i < 3; i++)
	{
		Enemy* enemy = new Wraith();
		enemy->SetUnitPos(unitPos);
		enemy->Init(m_regenPointArray[i],m_missileMgr);
		enemy->SetItemMgr(m_itemMgr);
		m_enemyPool.AddObject(enemy , "3Wraith");
	}
}

void EnemyMgr::AddScurgeEnemy(FPOINT* unitPos)
{
	m_regenPointArray[0].x = 0;
	m_regenPointArray[0].y = -100;

	m_regenPointArray[1].x = 0;
	m_regenPointArray[1].y = -200;

	m_regenPointArray[2].x = 0;
	m_regenPointArray[2].y = -300;


	for (int i = 0; i < 3; i++)
	{
		Enemy* enemy = new Scurge();
		enemy->SetUnitPos(unitPos);
		enemy->Init(m_regenPointArray[i], m_missileMgr);
		enemy->SetItemMgr(m_itemMgr);
		m_enemyPool.AddObject(enemy, "4Scurge");
	}
}

void EnemyMgr::AddBattleCruiserEnemy(FPOINT* unitPos)
{
	m_regenPointArray[0].x = -200;
	m_regenPointArray[0].y = 1200;

	m_regenPointArray[1].x = 1000;
	m_regenPointArray[1].y = 1200;



	for (int i = 0; i < 2; i++)
	{
		Enemy* enemy = new BattleCruiser();
		enemy->SetUnitPos(unitPos);
		enemy->Init(m_regenPointArray[i], m_missileMgr);
		enemy->SetItemMgr(m_itemMgr);
		m_enemyPool.AddObject(enemy, "2BattleCruiser");
	}
}

void EnemyMgr::AddDragoonEnemy(FPOINT* unitPos)
{
	m_regenPointArray[0].x = 200;
	m_regenPointArray[0].y = -300;

	m_regenPointArray[1].x = 600;
	m_regenPointArray[1].y = -600;



	for (int i = 0; i < 2; i++)
	{
		Enemy* enemy = new Dragoon();
		enemy->SetUnitPos(unitPos);
		enemy->Init(m_regenPointArray[i], m_missileMgr);
		enemy->SetItemMgr(m_itemMgr);
		m_enemyPool.AddObject(enemy, "1Dragoon");
	}
}

void EnemyMgr::AddGuardianEnemy(FPOINT * unitPos)
{
	m_regenPointArray[0].x = -200;
	m_regenPointArray[0].y = 100;

	m_regenPointArray[1].x = -400;
	m_regenPointArray[1].y = 100;

	m_regenPointArray[2].x = -600;
	m_regenPointArray[2].y = 100;


	for (int i = 0; i < 3; i++)
	{
		Enemy* enemy = new Guardian();
		enemy->SetUnitPos(unitPos);
		enemy->Init(m_regenPointArray[i], m_missileMgr);
		enemy->SetItemMgr(m_itemMgr);
		m_enemyPool.AddObject(enemy, "5Guardian");
	} 
}

void EnemyMgr::AddQueenEnemy(FPOINT * unitPos)
{
	m_regenPointArray[0].x = 220;
	m_regenPointArray[0].y = -100;

	m_regenPointArray[1].x = 220;
	m_regenPointArray[1].y = -200;

	m_regenPointArray[2].x = 220;
	m_regenPointArray[2].y = -300;


	for (int i = 0; i < 3; i++)
	{
		Enemy* enemy = new Queen();
		enemy->SetUnitPos(unitPos);
		enemy->Init(m_regenPointArray[i], m_missileMgr);
		enemy->SetItemMgr(m_itemMgr);
		m_enemyPool.AddObject(enemy, "6Queen");
	}
}

void EnemyMgr::AddKerriganEnemy(FPOINT* unitPos)
{
	m_regenPointArray[0].x = WINSIZE_X / 2;
	m_regenPointArray[0].y = -300;

	Enemy* enemy = new Kerrigan();
	enemy->SetUnitPos(unitPos);
	enemy->Init(m_regenPointArray[0], m_missileMgr);
	enemy->SetItemMgr(m_itemMgr);
	m_enemyPool.AddObject(enemy, "1Kerrigan");
}

void EnemyMgr::AddProtossEnemy(FPOINT * unitPos)
{
	m_regenPointArray[0].x = 200;
	m_regenPointArray[0].y = -100;

	m_regenPointArray[1].x = 400;
	m_regenPointArray[1].y = -200;


	/*for (int i = 0; i < 2; i++)
	{
		Enemy* enemy = new Protoss();
		enemy->SetUnitPos(unitPos);
		enemy->Init(m_regenPointArray[i], m_missileMgr);
		m_enemyPool.AddObject(enemy, "1Protoss");
	}*/
}

bool EnemyMgr::CheckBossDead()
{
	return m_enemyPool.CheckBossDead("1Kerrigan");
}

void EnemyMgr::ActivateBomb()
{
	m_enemyPool.ActivateBomB();
}
