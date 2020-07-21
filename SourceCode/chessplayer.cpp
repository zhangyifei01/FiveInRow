#include "chessplayer.h"



CChessPlayer::CChessPlayer()
{
	m_position = new char[10];
	//vec_position.clear();
}


CChessPlayer::~CChessPlayer()
{
	delete[] m_position;
}

void CChessPlayer::fallChess()
{
	//m_position = new char[10];
	std::cin >> m_position;
	//判断是否有棋子，是否越界

}

int CChessPlayer::str2int(std::string str)
{
	int a, k;
	a = 0;
	k = 1;
	for (int i = str.size() - 1; i >= 0; i--)
	{
		a += ((static_cast<int>(str[i]) - 48)*k);
		k *= 10;
	}
	return a;
}

CPosition CChessPlayer::position2point()
{
	CPosition position;
	int xx, yy;
	std::string str_ylabel;
	yy = m_position[0] - 65;//第几列
	str_ylabel = ((std::string)m_position).substr(1, strlen(m_position - 1));
	xx = BOARD_DIMENSION - str2int(str_ylabel);

	position.setX(xx);
	position.setY(yy);

	return position;
}

void CChessPlayer::setChess(bool chessType)
{
	m_chess = chessType;
}

bool CChessPlayer::getChess()
{
	return m_chess;
}
