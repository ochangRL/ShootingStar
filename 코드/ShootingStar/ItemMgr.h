#pragma once
#include "pch.h"
#include "ObjectPool.h"

class PowerItem;
class Item;
class ItemMgr
{
private:
	ObjectPool<Item*> m_ItemPool;
	Item* item;
	FPOINT m_pos;
	//FPOINT* m_unitpos;
public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void AddItemPower();
	void AddItemBoom();
	void SetItemRegen(FPOINT itempos);
	void SetBoomItemRegn(FPOINT itempos);
	bool CheckColisionWithPlayer(FPOINT unitPos, int unitSize);
	bool CheckColisionWithBoom(FPOINT unitPos, int unitSize);
};

