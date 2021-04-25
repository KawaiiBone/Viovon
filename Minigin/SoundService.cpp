#include "MiniginPCH.h"
#include "SoundService.h"
#include <mutex>

#include "audio.h"

using namespace std::literals::chrono_literals;

dae::SoundSystem::SoundSystem() :
	m_Thread(&SoundSystem::UpdateAudio, this), m_HasPLayedMusic{ false }, m_IsCleaningUp{false}
{

}

dae::SoundSystem::~SoundSystem()
{
	m_IsCleaningUp = true;
	m_Thread.join();
	//	SDL_Quit();
}

void dae::SoundSystem::PlaySound(const std::string& filename, const int volume)
{
	m_QueueSounds.push({ filename ,volume });

}

void dae::SoundSystem::PlayMusic(const std::string& filename, const int volume)
{
	m_QueueMusic.push({ filename ,volume });
}

void dae::SoundSystem::CleanUp()
{
	m_IsCleaningUp = true;
}

void dae::SoundSystem::PauseAudio()
{
	pauseAudio(); 

}

void dae::SoundSystem::UnpauseAudio()
{
	unpauseAudio();
	
}

void dae::SoundSystem::UpdateAudio()
{
	std::mutex m_Mutex;
	
	while (!m_IsCleaningUp)
	{
		
		if (m_QueueMusic.size() > 0)
		{
			m_Mutex.lock();

			if (m_HasPLayedMusic)
			{
				playSound(m_QueueMusic.front().filename.c_str(), SDL_MIX_MAXVOLUME - 1);
			}
			else
			{

				m_HasPLayedMusic = true;
				playSound(m_QueueMusic.front().filename.c_str(), m_QueueMusic.front().volume);
			}
			m_QueueMusic.pop();
			m_Mutex.unlock();

		}
		else if (m_QueueSounds.size() > 0)
		{
			m_Mutex.lock();
			playSound(m_QueueSounds.front().filename.c_str(), m_QueueSounds.front().volume);
			m_QueueSounds.pop();
			std::this_thread::sleep_for(0.1s);
			m_Mutex.unlock();
		}
	}
}


