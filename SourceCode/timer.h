#pragma once

#include <time.h>
#define TIME_THRESHOLD 15 //ʱ��15s

class CTimer
{
public:
	CTimer();
	~CTimer();
	void startTimer();//��ʼ��ʱ
	bool isTimeOut();//�Ƿ�ʱ
private:
	clock_t m_start;
	clock_t m_end;
	int m_interval;//ʱ���� ��
};

