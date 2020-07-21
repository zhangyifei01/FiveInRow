#pragma once

#include <time.h>
#define TIME_THRESHOLD 15 //时间15s

class CTimer
{
public:
	CTimer();
	~CTimer();
	void startTimer();//开始计时
	bool isTimeOut();//是否超时
private:
	clock_t m_start;
	clock_t m_end;
	int m_interval;//时间间隔 秒
};

