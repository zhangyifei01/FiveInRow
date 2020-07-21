#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
//#include <windows.h>
#include "position.h"

#define BOARD_DIMENSION 15 //棋盘大小是15*15

class CChessBoard
{
public:
	CChessBoard();
	~CChessBoard();
	void initChessBoard();//初始化棋盘
	void drawChessBoard();//画出棋盘
	int getPositionValue(int xx, int yy);//返回值是0-12,9、11是黑子，10、12是白子
	void changePositionValue(bool chesstype, CPosition & position);//下的棋子和位置
	bool isLegalPosition(CPosition & position);//是否是合法的位置
	void setCurrentChess(bool currentchess);//当前棋子
	bool getCurrentChess();
	bool isWin(int xx,int yy);
	void initPositionScore();//初始化位置打分
	void setArrayPositionScore(int xx, int yy,int scoreValue);//设置arr_positionscore的值

	//**************************************************************
	//对下子位置打分
	int slideWindowScore(int xx,int yy,bool ismychess,int windowtype);//检测一个窗口中棋子情况，返回一个窗口打分,以xx,yy为底部
	int blankPositionScore(int xx,int yy,bool ishavechess,bool ismychess);//对空位置八个方向滑动窗口求和进行打分
	void moveWindow();//移动窗口
	CPosition getMaxScorePosition();//得到打分最高位置
	//*******************************************************************

	//***************************************************************************************
	//判断是否禁手
	bool isLiveThree(int xx,int yy,bool currentChess,int windowType);//是不是活三
	bool isLiveFour(int xx, int yy, bool currentChess, int windowType);//是不是活四，大小为6的窗口可以看出是不是活四
	bool isDoubleThree(int xx, int yy, bool currentChess);//是不是双活三
	bool isDoubleFour(int xx, int yy, bool currentChess);//是不是双活四
	bool isLongString(int xx, int yy, bool currentChess);//是不是长连
	bool isForbidden(bool currentChess, CPosition position);//当前棋子和 要下棋的位置
	//*********************************************************************************

	//********************************************************************
	//判断vector是否为空
	bool checkVectorIsEmpty();//检查位置数组vec_black_chess vec_black_chess是否是空,ture返回非空

private:
	const char m_symbol[13][4] = { "┌","┬","┐","├","┼","┤","└","┴","┘","●","○","▲","△" };
	bool m_currentchess;
	int arr_position[BOARD_DIMENSION][BOARD_DIMENSION];
	int arr_havechess[BOARD_DIMENSION][BOARD_DIMENSION];
	int arr_positionscore[BOARD_DIMENSION][BOARD_DIMENSION];
	std::vector<CPosition> vec_black_chess;
	std::vector<CPosition> vec_white_chess;
};

