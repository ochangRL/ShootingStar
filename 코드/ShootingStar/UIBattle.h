#pragma once
#include "pch.h"


class BattleScene;
class UIBattle
{
	//미사일 레벨 업 숫자 넘길때 사용
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
	void Init(BattleScene* battleScene);		// 멤버 변수 초기화, 메모리 할당
	void Release();		// 메모리 해제
	void Update();		// 프레임 단위 게임 로직 실행 (데이터 변경)
	void Render(HDC hdc);	// 프레임 단위 출력 (이미지, 텍스트 등)

	int GetUnitHP();
	int GetUnitMAXHP();
	int GetUnitLevel();
	int GetUnitKillCount();
	int GetUnitBombCount();

	void SetUnitSkill(bool isOn);
	void SetBombSkill(bool isOn);
};

