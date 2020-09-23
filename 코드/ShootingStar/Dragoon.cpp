#include "Dragoon.h"
#include "pch.h"
#include "Image.h"
#include "MissileMgr.h"
#include "ItemMgr.h"

HRESULT Dragoon::Init(POINT regenPoint, MissileMgr* missileMgr)
{
	m_missileMgr = missileMgr;
	m_regenPos.x = regenPoint.x;
	m_regenPos.y = regenPoint.y;
	Reset();

	//m_idleImage = new Image();
	m_idleImage = *ImageManager::GetSingleton()->AddImage("DragoonIdle", "Enemy/DragoonIdle.bmp",
		39, 45, true, RGB(0, 0, 0));

	ImageManager::GetSingleton()->AddImage("Enemy_Die_20", "Effect/Effect_13_half.bmp", m_pos.x, m_pos.y, 384 * 3, 35 * 3, 12, 1, true, RGB(0, 0, 0));


	m_isRegen = false;
	m_test = false;
	return S_OK;
}

void Dragoon::Release()
{

}

void Dragoon::Update()
{
	m_time += TIME_MULTIPLE * TimeManager::GetSingleton()->GetDeltaTime();
	if (m_missileMgr->CheckColisionWithEnemy(m_pos, m_size) && m_enemyState != Die)
	{
		m_test = true;
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
			UpdateAniFrame();
		}
		else
		{
			this->MovePatton();
			if (m_pos.y > 1000)
			{
				m_isRegen = false;
				Reset();
			}
			//m_hp -= 5;
		}

	}
	if ((int)m_time % 200 == 0 && m_enemyState != Die)
	{
		m_missileMgr->SetEnemyMissileRegen(m_pos, 1);
	}
	else if ((int)m_time % 200 == 50 && m_enemyState != Die)
	{
		m_missileMgr->SetEnemyMissileRegen(m_pos, 1);
	}

	
}

void Dragoon::Render(HDC hdc)
{

	if (m_enemyState == Idle || m_enemyState == Attacked)
	{
		if (m_enemyState == Idle)
		{

			m_idleImage.Render(hdc, m_pos.x, m_pos.y);
		}
		if (m_test)
		{
			ImageManager::GetSingleton()->FindImage("Missile_Effect")->FrameRender(hdc, m_pos.x - rand() % 40, m_pos.y + rand() % 5, m_currentKeyFrameX, 0, 2.0f);
		}
	}
	else if (m_enemyState == Die)
	{
		ImageManager::GetSingleton()->FindImage("Enemy_Die_20")->FrameRender(hdc, m_pos.x, m_pos.y, m_currentKeyFrameX, 0);
	}
}

void Dragoon::MovePatton()
{
	m_pos.y += m_speed * TimeManager::GetSingleton()->GetDeltaTime();
}

void Dragoon::Reset()
{
	m_pos.x = m_regenPos.x;
	m_pos.y = m_regenPos.y;
	m_maxHp = 250;
	m_hp = m_maxHp;
	m_speed = 150.0f;
	m_enemyState = Idle;
	m_attackSpeed = 0;
	m_attackDamage = 0;
	m_size = 40;
	m_currentMovePatton = 0;
	m_currentKeyFrameX = 0;
	m_updateCount = 0;
	m_moveDirection = 0;
	m_test = false;
	m_time = 0;
}

void Dragoon::UpdateAniFrame()
{

	m_updateCount++;
	if (m_updateCount % 2 == 1)
	{
		m_currentKeyFrameX++;

		if (m_enemyState == Die)
		{
			if (m_currentKeyFrameX == ImageManager::GetSingleton()->FindImage("Enemy_Die_20")->GetMaxKeyFrameX())
			{
				m_updateCount = 0;
				m_currentKeyFrameX = 0;
				if (((rand() % 20)) % 10 == 0)
				{
					m_itemmgr->SetItemRegen(m_pos);
				}
				m_isRegen = false;
				Reset();
			}
		}
		/*if (m_enemyState == Attacked)
		{
			if (m_currentKeyFrameX == ImageManager::GetSingleton()->FindImage("Missile_Effect")->GetMaxKeyFrameX())
			{
				m_updateCount = 0;
				m_currentKeyFrameX = 0;
				m_enemyState = Idle;
			}
		}*/
		else if (m_test)
		{
			if (m_currentKeyFrameX >= ImageManager::GetSingleton()->FindImage("Missile_Effect")->GetMaxKeyFrameX())
			{
				m_updateCount = 0;
				m_currentKeyFrameX = 0;
				m_test = false;
			}
		}

	}
}
