#include "Kerrigan.h"
#include "Image.h"
#include "MissileMgr.h"

HRESULT Kerrigan::Init(POINT regenPoint, MissileMgr* missileMgr)
{
	m_isEnemyBoss = true;
	m_regenPos.x = 0;
	m_regenPos.y = 0;
	Reset();
	m_idleImage = *ImageManager::GetSingleton()->AddImage("Kerrigan", "Enemy/Kerrigan.bmp", m_pos.x, m_pos.y, 640, 60, 10, 1, true, RGB(3, 187, 176));
	ImageManager::GetSingleton()->AddImage("Boss_Die", "Effect/Effect_01.bmp", m_pos.x, m_pos.y, 2690, 157, 18, 1, true, RGB(0, 0, 0));
	m_missileMgr = missileMgr;
	m_isRegen = false;
	m_isposx = false;
	m_isposy = false;
	m_x = false;
	m_y = false;

	m_isGameClear = false;
	return S_OK;
}

void Kerrigan::Release()
{
}

void Kerrigan::Update()
{
	FPOINT pos;
	pos.x = m_pos.x + 100;
	pos.y = m_pos.y + 100;
	if (m_missileMgr->CheckColisionWithEnemy(pos, m_size) && m_enemyState != Die)
	{
		m_enemyState = Attacked;
		m_hp -= 10;
	}
	if (&m_idleImage)
	{
		if (m_hp < 0)
		{
			m_enemyState = Die;
			m_isGameClear = true;
		}
		else
		{
			this->MovePatton();
		}

	}
	

	int regenTime = (int)m_time % 20000;

	if (regenTime > 150 && regenTime < 500 && m_enemyState != Die)
	{
		if ((int)regenTime % 25 == 24)
		{
			FPOINT pos;
			pos.x = m_pos.x + 40;
			pos.y = m_pos.y + 80;

			m_missileMgr->SetEnemyMissileRegen(pos, 0);
			m_missileMgr->SetEnemyMissileRegen(pos, 3);
			m_missileMgr->SetEnemyMissileRegen(pos, 4);
		}

		if ((int)regenTime % 10 == 9)
		{

			m_missileMgr->SetEnemyMissileRegen(pos, 1);
		}
	}
	else if (regenTime > 520 && regenTime < 1200 && m_enemyState != Die)
	{
		if ((int)regenTime % 25 == 24)
		{
			FPOINT pos1;
			pos.x = 100;
			pos.y = m_pos.y + 80;
			FPOINT pos2;
			pos2.x = 200;
			pos2.y = m_pos.y + 80;
			FPOINT pos3;
			pos3.x = 300;
			pos3.y = m_pos.y + 80;
			FPOINT pos4;
			pos4.x = 400;
			pos4.y = m_pos.y + 80;
			FPOINT pos5;
			pos5.x = 500;
			pos5.y = m_pos.y + 80;
			FPOINT pos6;
			pos6.x = 600;
			pos6.y = m_pos.y + 80;

			m_missileMgr->SetEnemyMissileRegen(pos, 0);
			m_missileMgr->SetEnemyMissileRegen(pos2, 3);
			m_missileMgr->SetEnemyMissileRegen(pos3, 4);
			m_missileMgr->SetEnemyMissileRegen(pos4, 0);
			m_missileMgr->SetEnemyMissileRegen(pos5, 3);
			m_missileMgr->SetEnemyMissileRegen(pos6, 4);
		}

		if ((int)regenTime % 10 == 9)
		{

			m_missileMgr->SetEnemyMissileRegen(pos, 1);
		}
	}

	else if (regenTime < 2000 &&regenTime > 1200 && m_enemyState != Die)
	{
		if ((int)regenTime % 25 == 24)
		{
			FPOINT pos1;
			pos.x = 100;
			pos.y = m_pos.y + 20;
			FPOINT pos2;
			pos2.x = 200;
			pos2.y = m_pos.y + 10;
			FPOINT pos3;
			pos3.x = 300;
			pos3.y = m_pos.y + 50;
			FPOINT pos4;
			pos4.x = 400;
			pos4.y = m_pos.y + 30;
			FPOINT pos5;
			pos5.x = 500;
			pos5.y = m_pos.y + 90;
			FPOINT pos6;
			pos6.x = 600;
			pos6.y = m_pos.y + 44;

			m_missileMgr->SetEnemyMissileRegen(pos, 1);
			m_missileMgr->SetEnemyMissileRegen(pos2, 1);
			m_missileMgr->SetEnemyMissileRegen(pos3, 1);
			m_missileMgr->SetEnemyMissileRegen(pos4, 1);
			m_missileMgr->SetEnemyMissileRegen(pos5, 1);
			m_missileMgr->SetEnemyMissileRegen(pos6, 1);
		}
		if ((int)regenTime % 20 == 19)
		{

			m_missileMgr->SetEnemyMissileRegen(pos, 1);
		}
		if ((int)regenTime % 10 == 9)
		{

			m_missileMgr->SetEnemyMissileRegen(pos, 1);
		}
	}

	else if (regenTime > 2000 && m_enemyState != Die)
	{
		m_time = 0;
	}
	UpdateAniFrame();
}

