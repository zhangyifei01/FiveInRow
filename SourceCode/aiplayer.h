#pragma once

#include "chessboard.h"
#include "position.h"


class CAIPlayer
{
public:
	CAIPlayer();
	~CAIPlayer();
	std::string int2str(int a);//数字转为字符串
	std::string point2position(CPosition & position);//位置转为输入字符串形式
	void setBestPosition(CChessBoard & chessboard);
	std::string getBestPosition();
	void setChess(bool chessType);
	bool getChess();
private:
	char* m_position;//下棋的位置
	bool m_chess;//我是黑子还是白子
};

