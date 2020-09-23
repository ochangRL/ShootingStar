#pragma once
#include "pch.h"


class BattleScene;
class UIBattle
{
	//�̻��� ���� �� ���� �ѱ涧 ���
	int m_temp;
	bool m_isBombActive;
	int m_time = 0;

	int m_BombCount;
	float m_posX;
	float m_posY;

	int m_KillCount;

	float m_HpPosX;
	float m_HpPosY;

	int m_HpGaugeframeX;
	int m_currkeyframeY;

private:
	BattleScene* m_battleScene;

	
public:
	void Init(BattleScene* battleScene);		// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	void Release();		// �޸� ����
	void Update();		// ������ ���� ���� ���� ���� (������ ����)
	void Render(HDC hdc);	// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	int GetUnitHP();
	int GetUnitMAXHP();
	int GetUnitLevel();
	int GetUnitKillCount();
	int GetUnitBombCount();

	void SetUnitSkill(bool isOn);
	void SetBombSkill(bool isOn);
};

