#ifndef _TIMER_H_
#define _TIMER_H_

#include <iostream>
#include <ctime>

class Timer
{
private:
	double m_begTime;

public:

	void StartTime(void)
	{
		m_begTime = clock();
	}

	double GetElapsedTime(void) const
	{
		return (double(clock()) - m_begTime) / (CLOCKS_PER_SEC);
	}

};

#endif