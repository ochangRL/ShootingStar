#include "Wraith.h"
#include "pch.h"
#include "Image.h"
#include "MissileMgr.h"

HRESULT Wraith::Init(POINT regenPoint, MissileMgr* missileMgr)
{
	m_missileMgr = missileMgr;
	m_regenPos.x = regenPoint.x;
	m_regenPos.y = regenPoint.y;
	Reset();

	//m_idleImage = new Image();
	m_idleImage = *ImageManager::GetSingleton()->AddImage("WraithIdle", "Enemy/Enemy1.bmp",
		 48, 40, true, RGB(255, 255, 255));
	

	ImageManager::GetSingleton()->AddImage("Enemy_Die_02", "Effect/Effect_14_half.bmp", m_pos.x, m_pos.y, 384 * 2.5f, 35 * 2.5f, 12, 1, true, RGB(0, 0, 0));
	m_isRegen = false;

	
	return S_OK;
}

void Wraith::Release()
{

}

void Wraith::Update()
{
	m_time += TIME_MULTIPLE * TimeManager::GetSingleton()->GetDeltaTime();
	if (m_missileMgr->CheckColisionWithEnemy(m_pos, m_size) && m_enemyState!= Die)
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
			this->MovePatton();
			//m_hp -= 5;
		}
	}

	UpdateAniFrame();
	if ((int)m_time % 50 == 0 && m_enemyState != Die)
	{
		m_missileMgr->SetEnemyMissileRegen(m_pos, 1);
	}
	else if ((int)m_time % 50 == 25 && m_enemyState != Die)
	{
		m_missileMgr->SetEnemyMissileRegen(m_pos, 1);
	}
}

void Wraith::Render(HDC hdc)
{
	
	if (m_enemyState == Idle)
	{
		m_idleImage.Render(hdc, m_pos.x, m_pos.y);
	}
	if (m_enemyState== Attacked)
	{
		m_idleImage.Render(hdc, m_pos.x, m_pos.y);
		ImageManager::GetSingleton()->FindImage("Missile_Effect")->FrameRender(hdc, m_pos.x - rand() % 40, m_pos.y + rand() % 5, m_currentKeyFrameX, 0, 2.0f);
	}
	
	else if (m_enemyState == Die)
	{
		ImageManager::GetSingleton()->FindImage("Enemy_Die_02")->FrameRender(hdc, m_pos.x, m_pos.y, m_currentKeyFrameX, 0);
	}
}

void Wraith::MovePatton()
{
	if(m_moveDirection == 0)
		m_pos.y+=m_speed * TimeManager::GetSingleton()->GetDeltaTime();
	else
		m_pos.y -= m_speed * TimeManager::GetSingleton()->GetDeltaTime();
	if (m_pos.y > 600)
		m_moveDirection = 1;
	else if (m_pos.y < 0)
		m_moveDirection = 0;
}

void Wraith::Reset()
{
	m_pos.x = m_regenPos.x;
	m_pos.y = m_regenPos.y;
	m_maxHp = 300;
	m_hp = m_maxHp; 
	m_speed = 200.0f;
	m_enemyState = Idle;
	m_attackSpeed = 0;
	m_attackDamage = 0;
	m_size = 30;
	m_currentMovePatton = 0;
	RECT rc = { m_pos.x, m_pos.y, m_pos.x + m_size, m_pos.y + m_size };
	m_currentKeyFrameX = 0;
	m_updateCount = 0;
	m_moveDirection = 0;
	m_time = 0;
}

void Wraith::UpdateAniFrame()
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
			if (m_currentKeyFrameX == ImageManager::GetSingleton()->FindImage("Enemy_Die")->GetMaxKeyFrameX())
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
	}
}