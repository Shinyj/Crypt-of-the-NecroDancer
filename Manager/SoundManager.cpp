#include "stdafx.h"
#include "../stdafx.h"
#include "SoundManager.h"


SoundManager::SoundManager()
{
}


SoundManager::~SoundManager()
{
}

HRESULT SoundManager::Init()
{
	// 사운드를 추가하는 것이 아닌 사운드가 출력이 될 환경을 조성해야함
	System_Create(&m_system);
	
	// 사운드 채널 수 생성
	m_system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, 0);

	// 사운드 채널 동적할당
	m_sound = new Sound*[TOTALSOUNDBUFFER];
	m_channel = new Channel*[TOTALSOUNDBUFFER];

	memset(m_sound, 0, sizeof(Sound*)*(TOTALSOUNDBUFFER));
	memset(m_channel, 0, sizeof(Channel*)*(TOTALSOUNDBUFFER));

	return S_OK;
}

void SoundManager::Release()
{
	if (m_channel != nullptr || m_sound != nullptr)
	{
		for (int i = 0; i < TOTALSOUNDBUFFER; i++)
		{
			if (m_channel != nullptr)
			{
				if (m_channel[i]) m_channel[i]->stop();
			}
			if (m_sound != nullptr)
			{
				if (m_sound[i]) m_sound[i]->release();
			}
		}
	}
	SAFE_DELETE(m_channel);
	SAFE_DELETE(m_sound);

	if (m_system != nullptr)
	{
		m_system->release();
		m_system->close();
	}
}

void SoundManager::Update()
{
	m_system->update();
	
}

void SoundManager::Render()
{
	
}

void SoundManager::AddSound(string KeyName, string soundName, bool bgm, bool loop)
{
	if (loop)
	{
		//브금
		if (bgm)
		{
			m_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, nullptr, &m_sound[m_totalSounds.size()]);
		}
		// 이펙트
		else
		{
			m_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, nullptr, &m_sound[m_totalSounds.size()]);
		}
	}
	else
	{
		m_system->createSound(soundName.c_str(), FMOD_DEFAULT, nullptr, &m_sound[m_totalSounds.size()]);
	}
	m_totalSounds.insert(make_pair(KeyName, &m_sound[m_totalSounds.size()]));
}

void SoundManager::Play(string KeyName, float volume)
{
	int count = 0;
	arrSoundIter iter = m_totalSounds.begin();
	for (iter; iter != m_totalSounds.end(); ++iter, count++)
	{
		if (KeyName == iter->first)
		{
			m_system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &m_channel[count]);
			//m_channel[count]->setVolume(volume);
			m_channel[count]->setVolume(volume);
		}
	}

	//SetBit(KeyName);
}

void SoundManager::PlayZoneBGM(string key, float vol)
{
	int count = 0;
	int c1, c2;
	string key2 = key + "_shopkeeper";
	arrSoundIter iter1 = m_totalSounds.begin();
	arrSoundIter iter2 = m_totalSounds.begin();
	arrSoundIter iter = m_totalSounds.begin();

	for (iter; iter != m_totalSounds.end(); ++iter, count++)
	{
		if (key == iter->first)
		{
			iter1 = iter;
			c1 = count;
		}
		else if (key2 == iter->first)
		{
			iter2 = iter;
			c2 = count;
		}
	}
	m_system->playSound(FMOD_CHANNEL_FREE, *iter1->second, false, &m_channel[c1]);
	//m_channel[count]->setVolume(volume);
	m_channel[c1]->setVolume(vol);

	m_system->playSound(FMOD_CHANNEL_FREE, *iter2->second, false, &m_channel[c2]);
	//m_channel[count]->setVolume(volume);
	m_channel[c2]->setVolume(0.0f);

}

void SoundManager::PauseZoneBGM(string key)
{
	int count = 0;
	int c1, c2;
	string key2 = key + "_shopkeeper";
	arrSoundIter iter1 = m_totalSounds.begin();
	arrSoundIter iter2 = m_totalSounds.begin();
	arrSoundIter iter = m_totalSounds.begin();

	for (iter; iter != m_totalSounds.end(); ++iter, count++)
	{
		if (key == iter->first)
		{
			iter1 = iter;
			c1 = count;
		}
		else if (key2 == iter->first)
		{
			iter2 = iter;
			c2 = count;
		}
	}
	m_channel[c1]->setPaused(true);
	m_channel[c2]->setPaused(true);

}

void SoundManager::ResumeZoneBGM(string key, float vol)
{
	int count = 0;
	int c1, c2;
	string key2 = key + "_shopkeeper";
	arrSoundIter iter1 = m_totalSounds.begin();
	arrSoundIter iter2 = m_totalSounds.begin();
	arrSoundIter iter = m_totalSounds.begin();

	for (iter; iter != m_totalSounds.end(); ++iter, count++)
	{
		if (key == iter->first)
		{
			iter1 = iter;
			c1 = count;
		}
		else if (key2 == iter->first)
		{
			iter2 = iter;
			c2 = count;
		}
	}

	m_channel[c1]->setVolume(vol);
	m_channel[c2]->setVolume(vol);

	m_channel[c1]->setPaused(false);
	m_channel[c2]->setPaused(false);
}

