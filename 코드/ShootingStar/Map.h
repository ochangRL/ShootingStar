#pragma once
#include "pch.h"

class Image;
class Map
{
private:
	Image* image;
	FPOINT Pos;
public:
	void Init();		// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	void Release();		// �޸� ����
	void Update();		// ������ ���� ���� ���� ���� (������ ����)
	void Render(HDC hdc);	// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)
};

