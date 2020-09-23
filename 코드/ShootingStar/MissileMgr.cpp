#include "MissileMgr.h"
#include "EnemyMgr.h"
#include "Missile.h"
#include "UnitMissile.h"
#include "EnemyMissile.h"
#include "ObjectPool.h"
#include "Player.h"

//유닛과 적 미사일 구분
void MissileMgr::Init(Player* player)
{
	ImageManager::GetSingleton()->AddImage("UltraliskMissile", "Ultralisk/Missile.bmp", 33, 40, true, RGB(248, 0, 248));
	ImageManager::GetSingleton()->AddImage("MutaliskMissile", "Mutalisk/Missile.bmp", 0, 0, 500, 30, 10, 1, true, RGB(85, 170, 170));
	ImageManager::GetSingleton()->AddImage("DefilerMissile", "Defiler/Missile.bmp", 17,17, true, RGB(0, 0, 0));
	ImageManager::GetSingleton()->AddImage("EnemyMissile", "Enemy/Missile.bmp", 0, 0, 448, 32, 14, 1, true, RGB(248, 0, 248));
	AddEnemyMissile();
	m_player = player;
}


void MissileMgr::Release()
{
	
}

void MissileMgr::Update()
{
	if (m_missilePool.GetPoolSize() != 0)
	{
		m_missilePool.UpdateObj();
	}
}

void MissileMgr::Render(HDC hdc)
{
	if (m_missilePool.GetPoolSize() != 0)
	{
		m_missilePool.RenderObj(hdc);
	}
}


void MissileMgr::AddUnitMissile()
{
	for (int i = 0; i < 120; i++)
	{
		Missile* missile = new UnitMissile();
		missile->Init();
		m_missilePool.AddObject(missile, "UnitMissile");
	}
}
void MissileMgr::AddEnemyMissile()
{
	for (int i = 0; i < 200; i++)
	{
		Missile* missile = new EnemyMissile();
		missile->Init();
		m_missilePool.AddObject(missile, "EnemyMissile");
	}
}

void MissileMgr::SetMissileRegen(FPOINT unitPoint, int missileSort)
{
	m_missilePool.SetOneElementRegenTrue("UnitMissile",unitPoint, missileSort);
}

void MissileMgr::SetEnemyMissileRegen(FPOINT enemyPos, int missileSort)
{
	m_missilePool.SetOneElementRegenTrue("EnemyMissile", enemyPos, missileSort, *(m_player->GetUnitPos()));
}

bool MissileMgr::CheckColisionWithEnemy(FPOINT enemyPos, int enemySize)
{
	return m_missilePool.CheckColision("UnitMissile", enemyPos, enemySize);
}

bool MissileMgr::CheckColisionWithPlayer(FPOINT unitPos, int unitSize)
{
	return m_missilePool.CheckColision1("EnemyMissile", unitPos, unitSize);
}
