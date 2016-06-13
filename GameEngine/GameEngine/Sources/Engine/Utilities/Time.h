#ifndef _TIMER_H_
#define _TIMER_H_

#include <ctime>

class Timer
{
private:
	double m_begTime;

public:

	Timer() { m_begTime = 0; };
	~Timer(){};

	void StartTime(void)
	{
		m_begTime = clock();
	}

	double GetElapsedTime(void) const
	{
		return (double(clock()) - m_begTime) / (CLOCKS_PER_SEC);
	}

	static Timer& GetInstance(void)
	{
		static Timer gi_timer;
		return gi_timer;
	}
};

#endif