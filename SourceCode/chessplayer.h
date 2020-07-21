#pragma once

#include <iostream>
#include <vector>

#include "chessboard.h"
#include "position.h"

class CChessPlayer
{
public:
	CChessPlayer();
	~CChessPlayer();
	void fallChess();//下棋
	int str2int(std::string str);
	CPosition position2point();//转为position类
	void setChess(bool chessType);
	bool getChess();
private:
	char* m_position;
	bool m_chess;//我是黑子还是白子
	//std::vector<CPosition> vec_position;
};

