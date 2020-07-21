#include "aiplayer.h"



CAIPlayer::CAIPlayer()
{
	m_position = new char[10];
}


CAIPlayer::~CAIPlayer()
{
	delete[] m_position;
}

std::string CAIPlayer::int2str(int a)
{
	//将数字转成字符串,这种用法比stringstream用法效率高
	std::string str = "";
	std::string str_dig = "";
	if (a == 0)
		str += "0";
	if (a>0)
	{
		while (a)
		{
			str_dig = "";
			str_dig += (a % 10 + '0');
			str = str_dig + str;
			a /= 10;
		}
	}
	if (a<0)
	{
		a = -a;
		while (a)
		{
			str_dig = "";
			str_dig += (a % 10 + '0');
			str = str_dig + str;
			a /= 10;
		}
		str = "-" + str;
	}
	return str;
}

std::string CAIPlayer::point2position(CPosition & position)
{
	std::string inputform = "";
	char c_ylabel;//字母
	c_ylabel = position.getY() + 65;
	inputform += c_ylabel;
	inputform += int2str(BOARD_DIMENSION - position.getX());

	return inputform;
}

void CAIPlayer::setBestPosition(CChessBoard & chessboard)
{
	std::string str;
	str = point2position(chessboard.getMaxScorePosition());
	strcpy(m_position, str.c_str());
}

std::string CAIPlayer::getBestPosition()
{
	return m_position;
}

void CAIPlayer::setChess(bool chessType)
{
	m_chess = chessType;
}

bool CAIPlayer::getChess()
{
	return m_chess;
}


