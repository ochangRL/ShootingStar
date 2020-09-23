#pragma once
#include "pch.h"

class Image;
class BattleScene;
class SceneManager
{
private:
	int m_currScene;
	int m_charNum;
	int m_posX;
	int m_posY;

	int m_mouse_cursor_posX;
	int m_mouse_cursor_posY;

	int m_currKeyFrameX;
	int  m_currKeyFrameX_Ch01;
	int  m_currKeyFrameX_Ch02;
	int  m_currKeyFrameX_Ch03;
	int m_currKeyFrameY;


	int m_elapsedFrame = 0;
	int m_elapsedFrame_Ch01 = 0;
	int m_elapsedFrame_Ch02 = 0;
	int m_elapsedFrame_Ch03 = 0;
	int m_frameSpeed;
	int m_frameSpeedIndex = 0;;

	bool m_isStageClear = false;

	float m_scale;
	int m_playerHp;

	//이미지 추가 : 각 캐릭터들 가만히 서있는 거 추가
	POINT temp;

	BattleScene* m_battleScene;
public:
	virtual HRESULT Init(BattleScene* battlescene);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
	void Select_choice();
	void SetIsStageClear(bool isclear) { m_isStageClear = isclear; }

	int GetCurrScene() { return m_currScene; }
	int GetSelectedChar() { return m_charNum; }
	void SetCurrScene(int scene) { m_currScene = scene; }
	void SetPlayerHP(int hp) { m_playerHp = hp; }


};

