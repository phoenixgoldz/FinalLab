#pragma once
#include "Framework/Component.h"
#include "Audio/AudioChannel.h"

namespace phoenix
{
	class AudioComponent : public Component
	{
	public:
		CLASS_DECLARATION(AudioComponent)

		AudioComponent() = default;
		~AudioComponent();


		void Initialize() override;
		void Update() override;

		bool Write(const rapidjson::Value& value) const;
		bool Read(const rapidjson::Value& value);

		void Play();
		void Stop();

		AudioChannel m_channel;

		std::string sound_name;

		bool playOnAwake = false;
		bool loopAudio = false;

		float volume = 1;
		float pitch = 1;
		bool play_on_start = false;
		bool loop = false;


	};



}