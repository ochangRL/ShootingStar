#include "Protoss.h"
#include "pch.h"
#include "Image.h"
#include "MissileMgr.h"

HRESULT Protoss::Init(POINT regenPoint, MissileMgr* missileMgr)
{
	m_regenPos.x = regenPoint.x;
	m_regenPos.y = regenPoint.y;
	m_missileMgr = missileMgr;
	Reset();
	m_idleImage = *ImageManager::GetSingleton()->AddImage("Protoss", "Enemy/Protoss.bmp", m_pos.x, m_pos.y, 1476, 89, 18, 1, true, RGB(85, 170, 170));
	//	ImageManager::GetSingleton()->AddImage("Protoss_Effect", "Effect/Effect_12_03.bmp", m_pos.x, m_pos.y, 768 * 2.5f, 35 * 2.5f, 24, 1, true, RGB(0, 0, 0));

	ImageManager::GetSingleton()->AddImage("Protoss_Die", "Effect/Effect_12_05.bmp", m_pos.x, m_pos.y, 864 * 2.5f, 35 * 2.5f, 27, 1, true, RGB(0, 0, 0));
	srand(time(NULL));
	m_isRegen = false;
	return S_OK;
}

void Protoss::Release()
{
}

void Protoss::Update()
{
	if (m_missileMgr->CheckColisionWithEnemy(m_pos, m_size) && m_enemyState != Die)
	{
		m_enemyState = Attacked;
		m_hp -= 10;
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
		}
	}
	UpdateAniFrame();
}

void Protoss::Render(HDC hdc)
{
	if (m_enemyState == Idle || m_enemyState == Attacked)
	{
		//if (m_Protoss_Effect)
		//	ImageManager::GetSingleton()->FindImage("Protoss_Effect")->FrameRender(hdc, m_pos.x, m_pos.y + 10, m_currentKeyFrameX, 0);
		if (m_enemyState == Idle)
		{
			m_idleImage.FrameRender(hdc, m_pos.x, m_pos.y, m_currentKeyFrameX, 0);
		}
		if (m_enemyState == Attacked)
		{
			m_idleImage.FrameRender(hdc, m_pos.x, m_pos.y, m_currentKeyFrameX, 0);
			ImageManager::GetSingleton()->FindImage("Missile_Effect")->FrameRender(hdc, m_pos.x, m_pos.y, m_currentKeyFrameX, 0);
		}
	}
	else if (m_enemyState == Die)
	{
		ImageManager::GetSingleton()->FindImage("Protoss_Die")->FrameRender(hdc, m_pos.x, m_pos.y, m_currentKeyFrameX, 0);
	}

}

void Protoss::MovePatton()
{
	m_time += TIME_MULTIPLE * TimeManager::GetSingleton()->GetDeltaTime();
	if (m_missileMgr->CheckColisionWithEnemy(m_pos, m_size))
	{
		m_hp -= 30;
	}
	for (int i = 0; i < (rand() % 7) * 10; i++)
	{
		if ((int)m_time == 100 + i)
		{
			int randNum = (rand() % 50) * 10;
			m_pos.x = m_regenPos.x + randNum;
			m_pos.y = m_regenPos.y + randNum;

		}
		else if ((int)m_time == 300 + i)
		{
			int randNum = (rand() % 50) * 10;
			m_pos.x = m_regenPos.x + randNum;
			m_pos.y = m_regenPos.y + randNum;

		}

		else if ((int)m_time == 500 + i)
		{
			int randNum = (rand() % 50) * 10;
			m_pos.x = m_regenPos.x + randNum;
			m_pos.y = m_regenPos.y + randNum;

			m_time = 0;
		}

		if (m_pos.x > 750 || m_pos.x < 100)
		{
			int randNum = (rand() % 10) * 10;
			m_pos.x = m_regenPos.x + randNum;
		}
		if (m_pos.y > 950 || m_pos.y < 100)
		{
			int randNum = (rand() % 50) * 10;
			m_pos.y = m_regenPos.y + randNum;
		}

	}

	for (int i = 0; i < 10; i++)
	{
		if ((int)m_time == 100 + i)
		{
			m_Protoss_Effect = true;
			int randNum = (rand() % 50) * 10;
			m_pos.x = m_regenPos.x + randNum;
			m_pos.y = m_regenPos.y + randNum;
			//if (m_time == 180)

			m_Protoss_Effect = false;
		}

		else if ((int)m_time == 300 + i)
		{
			m_Protoss_Effect = true;
			int randNum = (rand() % 50) * 10;
			m_pos.x = m_regenPos.x + randNum;
			m_pos.y = m_regenPos.y + randNum;
			//if (m_time == 380)
			m_Protoss_Effect = false;

		}

		else if ((int)m_time == 500 + i)
		{
			m_Protoss_Effect = true;
			int randNum = (rand() % 50) * 10;
			m_pos.x = m_regenPos.x + randNum;
			m_pos.y = m_regenPos.y + randNum;
			//if (m_time == 580)
			m_Protoss_Effect = false;

			m_time = 0;
		}

		if (m_pos.x > 800 || m_pos.x < 0)
		{
			int randNum = (rand() % 10) * 10;
			m_pos.x = m_regenPos.x + randNum;
		}
		if (m_pos.y > 1000 || m_pos.y < 0)
		{
			int randNum = (rand() % 50) * 10;
			m_pos.y = m_regenPos.y + randNum;
		}
	}
}

void Protoss::Reset()
{
	m_pos.x = m_regenPos.x;
	m_pos.y = m_regenPos.y;
	m_maxHp = 200;
	m_hp = m_maxHp;
	m_speed = 10.0f;
	m_enemyState = Idle;
	m_attackSpeed = 0;
	m_attackDamage = 0;
	m_size = 70;
	m_currentMovePatton = 0;
	m_currentKeyFrameX = 0;
	m_updateCount = 0;
	m_time = 0;
}

void Protoss::UpdateAniFrame()
{
	m_updateCount++;
	if (m_updateCount % 2 == 1)
	{
		m_currentKeyFrameX++;
		if (m_enemyState == Idle)
		{
			if (m_currentKeyFrameX == ImageManager::GetSingleton()->FindImage("Protoss")->GetMaxKeyFrameX())
			{
				m_updateCount = 0;
				m_currentKeyFrameX = 0;
			}
		}
		if (m_enemyState == Die)
		{
			if (m_currentKeyFrameX == ImageManager::GetSingleton()->FindImage("Protoss_Die")->GetMaxKeyFrameX())
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
