#pragma once
#include "pch.h"

class Item
{
protected:
	FPOINT m_pos;
	float m_angle;
	float m_size;
	float m_speed;
	bool m_isRegen;
public:
	virtual HRESULT Init() = 0;
	virtual void Release() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;

	virtual void SetRegen(bool isRegen) = 0;
	virtual bool GetRegen() = 0;
	virtual void Reset() = 0;

	void SetPos(FPOINT pos) { m_pos = pos; }
	FPOINT GetPos() { return m_pos; }
	virtual int GetSize() { return m_size; }
};

