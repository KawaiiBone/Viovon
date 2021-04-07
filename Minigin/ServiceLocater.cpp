#include "MiniginPCH.h"
#include "ServiceLocater.h"


dae::NullSoundSystem dae::ServiceLocater::m_NullSoundSystem;
dae::SoundService* dae::ServiceLocater::m_pSoundSystem = &m_NullSoundSystem;

dae::ServiceLocater::ServiceLocater()
	
{
	m_pSoundSystem = &m_NullSoundSystem;
}

dae::ServiceLocater::~ServiceLocater()
{
	delete m_pSoundSystem;
	m_pSoundSystem = nullptr;
}

dae::SoundService& dae::ServiceLocater::GetSoundSystem()
{
	return *m_pSoundSystem; 
}

void dae::ServiceLocater::RegisterSoundSystem(SoundService* ss)
{
	////delete m_pSoundSystem;
	////m_pSoundSystem = nullptr;

	//m_pSoundSystem = ss;
	////if (ss)
	////{
	////	
	////}
	m_pSoundSystem = ss == nullptr ? &m_NullSoundSystem : ss;
}

void dae::ServiceLocater::CleanUp()
{

	m_pSoundSystem->CleanUp();
	delete m_pSoundSystem;
	m_pSoundSystem = nullptr;
}



