#pragma once
#include <thread>
#include <atomic>
#include "queue"

namespace dae
{
	class SoundService
	{
	public:
		virtual ~SoundService() = default;
		virtual void PlaySound(const std::string& filename, const int volume) = 0;
		virtual void PlayMusic(const std::string& filename, const int volume) = 0;
		virtual void UpdateAudio() = 0;
		virtual void CleanUp() = 0;
		virtual  bool IsNullSound()const = 0;

	};




	struct AudioInfo
	{
		const std::string filename;
		const int volume;
	};

	class SoundSystem final : public SoundService
	{
	public:
		SoundSystem();
		~SoundSystem();
		void PlaySound(const std::string& filename, const int volume) override;
		void PlayMusic(const std::string& filename, const int volume) override;
		void CleanUp() override;
		void PauseAudio();
		void UnpauseAudio();
		bool IsNullSound()const override { return false; };
	private:
		void UpdateAudio()override;
		std::queue<AudioInfo> m_QueueSounds;
		std::queue<AudioInfo> m_QueueMusic;
		std::thread m_Thread;
		std::atomic<bool> m_HasPLayedMusic;
		std::atomic<bool> m_IsCleaningUp;
	};


	class NullSoundSystem final : public SoundService
	{
	public:
		~NullSoundSystem() = default;
		void PlaySound(const std::string&, const int) override { std::cout << "Playing NULLSound"; };
		virtual void PlayMusic(const std::string&, const int) {};
		void UpdateAudio()override {};
		 void CleanUp() override {};
		 bool IsNullSound()const override { return true; };
	};
}