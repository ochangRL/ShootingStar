#include "SoundManager.h"

HRESULT SoundManager::Init()
{
	//사운드 시스템 생성

	System_Create(&system);

	//채널 설정
	system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, NULL);

	// 사운드 채널 동적할당

	sound = new Sound *[TOTALSOUNDBUFFER];
	channel = new Channel *[TOTALSOUNDBUFFER];

	memset(sound, 0, sizeof(Sound*) * TOTALSOUNDBUFFER);  //초기화함수.

	memset(channel, 0, sizeof(Channel*) * TOTALSOUNDBUFFER);

	return E_NOTIMPL;
}

void SoundManager::Release()
{
	SAFE_ARR_DELETE(sound);
	SAFE_ARR_DELETE(channel);

	system->close();
	system->release();
}

void SoundManager::Update()
{
	if (system)
	{
		system->update();
	}
}

void SoundManager::AddSound(string key, string filePath, bool isBGM, bool isLoop)
{
	if (isLoop)
	{
		if (isBGM)
		{
			system->createStream(filePath.c_str(), FMOD_LOOP_NORMAL, 0, &sound[mapSoundDatas.size()]);
		}
		else
		{
			system->createSound(filePath.c_str(), FMOD_LOOP_NORMAL, 0, &sound[mapSoundDatas.size()]);
		}
	}
	else
	{
		system->createSound(filePath.c_str(), FMOD_DEFAULT, 0, &sound[mapSoundDatas.size()]);
	}

	mapSoundDatas.insert(make_pair(key, &sound[mapSoundDatas.size()]));

}

void SoundManager::Play(string key, float volume)
{
	//(*(*channel)).setVolume(volume);
	map<string, Sound**>::iterator it;

	int count = 0;

	for (it = mapSoundDatas.begin(); it != mapSoundDatas.end(); it++, count++)
	{
		if (it->first == key)
		{
			system->playSound(FMOD_CHANNEL_FREE, (*mapSoundDatas[key]), false, &channel[count]);
			channel[count]->setVolume(volume);

			break;
		}
	}




}

void SoundManager::Stop(string key)
{
	//(*(*channel)).setVolume(volume);
	map<string, Sound**>::iterator it;

	int count = 0;

	for (it = mapSoundDatas.begin(); it != mapSoundDatas.end(); it++, count++)
	{
		if (it->first == key)
		{
			channel[count]->stop();
			break;
		}
	}
}

void SoundManager::Pause(string key)
{
	map<string, Sound**>::iterator it;

	int count = 0;

	for (it = mapSoundDatas.begin(); it != mapSoundDatas.end(); it++, count++)
	{
		if (it->first == key)
		{
			channel[count]->setPaused(true);
			break;
		}
	}
}

void SoundManager::Resume(string key)
{
	map<string, Sound**>::iterator it;

	int count = 0;

	for (it = mapSoundDatas.begin(); it != mapSoundDatas.end(); it++, count++)
	{
		if (it->first == key)
		{
			channel[count]->setPaused(false);
			break;
		}
	}
}

SoundManager::SoundManager()
	: system(nullptr), sound(nullptr), channel(nullptr)
{

}
