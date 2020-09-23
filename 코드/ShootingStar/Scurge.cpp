#include "Scurge.h"
#include "pch.h"
#include "Image.h"
#include "MissileMgr.h"

HRESULT Scurge::Init(POINT regenPoint, MissileMgr* missileMgr)
{
	m_missileMgr = missileMgr;
	m_regenPos.x =0;
	m_regenPos.y = regenPoint.y;
	m_isFired = false;
	m_idleImage = *ImageManager::GetSingleton()->AddImage("ScurgeIdle", "Enemy/ScurgeIdle.bmp",m_pos.x, m_pos.y,
		150, 25, 5, 1, true, RGB(0, 0, 0));


	ImageManager::GetSingleton()->AddImage("Enemy_Die_09", "Effect/Effect_06_02.bmp", m_pos.x, m_pos.y, 812, 87, 12, 1, true, RGB(255, 255, 255));
	m_isRegen = false;


	return S_OK;
}

void Scurge::Release()
{

}

void Scurge::Update()
{
	if (m_missileMgr->CheckColisionWithEnemy(m_pos, m_size) && m_enemyState != Die)
	{
		m_enemyState = Attacked;
		m_hp -= 30;
	}

	if (&m_idleImage)
	{
		if (m_hp < 0 || m_pos.y > 1000)
		{
			m_enemyState = Die;
		}
		else if (m_hp == m_maxHp)
		{
			Reset();
			m_hp--;

		}
		else
		{
			this->MovePatton();
		}


		UpdateAniFrame();
		
	}

	if (m_isFired == true && m_pos.y >0)
	{
		m_missileMgr->SetEnemyMissileRegen(m_pos, 5);
		m_isFired = false;
	}
}

void Scurge::Render(HDC hdc)
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
			ImageManager::GetSingleton()->FindImage("Missile_Effect")->FrameRender(hdc, m_pos.x + rand() % 10, m_pos.y + rand() % 10, m_currentKeyFrameX, 0);
		}
	}
	else if (m_enemyState == Die)
	{
		ImageManager::GetSingleton()->FindImage("Enemy_Die_09")->FrameRender(hdc, m_pos.x, m_pos.y, m_currentKeyFrameX, 0);
	}
}

void Scurge::MovePatton()
{
	m_pos.y += m_speed * TimeManager::GetSingleton()->GetDeltaTime();
}

void Scurge::Reset()
{
	m_pos.x = (*m_unitPos).x;
	m_pos.y = m_regenPos.y;
	m_maxHp = 200;
	m_hp = m_maxHp;
	m_speed = 400.0f;
	m_enemyState = Idle;
	m_attackSpeed = 0;
	m_attackDamage = 0;
	m_size = 20;
	m_currentMovePatton = 0;
	m_currentKeyFrameX = 0;
	m_updateCount = 0;
	m_time = 0;
	m_isFired = true;
}

void Scurge::UpdateAniFrame()
{
	m_updateCount++;
	if (m_updateCount % 2 == 1)
	{
		m_currentKeyFrameX++;
		if (m_enemyState == Idle)
		{
			if (m_currentKeyFrameX == ImageManager::GetSingleton()->FindImage("ScurgeIdle")->GetMaxKeyFrameX())
			{
				m_updateCount = 0;
				m_currentKeyFrameX = 0;
			}
		}
		if (m_enemyState == Die)
		{
			if (m_currentKeyFrameX == ImageManager::GetSingleton()->FindImage("Enemy_Die_09")->GetMaxKeyFrameX())
			{
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
		/*else if (m_unitState == Attack)
		{

		}*/
	}
}
