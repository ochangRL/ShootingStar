#include "BattleCruiser.h"
#include "pch.h"
#include "Image.h"
#include "MissileMgr.h"
#include "ObjectPool.h"
#include "ItemMgr.h"

HRESULT BattleCruiser::Init(POINT regenPoint, MissileMgr* missileMgr)
{
	m_missileMgr = missileMgr;

	m_regenPos.x = regenPoint.x;
	m_regenPos.y = regenPoint.y;
	Reset();

	//m_idleImage = new Image();
	m_idleImage = *ImageManager::GetSingleton()->AddImage("BattleCruiserIdle", "Enemy/BattleCruiserIdle.bmp",
		73, 75, true, RGB(255, 255, 255));

	ImageManager::GetSingleton()->AddImage("Enemy_Die_03", "Effect/Effect_16_half.bmp", m_pos.x, m_pos.y, 384 * 4, 35 * 4, 12, 1, true, RGB(0, 0, 0));

	m_isRegen = false;

	return S_OK;
}

void BattleCruiser::Release()
{

}

void BattleCruiser::Update()
{
	FPOINT pos;
	pos.x = m_pos.x + 40;
	pos.y = m_pos.y + 40;
	if (m_missileMgr->CheckColisionWithEnemy(m_pos, m_size) && m_enemyState != Die)
	{
		m_enemyState = Attacked;
		m_hp -= 30;
	}

	if (&m_idleImage)
	{
		if (m_hp <= 0)
		{
			m_enemyState = Die;
		}
		else
		{
			m_time += TIME_MULTIPLE * TimeManager::GetSingleton()->GetDeltaTime();
			this->MovePatton();
		}
	}

	if ((int)m_time % 25 == 24 && m_time > 150 && m_enemyState != Die)
	{
		FPOINT pos;
		pos.x = m_pos.x + 40;
		pos.y = m_pos.y + 80;

		m_missileMgr->SetEnemyMissileRegen(pos, 0);
		m_missileMgr->SetEnemyMissileRegen(pos, 3);
		m_missileMgr->SetEnemyMissileRegen(pos, 4);
	}
	UpdateAniFrame();
	
}

void BattleCruiser::Render(HDC hdc)
{
	
	if (m_enemyState == Idle)
	{
		m_idleImage.Render(hdc, m_pos.x, m_pos.y, 2.0f);
	}
	if (m_enemyState == Attacked)
	{
		m_idleImage.Render(hdc, m_pos.x, m_pos.y, 2.0f);
		ImageManager::GetSingleton()->FindImage("Missile_Effect")->FrameRender(hdc, m_pos.x + rand() % 20, m_pos.y + rand() % 80, m_currentKeyFrameX, 0, 2);
	}

	if (m_enemyState == Die)
	{
		ImageManager::GetSingleton()->FindImage("Enemy_Die_03")->FrameRender(hdc, m_pos.x + 35, m_pos.y + 50, m_currentKeyFrameX, 0);
	}
}

void BattleCruiser::MovePatton()
{
	if (m_time < 150)
	{
		
		if (m_pos.x > 400)
		{
			m_pos.x -= m_speed * 0.5 * TimeManager::GetSingleton()->GetDeltaTime();
		}
		else
			m_pos.x += m_speed * 0.5 * TimeManager::GetSingleton()->GetDeltaTime();
		m_pos.y -= m_speed * TimeManager::GetSingleton()->GetDeltaTime();
	}
}

void BattleCruiser::Reset()
{
	m_pos.x = m_regenPos.x;
	m_pos.y = m_regenPos.y;
	m_maxHp = 2500;
	m_hp = m_maxHp;
	m_speed = 200.0f;
	m_enemyState = Idle;
	m_attackSpeed = 0;
	m_attackDamage = 0;
	m_size = 100;
	m_currentMovePatton = 0;
	m_currentKeyFrameX = 0;
	m_updateCount = 0;
	m_moveDirection = 0;
	m_time = 0;
}

void BattleCruiser::UpdateAniFrame()
{

	m_updateCount++;
	if (m_updateCount % 2 == 1)
	{
		m_currentKeyFrameX++;
		
		if (m_enemyState == Idle)
		{
			m_currentKeyFrameX = 0;
		}
		if (m_enemyState == Die)
		{
			if (m_currentKeyFrameX == ImageManager::GetSingleton()->FindImage("Enemy_Die_03")->GetMaxKeyFrameX())
			{
				m_itemmgr->SetBoomItemRegn(m_pos);
				m_updateCount = 0;
				m_currentKeyFrameX = 0;
				m_isRegen = false;
				Reset();
			}
		}
		if (m_enemyState == Attacked)
		{
			if (m_currentKeyFrameX == ImageManager::GetSingleton()->FindImage("Missile_Effect")->GetMaxKeyFrameX())
			{
				m_updateCount = 0;
				m_currentKeyFrameX = 0;
				m_enemyState = Idle;
			}
		}

	}
}