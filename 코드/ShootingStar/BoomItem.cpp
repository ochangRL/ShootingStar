#include "BoomItem.h"
#include "Image.h"

HRESULT BoomItem::Init()
{
	m_angle = PI / (rand() % 5) + 1;
	m_speed = 300.0f;
	m_size = 1.5f;
	m_isRegen = false;

	return S_OK;
}

void BoomItem::Release()
{
}

void BoomItem::Update()
{
	m_pos.x += m_speed * cosf(m_angle) * TimeManager::GetSingleton()->GetDeltaTime();
	m_pos.y -= m_speed * -sinf(m_angle)* TimeManager::GetSingleton()->GetDeltaTime();

	if (m_pos.x - (m_size / 2) <= 0)
	{
		m_angle = PI - m_angle;
	}
	else if (m_pos.x + (m_size / 2) >= WINSIZE_X - 220)
	{
		m_angle = PI - m_angle;
	}
	if (m_pos.y - (m_size / 2) <= 0)
	{
		m_angle = PI * 2 - m_angle;
	}
	else if (m_pos.y + (m_size / 2) >= WINSIZE_Y)
	{
		m_angle = PI * 2 - m_angle;
	}
}

void BoomItem::Render(HDC hdc)
{
	if (ImageManager::GetSingleton()->FindImage("Boom"))
	{
		ImageManager::GetSingleton()->FindImage("Boom")->Render(hdc, m_pos.x, m_pos.y, m_size);
	}
}

void BoomItem::Reset()
{
	m_angle = PI / (rand() % 5) + 1;
	m_speed = 300.0f;
}
