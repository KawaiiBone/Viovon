#pragma once
//#include <mutex>
#include "SoundService.h"
namespace dae
{
	class ServiceLocater final 
	{
	private:
		static SoundService* m_pSoundSystem;
		static NullSoundSystem m_NullSoundSystem;
		ServiceLocater();
		~ServiceLocater();
	public:
		static SoundService& GetSoundSystem();
		static void RegisterSoundSystem(SoundService* ss);
		static void CleanUp();



	};

	//NullSoundSystem ServiceLocater::m_NullSoundSystem;
	//SoundService* ServiceLocater::m_pSoundSystem = &m_NullSoundSystem;
}




