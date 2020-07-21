#pragma once

#include <windows.h>
#include <conio.h>//kbhit()
#include "chessboard.h"
#include "position.h"
#include "chessplayer.h"
#include "aiplayer.h"
#include "timer.h"

class CMonitor
{
public:
	CMonitor();
	~CMonitor();
	void beginGame();//��ʼһ����Ϸ
	bool getCurrentChess();//�õ���ǰ����
	bool nextChess();//��һ��������
	bool checkIsLegalPosition(CChessBoard & chessboard,CPosition & position);
private:
	bool m_currentchess;//����������
};

