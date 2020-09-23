#include "Defiler.h"
#include "pch.h"
#include "Image.h"
#include "macroFunction.h"
#include "MissileMgr.h"
#include "ItemMgr.h"
#include "EnemyMgr.h"

HRESULT Defiler::Init(MissileMgr* missileMgr, EnemyMgr* enemyMgr)
{
	m_enemyMgr = enemyMgr;
	m_missileMgr = missileMgr;
	m_pos.x = 500;
	m_pos.y = 700;
	m_maxHp = 400;
	m_hp = m_maxHp;
	m_speed = 200.0f;
	m_unitState = Idle;
	m_attackSpeed = 0;
	m_attackDamage = 0;
	m_size = 10;
	m_currentKeyFrameX = 0;
	m_updateCount = 0;
	m_level = 1;
	//m_firepoint = 1;
	m_KillCount = 5;
	m_BombCount = 4;
	m_attacked = false;

	SoundManager::GetSingleton()->AddSound("MissileBGM", "BGM/MissileBGM.mp3", true, false);

	ImageManager::GetSingleton()->AddImage("DefilerIdle","Defiler/DefilerIdle.bmp",
		m_pos.x, m_pos.y, 552, 58, 8, 1, true, RGB(0, 0, 0));
	m_missileMgr->AddUnitMissile();

	ImageManager::GetSingleton()->AddImage("Unit_Die", "Effect/Unit_Die.bmp", m_pos.x, m_pos.y, 980, 105, 10, 1, true, RGB(50, 254, 194));
	ImageManager::GetSingleton()->AddImage("Unit_missile_effect", "Effect/missile_effect.bmp", m_pos.x, m_pos.y, 192, 32, 6, 1, true, RGB(0, 0, 0));
	return S_OK;
}

void Defiler::Release()
{
	//delete &m_pos;
	SAFE_DELETE(m_idleAni);

}

void Defiler::Update()
{
	if (m_missileMgr->CheckColisionWithPlayer(m_pos, m_size)&& m_isNoDamage == false)
	{
		m_attacked = true;
		m_hp -= 10;
	}
	if (m_itemmgr)
	{
		if (m_itemmgr->CheckColisionWithPlayer(m_pos, m_size))
		{
			m_level += 1;
			if (m_level >= 3)
			{
				m_level = 3;
			}
		}
		if (m_itemmgr->CheckColisionWithBoom(m_pos, m_size))
		{
			m_BombCount += 1;
			if (m_BombCount >= 3)
			{
				m_BombCount = 3;
			}
		}
	}
	if (ImageManager::GetSingleton()->FindImage("DefilerIdle"))
	{
		UpdateAniFrame();
		SetPosition();
	}
	//��ų
	if (m_isSkillOn)
	{
		if (m_hp < m_maxHp)
		{
			m_isSkillOn = false;
			m_KillCount = 0;
			m_hp = m_maxHp;
		}
	}
	//��ź
	
	if (m_BombCount >= 4)
	{
		m_BombCount = 4;
	}
}

void Defiler::Render(HDC hdc)
{
	if (ImageManager::GetSingleton()->FindImage("DefilerIdle"))
	{
		if (m_unitState == Idle)
		{
			ImageManager::GetSingleton()->FindImage("DefilerIdle")->FrameRender(hdc, m_pos.x, m_pos.y, m_currentKeyFrameX, 0, 1.0f);
		}
		if (m_attacked)
		{
			ImageManager::GetSingleton()->FindImage("Unit_missile_effect")->FrameRender(hdc, m_pos.x + rand() % 10, m_pos.y - rand() % 20, m_currentKeyFrameX, 0, 1);

		}
		if (m_unitState == Die)
		{
			ImageManager::GetSingleton()->FindImage("Unit_Die")->FrameRender(hdc, m_pos.x, m_pos.y, m_currentKeyFrameX, 0);
		}
	}

	if (m_BombCount != 0)
	{
		//m_BombCount = GetUnitBombCount();
		if (m_BombCount == 1)
		{
			ImageManager::GetSingleton()->FindImage("Bomb")->Render(hdc, 145, WINSIZE_Y + 98);
		}
		if (m_BombCount == 2)
		{
			ImageManager::GetSingleton()->FindImage("Bomb")->Render(hdc, 145, WINSIZE_Y + 98);
			ImageManager::GetSingleton()->FindImage("Bomb")->Render(hdc, 165, WINSIZE_Y + 98);

		}
		if (m_BombCount == 3)
		{
			ImageManager::GetSingleton()->FindImage("Bomb")->Render(hdc, 145, WINSIZE_Y + 98);
			ImageManager::GetSingleton()->FindImage("Bomb")->Render(hdc, 165, WINSIZE_Y + 98);
			ImageManager::GetSingleton()->FindImage("Bomb")->Render(hdc, 185, WINSIZE_Y + 98);

		}


	}

	if (m_isBombDown)
	{
		m_time++;
		for (int i = 0; i < rand() % 5; i++)
		{
			for (int j = 0; j < rand() % 4; j++)
			{
				ImageManager::GetSingleton()->FindImage("Skill_image")->Render(hdc, WINSTART_X - 600 + i, WINSTART_Y + 50 + i, 3 + j);
				for (int k = 0; k < rand() % 10; k++)
				{
					ImageManager::GetSingleton()->FindImage("Skill_image")->Render(hdc, WINSTART_X + 200 + i, WINSTART_Y + j, 2);
					ImageManager::GetSingleton()->FindImage("Skill_image")->Render(hdc, WINSTART_X - 400 + i, WINSTART_Y - 50, j + k);
				}
			}
		}

		if (m_time >= 100)
		{
			m_enemyMgr->ActivateBomb();
			m_isBombDown = false;
			m_time = 0;
		}
	}
}

