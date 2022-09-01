#include "Time.h"

namespace phoenix
{

	void Time::Tick()
	{
		auto duration = clock::now() - m_startTimePoint;
		time = duration.count() / static_cast<float>(clock_duration::period::den); //from nanoseconds to 1 second

		duration = clock::now() - m_frameTimePoint;
		deltaTime = duration.count() / static_cast<float>(clock_duration::period::den);

		m_frameTimePoint = clock::now();

	}

}