#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
//#include <windows.h>
#include "position.h"

#define BOARD_DIMENSION 15 //���̴�С��15*15

class CChessBoard
{
public:
	CChessBoard();
	~CChessBoard();
	void initChessBoard();//��ʼ������
	void drawChessBoard();//��������
	int getPositionValue(int xx, int yy);//����ֵ��0-12,9��11�Ǻ��ӣ�10��12�ǰ���
	void changePositionValue(bool chesstype, CPosition & position);//�µ����Ӻ�λ��
	bool isLegalPosition(CPosition & position);//�Ƿ��ǺϷ���λ��
	void setCurrentChess(bool currentchess);//��ǰ����
	bool getCurrentChess();
	bool isWin(int xx,int yy);
	void initPositionScore();//��ʼ��λ�ô��
	void setArrayPositionScore(int xx, int yy,int scoreValue);//����arr_positionscore��ֵ

	//**************************************************************
	//������λ�ô��
	int slideWindowScore(int xx,int yy,bool ismychess,int windowtype);//���һ���������������������һ�����ڴ��,��xx,yyΪ�ײ�
	int blankPositionScore(int xx,int yy,bool ishavechess,bool ismychess);//�Կ�λ�ð˸����򻬶�������ͽ��д��
	void moveWindow();//�ƶ�����
	CPosition getMaxScorePosition();//�õ�������λ��
	//*******************************************************************

	//***************************************************************************************
	//�ж��Ƿ����
	bool isLiveThree(int xx,int yy,bool currentChess,int windowType);//�ǲ��ǻ���
	bool isLiveFour(int xx, int yy, bool currentChess, int windowType);//�ǲ��ǻ��ģ���СΪ6�Ĵ��ڿ��Կ����ǲ��ǻ���
	bool isDoubleThree(int xx, int yy, bool currentChess);//�ǲ���˫����
	bool isDoubleFour(int xx, int yy, bool currentChess);//�ǲ���˫����
	bool isLongString(int xx, int yy, bool currentChess);//�ǲ��ǳ���
	bool isForbidden(bool currentChess, CPosition position);//��ǰ���Ӻ� Ҫ�����λ��
	//*********************************************************************************

	//********************************************************************
	//�ж�vector�Ƿ�Ϊ��
	bool checkVectorIsEmpty();//���λ������vec_black_chess vec_black_chess�Ƿ��ǿ�,ture���طǿ�

private:
	const char m_symbol[13][4] = { "��","��","��","��","��","��","��","��","��","��","��","��","��" };
	bool m_currentchess;
	int arr_position[BOARD_DIMENSION][BOARD_DIMENSION];
	int arr_havechess[BOARD_DIMENSION][BOARD_DIMENSION];
	int arr_positionscore[BOARD_DIMENSION][BOARD_DIMENSION];
	std::vector<CPosition> vec_black_chess;
	std::vector<CPosition> vec_white_chess;
};

