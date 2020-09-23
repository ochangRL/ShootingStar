#pragma once
#include <map>
#include <Windows.h>

template<typename t1>
class ObjectPool
{
private:
	multimap<string,t1> m_objects;
	typename multimap<string,t1>::iterator m_itObj;

public:

	void AddObject(t1 newObject, string key)
	{
		m_objects.insert(make_pair(key, newObject));
	}
	
	// 사이즈만큼 오브젝트를 만든다.
	ObjectPool() 
	{  
		
	}

	// 오브젝트를 비운다.
	~ObjectPool()
	{

	//{
	//	for (m_itObj = m_objects.begin(); m_itObj != m_objects.end(); m_itObj++)
	//	{
	//		if (((*m_itObj).second) != nullptr)
	//		{
	//			// second(value) 를 메모리 해제
	//			//((*m_itObj).second)->Release();
	//			SAFE_DELETE(((*m_itObj).second));

	//			// key, value (pair) 를 메모리 해제
	//			m_itObj = m_objects.erase(m_itObj);
	//		}
	//		else
	//		{
	//			m_itObj++;
	//		}
	//	}

		// 맵 을 메모리 해제
		m_objects.clear();
	}

	void UpdateObj()
	{
		for (m_itObj = m_objects.begin(); m_itObj != m_objects.end(); ++m_itObj)
		{
			if(((*m_itObj).second)->GetRegen() == true)
			((*m_itObj).second)->Update();
		}
	}

	void RenderObj(HDC hdc)
	{
		for (m_itObj = m_objects.begin(); m_itObj != m_objects.end(); ++m_itObj)
		{
			if (((*m_itObj).second)->GetRegen() == true)
				((*m_itObj).second)->Render(hdc);
		}
	} 

	void SetElementRegenTrue(string key)
	{
		for (m_itObj = m_objects.lower_bound(key); m_itObj != m_objects.upper_bound(key); ++m_itObj)
		{
			if (((*m_itObj).second)->GetRegen() == false)
			{
				((*m_itObj).second)->SetRegen(true);
			} 
		}
	}
	bool CheckElementRegen(string key)
	{
		for (m_itObj = m_objects.lower_bound(key); m_itObj != m_objects.upper_bound(key); ++m_itObj)
		{
			if (((*m_itObj).second)->GetRegen() == true)
				return false;
		}
		return true;
	}

	void SetOneElementRegenTrue(string key, FPOINT unitPoint, int missileSort, FPOINT targetPoint = {0})
	{
		for (m_itObj = m_objects.lower_bound(key); m_itObj != m_objects.upper_bound(key); ++m_itObj)
		{
			if (((*m_itObj).second)->GetRegen() == false)
			{
				((*m_itObj).second)->SetRegen(true);
				((*m_itObj).second)->SetUnitPos(unitPoint);
				((*m_itObj).second)->SetMissileSort(missileSort);
				if (key == "EnemyMissile")
				{
					((*m_itObj).second)->SetTargetPos(targetPoint);
				}
				break;
			}
		}
	}


	bool CheckColision(string key, FPOINT enemyPos, int enemySize)
	{
		for (m_itObj = m_objects.lower_bound(key); m_itObj != m_objects.upper_bound(key); ++m_itObj)
		{
			if (((*m_itObj).second)->GetRegen() == true)
			{
				if (CheckCircleCollision(((*m_itObj).second)->GetPos(), enemyPos, enemySize, ((*m_itObj).second)->GetSize()))
				{
					((*m_itObj).second)->SetRegen(false);
					((*m_itObj).second)->Reset();
					return true;
				}
				continue;
			}
		}
		return false;
	}

	bool CheckColision1(string key, FPOINT unitPos, int unitSize)
	{
		for (m_itObj = m_objects.lower_bound(key); m_itObj != m_objects.upper_bound(key); ++m_itObj)
		{
			if (((*m_itObj).second)->GetRegen() == true)
			{
				if (CheckCircleCollision(((*m_itObj).second)->GetPos(), unitPos, unitSize, ((*m_itObj).second)->GetSize()) )
				{
					((*m_itObj).second)->SetRegen(false);
					((*m_itObj).second)->Reset();
					return true;
				}
				continue;
			}
		}
		return false;
	}

	void SetOneItemRegenTrue(string key, FPOINT itemPoint)
	{
		for (m_itObj = m_objects.lower_bound(key); m_itObj != m_objects.upper_bound(key); ++m_itObj)
		{
			if (((*m_itObj).second)->GetRegen() == false)
			{
				((*m_itObj).second)->SetRegen(true);
				((*m_itObj).second)->SetPos(itemPoint);
				break;
			}
		}
	}

	bool CheckCollisionItem(string key, FPOINT unitPos, int unitSize)
	{
		for (m_itObj = m_objects.lower_bound(key); m_itObj != m_objects.upper_bound(key); ++m_itObj)
		{
			if (((*m_itObj).second)->GetRegen() == true)
			{
				if (CheckCircleCollision(((*m_itObj).second)->GetPos(), unitPos, unitSize, ((*m_itObj).second)->GetSize()))
				{
					((*m_itObj).second)->SetRegen(false);
					((*m_itObj).second)->Reset();
					return true;
				}
				continue;
			}
		}
		return false;
	}

	bool CheckBossDead(string Key)
	{
		for (m_itObj = m_objects.lower_bound(Key); m_itObj != m_objects.upper_bound(Key); ++m_itObj)
		{
			if (((*m_itObj).second)->GetRegen() == true)
			{
				if (((*m_itObj).second)->GetIsGameClear())
					return true;
			}
		}
		return false;
	}

	void ActivateBomB()
	{
		for (m_itObj = m_objects.begin(); m_itObj != m_objects.end(); ++m_itObj)
		{
			if (((*m_itObj).second)->GetRegen() == true && ((*m_itObj).second)->GetIsEnemyBoss() == false)
			{
				((*m_itObj).second)->SetRegen(false);
				((*m_itObj).second)->Reset();
			}
		}
	}

	int GetPoolSize()
	{
		return m_objects.size();
	}

	inline bool CheckCircleCollision(FPOINT pos1, FPOINT pos2, int size1, int size2)
	{
		if (size1 + size2 <= sqrtf(pow(pos1.x - pos2.x,2) + pow(pos1.y - pos2.y, 2)))
			return false;
		else return true;
	}

};