void Kerrigan::Render(HDC hdc)
{
	if (m_enemyState == Idle || m_enemyState == Attacked)
	{
		if (m_enemyState == Idle)
		{
			m_idleImage.FrameRender(hdc, m_pos.x, m_pos.y, m_currentKeyFrameX, 0, 3.0f);
		}
		if (m_enemyState == Attacked)
		{
			m_idleImage.FrameRender(hdc, m_pos.x, m_pos.y, m_currentKeyFrameX, 0, 3.0f);
			ImageManager::GetSingleton()->FindImage("Missile_Effect")->FrameRender(hdc, m_pos.x + 50, m_pos.y + rand() % 30, m_currentKeyFrameX, 0, 3.0f);

		}
	}
	else if (m_enemyState == Die)
	{
		ImageManager::GetSingleton()->FindImage("Boss_Die")->FrameRender(hdc, m_pos.x + 100, m_pos.y + 100, m_currentKeyFrameX, 0);
	}
}

void Kerrigan::MovePatton()
{
	m_time += TIME_MULTIPLE * TimeManager::GetSingleton()->GetDeltaTime();

	if (m_pos.y <= (WINSIZE_Y / 2) - 300)
	{
		m_pos.y += m_speed * TimeManager::GetSingleton()->GetDeltaTime();
	}
	if (m_time % 2 == 1)
	{
		//if (m_x)
		//{
		if (!m_isposx)
		{
			m_pos.x += m_speed * TimeManager::GetSingleton()->GetDeltaTime();
		}
		if (m_isposx)
		{
			m_pos.x -= m_speed * TimeManager::GetSingleton()->GetDeltaTime();
		}
		//	}
			//if (!m_x)
			//{
			//	if (m_pos.y >= (WINSIZE_Y / 2) - 300 && m_pos.x >= WINSIZE_X - 300)
			//	{
			//		m_pos.y -= m_speed * TimeManager::GetSingleton()->GetDeltaTime();
			//	}
			//	if (!m_isposy)
			//	{
			//		m_pos.y += m_speed * TimeManager::GetSingleton()->GetDeltaTime();
			//	}
			//}
	}


	if (m_pos.x >= WINSIZE_X - 300)
	{
		m_isposx = true;
		m_x = false;
	}
	if (m_pos.x <= 0)
	{
		m_isposx = false;
	}
	//if (m_pos.y >= (WINSIZE_Y / 2) - 300)
	//{
	//	m_isposy = true;
	//	m_x = true;
	//}
	//if (m_pos.y <= 0)
	//{
	//	m_isposy = false;
	//}
}

void Kerrigan::Reset()
{
	m_pos.x = m_regenPos.x;
	m_pos.y = m_regenPos.y;
	m_maxHp = 9000;
	m_hp = m_maxHp;
	m_speed = 200.0f;
	m_enemyState = Idle;
	m_attackSpeed = 0;
	m_attackDamage = 0;
	m_size = 180;
	m_currentMovePatton = 0;
	m_currentKeyFrameX = 0;
	m_updateCount = 0;
	m_time = 0;
}

void Kerrigan::UpdateAniFrame()
{
	m_updateCount++;
	if (m_updateCount % 3 == 2)
	{
		m_currentKeyFrameX++;
		if (m_enemyState == Idle)
		{
			if (m_currentKeyFrameX == ImageManager::GetSingleton()->FindImage("Kerrigan")->GetMaxKeyFrameX())
			{
				m_updateCount = 0;
				m_currentKeyFrameX = 0;
			}
		}
		if (m_enemyState == Die)
		{
			if (m_currentKeyFrameX == ImageManager::GetSingleton()->FindImage("Boss_Die")->GetMaxKeyFrameX())
			{
				m_updateCount = 0;
				m_currentKeyFrameX = 0;
				m_isRegen = false;
				Reset();
			}
		}
		if (m_enemyState == Attacked)
		{
			if (m_currentKeyFrameX >= ImageManager::GetSingleton()->FindImage("Missile_Effect")->GetMaxKeyFrameX())
			{
				m_updateCount = 0;
				m_currentKeyFrameX = 0;
				m_enemyState = Idle;
			}
		}
	}
}
