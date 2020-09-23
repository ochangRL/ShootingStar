#include "UIBattle.h"
#include "Map.h"
#include "Image.h"
#include "BattleScene.h"

void UIBattle::Init(BattleScene* battleScene)
{
	m_posX = 0;
	m_posY = 0;

	m_HpGaugeframeX = 0;
	m_currkeyframeY = 0;
	m_HpPosX = 0;
	m_HpPosY = 0;

	m_temp = 0;
	m_BombCount = 4;
	m_isBombActive = false;

	m_battleScene = battleScene;

	ImageManager::GetSingleton()->AddImage("HpBar", "UiBattle/HpBar.bmp", m_posX, m_posY, 204 * 1.4f, 71, 1, 1, true, RGB(0, 0, 0));
	ImageManager::GetSingleton()->AddImage("HpGauge", "UiBattle/HpGauge.bmp", m_HpPosX, m_HpPosY, 73 * 4, 5 * 5, 24, 1); // 너비가 73*4 초록칸이 24개
	ImageManager::GetSingleton()->AddImage("ItemBar", "UiBattle/ItemBar.bmp", m_posX, m_posY, 172 * 1.5f, 92, 1, 1, true, RGB(0, 0, 0));
	ImageManager::GetSingleton()->AddImage("Level_font", "UiBattle/level.bmp", m_posX, m_posY, 45 * 1.3, 7 * 2.7, 1, 1, true, RGB(0, 0, 0));
	ImageManager::GetSingleton()->AddImage("Level_01", "UiBattle/num_01.bmp", m_posX, m_posY, 17, 20, 1, 1, true, RGB(255, 243, 0));
	ImageManager::GetSingleton()->AddImage("Level_02", "UiBattle/num_02.bmp", m_posX, m_posY, 17, 20, 1, 1, true, RGB(255, 243, 0));
	ImageManager::GetSingleton()->AddImage("Level_03", "UiBattle/num_03.bmp", m_posX, m_posY, 17, 20, 1, 1, true, RGB(255, 243, 0));
	ImageManager::GetSingleton()->AddImage("Level_04", "UiBattle/num_04.bmp", m_posX, m_posY, 17, 20, 1, 1, true, RGB(255, 243, 0));
	ImageManager::GetSingleton()->AddImage("Bomb", "UiBattle/item_08.bmp", m_posX, m_posY, 20 * 2, 21 * 2, 1, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("Kill_Mon", "Uibattle/red.bmp", m_posX, m_posY, 5 * 2.5, 12 * 2, 1, 1);
	ImageManager::GetSingleton()->AddImage("Kill_Max", "Uibattle/max_02.bmp", m_posX, m_posY, 51, 15, 1, 1, true, RGB(0, 71, 46));
	ImageManager::GetSingleton()->AddImage("Skill_image", "Uibattle/skill_image.bmp", m_posX, m_posY, 185, 150, 1, 1, true, RGB(255, 255, 255));

}

void UIBattle::Release()
{
	
}

void UIBattle::Update()
{

	m_BombCount = GetUnitBombCount();

	

	//HP바 줄어드는 코드
	if (GetUnitHP() >= 0)
	{
		float hpPercent = (float)GetUnitHP() / (float)GetUnitMAXHP();
		m_HpGaugeframeX = (int)(hpPercent * 24);
	}

	//레벨에 따른 미사일 수 증가 m_temp로 미사일 연결
	if (GetUnitLevel() == 1)
	{
		m_temp = 1;
	}
	if (GetUnitLevel() == 2)
	{
		m_temp = 2;
	}
	if (GetUnitLevel() == 3)
	{
		m_temp = 3;
	}

	//폭탄 Count
	//if (GetUnitKillCount() == 1)
	//{
	//	if (KeyManager::GetSingleton()->IsOnceKeyDown('S'))
	//	{
	//		m_battleScene->SetBombSkill(true);
	//	}
	//}
	//if (GetUnitKillCount() == 2)
	//{
	//	if (KeyManager::GetSingleton()->IsOnceKeyDown('S'))
	//	{
	//		m_battleScene->SetBombSkill(true);
	//	}
	//}
	//if (GetUnitKillCount() == 3)
	//{
	//	if (KeyManager::GetSingleton()->IsOnceKeyDown('S'))
	//	{
	//		m_battleScene->SetBombSkill(true);
	//	}
	//}

	//킬 Count
	if (GetUnitKillCount() >= 4)
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown('C'))
		{
			m_battleScene->SetPlayerSkill(true);
		}
	}

	if (GetUnitKillCount() >= 3)
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown('C'))
		{
			m_battleScene->SetPlayerSkill(true);
		}
	}
}

