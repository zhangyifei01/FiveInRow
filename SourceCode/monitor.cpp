#include "monitor.h"



CMonitor::CMonitor()
{
	m_currentchess = 1;//����������
}


CMonitor::~CMonitor()
{
}

void CMonitor::beginGame()
{
	
	CChessBoard chessBoard;//һ��������
	CChessPlayer chessPlayer;
	CTimer timer;
	CPosition position;

	bool h_vs_h_or_h_vs_ai = 0;//Ĭ���˻���ս,0���˻���1������
	

	int chessPositionNum;//���̵���

	m_currentchess = true;//����������
	chessBoard.setCurrentChess(m_currentchess);

	chessPositionNum = BOARD_DIMENSION * BOARD_DIMENSION;

	std::cout << "welcome to game five-in-row " << std::endl;
	std::cout << "choose 1 (human vs human)  or 0 (human vs computer): ";
	std::cin >> h_vs_h_or_h_vs_ai;
	if (h_vs_h_or_h_vs_ai)//���˶�ս
	{
		CChessPlayer chessPlayer2;
		int user1Score = 0, user2Score = 0;//����
		std::cout << "Player1 is first using black chess in first round " << std::endl;

		chessPlayer.setChess(false);//�����෴�ģ���forѭ���з�����
		chessPlayer2.setChess(true);

		for (int gameRound = 0; gameRound < 2; gameRound++)
		{
			//��������
			chessPlayer.setChess(!chessPlayer.getChess());//��Ϊÿ��Ҫ������
			chessPlayer2.setChess(!chessPlayer2.getChess());

			while (1)
			{
				//*****************************************************************************************
				if (chessPlayer.getChess() && m_currentchess)//user1���£���ǰ�Ǻ���
				{//��һ���ǵ�һ��
					chessBoard.drawChessBoard();
					std::cout << "now user1 turn, please input your position: ";
					timer.startTimer();
					while (1)
					{
						if (kbhit())//����������Ӧ���������¼�
						{
							chessPlayer.fallChess();//������
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
						//Խ�������������
						std::cout << "this postion have chess or out of chessboard!!!" << std::endl;
						Sleep(1000);
						continue;
					}
					if (chessBoard.isForbidden(m_currentchess, chessPlayer.position2point()))
					{
						//������
						std::cout << "you are first, this position is forbidened!!! " << std::endl;
						Sleep(1000);
						continue;
					}

					chessBoard.changePositionValue(true, chessPlayer.position2point());//�����µ�λ��
					chessPositionNum--;

					if (chessBoard.isWin(chessPlayer.position2point().getX(), chessPlayer.position2point().getY()))
					{
						//����Ƿ�Ӯ��
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
						//����ռ���˻�û�ֳ�ʤ��
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
				if (chessPlayer.getChess() && !m_currentchess)//user1���£���ǰ�ǰ���
				{//��һ��
					chessBoard.drawChessBoard();
					//if(gameRound == 0)
					std::cout << "now user2 turn, please input your position: ";
					//else
					//	std::cout << "now user2 turn, please input your position: ";
					timer.startTimer();
					while (1)
					{
						if (kbhit())//����������Ӧ���������¼�
						{
							chessPlayer2.fallChess();//������
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
						//Խ�������������
						std::cout << "this postion have chess or out of chessboard!!!" << std::endl;
						Sleep(1000);
						continue;
					}
					if (chessBoard.isForbidden(m_currentchess, chessPlayer2.position2point()))
					{
						//������
						std::cout << "you are first, this position is forbidened!!! " << std::endl;
						Sleep(1000);
						continue;
					}

					chessBoard.changePositionValue(false, chessPlayer2.position2point());//�����µ�λ��
					chessPositionNum--;

					if (chessBoard.isWin(chessPlayer2.position2point().getX(), chessPlayer2.position2point().getY()))
					{
						//����Ƿ�Ӯ��
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
						//����ռ���˻�û�ֳ�ʤ��
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
				if (chessPlayer2.getChess() && m_currentchess)//user2���£���ǰ�Ǻ���
				{//�ڶ���
					chessBoard.drawChessBoard();
					//if (gameRound == 0)//��һ��user1�Ǻ���
					//	std::cout << "now user1 turn, please input your position: ";
					//else//�ڶ���user2�Ǻ���
					std::cout << "now user2 turn, please input your position: ";
					timer.startTimer();
					while (1)
					{
						if (kbhit())//����������Ӧ���������¼�
						{
							chessPlayer2.fallChess();//������
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
						//Խ�������������
						std::cout << "this postion have chess or out of chessboard!!!" << std::endl;
						Sleep(1000);
						continue;
					}
					if (chessBoard.isForbidden(m_currentchess, chessPlayer2.position2point()))
					{
						//������
						std::cout << "you are first, this position is forbidened!!! " << std::endl;
						Sleep(1000);
						continue;
					}

					chessBoard.changePositionValue(true, chessPlayer2.position2point());//�����µ�λ��
					chessPositionNum--;

					if (chessBoard.isWin(chessPlayer2.position2point().getX(), chessPlayer2.position2point().getY()))
					{
						//����Ƿ�Ӯ��
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
						//����ռ���˻�û�ֳ�ʤ��
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
				if (chessPlayer2.getChess() && !m_currentchess)//user2���£���ǰ�ǰ���
				{//�ڶ���
					chessBoard.drawChessBoard();
					//if (gameRound == 0)
						std::cout << "now user1 turn, please input your position: ";
					//else
					//std::cout << "now user2 turn, please input your position: ";
					timer.startTimer();
					while (1)
					{
						if (kbhit())//����������Ӧ���������¼�
						{
							chessPlayer2.fallChess();//������
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
						//Խ�������������
						std::cout << "this postion have chess or out of chessboard!!!" << std::endl;
						Sleep(1000);
						continue;
					}
					if (chessBoard.isForbidden(m_currentchess, chessPlayer2.position2point()))
					{
						//������
						std::cout << "you are first, this position is forbidened!!! " << std::endl;
						Sleep(1000);
						continue;
					}

					chessBoard.changePositionValue(false, chessPlayer2.position2point());//�����µ�λ��
					chessPositionNum--;

					if (chessBoard.isWin(chessPlayer2.position2point().getX(), chessPlayer2.position2point().getY()))
					{
						//����Ƿ�Ӯ��
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
						//����ռ���˻�û�ֳ�ʤ��
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
	else//�˻���ս
	{
		CAIPlayer aiPlayer;
		int userScore = 0, aiScore = 0;//����
		bool chooseMode = 0;//0�Ǽ�������֣�1��������
		std::cout << "choose you first (input 1) or computer first (input 0) : ";
		std::cin >> chooseMode;

		if (!chooseMode)
		{
			chessPlayer.setChess(true);//������
			aiPlayer.setChess(false);
		}
		else
		{
			chessPlayer.setChess(false);//���������
			aiPlayer.setChess(true);
		}

		for (int gameRound = 0; gameRound < 2; gameRound++)
		{//���������˻���ս
			chessPlayer.setChess(!chessPlayer.getChess());//ִ��˳�򽻻�
			aiPlayer.setChess(!aiPlayer.getChess());

			while (1)
			{
				//chessBoard.drawChessBoard();
				/*****************************************************************/
				if (chessPlayer.getChess() && m_currentchess)//������,��ǰ�Ǻ�����
				{
					chessBoard.drawChessBoard();
					std::cout << "now your turn, please input your position: ";
					timer.startTimer();
					while (1)
					{
						if (kbhit())//����������Ӧ���������¼�
						{
							chessPlayer.fallChess();//������
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
						//Խ�������������
						std::cout << "this postion have chess or out of chessboard!!!" << std::endl;
						Sleep(1000);
						continue;
					}
					if (chessBoard.isForbidden(m_currentchess, chessPlayer.position2point()))
					{
						//������
						std::cout << "you are first, this position is forbidened!!! " << std::endl;
						Sleep(1000);
						continue;
					}

					chessBoard.changePositionValue(true, chessPlayer.position2point());//�����µ�λ��
					chessPositionNum--;

					if (chessBoard.isWin(chessPlayer.position2point().getX(), chessPlayer.position2point().getY()))
					{
						//����Ƿ�Ӯ��
						chessBoard.drawChessBoard();
						std::cout << "you win " << std::endl;
						Sleep(1000);
						//exit(0);
						userScore += 2;
						goto SECOND_GAME;
					}
					if (!chessBoard.isWin(chessPlayer.position2point().getX(), chessPlayer.position2point().getY()) && chessPositionNum < 1)
					{
						//����ռ���˻�û�ֳ�ʤ��
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
				if (aiPlayer.getChess() && m_currentchess)//�������£���ǰ�Ǻ���
				{
					chessBoard.drawChessBoard();
					timer.startTimer();//��ʼ��ʱ
					chessBoard.initPositionScore();//��־�������

					//if (chessBoard.checkVectorIsEmpty())//����true�Ƿǿ�
					//{
					//	chessBoard.moveWindow();//���ƶ����ڲ��������ֵ
					//}
					position = chessBoard.getMaxScorePosition();//����λ��


					if (chessBoard.isForbidden(true, position))
					{
						//�����µ�λ�ý�����
						chessBoard.setArrayPositionScore(position.getX(), position.getY(), 0);//���λ�ô����Ϊ0
						continue;
					}
					//std::cout << "�����ǣ���" << position.getX() << "," << position.getY() << ")" << std::endl;
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
						//����ռ���˻�û�ֳ�ʤ��
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
				if (chessPlayer.getChess() && !m_currentchess)//�����£���ǰ������
				{
					chessBoard.drawChessBoard();
					timer.startTimer();//��ʼ��ʱ
					chessBoard.initPositionScore();//��־�������
					//if (chessBoard.checkVectorIsEmpty())//����true�Ƿǿ�
					//{
					//	chessBoard.moveWindow();//���ƶ����ڲ��������ֵ
					//}
					position = chessBoard.getMaxScorePosition();//����λ��
					/*��ǰ���Ӳ������
					if (chessBoard.isForbidden(true, position))
					{
						//�����µ�λ�ý�����
						chessBoard.setArrayPositionScore(position.getX(), position.getY(), 0);//���λ�ô����Ϊ0
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
						//����ռ���˻�û�ֳ�ʤ��
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
				if (aiPlayer.getChess() && !m_currentchess)//�������£���ǰ����
				{
					chessBoard.drawChessBoard();
					std::cout << "now your turn, please input your position: ";
					timer.startTimer();
					while (1)
					{
						if (kbhit())//����������Ӧ���������¼�
						{
							chessPlayer.fallChess();//������
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
						//Խ�������������
						std::cout << "this postion have chess or out of chessboard!!!" << std::endl;
						Sleep(1000);
						continue;
					}
					/*��ǰ���� �������
					if (chessBoard.isForbidden(m_currentchess, chessPlayer.position2point()))
					{
						//������
						std::cout << "you are first, this position is forbidened!!! " << std::endl;
						continue;
					}*/

					chessBoard.changePositionValue(false, chessPlayer.position2point());//�����µ�λ��
					chessPositionNum--;
					//std::cout << "222222222222222222222" << std::endl;
					if (chessBoard.isWin(chessPlayer.position2point().getX(), chessPlayer.position2point().getY()))
					{
						//����Ƿ�Ӯ��
						chessBoard.drawChessBoard();
						std::cout << "you win " << std::endl;
						Sleep(1000);
						//exit(0);
						userScore += 2;
						goto SECOND_GAME;
					}
					if (!chessBoard.isWin(chessPlayer.position2point().getX(), chessPlayer.position2point().getY()) && chessPositionNum < 1)
					{
						//����ռ���˻�û�ֳ�ʤ��
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
			chessBoard.initChessBoard();//�����˵ڶ����������
			m_currentchess = true;
		}//end����forѭ��
		std::cout << "\n**************** display score **************************" << std::endl;
		std::cout << "your score is " << userScore << ", computer score is " << aiScore << std::endl;

    }//end else�˻���ս
}

bool CMonitor::getCurrentChess()
{
	return m_currentchess;//��ǰ����
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
