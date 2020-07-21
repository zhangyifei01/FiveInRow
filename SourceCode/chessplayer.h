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
	void fallChess();//����
	int str2int(std::string str);
	CPosition position2point();//תΪposition��
	void setChess(bool chessType);
	bool getChess();
private:
	char* m_position;
	bool m_chess;//���Ǻ��ӻ��ǰ���
	//std::vector<CPosition> vec_position;
};