void SoundManager::Stop(string KeyName)
{
	int count = 0;
	arrSoundIter iter = m_totalSounds.begin();
	for (iter; iter != m_totalSounds.end(); ++iter, count++)
	{
		if (KeyName == iter->first)
		{
			m_channel[count]->stop();
			break;
		}
	}
}

void SoundManager::Pause(string KeyName)
{
	int count = 0;
	arrSoundIter iter = m_totalSounds.begin();
	for (iter; iter != m_totalSounds.end(); ++iter, count++)
	{
		if (KeyName == iter->first)
		{
			m_channel[count]->setPaused(true);
			break;
		}
	}
}

void SoundManager::resume(string KeyName, float volume)
{
	int count = 0;
	arrSoundIter iter = m_totalSounds.begin();
	for (iter; iter != m_totalSounds.end(); ++iter, count++)
	{
		if (KeyName == iter->first)
		{
			m_channel[count]->setVolume(volume);
			m_channel[count]->setPaused(false);
			break;
		}
	}
}

bool SoundManager::isPlaySound(string KeyName)
{
	int count = 0;
	bool isPlay;

	arrSoundIter iter = m_totalSounds.begin();
	for (iter; iter != m_totalSounds.end(); ++iter, count++)
	{
		if (KeyName == iter->first)
		{
			m_channel[count]->isPlaying(&isPlay);
			break;
		}
	}

	return isPlay;
}

bool SoundManager::IspauserSound(string KeyName)
{
	int count = 0;
	bool isPause;

	arrSoundIter iter = m_totalSounds.begin();
	for (iter; iter != m_totalSounds.end(); ++iter, count++)
	{
		if (KeyName == iter->first)
		{
			m_channel[count]->getPaused(&isPause);
			break;
		}
	}
	return isPause;
}

void SoundManager::PlayBGM(string KeyName)
{
}

void SoundManager::PlayEffect(string KeyName)
{
}

void SoundManager::SetVolume(string key, float vol)
{
	int count = 0;
	arrSoundIter iter = m_totalSounds.begin();
	for (iter; iter != m_totalSounds.end(); ++iter, count++)
	{
		if (key == iter->first)
		{
			m_channel[count]->setPaused(true);
			break;
		}
	}

	m_channel[count]->setVolume(vol);
	m_channel[count]->setPaused(false);
}

void SoundManager::SetBGMVolume(string key, float vol)
{
	int count = 0;
	int c1, c2 = -1;
	string key2 = key + "_shopkeeper";
	arrSoundIter iter1 = m_totalSounds.begin();
	arrSoundIter iter2 = m_totalSounds.begin();
	arrSoundIter iter = m_totalSounds.begin();

	for (iter; iter != m_totalSounds.end(); ++iter, count++)
	{
		if (key == iter->first)
		{
			iter1 = iter;
			c1 = count;
		}
		else if (key2 == iter->first)
		{
			iter2 = iter;
			c2 = count;
		}
	}

	m_channel[c1]->setPaused(true);

	m_channel[c1]->setVolume(vol);

	m_channel[c1]->setPaused(false);

	if (c2 != -1)
	{
		m_channel[c2]->setPaused(true);
		m_channel[c2]->setVolume(vol);
		m_channel[c2]->setPaused(false);

	}


}

void SoundManager::AllStop()
{
	int count = 0;
	arrSoundIter iter = m_totalSounds.begin();
	for (iter; iter != m_totalSounds.end(); ++iter, count++)
	{
			m_channel[count]->stop();
	}
}

// 비트 정보를 받은 파일를 연결해서 벡터에 넣어야 합니다.
void SoundManager::SetBit(string KeyName)
{

	m_vBeat.clear();

	if (m_mBeat.find(KeyName) == m_mBeat.end())
	{
		m_vBeat.clear();

		char str[255];
		char * tok;
		char buf[10000];

		sprintf(str, "sound/%s.txt", KeyName.c_str());
		fp = fopen(str, "r");

		fgets(buf, 10000, fp);

		tok = strtok(buf, ",");
		//m_vBeat.push_back(atoi(tok));
		while (tok != NULL)
		{
			m_vBeat.push_back(atoi(tok));
			tok = strtok(NULL, ",");
		}
		m_mBeat.insert(make_pair(KeyName, m_vBeat));
		fclose(fp);
	}
	else
	{
		for (m_miBeat = m_mBeat.begin(); m_miBeat != m_mBeat.end(); m_miBeat++)
		{
			if (m_miBeat->first == KeyName)
			{
				m_vBeat = m_miBeat->second;
				break;
			}
		}
	}

	
}