void Defiler::UpdateAniFrame()
{
	m_updateCount++;
	if (m_updateCount % 3 == 2)
	{
		m_currentKeyFrameX++;
		if (m_unitState == Idle)
		{
			if (m_currentKeyFrameX == ImageManager::GetSingleton()->FindImage("DefilerIdle")->GetMaxKeyFrameX())
			{
				m_updateCount = 0;
				m_currentKeyFrameX = 0;
			}
		}
		if (m_unitState == Die)
		{
			if (m_currentKeyFrameX == ImageManager::GetSingleton()->FindImage("Enemy_Die")->GetMaxKeyFrameX())
			{
				m_updateCount = 0;
				m_currentKeyFrameX = 0;

			}
		}
		if (m_attacked)
		{
			if (m_currentKeyFrameX >= ImageManager::GetSingleton()->FindImage("Unit_missile_effect")->GetMaxKeyFrameX())
			{
				m_updateCount = 0;
				m_currentKeyFrameX = 0;
				m_attacked = false;
			}
		}
	}
}

void Defiler::SetPosition()
{
	if (KeyManager::GetSingleton()->IsOnceKeyDown('O'))
	{
		if(m_isNoDamage == true)
		m_isNoDamage = false;
		else m_isNoDamage = true;
		
	}
	if (KeyManager::GetSingleton()->IsOnceKeyDown('P'))
	{
		m_level++;
		if (m_level > 3)
			m_level = 3;
	}

	if (KeyManager::GetSingleton()->IsOnceKeyDown('X'))
	{
		if (m_BombCount > 0 && m_isBombDown == false)
		{
			m_isBombDown = true;
			m_BombCount -= 1;
		}
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))
	{
		m_pos.y += m_speed * TimeManager::GetSingleton()->GetDeltaTime();
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
	{
		m_pos.y -= m_speed * TimeManager::GetSingleton()->GetDeltaTime();;
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
	{
		m_pos.x += m_speed * TimeManager::GetSingleton()->GetDeltaTime();;
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
	{
		m_pos.x -= m_speed * TimeManager::GetSingleton()->GetDeltaTime();;
	}
	if (KeyManager::GetSingleton()->IsOnceKeyDown('Z'))
	{
		SoundManager::GetSingleton()->Play("MissileBGM");
		FPOINT level2FirePoint1 = m_pos;
		level2FirePoint1.x += 10;
		FPOINT level2FirePoint2 = m_pos;
		level2FirePoint2.x -= 10;
		FPOINT level3FirePoint1 = m_pos;
		level3FirePoint1.x += 20;
		FPOINT level3FirePoint2 = m_pos;
		level3FirePoint2.x -= 20;

		if (m_level == 1)
			m_missileMgr->SetMissileRegen(m_pos, 2);
		else if (m_level == 2)
		{

			m_missileMgr->SetMissileRegen(m_pos, 2);
			m_missileMgr->SetMissileRegen(level2FirePoint1, 2);
			m_missileMgr->SetMissileRegen(level2FirePoint2, 2);
		}
		else if (m_level == 3)
		{
			m_missileMgr->SetMissileRegen(m_pos, 2);
			m_missileMgr->SetMissileRegen(level2FirePoint1, 2);
			m_missileMgr->SetMissileRegen(level2FirePoint2, 2);
			m_missileMgr->SetMissileRegen(level3FirePoint1, 2);
			m_missileMgr->SetMissileRegen(level3FirePoint2, 2);
		}
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown('Z'))
	{
		m_time++;
		if (m_time % 2 == 1)
		{
			FPOINT level2FirePoint1 = m_pos;
			level2FirePoint1.x += 10;
			FPOINT level2FirePoint2 = m_pos;
			level2FirePoint2.x -= 10;
			FPOINT level3FirePoint1 = m_pos;
			level3FirePoint1.x += 20;
			FPOINT level3FirePoint2 = m_pos;
			level3FirePoint2.x -= 20;

			if (m_level == 1)
				m_missileMgr->SetMissileRegen(m_pos,2);
			else if (m_level == 2)
			{

				m_missileMgr->SetMissileRegen(m_pos, 2);
				m_missileMgr->SetMissileRegen(level2FirePoint1, 2);
				m_missileMgr->SetMissileRegen(level2FirePoint2, 2);
			}
			else if (m_level == 3)
			{

				m_missileMgr->SetMissileRegen(m_pos, 2);
				m_missileMgr->SetMissileRegen(level2FirePoint1, 2 );
				m_missileMgr->SetMissileRegen(level2FirePoint2, 2);
				m_missileMgr->SetMissileRegen(level3FirePoint1, 2);
				m_missileMgr->SetMissileRegen(level3FirePoint2, 2);
			}
		}
	}
	if (KeyManager::GetSingleton()->IsOnceKeyUp('Z'))
	{
		m_time = 0;
	}
	
	if (m_pos.y <= 0)
	{
		m_pos.y = 0;
	}
	else if (m_pos.y>= 950)
	{
		m_pos.y = 950;
	}
	else if (m_pos.x <= 0)
	{
		m_pos.x = 0;
	}
	else if (m_pos.x>= 750)
	{
		m_pos.x = 750;
	}
}


