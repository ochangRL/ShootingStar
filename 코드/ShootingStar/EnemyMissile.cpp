#include "EnemyMissile.h"
#include "Image.h"
#include "macroFunction.h"



HRESULT EnemyMissile::Init()
{
	m_img = *(ImageManager::GetSingleton()->FindImage("EnemyMissile"));
	m_isRegen = false;
	Reset();
	return S_OK;
}

void EnemyMissile::Release()
{

}

void EnemyMissile::Update()
{
	if (m_pos.x == -500/*추후 리젠 포인트들어감*/)
	{
		m_pos.x = m_ownerPos.x;
		m_pos.y = m_ownerPos.y;
		if (m_missileSort == 0)
		{
			m_speed = 200.0f;
		}
		else if (m_missileSort == 1 || m_missileSort == 5)
		{
			m_speed = 400.0f;
		}
		else if (m_missileSort == 2)
		{
			m_speed = 300.0f;
		}
		else if (m_missileSort == 3 || m_missileSort == 4)
		{
			m_speed = 100.0f;
		}
	}

	if (m_missileSort == 0 || m_missileSort == 2 || m_missileSort == 5)
	{
		m_pos.y += m_speed * TimeManager::GetSingleton()->GetDeltaTime();
	}
	
	else if (m_missileSort == 1)
	{
		MissileToUnitPatton();
	}

	else if (m_missileSort == 3)
	{
		MissileToUnitPatton1();
	}

	else if (m_missileSort == 4)
	{
		MissileToUnitPatton2();
	}


	UpdateAniFrame();

	if (m_pos.y > 1000 ||m_pos.y < 0 ||m_pos.x < 0 ||m_pos.x > 800)
	{
		if (m_missileSort != 5)
		{
			m_isRegen = false;
			Reset();
		}
		if (m_pos.y > 1000)
		{
			m_isRegen = false;
			Reset();
		}
	}

}

void EnemyMissile::Render(HDC hdc)
{
	m_img.FrameRender(hdc, m_pos.x, m_pos.y, m_currFrameX, m_currFrameY);
	
}

void EnemyMissile::Reset()
{
	m_pos.x = -500;
	m_pos.y = -300;
	//m_targetpos = { 0 };
	m_speed = 0;
	m_size = 10;
	m_isFire = false;
	m_angle = 0;
	m_currFrameX = 0;
	m_currFrameY = 0;
	m_updateCount = 0;
	m_missileSort = 0;
	m_isReachedPlayer = false;
	m_savedAngle = 0;
}

void EnemyMissile::UpdateAniFrame()
{
	m_updateCount++;
	if (m_updateCount % 3 == 2)
	{
		m_currFrameX++;

		if (m_currFrameX == ImageManager::GetSingleton()->FindImage("MutaliskMissile")->GetMaxKeyFrameX())
		{
			m_updateCount = 0;
			m_currFrameX = 0;
		}
	}
}

void EnemyMissile::MissileToUnitPatton()
{
	int x;
	int y;
	float cosRate;
	float sinRate;
	
	
	x = m_targetpos.x - m_pos.x;
	y = m_targetpos.y - m_pos.y;
	if (x <= 10 && y <= 10 && x >= -10 && y >= -10)
	{
		m_isReachedPlayer = true;
		m_savedAngle = m_angle;
	}
	if (m_isReachedPlayer == true)
	{
		m_angle = m_savedAngle;
	}
	else m_angle = atan2(y, x);
	cosRate = cos(m_angle);
	sinRate = sin(m_angle);
	
	m_pos.x += m_speed * cosRate * TimeManager::GetSingleton()->GetDeltaTime();
	m_pos.y += m_speed * sinRate * TimeManager::GetSingleton()->GetDeltaTime();
}

void EnemyMissile::MissileToUnitPatton1()
{
	float cosRate;
	float sinRate;
	m_angle = DEGREE_TO_RADIAN(120);
	cosRate = cos(m_angle);
	sinRate = sin(m_angle);
	m_pos.x += m_speed * cosRate * TimeManager::GetSingleton()->GetDeltaTime();
	m_pos.y += m_speed * sinRate * TimeManager::GetSingleton()->GetDeltaTime();
}

void EnemyMissile::MissileToUnitPatton2()
{
	float cosRate;
	float sinRate;
	m_angle = DEGREE_TO_RADIAN(60);
	cosRate = cos(m_angle);
	sinRate = sin(m_angle);
	m_pos.x += m_speed * cosRate * TimeManager::GetSingleton()->GetDeltaTime();
	m_pos.y += m_speed * sinRate * TimeManager::GetSingleton()->GetDeltaTime();
}


EnemyMissile::EnemyMissile()
{
}

EnemyMissile::~EnemyMissile()
{
}

