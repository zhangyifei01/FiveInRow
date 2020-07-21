#pragma once

#include "chessboard.h"
#include "position.h"


class CAIPlayer
{
public:
	CAIPlayer();
	~CAIPlayer();
	std::string int2str(int a);//����תΪ�ַ���
	std::string point2position(CPosition & position);//λ��תΪ�����ַ�����ʽ
	void setBestPosition(CChessBoard & chessboard);
	std::string getBestPosition();
	void setChess(bool chessType);
	bool getChess();
private:
	char* m_position;//�����λ��
	bool m_chess;//���Ǻ��ӻ��ǰ���
};

