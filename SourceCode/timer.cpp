#include "timer.h"



CTimer::CTimer()
{
}


CTimer::~CTimer()
{
}

void CTimer::startTimer()
{
	m_start = clock();
}

bool CTimer::isTimeOut()
{
	m_end = clock();
	m_interval = (m_end - m_start) / CLOCKS_PER_SEC;
	if (m_interval > TIME_THRESHOLD)
		return true;//≥¨ ±¡À
	else
		return false;
}
