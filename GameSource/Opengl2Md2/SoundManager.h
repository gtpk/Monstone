#pragma once
namespace MarxEngine
{
	class SoundManager
	{
	public:
		SoundManager();
		~SoundManager();

		int DamagedSound;//
		int GameOverSound;//cat
		int AddScoureSound;//swallow
		int goScoureSound;//swallow
		int readyScoureSound;//swallow
		int rolling_coinScoureSound;
		//SoundPool m_sound_pool;

		//static MediaPlayer m_Media;
		//static MediaPlayer m_Ingame;

#pragma region SoundLIB

		void PlayDamagedSound()
		{
			//m_sound_pool.play(DamagedSound, 1f, 1f, 0, 0, 1);
		}

		void PlayGameOverSound()
		{
			//m_sound_pool.play(GameOverSound, 1f, 1f, 0, 0, 1);
		}

		void PlayAddScoureSound()
		{
			//m_sound_pool.play(AddScoureSound, 0.5f, 0.5f, 0, 0, 1);
		}

		void PlayGoSound()
		{
			//m_sound_pool.play(goScoureSound, 1f, 1f, 0, 0, 1);
		}

		void PlayReadySound()
		{
			//m_sound_pool.play(readyScoureSound, 1f, 1f, 0, 0, 1);
		}

		void PlayRollingSound()
		{
			//m_sound_pool.play(rolling_coinScoureSound, 1f, 1f, 0, 0, 1);
		}

		void PlayBackgroundSound()
		{
		}
		void StopBackgroundSound()
		{

		}

		void PauseBackgroundSound()
		{

		}

		void PlayInGameBackgroundSound()
		{
		}
		void StopInGameBackgroundSound()
		{
		}

		void PauseInGameBackgroundSound()
		{
		}

		void ResumeBackgroundSound()
		{
		}
#pragma endregion


	};

}