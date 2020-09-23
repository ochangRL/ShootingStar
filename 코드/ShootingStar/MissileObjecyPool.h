#pragma once
#include <map>
#include <Windows.h>

template<typename t1>
class MissileObjectpool
{
private:
	multimap<string, t1> m_Missiles;
	typename multimap<string, t1>::iterator m_iterMissiles;

public:
	MissileObjectpool() {}
	~MissileObjectpool() {}

	void AddObject(t1 newObject, string key)
	{
		m_Missiles.insert(make_pair(key, newObject));
	}

	void UpdateObj()
	{
		for (m_iterMissiles = m_Missiles.begin(); m_iterMissiles != m_Missiles.end(); ++m_iterMissiles)
		{
			((*m_iterMissiles).second)->Update();
		}
	}

	void RenderObj(HDC hdc)
	{
		for (m_iterMissiles = m_Missiles.begin(); m_iterMissiles != m_Missiles.end(); ++m_iterMissiles)
		{
			((*m_iterMissiles).second)->Render(hdc);
		}
	}

	void Fire(int m_firepoint, FPOINT owner)
	{
		for (m_iterMissiles = m_Missiles.begin(); m_iterMissiles != m_Missiles.end(); m_iterMissiles++)
		{
			if (((*m_iterMissiles).second)->GetIsFire())
			{
				continue;
			}
			((*m_iterMissiles).second)->SetIsFire(true);
			((*m_iterMissiles).second)->SetAngle(DEGREE_TO_RADIAN(270));
			((*m_iterMissiles).second)->SetFirePoint(m_firepoint);
			((*m_iterMissiles).second)->SetPos(owner);
			break;
		}
	}
};