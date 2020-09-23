#include "Queen.h"
#include "pch.h"
#include "Image.h"
#include "MissileMgr.h"
#include "ItemMgr.h"

HRESULT Queen::Init(POINT regenPoint, MissileMgr* missileMgr)
{
	m_missileMgr = missileMgr;
	m_regenPos.x = regenPoint.x;
	m_regenPos.y = regenPoint.y;
	Reset();
	m_idleImage = *ImageManager::GetSingleton()->AddImage("QueenIdle", "Enemy/QueenIdle.bmp", m_pos.x, m_pos.y,
		325, 56, 5, 1, true, RGB(0, 0, 0));
	ImageManager::GetSingleton()->AddImage("Enemy_Die", "Effect/Effect_05.bmp", m_pos.x, m_pos.y, 666, 71, 10, 1, true, RGB(255, 255, 255));
	m_isRegen = false;


	return S_OK;
}

void Queen::Release()
{

}

void Queen::Update()
{
	

	if (m_missileMgr->CheckColisionWithEnemy(m_pos, m_size) && m_enemyState != Die)
	{
		m_enemyState = Attacked;
		m_hp -= 30;
	}
	if (&m_idleImage)
	{
		if (m_hp < 0)
		{
			/*if (((rand() % 10)) % 5 == 0)
			{
				m_itemmgr->SetItemRegen(m_pos);
			}*/
			m_enemyState = Die;
		}
		else
		{
			m_time += TIME_MULTIPLE * TimeManager::GetSingleton()->GetDeltaTime();
			this->MovePatton();
		}

		UpdateAniFrame();
	}

	if ((int)m_time % 10 == 9 && m_enemyState != Die)
	{
		m_missileMgr->SetEnemyMissileRegen(m_pos, 0);
	}
	
}

void Queen::Render(HDC hdc)
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
			ImageManager::GetSingleton()->FindImage("Missile_Effect")->FrameRender(hdc, m_pos.x - rand() % 20, m_pos.y + rand() % 10, m_currentKeyFrameX, 0, 2);
		}
	}
	else if (m_enemyState == Die)
	{
		ImageManager::GetSingleton()->FindImage("Enemy_Die")->FrameRender(hdc, m_pos.x, m_pos.y, m_currentKeyFrameX, 0);
	}
}

void Queen::MovePatton()
{
	
	if (m_pos.y <= 20 && m_isTurn ==false)
	{
		m_pos.y += m_speed * TimeManager::GetSingleton()->GetDeltaTime();

	}
	else
	{
		m_isTurn = true;

		if (m_isTurn == true)
		{
			m_pattonTime += 2 * TIME_MULTIPLE * TimeManager::GetSingleton()->GetDeltaTime();
			if (m_pattonTime >= (m_turnCount * TIME_MULTIPLE * TimeManager::GetSingleton()->GetDeltaTime()))
			{
			
				m_pattonTime = 0;
				m_direction *= -1;
				m_turnCount = 360;
			}
			m_angle -= DEGREE_TO_RADIAN(2) * m_direction * TIME_MULTIPLE * TimeManager::GetSingleton()->GetDeltaTime();
			m_pos.x += m_speed * cosf(m_angle)* TimeManager::GetSingleton()->GetDeltaTime();
			m_pos.y -= m_speed * sinf(m_angle)* TimeManager::GetSingleton()->GetDeltaTime();
		}
	}
}

void Queen::Reset()
{
	m_angle = 0;// RADIAN_TO_DEGREE(-90);
	m_pos.x = m_regenPos.x;
	m_pos.y = m_regenPos.y;
	m_maxHp = 400;
	m_hp = m_maxHp;
	m_speed = 200.0f;
	m_enemyState = Idle;
	m_attackSpeed = 0;
	m_pattonTime = 0;
	m_direction = 1;
	m_attackDamage = 0;
	m_size = 40;
	m_currentMovePatton = 0;
	m_currentKeyFrameX = 0;
	m_updateCount = 0;
	m_time = 0;
	m_turnCount = 450;
	m_isTurn = false;
}

void Queen::UpdateAniFrame()
{
	m_updateCount++;
	if (m_updateCount % 2 == 1)
	{
		m_currentKeyFrameX++;
		if (m_enemyState == Idle)
		{
			if (m_currentKeyFrameX == ImageManager::GetSingleton()->FindImage("QueenIdle")->GetMaxKeyFrameX())
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


