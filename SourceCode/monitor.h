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
	void beginGame();//开始一局游戏
	bool getCurrentChess();//得到当前棋子
	bool nextChess();//下一个下棋者
	bool checkIsLegalPosition(CChessBoard & chessboard,CPosition & position);
private:
	bool m_currentchess;//黑子是先手
};

