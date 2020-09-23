#include "ItemMgr.h"
#include "Item.h"
#include "PowerItem.h"
#include "BoomItem.h"

void ItemMgr::Init()
{
	ImageManager::GetSingleton()->AddImage("Power", "UiBattle/level.bmp", 45, 7);
	ImageManager::GetSingleton()->AddImage("Boom", "UiBattle/item_08.bmp", 20, 21, true, RGB(255, 255, 255));
	m_pos.x = -200;
	m_pos.y = -200;
	AddItemPower();
	AddItemBoom();
}

void ItemMgr::Release()
{

}

void ItemMgr::Update()
{
	if (m_ItemPool.GetPoolSize() != 0)
	{
		m_ItemPool.UpdateObj();
	}
}

void ItemMgr::Render(HDC hdc)
{
	if (m_ItemPool.GetPoolSize() != 0)
	{
		m_ItemPool.RenderObj(hdc);
	}
}

void ItemMgr::AddItemPower()
{
	for (int i = 0; i < 5; ++i)
	{
		item = new PowerItem();
		item->SetPos(m_pos);
		item->Init();
		m_ItemPool.AddObject(item, "Poweritem");
	}
}

void ItemMgr::AddItemBoom()
{
	for (int i = 0; i < 5; ++i)
	{
		Item* itemBoom = new BoomItem();
		itemBoom->SetPos(m_pos);
		itemBoom->Init();
		m_ItemPool.AddObject(itemBoom, "Boomitem");
	}
}

void ItemMgr::SetItemRegen(FPOINT itempos)
{
	m_ItemPool.SetOneItemRegenTrue("Poweritem", itempos);
}

void ItemMgr::SetBoomItemRegn(FPOINT itempos)
{
	m_ItemPool.SetOneItemRegenTrue("Boomitem", itempos);
}

bool ItemMgr::CheckColisionWithPlayer(FPOINT unitPos, int unitSize)
{
	return m_ItemPool.CheckCollisionItem("Poweritem", unitPos, unitSize);
}

bool ItemMgr::CheckColisionWithBoom(FPOINT unitPos, int unitSize)
{
	return m_ItemPool.CheckCollisionItem("Boomitem", unitPos, unitSize);
}