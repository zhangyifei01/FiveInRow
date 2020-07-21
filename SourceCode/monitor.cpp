#include "monitor.h"



CMonitor::CMonitor()
{
	m_currentchess = 1;//黑子是先手
}


CMonitor::~CMonitor()
{
}

void CMonitor::beginGame()
{
	
	CChessBoard chessBoard;//一个棋盘类
	CChessPlayer chessPlayer;
	CTimer timer;
	CPosition position;

	bool h_vs_h_or_h_vs_ai = 0;//默认人机对战,0是人机，1是人人
	

	int chessPositionNum;//棋盘点数

	m_currentchess = true;//黑子是先手
	chessBoard.setCurrentChess(m_currentchess);

	chessPositionNum = BOARD_DIMENSION * BOARD_DIMENSION;

	std::cout << "welcome to game five-in-row " << std::endl;
	std::cout << "choose 1 (human vs human)  or 0 (human vs computer): ";
	std::cin >> h_vs_h_or_h_vs_ai;
	if (h_vs_h_or_h_vs_ai)//人人对战
	{
		CChessPlayer chessPlayer2;
		int user1Score = 0, user2Score = 0;//分数
		std::cout << "Player1 is first using black chess in first round " << std::endl;

		chessPlayer.setChess(false);//先设相反的，在for循环中返回来
		chessPlayer2.setChess(true);

		for (int gameRound = 0; gameRound < 2; gameRound++)
		{
			//进行两局
			chessPlayer.setChess(!chessPlayer.getChess());//因为每局要换棋子
			chessPlayer2.setChess(!chessPlayer2.getChess());

			while (1)
			{
				//*****************************************************************************************
				if (chessPlayer.getChess() && m_currentchess)//user1先下，当前是黑子
				{//这一定是第一局
					chessBoard.drawChessBoard();
					std::cout << "now user1 turn, please input your position: ";
					timer.startTimer();
					while (1)
					{
						if (kbhit())//非阻塞的响应键盘输入事件
						{
							chessPlayer.fallChess();//人下棋
							break;
						}
						if (timer.isTimeOut())
						{
							//if (gameRound == 0)
							//{
							std::cout << "\n user1 time out, user2 win!!!" << std::endl;
							Sleep(1000);
							//exit(0);
							user2Score += 2;
							/*}
							else
							{
								std::cout << "\n user2 time out, user1 win!!!" << std::endl;
								Sleep(1000);
								//exit(0);
								user1Score += 2;
							}*/
							goto SECOND_ROUND;
						}

					}


					if (!checkIsLegalPosition(chessBoard, chessPlayer.position2point()))
					{
						//越界或者有棋子了
						std::cout << "this postion have chess or out of chessboard!!!" << std::endl;
						Sleep(1000);
						continue;
					}
					if (chessBoard.isForbidden(m_currentchess, chessPlayer.position2point()))
					{
						//禁手了
						std::cout << "you are first, this position is forbidened!!! " << std::endl;
						Sleep(1000);
						continue;
					}

					chessBoard.changePositionValue(true, chessPlayer.position2point());//黑子下的位置
					chessPositionNum--;

					if (chessBoard.isWin(chessPlayer.position2point().getX(), chessPlayer.position2point().getY()))
					{
						//检查是否赢了
						chessBoard.drawChessBoard();
						//if (gameRound == 0)
						//{
						std::cout << "user1 win " << std::endl;
						Sleep(1000);
						//exit(0);
						user1Score += 2;
						//}
						/*else
						{
							std::cout << "user2 win " << std::endl;
							Sleep(1000);
							//exit(0);
							user2Score += 2;
						}*/
						goto SECOND_ROUND;
					}
					if (!chessBoard.isWin(chessPlayer.position2point().getX(), chessPlayer.position2point().getY()) && chessPositionNum < 1)
					{
						//棋盘占满了还没分出胜负
						chessBoard.drawChessBoard();
						std::cout << "user1 and user2 both win " << std::endl;
						Sleep(1000);
						//exit(0);
						user1Score += 1;
						user2Score += 1;
						goto SECOND_ROUND;
					}

					m_currentchess = !m_currentchess;
					chessBoard.setCurrentChess(m_currentchess);
				}


				//*********************************************************
				if (chessPlayer.getChess() && !m_currentchess)//user1先下，当前是白子
				{//第一局
					chessBoard.drawChessBoard();
					//if(gameRound == 0)
					std::cout << "now user2 turn, please input your position: ";
					//else
					//	std::cout << "now user2 turn, please input your position: ";
					timer.startTimer();
					while (1)
					{
						if (kbhit())//非阻塞的响应键盘输入事件
						{
							chessPlayer2.fallChess();//人下棋
							break;
						}
						if (timer.isTimeOut())
						{
							//if (gameRound == 0)
							//{
							std::cout << "\n user2 time out, user1 win!!!" << std::endl;
							Sleep(1000);
							//exit(0);
							user1Score += 2;
							//}
							/*else
							{
								std::cout << "\n user1 time out, user2 win!!!" << std::endl;
								Sleep(1000);
								//exit(0);
								user2Score += 2;
							}*/
							goto SECOND_ROUND;
						}

					}
					//std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;

					if (!checkIsLegalPosition(chessBoard, chessPlayer2.position2point()))
					{
						//越界或者有棋子了
						std::cout << "this postion have chess or out of chessboard!!!" << std::endl;
						Sleep(1000);
						continue;
					}
					if (chessBoard.isForbidden(m_currentchess, chessPlayer2.position2point()))
					{
						//禁手了
						std::cout << "you are first, this position is forbidened!!! " << std::endl;
						Sleep(1000);
						continue;
					}

					chessBoard.changePositionValue(false, chessPlayer2.position2point());//白子下的位置
					chessPositionNum--;

					if (chessBoard.isWin(chessPlayer2.position2point().getX(), chessPlayer2.position2point().getY()))
					{
						//检查是否赢了
						chessBoard.drawChessBoard();
						//if (gameRound == 0)
						//{
						std::cout << "user2 win " << std::endl;
						Sleep(1000);
						//exit(0);
						user2Score += 2;
						//}
						/*else
						{
							std::cout << "user1 win " << std::endl;
							Sleep(1000);
							//exit(0);
							user1Score += 2;
						}*/
						goto SECOND_ROUND;
					}
					if (!chessBoard.isWin(chessPlayer2.position2point().getX(), chessPlayer2.position2point().getY()) && chessPositionNum < 1)
					{
						//棋盘占满了还没分出胜负
						chessBoard.drawChessBoard();
						std::cout << "user1 and user2 both win " << std::endl;
						Sleep(1000);
						//exit(0);
						user1Score += 1;
						user2Score += 1;
						goto SECOND_ROUND;
					}

					m_currentchess = !m_currentchess;
					chessBoard.setCurrentChess(m_currentchess);
				}

				//*****************************************************************************************
				if (chessPlayer2.getChess() && m_currentchess)//user2先下，当前是黑子
				{//第二局
					chessBoard.drawChessBoard();
					//if (gameRound == 0)//第一局user1是黑子
					//	std::cout << "now user1 turn, please input your position: ";
					//else//第二局user2是黑子
					std::cout << "now user2 turn, please input your position: ";
					timer.startTimer();
					while (1)
					{
						if (kbhit())//非阻塞的响应键盘输入事件
						{
							chessPlayer2.fallChess();//人下棋
							break;
						}
						if (timer.isTimeOut())
						{
							/*if (gameRound == 0)
							{
								std::cout << "\n user1 time out, user2 win!!!" << std::endl;
								Sleep(1000);
								//exit(0);
								user2Score += 2;
							}*/
							//else
							//{
							std::cout << "\n user2 time out, user1 win!!!" << std::endl;
							Sleep(1000);
							//exit(0);
							user1Score += 2;
							//}
							goto SECOND_ROUND;
						}

					}


					if (!checkIsLegalPosition(chessBoard, chessPlayer2.position2point()))
					{
						//越界或者有棋子了
						std::cout << "this postion have chess or out of chessboard!!!" << std::endl;
						Sleep(1000);
						continue;
					}
					if (chessBoard.isForbidden(m_currentchess, chessPlayer2.position2point()))
					{
						//禁手了
						std::cout << "you are first, this position is forbidened!!! " << std::endl;
						Sleep(1000);
						continue;
					}

					chessBoard.changePositionValue(true, chessPlayer2.position2point());//黑子下的位置
					chessPositionNum--;

					if (chessBoard.isWin(chessPlayer2.position2point().getX(), chessPlayer2.position2point().getY()))
					{
						//检查是否赢了
						chessBoard.drawChessBoard();
						/*if (gameRound == 0)
						{
							std::cout << "user1 win " << std::endl;
							Sleep(1000);
							//exit(0);
							user1Score += 2;
						}*/
						//else
						//{
						std::cout << "user2 win " << std::endl;
						Sleep(1000);
						//exit(0);
						user2Score += 2;
						//}
						goto SECOND_ROUND;
					}
					if (!chessBoard.isWin(chessPlayer2.position2point().getX(), chessPlayer2.position2point().getY()) && chessPositionNum < 1)
					{
						//棋盘占满了还没分出胜负
						chessBoard.drawChessBoard();
						std::cout << "user1 and user2 both win " << std::endl;
						Sleep(1000);
						//exit(0);
						user1Score += 1;
						user2Score += 1;
						goto SECOND_ROUND;
					}

					m_currentchess = !m_currentchess;
					chessBoard.setCurrentChess(m_currentchess);
				}


				//*********************************************************
				if (chessPlayer2.getChess() && !m_currentchess)//user2先下，当前是白子
				{//第二局
					chessBoard.drawChessBoard();
					//if (gameRound == 0)
						std::cout << "now user1 turn, please input your position: ";
					//else
					//std::cout << "now user2 turn, please input your position: ";
					timer.startTimer();
					while (1)
					{
						if (kbhit())//非阻塞的响应键盘输入事件
						{
							chessPlayer2.fallChess();//人下棋
							break;
						}
						if (timer.isTimeOut())
						{
							//if (gameRound == 0)
							//{
								std::cout << "\n user1 time out, user2 win!!!" << std::endl;
								Sleep(1000);
								//exit(0);
								user1Score += 2;
							//}
							/*//else
							//{
							std::cout << "\n user1 time out, user2 win!!!" << std::endl;
							Sleep(1000);
							//exit(0);
							user2Score += 2;
							//}*/
							goto SECOND_ROUND;
						}

					}


					if (!checkIsLegalPosition(chessBoard, chessPlayer2.position2point()))
					{
						//越界或者有棋子了
						std::cout << "this postion have chess or out of chessboard!!!" << std::endl;
						Sleep(1000);
						continue;
					}
					if (chessBoard.isForbidden(m_currentchess, chessPlayer2.position2point()))
					{
						//禁手了
						std::cout << "you are first, this position is forbidened!!! " << std::endl;
						Sleep(1000);
						continue;
					}

					chessBoard.changePositionValue(false, chessPlayer2.position2point());//白子下的位置
					chessPositionNum--;

					if (chessBoard.isWin(chessPlayer2.position2point().getX(), chessPlayer2.position2point().getY()))
					{
						//检查是否赢了
						chessBoard.drawChessBoard();
						//if (gameRound == 0)
						//{
							std::cout << "user1 win " << std::endl;
							Sleep(1000);
							//exit(0);
							user2Score += 2;
						//}
						/*//else
						//{
						std::cout << "user1 win " << std::endl;
						Sleep(1000);
						//exit(0);
						user1Score += 2;
						//}*/
						goto SECOND_ROUND;
					}
					if (!chessBoard.isWin(chessPlayer2.position2point().getX(), chessPlayer2.position2point().getY()) && chessPositionNum < 1)
					{
						//棋盘占满了还没分出胜负
						chessBoard.drawChessBoard();
						std::cout << "user1 and user2 both win " << std::endl;
						Sleep(1000);
						//exit(0);
						user1Score += 1;
						user2Score += 1;
						goto SECOND_ROUND;
					}

					m_currentchess = !m_currentchess;
					chessBoard.setCurrentChess(m_currentchess);
				}
			}

		SECOND_ROUND:;
			if (gameRound == 0)
			    std::cout << "Now second round, user2 is first using black chess in exchange!!!" << std::endl;
			Sleep(2000);
			chessBoard.initChessBoard();
			m_currentchess = true;
		}
		std::cout << "\n**************** display score **************************" << std::endl;
		std::cout << "user1 score is " << user1Score << ", user2 score is " << user2Score << std::endl;
	}
	else//人机对战
	{
		CAIPlayer aiPlayer;
		int userScore = 0, aiScore = 0;//分数
		bool chooseMode = 0;//0是计算机先手，1是人先手
		std::cout << "choose you first (input 1) or computer first (input 0) : ";
		std::cin >> chooseMode;

		if (!chooseMode)
		{
			chessPlayer.setChess(true);//人先下
			aiPlayer.setChess(false);
		}
		else
		{
			chessPlayer.setChess(false);//计算机先下
			aiPlayer.setChess(true);
		}

		for (int gameRound = 0; gameRound < 2; gameRound++)
		{//进行两局人机对战
			chessPlayer.setChess(!chessPlayer.getChess());//执子顺序交换
			aiPlayer.setChess(!aiPlayer.getChess());

			while (1)
			{
				//chessBoard.drawChessBoard();
				/*****************************************************************/
				if (chessPlayer.getChess() && m_currentchess)//人先下,当前是黑子下
				{
					chessBoard.drawChessBoard();
					std::cout << "now your turn, please input your position: ";
					timer.startTimer();
					while (1)
					{
						if (kbhit())//非阻塞的响应键盘输入事件
						{
							chessPlayer.fallChess();//人下棋
							break;
						}
						if (timer.isTimeOut())
						{
							std::cout << "\n your time out, computer win!!!" << std::endl;
							Sleep(1000);
							//exit(0);
							aiScore += 2;
							goto SECOND_GAME;
						}

					}


					if (!checkIsLegalPosition(chessBoard, chessPlayer.position2point()))
					{
						//越界或者有棋子了
						std::cout << "this postion have chess or out of chessboard!!!" << std::endl;
						Sleep(1000);
						continue;
					}
					if (chessBoard.isForbidden(m_currentchess, chessPlayer.position2point()))
					{
						//禁手了
						std::cout << "you are first, this position is forbidened!!! " << std::endl;
						Sleep(1000);
						continue;
					}

					chessBoard.changePositionValue(true, chessPlayer.position2point());//黑子下的位置
					chessPositionNum--;

					if (chessBoard.isWin(chessPlayer.position2point().getX(), chessPlayer.position2point().getY()))
					{
						//检查是否赢了
						chessBoard.drawChessBoard();
						std::cout << "you win " << std::endl;
						Sleep(1000);
						//exit(0);
						userScore += 2;
						goto SECOND_GAME;
					}
					if (!chessBoard.isWin(chessPlayer.position2point().getX(), chessPlayer.position2point().getY()) && chessPositionNum < 1)
					{
						//棋盘占满了还没分出胜负
						chessBoard.drawChessBoard();
						std::cout << "you and computer both win " << std::endl;
						Sleep(1000);
						//exit(0);
						userScore += 1;
						aiScore += 1;
						goto SECOND_GAME;
					}

					m_currentchess = !m_currentchess;
					chessBoard.setCurrentChess(m_currentchess);
				}
				/*****************************************************************/
				if (aiPlayer.getChess() && m_currentchess)//电脑先下，当前是黑子
				{
					chessBoard.drawChessBoard();
					timer.startTimer();//开始计时
					chessBoard.initPositionScore();//打分矩阵置零

					//if (chessBoard.checkVectorIsEmpty())//返回true是非空
					//{
					//	chessBoard.moveWindow();//先移动窗口才能找最大值
					//}
					position = chessBoard.getMaxScorePosition();//最优位置


					if (chessBoard.isForbidden(true, position))
					{
						//电脑下的位置禁手了
						chessBoard.setArrayPositionScore(position.getX(), position.getY(), 0);//这个位置打分置为0
						continue;
					}
					//std::cout << "坐标是：（" << position.getX() << "," << position.getY() << ")" << std::endl;
					aiPlayer.setBestPosition(chessBoard);
					if (timer.isTimeOut())
					{
						std::cout << "computer time out, you win " << std::endl;
						//exit(0);
						userScore += 2;
						goto SECOND_GAME;
					}

					std::cout << "computer' position is " << aiPlayer.getBestPosition().c_str() << std::endl;

					chessBoard.changePositionValue(true, position);
					chessPositionNum--;

					if (chessBoard.isWin(position.getX(), position.getY()))
					{
						chessBoard.drawChessBoard();
						std::cout << "computer win " << std::endl;
						Sleep(1000);
						//exit(0);
						userScore += 2;
						goto SECOND_GAME;
					}
					if (!chessBoard.isWin(position.getX(), position.getY()) && chessPositionNum < 1)
					{
						//棋盘占满了还没分出胜负
						chessBoard.drawChessBoard();
						std::cout << "you and computer both win " << std::endl;
						Sleep(1000);
						//exit(0);
						userScore += 1;
						aiScore += 1;
						goto SECOND_GAME;
					}
					Sleep(1000);
					m_currentchess = !m_currentchess;
					chessBoard.setCurrentChess(m_currentchess);
				}
				/*****************************************************************/
				if (chessPlayer.getChess() && !m_currentchess)//人先下，当前电脑下
				{
					chessBoard.drawChessBoard();
					timer.startTimer();//开始计时
					chessBoard.initPositionScore();//打分矩阵置零
					//if (chessBoard.checkVectorIsEmpty())//返回true是非空
					//{
					//	chessBoard.moveWindow();//先移动窗口才能找最大值
					//}
					position = chessBoard.getMaxScorePosition();//最优位置
					/*当前白子不会禁手
					if (chessBoard.isForbidden(true, position))
					{
						//电脑下的位置禁手了
						chessBoard.setArrayPositionScore(position.getX(), position.getY(), 0);//这个位置打分置为0
						continue;
					}*/
					aiPlayer.setBestPosition(chessBoard);

					if (timer.isTimeOut())
					{
						std::cout << "computer time out, you win " << std::endl;
						//exit(0);
						userScore += 2;
						goto SECOND_GAME;

					}
					std::cout << " computer' position is " << aiPlayer.getBestPosition().c_str() << std::endl;

					chessBoard.changePositionValue(false, position);
					chessPositionNum--;

					if (chessBoard.isWin(position.getX(), position.getY()))
					{
						chessBoard.drawChessBoard();
						std::cout << "computer win " << std::endl;
						//exit(0);
						aiScore += 2;
						goto SECOND_GAME;
					}
					if (!chessBoard.isWin(position.getX(), position.getY()) && chessPositionNum < 1)
					{
						//棋盘占满了还没分出胜负
						chessBoard.drawChessBoard();
						std::cout << "you and computer both win " << std::endl;
						Sleep(1000);
						//exit(0);
						userScore += 1;
						aiScore += 1;
					}
					Sleep(1000);
					m_currentchess = !m_currentchess;
					chessBoard.setCurrentChess(m_currentchess);
				}
				/*****************************************************************/
				if (aiPlayer.getChess() && !m_currentchess)//电脑先下，当前人下
				{
					chessBoard.drawChessBoard();
					std::cout << "now your turn, please input your position: ";
					timer.startTimer();
					while (1)
					{
						if (kbhit())//非阻塞的响应键盘输入事件
						{
							chessPlayer.fallChess();//人下棋
							break;
						}
						if (timer.isTimeOut())
						{
							std::cout << "\n your time out, computer win!!!" << std::endl;
							Sleep(1000);
							//exit(0);
							aiScore += 1;
							goto SECOND_GAME;
						}

					}

					if (!checkIsLegalPosition(chessBoard, chessPlayer.position2point()))
					{
						//越界或者有棋子了
						std::cout << "this postion have chess or out of chessboard!!!" << std::endl;
						Sleep(1000);
						continue;
					}
					/*当前白子 不会禁手
					if (chessBoard.isForbidden(m_currentchess, chessPlayer.position2point()))
					{
						//禁手了
						std::cout << "you are first, this position is forbidened!!! " << std::endl;
						continue;
					}*/

					chessBoard.changePositionValue(false, chessPlayer.position2point());//黑子下的位置
					chessPositionNum--;
					//std::cout << "222222222222222222222" << std::endl;
					if (chessBoard.isWin(chessPlayer.position2point().getX(), chessPlayer.position2point().getY()))
					{
						//检查是否赢了
						chessBoard.drawChessBoard();
						std::cout << "you win " << std::endl;
						Sleep(1000);
						//exit(0);
						userScore += 2;
						goto SECOND_GAME;
					}
					if (!chessBoard.isWin(chessPlayer.position2point().getX(), chessPlayer.position2point().getY()) && chessPositionNum < 1)
					{
						//棋盘占满了还没分出胜负
						chessBoard.drawChessBoard();
						std::cout << "you and computer both win " << std::endl;
						Sleep(1000);
						//exit(0);
						userScore += 1;
						aiScore += 1;
						goto SECOND_GAME;
					}
					m_currentchess = !m_currentchess;
					chessBoard.setCurrentChess(m_currentchess);
				}
			}

		SECOND_GAME:;
			if(gameRound == 0)
			    std::cout << "Now second round, change chess color!!!" << std::endl;
			Sleep(2000);
			chessBoard.initChessBoard();//别忘了第二局清空棋盘
			m_currentchess = true;
		}//end两次for循环
		std::cout << "\n**************** display score **************************" << std::endl;
		std::cout << "your score is " << userScore << ", computer score is " << aiScore << std::endl;

    }//end else人机对战
}

bool CMonitor::getCurrentChess()
{
	return m_currentchess;//当前棋子
}

bool CMonitor::nextChess()
{
	return (!m_currentchess);
}

bool CMonitor::checkIsLegalPosition(CChessBoard & chessboard, CPosition & position)
{
	if (chessboard.isLegalPosition(position))
		return true;
	else
		return false;
}
