#include "SceneManager.h"
#include "Image.h"
#include "BattleScene.h"


extern Image* backBuffer;

HRESULT SceneManager::Init(BattleScene* battlescene)
{
	m_posX = 0;
	m_posY = 0;
	m_currKeyFrameX = 0;
	m_currKeyFrameY = 0;

	m_mouse_cursor_posX = 0;
	m_mouse_cursor_posY = 0;

	m_currKeyFrameX_Ch01 = 0;
	m_currKeyFrameX_Ch02 = 0;
	m_currKeyFrameX_Ch03 = 0;

	m_battleScene = battlescene;
	m_frameSpeed = 1;
	m_scale = 1;

	//인트로, 셀렉트, 엔딩 숫자 선택
	m_currScene = 0;
	//셀렉트에서 캐릭터 숫자 선택
	m_charNum = 0;
	SoundManager::GetSingleton()->AddSound("IntroSound", "BGM/IntroBGM.mp3", true, true);
	SoundManager::GetSingleton()->Play("IntroSound");

	//이미지 추가 : 각 캐릭터들 가만히 서있는 거 추가


 
	ImageManager::GetSingleton()->AddImage("Intro", "View/intro.bmp", m_posX, m_posY, 14080, 360, 22, 1, true, true, RGB(255, 0, 0));
	ImageManager::GetSingleton()->AddImage("Ending", "View/ending_v04.bmp", m_posX, m_posY, 10880, 1000, 17, 1, true, true, RGB(255, 0, 0));
	//ImageManager::GetSingleton()->AddImage("Ending", "View/ending_v04.bmp", m_posX, m_posY, 10880, 1000, 17, 1, true, true, RGB(255, 0, 0));
	ImageManager::GetSingleton()->AddImage("GameOver", "View/GameOver_v01.bmp", m_posX, m_posY, 5760, 1000, 9, 1, true, RGB(255, 0, 0));
	ImageManager::GetSingleton()->AddImage("Select_CH01", "View/Ultralisk_Idle.bmp", m_posX, m_posY, 980, 105, 10, 1, true, RGB(50, 254, 194));
	ImageManager::GetSingleton()->AddImage("Select_CH02", "View/Mutalisk_Idle.bmp", m_posX, m_posY, 500, 74, 5, 1, true, RGB(85, 170, 170));
	ImageManager::GetSingleton()->AddImage("Select_CH03", "View/Defiler_Idle.bmp", m_posX, m_posY, 552, 58, 8, 1, true, RGB(0, 0, 0));
	ImageManager::GetSingleton()->AddImage("Mourse_Cursor","View/cursor.bmp", m_mouse_cursor_posX, m_mouse_cursor_posY, 42, 43, 1, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("Select", "View/select.bmp", m_posX, m_posY, 3108, 60, 21, 1, true, RGB(0, 0, 0));
	ImageManager::GetSingleton()->AddImage("SelectView","View/SelectView_01.bmp", m_posX, m_posY, 637, 485, 1, 1, true, true, RGB(0, 0, 255));
	

	////이미지 추가 : 각 캐릭터들 가만히 서있는 거 추가




	return S_OK;
}

void SceneManager::Release()
{
	/*m_Intro->Release();
	SAFE_DELETE(m_Intro);

	m_Ending->Release();
	SAFE_DELETE(m_Ending);

	m_Select->Release();
	SAFE_DELETE(m_Select);

	m_Select_CH01->Release();
	SAFE_DELETE(m_Select_CH01);

	m_Select_CH02->Release();
	SAFE_DELETE(m_Select_CH02);

	m_Select_CH02->Release();
	SAFE_DELETE(m_Select_CH02);

	m_SelectView->Release();
	SAFE_DELETE(m_SelectView);*/

}

void SceneManager::Update()
{
	if (m_currScene == 0) //인트로
	{
		m_elapsedFrame++;
		if (m_elapsedFrame % 5 == 4 && m_currKeyFrameX != 22) //속도계산은 앞에 숫자 바꿔주면서 조절하고
		{
			m_currKeyFrameX++;
			m_elapsedFrame = 0;
		}
		else if (m_elapsedFrame % 5 == 4 && m_currKeyFrameX == 22)
		{
			m_currKeyFrameX = 0;
			m_elapsedFrame = 0;
			m_currScene = 1;
		}

		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
		{
			m_currScene = 1;
			m_currKeyFrameX = 0;
			m_currKeyFrameY = 0;
			m_elapsedFrame = 0;
		}
	}

	else if (m_currScene == 1) //선택창
	{
		//마우스 커서


		//캐릭터 아래 보라색 창
		m_elapsedFrame++;

		if (m_elapsedFrame % 10 == 9 && m_currKeyFrameX != 21) //속도계산은 앞에 숫자 바꿔주면서 조절하고
		{
			m_currKeyFrameX++;
			m_elapsedFrame = 0;
		}
		else if (m_elapsedFrame % 10 == 9 && m_currKeyFrameX == 21)
		{
			m_currKeyFrameX = 0;
			m_elapsedFrame = 0;

		}

		//캐릭터1
		m_elapsedFrame_Ch01++;

		if (m_elapsedFrame_Ch01 % 5 == 4 && m_currKeyFrameX_Ch01 != 10)
		{
			m_currKeyFrameX_Ch01++;
			m_elapsedFrame_Ch01 = 0;
		}
		else if (m_elapsedFrame_Ch01 % 5 == 4 && m_currKeyFrameX_Ch01 == 10)
		{
			m_currKeyFrameX_Ch01 = 0;
			m_elapsedFrame_Ch01 = 0;
		}

		//캐릭터2
		m_elapsedFrame_Ch02++;

		if (m_elapsedFrame_Ch02 % 5 == 4 && m_currKeyFrameX_Ch02 != 5)
		{
			m_currKeyFrameX_Ch02++;
			m_elapsedFrame_Ch02 = 0;
		}
		else if (m_elapsedFrame_Ch02 % 5 == 4 && m_currKeyFrameX_Ch02 == 5)
		{
			m_currKeyFrameX_Ch02 = 0;
			m_elapsedFrame_Ch02 = 0;
		}

		//캐릭터3
		m_elapsedFrame_Ch03++;

		if (m_elapsedFrame_Ch03 % 5 == 4 && m_currKeyFrameX_Ch03 != 10)
		{
			m_currKeyFrameX_Ch03++;
			m_elapsedFrame_Ch03 = 0;
		}
		else if (m_elapsedFrame_Ch03 % 5 == 4 && m_currKeyFrameX_Ch03 == 10)
		{
			m_currKeyFrameX_Ch03 = 0;
			m_elapsedFrame_Ch03 = 0;
		}

		ShowCursor(false);
		Select_choice();
		GetCursorPos(&temp);
		ScreenToClient(g_hWnd, &temp);
		m_mouse_cursor_posX = temp.x;
		m_mouse_cursor_posY = temp.y;
	}

	if (m_currScene == 3) //엔딩
	{

		m_elapsedFrame++;
		if (m_elapsedFrame % 6 == 5 && m_currKeyFrameX != 32)
		{
			m_currKeyFrameX++;
			m_elapsedFrame = 0;
		}
		else if (m_elapsedFrame % 6 == 5 && m_currKeyFrameX == 32)
		{
			//m_currScene = 0;
			m_currKeyFrameX = 1;
			m_elapsedFrame = 1;

		}
	}
}

void SceneManager::Render(HDC hdc)
{
	if (m_currScene == 0)
	{
		ImageManager::GetSingleton()->FindImage("Intro")->FrameRender_Title(hdc, m_posX, m_posY, m_currKeyFrameX, m_currKeyFrameY);
	}
	else if (m_currScene == 1)
	{


		ImageManager::GetSingleton()->FindImage("SelectView")->FrameRender_Title(hdc, m_posX, m_posY, m_currKeyFrameX, m_currKeyFrameY);
		ImageManager::GetSingleton()->FindImage("Select")->FrameRender(hdc, m_posX + 150, m_posY + 450, m_currKeyFrameX, m_currKeyFrameY, 1.8f);
		ImageManager::GetSingleton()->FindImage("Select_CH01")->FrameRender(hdc, m_posX + 110, m_posY + 230, m_currKeyFrameX_Ch01, m_currKeyFrameY, 3.0f);
		ImageManager::GetSingleton()->FindImage("Select")->FrameRender(hdc, m_posX + 450, m_posY + 350, m_currKeyFrameX, m_currKeyFrameY, 1.8f);
		ImageManager::GetSingleton()->FindImage("Select_CH02")->FrameRender(hdc, m_posX + 410, m_posY + 180, m_currKeyFrameX_Ch02, m_currKeyFrameY, 3.0f);

		ImageManager::GetSingleton()->FindImage("Select")->FrameRender(hdc, m_posX + 750, m_posY + 450, m_currKeyFrameX, m_currKeyFrameY, 1.8f);
		ImageManager::GetSingleton()->FindImage("Select_CH03")->FrameRender(hdc, m_posX + 730, m_posY + 270, m_currKeyFrameX_Ch03, m_currKeyFrameY, 3.0f);
		ImageManager::GetSingleton()->FindImage("Mourse_Cursor")->Render(hdc, m_mouse_cursor_posX, m_mouse_cursor_posY);
	}

	else if (m_currScene == 3)
	{

		if(m_isStageClear == false)
		ImageManager::GetSingleton()->FindImage("GameOver")->FrameRender_Ending(hdc, m_posX, m_posY, m_currKeyFrameX, m_currKeyFrameY, 0);
		else
		ImageManager::GetSingleton()->FindImage("Ending")->FrameRender_Ending(hdc, m_posX, m_posY, m_currKeyFrameX, m_currKeyFrameY, 1);
	}



}

void SceneManager::Select_choice()
{
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
	{

		GetCursorPos(&temp);
		temp.x;
		temp.y;

		//Ultralisk
		if (temp.x > 643 && temp.x < 835 && temp.y > 360 && temp.y < 560)
		{
			m_charNum = 0;
			m_currScene = 2;
			m_battleScene->Init(m_charNum);
			SetWindowPos(g_hWnd, NULL, 0, 0, 800, 1000, SWP_NOMOVE);
			backBuffer->Init(800, 1000);
		}

		//Mutalisk
		if (temp.x > 946 && temp.x < 1129 && temp.y > 270 && temp.y < 454)
		{
			m_charNum = 1;
			m_currScene = 2;
			m_battleScene->Init(m_charNum);
			SetWindowPos(g_hWnd, NULL, 0, 0, 800, 1000, SWP_NOMOVE);
			backBuffer->Init(800, 1000);
		}

		//Defiler
		if (temp.x > 1240 && temp.x < 1430 && temp.y > 361 && temp.y < 557)
		{
			m_charNum = 2;
			m_currScene = 2;
			m_battleScene->Init(m_charNum);
			SetWindowPos(g_hWnd, NULL, 0, 0, 800, 1000, SWP_NOMOVE);
			backBuffer->Init(800, 1000);
		}
		
	}
}