void UIBattle::Render(HDC hdc)
{

	//HP_BAR
	ImageManager::GetSingleton()->FindImage("HpBar")->Render(hdc, WINSIZE_X - 430, WINSIZE_Y + 60, 1.4f);
	ImageManager::GetSingleton()->FindImage("HpGauge")->FrameRenderHP(hdc, WINSIZE_X - 560, WINSIZE_Y + 92, m_HpGaugeframeX, 0, 1.0f, true);
	ImageManager::GetSingleton()->FindImage("ItemBar")->Render(hdc, 110, WINSIZE_Y + 100, 1.4f);

	// 레벨숫자
	ImageManager::GetSingleton()->FindImage("Level_font")->Render(hdc, 45, WINSIZE_Y + 88);
	if (GetUnitLevel() == 1)
	{
		ImageManager::GetSingleton()->FindImage("Level_01")->Render(hdc, 86, WINSIZE_Y + 88);
	}
	if (GetUnitLevel() == 2)
	{
		ImageManager::GetSingleton()->FindImage("Level_02")->Render(hdc, 86, WINSIZE_Y + 88);
	}
	if (GetUnitLevel() == 3)
	{
		ImageManager::GetSingleton()->FindImage("Level_03")->Render(hdc, 86, WINSIZE_Y + 88);
	}
	if (GetUnitLevel() == 4)
	{
		ImageManager::GetSingleton()->FindImage("Level_04")->Render(hdc, 86, WINSIZE_Y + 88);
	}

	//죽인 적 Count
	if (GetUnitKillCount())
	{
		if (GetUnitKillCount() == 1)
		{
			ImageManager::GetSingleton()->FindImage("Kill_Mon")->Render(hdc, 240, WINSIZE_Y + 85);
		}
		if (GetUnitKillCount() == 2)
		{
			ImageManager::GetSingleton()->FindImage("Kill_Mon")->Render(hdc, 240, WINSIZE_Y + 85);
			ImageManager::GetSingleton()->FindImage("Kill_Mon")->Render(hdc, 260, WINSIZE_Y + 85);
		}
		if (GetUnitKillCount() == 3)
		{
			ImageManager::GetSingleton()->FindImage("Kill_Mon")->Render(hdc, 240, WINSIZE_Y + 85);
			ImageManager::GetSingleton()->FindImage("Kill_Mon")->Render(hdc, 260, WINSIZE_Y + 85);
			ImageManager::GetSingleton()->FindImage("Kill_Mon")->Render(hdc, 280, WINSIZE_Y + 85);
		}
		if (GetUnitKillCount() == 4)
		{
			ImageManager::GetSingleton()->FindImage("Kill_Mon")->Render(hdc, 240, WINSIZE_Y + 85);
			ImageManager::GetSingleton()->FindImage("Kill_Mon")->Render(hdc, 260, WINSIZE_Y + 85);
			ImageManager::GetSingleton()->FindImage("Kill_Mon")->Render(hdc, 280, WINSIZE_Y + 85);
			ImageManager::GetSingleton()->FindImage("Kill_Mon")->Render(hdc, 300, WINSIZE_Y + 85);
		}
		if (GetUnitKillCount() > 4)
		{
			ImageManager::GetSingleton()->FindImage("Kill_Mon")->Render(hdc, 240, WINSIZE_Y + 85);
			ImageManager::GetSingleton()->FindImage("Kill_Mon")->Render(hdc, 260, WINSIZE_Y + 85);
			ImageManager::GetSingleton()->FindImage("Kill_Mon")->Render(hdc, 280, WINSIZE_Y + 85);
			ImageManager::GetSingleton()->FindImage("Kill_Mon")->Render(hdc, 300, WINSIZE_Y + 85);
			ImageManager::GetSingleton()->FindImage("Kill_Max")->Render(hdc, 260, WINSIZE_Y + 85);
		}
	}

	//폭탄
	if (GetUnitBombCount())
	{
		//m_BombCount = GetUnitBombCount();
		if (m_BombCount == 1)
		{
			//m_BombShow = 2;
		}
		if (m_BombCount == 2)
		{
			ImageManager::GetSingleton()->FindImage("Bomb")->Render(hdc, 145, WINSIZE_Y + 98);
			//m_BombShow = 3;

		}
		if (m_BombCount == 3)
		{
			ImageManager::GetSingleton()->FindImage("Bomb")->Render(hdc, 145, WINSIZE_Y + 98);
			ImageManager::GetSingleton()->FindImage("Bomb")->Render(hdc, 165, WINSIZE_Y + 98);
			//m_BombShow = 4;

		}
		if (m_BombCount == 4)
		{
			ImageManager::GetSingleton()->FindImage("Bomb")->Render(hdc, 145, WINSIZE_Y + 98);
			ImageManager::GetSingleton()->FindImage("Bomb")->Render(hdc, 165, WINSIZE_Y + 98);
			ImageManager::GetSingleton()->FindImage("Bomb")->Render(hdc, 185, WINSIZE_Y + 98);
		}

		if (m_isBombActive)
		{
			m_time++;
			for (int i = 0; i < rand() % 5; i++)
			{
				for (int j = 0; j < rand() % 4; j++)
				{
					ImageManager::GetSingleton()->FindImage("Skill_image")->Render(hdc, WINSTART_X - 600 + i, WINSTART_Y + 50 + i, 3 + j);
					for (int k = 0; k < rand() % 10; k++)
					{
						ImageManager::GetSingleton()->FindImage("Skill_image")->Render(hdc, WINSTART_X + 200 + i, WINSTART_Y + j, 2);
						ImageManager::GetSingleton()->FindImage("Skill_image")->Render(hdc, WINSTART_X - 400 + i, WINSTART_Y - 50, j + k);
					}
				}
			}

			if (m_time == 100)
			{
				m_isBombActive = false;
				m_time = 0;
			}
		}
	}


}

int UIBattle::GetUnitHP()
{
	return m_battleScene->GetPlayerHp();
}

int UIBattle::GetUnitMAXHP()
{
	return m_battleScene->GetPlayerMaxHP();
}

int UIBattle::GetUnitLevel()
{
	return m_battleScene->GetPlayerLevel();
}

int UIBattle::GetUnitKillCount()
{
	return m_battleScene->GetPlayerKillCount();
}

int UIBattle::GetUnitBombCount()
{
	return m_battleScene->GetPlayerBombCount();
}

void UIBattle::SetUnitSkill(bool isOn)
{
	m_battleScene->SetPlayerSkill(isOn);
}

void UIBattle::SetBombSkill(bool isOn)
{
	m_battleScene->SetBombSkill(isOn);
}
