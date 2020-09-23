#include "UnitMissile.h"
#include "Image.h"

HRESULT UnitMissile::Init()
{
	m_missileSort1Image = *ImageManager::GetSingleton()->FindImage("UltraliskMissile");
	m_missileSort2Image = *ImageManager::GetSingleton()->FindImage("MutaliskMissile");
	m_missileSort3Image = *ImageManager::GetSingleton()->FindImage("DefilerMissile");
	m_isRegen = false;
	Reset();
	return S_OK;
}

void UnitMissile::Release()
{

}

void UnitMissile::Update()
{
	if (m_pos.x == -500/*추후 리젠 포인트들어감*/)
	{
		m_pos.x = m_ownerPos.x;
		m_pos.y = m_ownerPos.y;
	}
	m_pos.y -= m_speed * TimeManager::GetSingleton()->GetDeltaTime();
	UpdateAniFrame();

	if (m_pos.y <= 0 || m_pos.y >= 1000 || m_pos.x >= 800 || m_pos.x <= 0) 
	{
		m_isRegen = false;
		Reset();
	}
}

void UnitMissile::Render(HDC hdc)
{
	if (m_missileSort == 0)
	{
		m_missileSort1Image.Render(hdc, m_pos.x, m_pos.y);
	}
	else if(m_missileSort == 1)
		m_missileSort2Image.FrameRender(hdc, m_pos.x, m_pos.y, m_currFrameX, m_currFrameY);
	else if (m_missileSort == 2)
		m_missileSort3Image.Render(hdc, m_pos.x, m_pos.y);
}

void UnitMissile::Reset()
{
	m_pos.x = -500;
	m_pos.y = -500;
	m_targetpos = { 0 };
	m_speed = 1200.0f;
	m_size = 5;
	m_angle = 0;
	m_currFrameX = 0;
	m_currFrameY = 0;
	m_updateCount = 0;
	m_missileSort = 0;
}

void UnitMissile::UpdateAniFrame()
{
	m_updateCount++;
	if (m_updateCount % 3 == 2)
	{
		m_currFrameX++;
		
		if (m_currFrameX == m_missileSort2Image.GetMaxKeyFrameX())
		{
			m_updateCount = 0;
			m_currFrameX = 0;
		}
	}
}
