#include "Guardian.h"
#include "pch.h"
#include "Image.h"
#include "MissileMgr.h"
#include "ItemMgr.h"

HRESULT Guardian::Init(POINT regenPoint, MissileMgr* missileMgr)
{
	m_missileMgr = missileMgr;
	m_regenPos.x = regenPoint.x;
	m_regenPos.y = regenPoint.y;
	Reset();
	m_idleImage = *ImageManager::GetSingleton()->AddImage("GuardianIdle", "Enemy/GuardianIdle.bmp", m_pos.x, m_pos.y,
		518, 60, 7, 1, true, RGB(0, 0, 0));

	m_isRegen = false;


	return S_OK;
}

void Guardian::Release()
{

}

void Guardian::Update()
{
	if (m_missileMgr->CheckColisionWithEnemy(m_pos, m_size))
	{
		m_enemyState = Attacked;
		m_hp -= 30;
	}
	if (&m_idleImage)
	{
		if (m_hp < 0)
		{
			m_enemyState = Die;
		}
		else
		{
			m_time += TIME_MULTIPLE * TimeManager::GetSingleton()->GetDeltaTime();
			this->MovePatton();
			
		}

	}

	if ((int)m_time % 40 == 39 && m_time > 120 && m_enemyState != Die)
	{
		FPOINT pos1;
		pos1.x = m_pos.x + 20;
		pos1.y = m_pos.y;
		FPOINT pos2;
		pos2.x = m_pos.x - 20;
		pos2.y = m_pos.y;
		m_missileMgr->SetEnemyMissileRegen(m_pos, 2);
		m_missileMgr->SetEnemyMissileRegen(pos1, 2);
		m_missileMgr->SetEnemyMissileRegen(pos2, 2);
	}
	UpdateAniFrame();
}

void Guardian::Render(HDC hdc)
{
	if (m_enemyState == Idle || m_enemyState == Attacked)
	{
		if (m_enemyState == Idle)
		{
			m_idleImage.FrameRender(hdc, m_pos.x, m_pos.y, m_currentKeyFrameX, 0);
		}
		if (m_enemyState == Attacked)
		{
			m_idleImage.FrameRender(hdc, m_pos.x, m_pos.y, m_currentKeyFrameX, 0);
			ImageManager::GetSingleton()->FindImage("Missile_Effect")->FrameRender(hdc, m_pos.x - rand() % 30, m_pos.y + rand() % 10, m_currentKeyFrameX, 0, 2);
		}
	}
	else if (m_enemyState == Die)
	{
		ImageManager::GetSingleton()->FindImage("Enemy_Die")->FrameRender(hdc, m_pos.x, m_pos.y, m_currentKeyFrameX, 0);
	}
}

void Guardian::MovePatton()
{
	if(m_time < 120)
	m_pos.x += m_speed * TimeManager::GetSingleton()->GetDeltaTime();
}

void Guardian::Reset()
{
	m_pos.x = m_regenPos.x;
	m_pos.y = m_regenPos.y;
	m_maxHp = 800;
	m_hp = m_maxHp;
	m_speed = 200.0f;
	m_enemyState = Idle;
	m_attackSpeed = 0;
	m_attackDamage = 0;
	m_size = 40;
	m_currentMovePatton = 0;
	m_currentKeyFrameX = 0;
	m_updateCount = 0;
	m_time = 0;
}

void Guardian::UpdateAniFrame()
{

	m_updateCount++;
	if (m_updateCount % 2 == 1)
	{
		m_currentKeyFrameX++;
		if (m_enemyState == Idle)
		{
			if (m_currentKeyFrameX == ImageManager::GetSingleton()->FindImage("GuardianIdle")->GetMaxKeyFrameX())
			{
				m_updateCount = 0;
				m_currentKeyFrameX = 0;
			}
		}
		if (m_enemyState == Die)
		{
			if (m_currentKeyFrameX == ImageManager::GetSingleton()->FindImage("Enemy_Die")->GetMaxKeyFrameX())
			{
				if (((rand() % 20)) % 10 == 0)
				{
					m_itemmgr->SetItemRegen(m_pos);
				}
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
