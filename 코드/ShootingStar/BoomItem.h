#pragma once
#include "Item.h"

class BoomItem : public Item
{
private:

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	virtual void SetRegen(bool isRegen) { m_isRegen = isRegen; };
	virtual bool GetRegen() { return m_isRegen; };
	virtual void Reset();
};

