#include "chessboard.h"



CChessBoard::CChessBoard()
{
	initChessBoard();
	

}


CChessBoard::~CChessBoard()
{
}

void CChessBoard::initChessBoard()
{
	vec_black_chess.clear();
	vec_white_chess.clear();
	
	//��ʼ��arr_havechess����
	for (int i = 0; i < BOARD_DIMENSION; i++)
		for (int j = 0; j < BOARD_DIMENSION; j++)
			arr_havechess[i][j] = 0;//�տ�ʼ��û������
									
	//���滭���̣���ʼ��arr_position����
	//��һ��
	arr_position[0][0] = 0;
	for (int i = 0; i < BOARD_DIMENSION - 2; i++)
		arr_position[0][i + 1] = 1;
	arr_position[0][BOARD_DIMENSION - 1] = 2;
	//�м���
	for (int j = 0; j < BOARD_DIMENSION - 2; j++)
	{
		arr_position[j + 1][0] = 3;
		for (int i = 0; i < BOARD_DIMENSION; i++)
			arr_position[j + 1][i + 1] = 4;
		arr_position[j + 1][BOARD_DIMENSION - 1] = 5;
	}
	//���һ��
	arr_position[BOARD_DIMENSION - 1][0] = 6;
	for (int i = 0; i < BOARD_DIMENSION - 2; i++)
		arr_position[BOARD_DIMENSION - 1][i + 1] = 7;
	arr_position[BOARD_DIMENSION - 1][BOARD_DIMENSION - 1] = 8;
}

void CChessBoard::drawChessBoard()
{
	char x_label[BOARD_DIMENSION];//������ĸ��ʶA��O
	for (int i = 0; i < BOARD_DIMENSION; i++)
		x_label[i] = 65 + i;

	system("cls");//�����һ���������
	system("color 02");//�ڵ�����
	std::cout << "     --   Game FiveInRow   --" << std::endl;
	for (int i = 0; i < BOARD_DIMENSION; i++)
	{
		std::cout << std::setw(2) << BOARD_DIMENSION - i;//y_label
		for (int j = 0; j < BOARD_DIMENSION; j++)
			std::cout << m_symbol[arr_position[i][j]];//������λ�÷���
		std::cout << std::endl;
	}
	std::cout << " ";
	for (int i = 0; i < BOARD_DIMENSION; i++)
		std::cout << std::setw(2) << x_label[i];
	std::cout << std::endl;
}

int CChessBoard::getPositionValue(int xx, int yy)
{//���ط���λ��
	if (xx >= 0 && xx < BOARD_DIMENSION && yy >= 0 && yy < BOARD_DIMENSION)
		return arr_position[xx][yy];
	else
	{
		std::cout << "input position out of bound!!!" << std::endl;
		return 13;//�Ǹ����������12
	}
}

void CChessBoard::changePositionValue(bool chesstype, CPosition & position)
{
	if (chesstype)//�Ǻ���
	{
		arr_position[position.getX()][position.getY()] = 11;//��������
		arr_havechess[position.getX()][position.getY()] = 1;

		if (vec_black_chess.size() > 0)
		{
			//����һ������Բ��
			arr_position[vec_black_chess[vec_black_chess.size() - 1].getX()][vec_black_chess[vec_black_chess.size() - 1].getY()] = 9;
		}

		//�洢��ǰλ��
		vec_black_chess.push_back(position);
	}
	else
	{//�ǰ���
		arr_position[position.getX()][position.getY()] = 12;//��������
		arr_havechess[position.getX()][position.getY()] = 1;

		if (vec_white_chess.size() > 0)
		{
			//����һ������Բ��
			arr_position[vec_white_chess[vec_white_chess.size() - 1].getX()][vec_white_chess[vec_white_chess.size() - 1].getY()] = 10;
		}

		//�洢��ǰλ��
		vec_white_chess.push_back(position);
	}
}

bool CChessBoard::isLegalPosition(CPosition & position)
{
	if (position.getX() >= 0 && position.getX() < BOARD_DIMENSION && position.getY() >= 0 && position.getY() < BOARD_DIMENSION && arr_havechess[position.getX()][position.getY()] == 0)
	{
		//û��Խ�磬��λ��Ҳû������
		return true;
	}
	else
		return false;
}

void CChessBoard::setCurrentChess(bool currentchess)
{
	m_currentchess = currentchess;
}

bool CChessBoard::getCurrentChess()
{
	return m_currentchess;
}

bool CChessBoard::isWin(int xx,int yy)
{
	int chessvalue = 0;
	//�ж����λ�õ�������������ɫ
	if (arr_position[xx][yy] == 11)//����
	{
		chessvalue = 9;//��ɫԲ��
	}
	if (arr_position[xx][yy] == 12)//����
	{
		chessvalue = 10;//��ɫԲ��
	}

	int chessNum = 0;//������
	int x, y;
	
	//�ж�������
	
		//1����
		//1.1��������
		x = xx + 1;
		y = yy;
		for (int i = 0; i < 5; i++)
		{
			if (x < BOARD_DIMENSION && arr_havechess[x][y] == 1 && arr_position[x][y] == chessvalue)
			{
				chessNum++;
				x++;
			}
			else
				break;
		}
		if (chessNum >= 4)
			return true;//���ϵ�ǰ�����ܹ������
		//1.2�������� 
		x = xx - 1;
		for (int i = 0; i < 5; i++)
		{
			if (x >= 0 && arr_havechess[x][y] == 1 && arr_position[x][y] == chessvalue)
			{
				chessNum++;
				x--;
			}
			else
				break;
		}
		if (chessNum >= 4)
			return true;//���ϵ�ǰ�����ܹ������
		chessNum = 0;

		//2����
		//2.1��������
		x = xx ;
		y = yy + 1;
		for (int i = 0; i < 5; i++)
		{
			if (y < BOARD_DIMENSION && arr_havechess[x][y] == 1 && arr_position[x][y] == chessvalue)
			{
				chessNum++;
				y++;
			}
			else
				break;
		}
		if (chessNum >= 4)
			return true;//���ϵ�ǰ�����ܹ������
		//2.2��������
		y = yy - 1;
		for (int i = 0; i < 5; i++)
		{
			if (y >= 0 && arr_havechess[x][y] == 1 && arr_position[x][y] == chessvalue)
			{
				chessNum++;
				y--;
			}
			else
				break;
		}
		if (chessNum >= 4)
			return true;//���ϵ�ǰ�����ܹ������
		chessNum = 0;
	


	
		//3����45��
		//3.1����45�� ������
		x = xx - 1;
		y = yy + 1;
		for (int i = 0; i < 5; i++)
		{
			if (x >= 0 && y < BOARD_DIMENSION && arr_havechess[x][y] == 1 && arr_position[x][y] == chessvalue)
			{
				chessNum++;
				x--;
				y++;
			}
			else
				break;
		}
		if (chessNum >= 4)
			return true;//���ϵ�ǰ�����ܹ������
		//3.2 ����45�� ������
		x = xx + 1;
		y = yy - 1;
		for (int i = 0; i < 5; i++)
		{
			if (x < BOARD_DIMENSION && y >= 0 && arr_havechess[x][y] == 1 && arr_position[x][y] == chessvalue)
			{
				chessNum++;
				x++;
				y--;
			}
			else
				break;
		}
		if (chessNum >= 4)
			return true;//���ϵ�ǰ�����ܹ������
		chessNum = 0;
	


	
		//4����135��
		//4.1����135�� ������
		x = xx + 1;
		y = yy + 1;
		for (int i = 0; i < 5; i++)
		{
			if (y < BOARD_DIMENSION && x < BOARD_DIMENSION && arr_havechess[x][y] == 1 && arr_position[x][y] == chessvalue)
			{
				chessNum++;
				y++;
				x++;
			}
			else
				break;
		}
		if (chessNum >= 4)
			return true;//���ϵ�ǰ�����ܹ������
		//4.2����135�� ������
		x = xx - 1;
		y = yy - 1;
		for (int i = 0; i < 5; i++)
		{
			if (x >= 0 && y >= 0 && arr_havechess[x][y] == 1 && arr_position[x][y] == chessvalue)
			{
				chessNum++;
				x--;
				y--;
			}
			else
				break;
		}
		if (chessNum >= 4)
			return true;//���ϵ�ǰ�����ܹ������
		chessNum = 0;
	
	return false;
}

void CChessBoard::initPositionScore()
{
	for (int i = 0; i < BOARD_DIMENSION; i++)
		for (int j = 0; j < BOARD_DIMENSION; j++)
			arr_positionscore[i][j] = 0;//����λ�ó�ʼ����0��
}

void CChessBoard::setArrayPositionScore(int xx, int yy, int scoreValue)
{
	arr_positionscore[xx][yy] = scoreValue;
}

int CChessBoard::slideWindowScore(int xx, int yy, bool ismychess, int windowtype)
{
	//windowtype 1�����£�2�����ң�3���������ϣ�4����������
	bool haveblack, havewhite;//�ж������������û�к��ӣ�����
	int blacknum, whitenum;//���Ӱ�����
	haveblack = false;
	havewhite = false;
	blacknum = 0;
	whitenum = 0;
	if (windowtype == 1)
	{//���������µ�
		for (int i = 1; i < 5; i++)
		{
			
		    if (arr_position[xx - i][yy] == 9 || arr_position[xx - i][yy] == 11)//����
			{
				haveblack = true;
				blacknum++;
			}
			if (arr_position[xx - i][yy] == 10 || arr_position[xx - i][yy] == 12)//����
			{
				havewhite = true;
				whitenum++;
			}
		}
		if (haveblack && havewhite)
			return 0;//�ڰ׶��л�ϵĴ��0
		else if(haveblack && !havewhite)
		{//�к�û�а�
			if (m_currentchess)//���Ǻ���
			{
				if (blacknum == 1)
					return 50;//�ҷ���һ���� 50��
				if (blacknum == 2)
					return 1000;//�ҷ��������� 1000��
				if (blacknum == 3)
					return 150000;
				if (blacknum == 4)
					return 8000000;
			}
			else
			{
				if (blacknum == 1)
					return 25;//�Է���һ���� 50��
				if (blacknum == 2)
					return 500;//�Է��������� 1000��
				if (blacknum == 3)
					return 100000;
				if (blacknum == 4)
					return 1000000;
			}
		}
		else if (!haveblack && havewhite)
		{//�а�û�к�
			if (m_currentchess)//���Ǻ���
			{
				if (blacknum == 1)
					return 25;//�Է���һ���� 50��
				if (blacknum == 2)
					return 500;//�Է��������� 1000��
				if (blacknum == 3)
					return 100000;
				if (blacknum == 4)
					return 1000000;
				
			}
			else
			{
				if (blacknum == 1)
					return 50;//�ҷ���һ���� 50��
				if (blacknum == 2)
					return 1000;//�ҷ��������� 1000��
				if (blacknum == 3)
					return 150000;
				if (blacknum == 4)
					return 8000000;
			}
		}
		else//��û��
			return 5;//��λ�ô�5��
	}

	if (windowtype == 2)
	{//���������ҵ�
		for (int i = 1; i < 5; i++)
		{

			if (arr_position[xx][yy + i] == 9 || arr_position[xx][yy + i] == 11)//����
			{
				haveblack = true;
				blacknum++;
			}
			if (arr_position[xx][yy + i] == 10 || arr_position[xx][yy + i] == 12)//����
			{
				havewhite = true;
				whitenum++;
			}
		}
		if (haveblack && havewhite)
			return 0;//�ڰ׶��л�ϵĴ��0
		else if (haveblack && !havewhite)
		{//�к�û�а�
			if (m_currentchess)//���Ǻ���
			{
				if (blacknum == 1)
					return 50;//�ҷ���һ���� 50��
				if (blacknum == 2)
					return 1000;//�ҷ��������� 1000��
				if (blacknum == 3)
					return 150000;
				if (blacknum == 4)
					return 8000000;
			}
			else
			{
				if (blacknum == 1)
					return 25;//�Է���һ���� 50��
				if (blacknum == 2)
					return 500;//�Է��������� 1000��
				if (blacknum == 3)
					return 100000;
				if (blacknum == 4)
					return 1000000;
			}
		}
		else if (!haveblack && havewhite)
		{//�а�û�к�
			if (m_currentchess)//���Ǻ���
			{
				if (blacknum == 1)
					return 25;//�Է���һ���� 50��
				if (blacknum == 2)
					return 500;//�Է��������� 1000��
				if (blacknum == 3)
					return 100000;
				if (blacknum == 4)
					return 1000000;

			}
			else
			{
				if (blacknum == 1)
					return 50;//�ҷ���һ���� 50��
				if (blacknum == 2)
					return 1000;//�ҷ��������� 1000��
				if (blacknum == 3)
					return 150000;
				if (blacknum == 4)
					return 8000000;
			}
		}
		else//��û��
			return 5;//��λ�ô�5��
	}

	if (windowtype == 3)
	{//�������������ϵ�
		for (int i = 1; i < 5; i++)
		{

			if (arr_position[xx - i][yy + i] == 9 || arr_position[xx - i][yy + i] == 11)//����
			{
				haveblack = true;
				blacknum++;
			}
			if (arr_position[xx - i][yy + i] == 10 || arr_position[xx - i][yy + i] == 12)//����
			{
				havewhite = true;
				whitenum++;
			}
		}
		if (haveblack && havewhite)
			return 0;//�ڰ׶��л�ϵĴ��0
		else if (haveblack && !havewhite)
		{//�к�û�а�
			if (m_currentchess)//���Ǻ���
			{
				if (blacknum == 1)
					return 50;//�ҷ���һ���� 50��
				if (blacknum == 2)
					return 1000;//�ҷ��������� 1000��
				if (blacknum == 3)
					return 150000;
				if (blacknum == 4)
					return 8000000;
			}
			else
			{
				if (blacknum == 1)
					return 25;//�Է���һ���� 50��
				if (blacknum == 2)
					return 500;//�Է��������� 1000��
				if (blacknum == 3)
					return 100000;
				if (blacknum == 4)
					return 1000000;
			}
		}
		else if (!haveblack && havewhite)
		{//�а�û�к�
			if (m_currentchess)//���Ǻ���
			{
				if (blacknum == 1)
					return 25;//�Է���һ���� 50��
				if (blacknum == 2)
					return 500;//�Է��������� 1000��
				if (blacknum == 3)
					return 100000;
				if (blacknum == 4)
					return 1000000;

			}
			else
			{
				if (blacknum == 1)
					return 50;//�ҷ���һ���� 50��
				if (blacknum == 2)
					return 1000;//�ҷ��������� 1000��
				if (blacknum == 3)
					return 150000;
				if (blacknum == 4)
					return 8000000;
			}
		}
		else//��û��
			return 5;//��λ�ô�5��
	}
	if (windowtype == 4)
	{//�������������µ�
		for (int i = 1; i < 5; i++)
		{

			if (arr_position[xx - i][yy - i] == 9 || arr_position[xx - i][yy - i] == 11)//����
			{
				haveblack = true;
				blacknum++;
			}
			if (arr_position[xx - i][yy - i] == 10 || arr_position[xx - i][yy - i] == 12)//����
			{
				havewhite = true;
				whitenum++;
			}
		}
		if (haveblack && havewhite)
			return 0;//�ڰ׶��л�ϵĴ��0
		else if (haveblack && !havewhite)
		{//�к�û�а�
			if (m_currentchess)//���Ǻ���
			{
				if (blacknum == 1)
					return 50;//�ҷ���һ���� 50��
				if (blacknum == 2)
					return 1000;//�ҷ��������� 1000��
				if (blacknum == 3)
					return 150000;
				if (blacknum == 4)
					return 8000000;
			}
			else
			{
				if (blacknum == 1)
					return 25;//�Է���һ���� 50��
				if (blacknum == 2)
					return 500;//�Է��������� 1000��
				if (blacknum == 3)
					return 100000;
				if (blacknum == 4)
					return 2000000;
			}
		}
		else if (!haveblack && havewhite)
		{//�а�û�к�
			if (m_currentchess)//���Ǻ���
			{
				if (blacknum == 1)
					return 25;//�Է���һ���� 50��
				if (blacknum == 2)
					return 500;//�Է��������� 1000��
				if (blacknum == 3)
					return 100000;
				if (blacknum == 4)
					return 1000000;

			}
			else
			{
				if (blacknum == 1)
					return 50;//�ҷ���һ���� 50��
				if (blacknum == 2)
					return 1000;//�ҷ��������� 1000��
				if (blacknum == 3)
					return 150000;
				if (blacknum == 4)
					return 8000000;
			}
		}
		else//��û��
			return 5;//��λ�ô�5��
	}
	return 0;
}

int CChessBoard::blankPositionScore(int xx, int yy, bool ishavechess, bool ismychess)
{
	
	int x, y;//���ڵײ�����
	int sumScore = 0;
	if (ishavechess)
		return 0;
	else
	{
		

		//**********************************************
		//���»�������
		if (xx - 4 >= 0 && xx + 4 < BOARD_DIMENSION)
		{
			//���м�λ�ã�������㻬������Խ��
			x = xx;//����xx, yyΪ��
			y = yy;
			for (int i = 0; i < 5; i++)
			{
				x = x + i;//�ײ��ǵڼ���
				sumScore += slideWindowScore(x, y, ismychess, 1);
			}
		}
		else
		{
			//������㻬����
			if (xx - 4 < 0)
			{
				//��xx+1������
				x = 4;//����xx, yyΪ��
				y = yy;
				for (int i = 0; i < xx + 1; i++)
				{
					x = x + i;
					sumScore += slideWindowScore(x, y, ismychess, 1);
				}
			}
			if (xx + 4 >= BOARD_DIMENSION)
			{
				//��BOARD_DIMENSION - xx������
				x = xx;
				y = yy;
				for (int i = 0; i < BOARD_DIMENSION - xx; i++)
				{
					x = x + i;
					sumScore += slideWindowScore(x, y, ismychess, 1);
				}
			}
		}

		//**********************************************
		//���һ�������
		if (yy - 4 >= 0 && yy + 4 < BOARD_DIMENSION)
		{
			//���м�λ�ã�������㻬������Խ��
			x = xx;//����xx, yyΪ��
			y = yy;
			for (int i = 0; i < 5; i++)
			{
				y = y + i;//�ײ��ǵڼ���
				sumScore += slideWindowScore(x, y, ismychess, 2);
			}
		}
		else
		{
			//������㻬����
			if (yy - 4 < 0)
			{
				//��yy+1������
				y = 4;//����xx, yyΪ��
				x = xx;
				for (int i = 0; i < yy + 1; i++)
				{
					y = y + i;
					sumScore += slideWindowScore(x, y, ismychess, 2);
				}
			}
			if (yy + 4 >= BOARD_DIMENSION)
			{
				//��BOARD_DIMENSION - yy������
				x = xx;
				y = yy;
				for (int i = 0; i < BOARD_DIMENSION - yy; i++)
				{
					y = y + i;
					sumScore += slideWindowScore(x, y, ismychess, 2);
				}
			}
		}
		//**********************************************
		//�������ϻ�������
		x = xx;
		y = yy;
		for (int i = 0; i < 5; i++)//�Ըÿ�λ��Ϊ�׻���������û��Խ��Ŀ�
		{
			if (x + i < BOARD_DIMENSION && y - i >= 0 && x - 4 >= 0 && y + 4 < BOARD_DIMENSION)//�������º����϶�û��Խ��
			{
				sumScore += slideWindowScore(x+i, y-i, ismychess, 3);
			}
		}
		//**********************************************
		//�������»�������
		x = xx;
		y = yy;
		for (int i = 0; i < 5; i++)//�Ըÿ�λ��Ϊ�׻���������û��Խ��Ŀ�
		{
			if (x + i < BOARD_DIMENSION && y + i < BOARD_DIMENSION && x - 4 >= 0 && y - 4 >= 0)//�������º����϶�û��Խ��
			{
				sumScore += slideWindowScore(x+i, y+i, ismychess, 4);
			}
		}
		
		return sumScore;
	}
}

void CChessBoard::moveWindow()
{
	CPosition myposition, position1;//���ϴ�����λ�ã��Է���һ������λ��
	int x, y;//��ʱ����ֵ
	int tmp_doublescore = 0;//�ҷ��ͶԷ��������λ�ô��
	if (m_currentchess )
	{
		//���Ǻ���
		myposition = vec_black_chess[vec_black_chess.size() - 1];
		position1 = vec_white_chess[vec_white_chess.size() - 1];
	}
	else
	{//�ҵİ���
		position1 = vec_black_chess[vec_black_chess.size() - 1];
		myposition = vec_white_chess[vec_white_chess.size() - 1];
	}

	
	
	//*********************************************************************************
	//��������һ��������Χλ�ý��д��
	x = myposition.getX();
	y = myposition.getY();
	for (int i = 0; i < 5; i++)
	{
		//������
		x--;
		if (x < 0)
			break;//Խ��
		if (arr_havechess[x][y] == 1)
			//�Ѿ��������ˣ��Ͳ��ô���ˣ�0��
			arr_positionscore[x][y] = blankPositionScore(x, y, true, true);
		else
		{
			tmp_doublescore = 0;
			if (arr_positionscore[x][y] > 0)
			{//˵��������ֹ���ȡ���δ�����ֵ
				tmp_doublescore = arr_positionscore[x][y];
				arr_positionscore[x][y] = 0;
			}

			arr_positionscore[x][y] = blankPositionScore(x, y, false, true);

			if (arr_positionscore[x][y] < tmp_doublescore)//���������λ�ô�ֱ�ǰһ�δ�ֻ��ͣ�������ߵĴ��ֵ
				arr_positionscore[x][y] = tmp_doublescore;
		}
	}
	x = myposition.getX();
	for (int i = 0; i < 5; i++)
	{
		//������
		x++;
		if (x >= BOARD_DIMENSION)
			break;//Խ��
		if (arr_havechess[x][y] == 1)
			//�Ѿ��������ˣ��Ͳ��ô���ˣ�0��
			arr_positionscore[x][y] = blankPositionScore(x, y, true, true);
		else
		{
			tmp_doublescore = 0;
			if (arr_positionscore[x][y] > 0)
			{//˵��������ֹ���ȡ���δ�����ֵ
				tmp_doublescore = arr_positionscore[x][y];
				arr_positionscore[x][y] = 0;
			}

			arr_positionscore[x][y] = blankPositionScore(x, y, false, true);

			if (arr_positionscore[x][y] < tmp_doublescore)//���������λ�ô�ֱ�ǰһ�δ�ֻ��ͣ�������ߵĴ��ֵ
				arr_positionscore[x][y] = tmp_doublescore;
		}
			
	}
	x = myposition.getX();
	for (int i = 0; i < 5; i++)
	{
		//������
		y--;
		if (y < 0)
			break;//Խ��
		if (arr_havechess[x][y] == 1)
			//�Ѿ��������ˣ��Ͳ��ô���ˣ�0��
			arr_positionscore[x][y] = blankPositionScore(x, y, true, true);
		else
		{
			tmp_doublescore = 0;
			if (arr_positionscore[x][y] > 0)
			{//˵��������ֹ���ȡ���δ�����ֵ
				tmp_doublescore = arr_positionscore[x][y];
				arr_positionscore[x][y] = 0;
			}

			arr_positionscore[x][y] = blankPositionScore(x, y, false, true);

			if (arr_positionscore[x][y] < tmp_doublescore)//���������λ�ô�ֱ�ǰһ�δ�ֻ��ͣ�������ߵĴ��ֵ
				arr_positionscore[x][y] = tmp_doublescore;
		}
			
	}
	y = myposition.getY();
	for (int i = 0; i < 5; i++)
	{
		//������
		y++;
		if (y >= BOARD_DIMENSION)
			break;//Խ��
		if (arr_havechess[x][y] == 1)
			//�Ѿ��������ˣ��Ͳ��ô���ˣ�0��
			arr_positionscore[x][y] = blankPositionScore(x, y, true, true);
		else
		{
			tmp_doublescore = 0;
			if (arr_positionscore[x][y] > 0)
			{//˵��������ֹ���ȡ���δ�����ֵ
				tmp_doublescore = arr_positionscore[x][y];
				arr_positionscore[x][y] = 0;
			}

			arr_positionscore[x][y] = blankPositionScore(x, y, false, true);

			if (arr_positionscore[x][y] < tmp_doublescore)//���������λ�ô�ֱ�ǰһ�δ�ֻ��ͣ�������ߵĴ��ֵ
				arr_positionscore[x][y] = tmp_doublescore;
		}
			
	}
	y = myposition.getY();
	for (int i = 0; i < 5; i++)
	{
		//��������
		x--;
		y++;
		if (y >= BOARD_DIMENSION || x < 0)
			break;//Խ��
		if (arr_havechess[x][y] == 1)
			//�Ѿ��������ˣ��Ͳ��ô���ˣ�0��
			arr_positionscore[x][y] = blankPositionScore(x, y, true, true);
		else
		{
			tmp_doublescore = 0;
			if (arr_positionscore[x][y] > 0)
			{//˵��������ֹ���ȡ���δ�����ֵ
				tmp_doublescore = arr_positionscore[x][y];
				arr_positionscore[x][y] = 0;
			}

			arr_positionscore[x][y] = blankPositionScore(x, y, false, true);

			if (arr_positionscore[x][y] < tmp_doublescore)//���������λ�ô�ֱ�ǰһ�δ�ֻ��ͣ�������ߵĴ��ֵ
				arr_positionscore[x][y] = tmp_doublescore;
		}
	}
	x = myposition.getX();
	y = myposition.getY();
	for (int i = 0; i < 5; i++)
	{
		//��������
		y--;
		x++;
		if (x >= BOARD_DIMENSION || y < 0)
			break;//Խ��
		if (arr_havechess[x][y] == 1)
			//�Ѿ��������ˣ��Ͳ��ô���ˣ�0��
			arr_positionscore[x][y] = blankPositionScore(x, y, true, true);
		else
		{
			tmp_doublescore = 0;
			if (arr_positionscore[x][y] > 0)
			{//˵��������ֹ���ȡ���δ�����ֵ
				tmp_doublescore = arr_positionscore[x][y];
				arr_positionscore[x][y] = 0;
			}

			arr_positionscore[x][y] = blankPositionScore(x, y, false, true);

			if (arr_positionscore[x][y] < tmp_doublescore)//���������λ�ô�ֱ�ǰһ�δ�ֻ��ͣ�������ߵĴ��ֵ
				arr_positionscore[x][y] = tmp_doublescore;
		}
	}
	x = myposition.getX();
	y = myposition.getY();
	for (int i = 0; i < 5; i++)
	{
		//��������
		y--;
		x--;
		if (x < 0 || y < 0)
			break;//Խ��
		if (arr_havechess[x][y] == 1)
			//�Ѿ��������ˣ��Ͳ��ô���ˣ�0��
			arr_positionscore[x][y] = blankPositionScore(x, y, true, true);
		else
		{
			tmp_doublescore = 0;
			if (arr_positionscore[x][y] > 0)
			{//˵��������ֹ���ȡ���δ�����ֵ
				tmp_doublescore = arr_positionscore[x][y];
				arr_positionscore[x][y] = 0;
			}

			arr_positionscore[x][y] = blankPositionScore(x, y, false, true);

			if (arr_positionscore[x][y] < tmp_doublescore)//���������λ�ô�ֱ�ǰһ�δ�ֻ��ͣ�������ߵĴ��ֵ
				arr_positionscore[x][y] = tmp_doublescore;
		}
			
	}
	x = myposition.getX();
	y = myposition.getY();
	for (int i = 0; i < 5; i++)
	{
		//��������
		y++;
		x++;
		if (x >= BOARD_DIMENSION || y >= BOARD_DIMENSION)
			break;//Խ��
		if (arr_havechess[x][y] == 1)
			//�Ѿ��������ˣ��Ͳ��ô���ˣ�0��
			arr_positionscore[x][y] = blankPositionScore(x, y, true, true);
		else
		{
			tmp_doublescore = 0;
			if (arr_positionscore[x][y] > 0)
			{//˵��������ֹ���ȡ���δ�����ֵ
				tmp_doublescore = arr_positionscore[x][y];
				arr_positionscore[x][y] = 0;
			}

			arr_positionscore[x][y] = blankPositionScore(x, y, false, true);

			if (arr_positionscore[x][y] < tmp_doublescore)//���������λ�ô�ֱ�ǰһ�δ�ֻ��ͣ�������ߵĴ��ֵ
				arr_positionscore[x][y] = tmp_doublescore;
		}
	}
	

	//*********************************************************************************
	//���ҶԷ�������Χ��λ��
	x = position1.getX();
	y = position1.getY();
	for (int i = 0; i < 5; i++)
	{
		//������
		x--;
		if (x < 0)
			break;//Խ��
		if (arr_havechess[x][y] == 1)
			//�Ѿ��������ˣ��Ͳ��ô���ˣ�0��
			arr_positionscore[x][y] = blankPositionScore(x, y, true, false);
		else
		{
			tmp_doublescore = 0;
			if (arr_positionscore[x][y] > 0)
			{//˵��������ֹ���ȡ���δ�����ֵ
				tmp_doublescore = arr_positionscore[x][y];
				arr_positionscore[x][y] = 0;
			}

			arr_positionscore[x][y] = blankPositionScore(x, y, false, false);

			if (arr_positionscore[x][y] < tmp_doublescore)//���������λ�ô�ֱ�ǰһ�δ�ֻ��ͣ�������ߵĴ��ֵ
				arr_positionscore[x][y] = tmp_doublescore;
		}
			
	}
	x = position1.getX();
	for (int i = 0; i < 5; i++)
	{
		//������
		x++;
		if (x >= BOARD_DIMENSION)
			break;//Խ��
		if (arr_havechess[x][y] == 1)
			//�Ѿ��������ˣ��Ͳ��ô���ˣ�0��
			arr_positionscore[x][y] = blankPositionScore(x, y, true, false);
		else
		{
			tmp_doublescore = 0;
			if (arr_positionscore[x][y] > 0)
			{//˵��������ֹ���ȡ���δ�����ֵ
				tmp_doublescore = arr_positionscore[x][y];
				arr_positionscore[x][y] = 0;
			}

			arr_positionscore[x][y] = blankPositionScore(x, y, false, false);

			if (arr_positionscore[x][y] < tmp_doublescore)//���������λ�ô�ֱ�ǰһ�δ�ֻ��ͣ�������ߵĴ��ֵ
				arr_positionscore[x][y] = tmp_doublescore;
		}
			
	}
	x = position1.getX();
	for (int i = 0; i < 5; i++)
	{
		//������
		y--;
		if (y < 0)
			break;//Խ��
		if (arr_havechess[x][y] == 1)
			//�Ѿ��������ˣ��Ͳ��ô���ˣ�0��
			arr_positionscore[x][y] = blankPositionScore(x, y, true, false);
		else
		{
			tmp_doublescore = 0;
			if (arr_positionscore[x][y] > 0)
			{//˵��������ֹ���ȡ���δ�����ֵ
				tmp_doublescore = arr_positionscore[x][y];
				arr_positionscore[x][y] = 0;
			}

			arr_positionscore[x][y] = blankPositionScore(x, y, false, false);

			if (arr_positionscore[x][y] < tmp_doublescore)//���������λ�ô�ֱ�ǰһ�δ�ֻ��ͣ�������ߵĴ��ֵ
				arr_positionscore[x][y] = tmp_doublescore;
		}
			
	}
	y = position1.getY();
	for (int i = 0; i < 5; i++)
	{
		//������
		y++;
		if (y >= BOARD_DIMENSION)
			break;//Խ��
		if (arr_havechess[x][y] == 1)
			//�Ѿ��������ˣ��Ͳ��ô���ˣ�0��
			arr_positionscore[x][y] = blankPositionScore(x, y, true, false);
		else
		{
			tmp_doublescore = 0;
			if (arr_positionscore[x][y] > 0)
			{//˵��������ֹ���ȡ���δ�����ֵ
				tmp_doublescore = arr_positionscore[x][y];
				arr_positionscore[x][y] = 0;
			}

			arr_positionscore[x][y] = blankPositionScore(x, y, false, false);

			if (arr_positionscore[x][y] < tmp_doublescore)//���������λ�ô�ֱ�ǰһ�δ�ֻ��ͣ�������ߵĴ��ֵ
				arr_positionscore[x][y] = tmp_doublescore;
		}
			
	}
	y = position1.getY();
	for (int i = 0; i < 5; i++)
	{
		//��������
		x--;
		y++;
		if (y >= BOARD_DIMENSION || x < 0)
			break;//Խ��
		if (arr_havechess[x][y] == 1)
			//�Ѿ��������ˣ��Ͳ��ô���ˣ�0��
			arr_positionscore[x][y] = blankPositionScore(x, y, true, false);
		else
		{
			tmp_doublescore = 0;
			if (arr_positionscore[x][y] > 0)
			{//˵��������ֹ���ȡ���δ�����ֵ
				tmp_doublescore = arr_positionscore[x][y];
				arr_positionscore[x][y] = 0;
			}

			arr_positionscore[x][y] = blankPositionScore(x, y, false, false);

			if (arr_positionscore[x][y] < tmp_doublescore)//���������λ�ô�ֱ�ǰһ�δ�ֻ��ͣ�������ߵĴ��ֵ
				arr_positionscore[x][y] = tmp_doublescore;
		}
			
	}
	x = position1.getX();
	y = position1.getY();
	for (int i = 0; i < 5; i++)
	{
		//��������
		y--;
		x++;
		if (x >= BOARD_DIMENSION || y < 0)
			break;//Խ��
		if (arr_havechess[x][y] == 1)
			//�Ѿ��������ˣ��Ͳ��ô���ˣ�0��
			arr_positionscore[x][y] = blankPositionScore(x, y, true, false);
		else
		{
			tmp_doublescore = 0;
			if (arr_positionscore[x][y] > 0)
			{//˵��������ֹ���ȡ���δ�����ֵ
				tmp_doublescore = arr_positionscore[x][y];
				arr_positionscore[x][y] = 0;
			}

			arr_positionscore[x][y] = blankPositionScore(x, y, false, false);

			if (arr_positionscore[x][y] < tmp_doublescore)//���������λ�ô�ֱ�ǰһ�δ�ֻ��ͣ�������ߵĴ��ֵ
				arr_positionscore[x][y] = tmp_doublescore;
		}
			
	}
	x = position1.getX();
	y = position1.getY();
	for (int i = 0; i < 5; i++)
	{
		//��������
		y--;
		x--;
		if (x < 0 || y < 0)
			break;//Խ��
		if (arr_havechess[x][y] == 1)
			//�Ѿ��������ˣ��Ͳ��ô���ˣ�0��
			arr_positionscore[x][y] = blankPositionScore(x, y, true, false);
		else
		{
			tmp_doublescore = 0;
			if (arr_positionscore[x][y] > 0)
			{//˵��������ֹ���ȡ���δ�����ֵ
				tmp_doublescore = arr_positionscore[x][y];
				arr_positionscore[x][y] = 0;
			}

			arr_positionscore[x][y] = blankPositionScore(x, y, false, false);

			if (arr_positionscore[x][y] < tmp_doublescore)//���������λ�ô�ֱ�ǰһ�δ�ֻ��ͣ�������ߵĴ��ֵ
				arr_positionscore[x][y] = tmp_doublescore;
		}
			
	}
	x = position1.getX();
	y = position1.getY();
	for (int i = 0; i < 5; i++)
	{
		//��������
		y++;
		x++;
		if (x >= BOARD_DIMENSION || y >= BOARD_DIMENSION)
			break;//Խ��
		if (arr_havechess[x][y] == 1)
			//�Ѿ��������ˣ��Ͳ��ô���ˣ�0��
			arr_positionscore[x][y] = blankPositionScore(x, y, true, false);
		else
		{
			tmp_doublescore = 0;
			if (arr_positionscore[x][y] > 0)
			{//˵��������ֹ���ȡ���δ�����ֵ
				tmp_doublescore = arr_positionscore[x][y];
				arr_positionscore[x][y] = 0;
			}

			arr_positionscore[x][y] = blankPositionScore(x, y, false, false);

			if (arr_positionscore[x][y] < tmp_doublescore)//���������λ�ô�ֱ�ǰһ�δ�ֻ��ͣ�������ߵĴ��ֵ
				arr_positionscore[x][y] = tmp_doublescore;
		}
			
	}
	//�������ˣ�������
}

CPosition CChessBoard::getMaxScorePosition()
{
	CPosition bestPosition;//���λ��
	CPosition position;
	int maxScore = -1;
	if (m_currentchess)
	{//���Ǻ���
		if (vec_black_chess.size() == 0)
		{
			//���ǵ�һ���µ�
			bestPosition.setX(7);//ѡ�����м��λ��
			bestPosition.setY(7);
			return bestPosition;//�տ�ʼ���壬λ�ÿ��������
		}
		else
		{//���ǵ�һ��������Ҫ����λ�ô����
			moveWindow();
			for (int i = 0; i < BOARD_DIMENSION; i++)
				for (int j = 0; j < BOARD_DIMENSION;j++)
					if (arr_positionscore[i][j] >= maxScore)
					{
						maxScore = arr_positionscore[i][j];
						bestPosition.setX(i);
						bestPosition.setY(j);
					}
			return bestPosition;
		}
	}
	else
	{//���ǰ���
		if (vec_white_chess.size() == 0)
		{
			//���������ˣ����ǵ�һ����
			position = vec_black_chess[0];
			if (position.getX() + 1 >= BOARD_DIMENSION)//���Խ���˻�����λ��
			{
				bestPosition.setX(position.getX() - 1);
				bestPosition.setY(position.getY());
				return bestPosition;//�տ�ʼ���壬λ�ÿ��������
			}
			else
			{
				bestPosition.setX(position.getX() + 1);
				bestPosition.setY(position.getY());
				return bestPosition;//�տ�ʼ���壬λ�ÿ��������
			}

		}
		else
		{//���ǵ�һ��������Ҫ����λ�ô����
			moveWindow();
			for (int i = 0; i < BOARD_DIMENSION; i++)
				for (int j = 0; j < BOARD_DIMENSION; j++)
					if (arr_positionscore[i][j] >= maxScore)
					{
						maxScore = arr_positionscore[i][j];
						bestPosition.setX(i);
						bestPosition.setY(j);
					}
			return bestPosition;
		}
	}

	return bestPosition;
}

bool CChessBoard::isLiveThree(int xx, int yy, bool currentChess, int windowType)
{//�ǲ��ǻ���
	/**
	�Ȱ�����ӷ��ϣ��ж��ټ�һ���ǲ��ǻ���
	*/
	int havechess, chessposition;//�ȱ��������Ϣ���������ڻ�ԭ
	if (currentChess)
	{
		havechess = arr_havechess[xx][yy];
		chessposition = arr_position[xx][yy];//������Ϣ


		if (windowType == 1)
		{//���´���
			if (xx + 1 < BOARD_DIMENSION && arr_havechess[xx + 1][yy] == 0 && isLiveFour(xx + 1, yy, currentChess, windowType))
			{
				arr_havechess[xx][yy] = havechess;
				arr_position[xx][yy] = chessposition;
				return true;
			}
			if (xx + 2 < BOARD_DIMENSION && arr_havechess[xx + 2][yy] == 0 && isLiveFour(xx + 2, yy, currentChess, windowType))
			{
				arr_havechess[xx][yy] = havechess;
				arr_position[xx][yy] = chessposition;
				return true;
			}
			if (xx + 3 < BOARD_DIMENSION && arr_havechess[xx + 3][yy] == 0 && isLiveFour(xx + 3, yy, currentChess, windowType))
			{
				arr_havechess[xx][yy] = havechess;
				arr_position[xx][yy] = chessposition;
				return true;
			}
			if (xx - 1 >= 0 && arr_havechess[xx - 1][yy] == 0 && isLiveFour(xx - 1, yy, currentChess, windowType))
			{
				arr_havechess[xx][yy] = havechess;
				arr_position[xx][yy] = chessposition;
				return true;
			}
			if (xx - 2 >= 0 && arr_havechess[xx - 2][yy] == 0 && isLiveFour(xx - 2, yy, currentChess, windowType))
			{
				arr_havechess[xx][yy] = havechess;
				arr_position[xx][yy] = chessposition;
				return true;
			}
			if (xx - 3 >= 0 && arr_havechess[xx - 3][yy] == 0 && isLiveFour(xx - 3, yy, currentChess, windowType))
			{
				arr_havechess[xx][yy] = havechess;
				arr_position[xx][yy] = chessposition;
				return true;
			}
			arr_havechess[xx][yy] = havechess;
			arr_position[xx][yy] = chessposition;
			return false;
		}
		if (windowType == 2)
		{//���Ҵ���
			if (yy + 1 < BOARD_DIMENSION && arr_havechess[xx ][yy+1] == 0 && isLiveFour(xx , yy+1, currentChess, windowType))
			{
				arr_havechess[xx][yy] = havechess;
				arr_position[xx][yy] = chessposition;
				return true;
			}
			if (yy + 2 < BOARD_DIMENSION && arr_havechess[xx ][yy+2] == 0 && isLiveFour(xx , yy+2, currentChess, windowType))
			{
				arr_havechess[xx][yy] = havechess;
				arr_position[xx][yy] = chessposition;
				return true;
			}
			if (yy + 3 < BOARD_DIMENSION && arr_havechess[xx ][yy+3] == 0 && isLiveFour(xx , yy+3, currentChess, windowType))
			{
				arr_havechess[xx][yy] = havechess;
				arr_position[xx][yy] = chessposition;
				return true;
			}
			if (yy - 1 >= 0 && arr_havechess[xx ][yy-1] == 0 && isLiveFour(xx , yy-1, currentChess, windowType))
			{
				arr_havechess[xx][yy] = havechess;
				arr_position[xx][yy] = chessposition;
				return true;
			}
			if (yy - 2 >= 0 && arr_havechess[xx][yy-2] == 0 && isLiveFour(xx, yy-2, currentChess, windowType))
			{
				arr_havechess[xx][yy] = havechess;
				arr_position[xx][yy] = chessposition;
				return true;
			}
			if (yy - 3 >= 0 && arr_havechess[xx][yy-3] == 0 && isLiveFour(xx, yy-3, currentChess, windowType))
			{
				arr_havechess[xx][yy] = havechess;
				arr_position[xx][yy] = chessposition;
				return true;
			}
			arr_havechess[xx][yy] = havechess;
			arr_position[xx][yy] = chessposition;
			return false;
		}
		if (windowType == 3)
		{//��������
			if (xx + 1 < BOARD_DIMENSION && yy-1 >= 0 && arr_havechess[xx + 1][yy-1] == 0 && isLiveFour(xx + 1, yy-1, currentChess, windowType))
			{
				arr_havechess[xx][yy] = havechess;
				arr_position[xx][yy] = chessposition;
				return true;
			}
			if (xx + 2 < BOARD_DIMENSION && yy - 2 >= 0 && arr_havechess[xx + 2][yy-2] == 0 && isLiveFour(xx + 2, yy-2, currentChess, windowType))
			{
				arr_havechess[xx][yy] = havechess;
				arr_position[xx][yy] = chessposition;
				return true;
			}
			if (xx + 3 < BOARD_DIMENSION && yy - 3 >= 0 && arr_havechess[xx + 3][yy-3] == 0 && isLiveFour(xx + 3, yy-3, currentChess, windowType))
			{
				arr_havechess[xx][yy] = havechess;
				arr_position[xx][yy] = chessposition;
				return true;
			}
			if (xx - 1 >= 0 && yy + 1 < BOARD_DIMENSION && arr_havechess[xx - 1][yy+1] == 0 && isLiveFour(xx - 1, yy+1, currentChess, windowType))
			{
				arr_havechess[xx][yy] = havechess;
				arr_position[xx][yy] = chessposition;
				return true;
			}
			if (xx - 2 >= 0 && yy + 2 < BOARD_DIMENSION && arr_havechess[xx - 2][yy+2] == 0 && isLiveFour(xx - 2, yy+2, currentChess, windowType))
			{
				arr_havechess[xx][yy] = havechess;
				arr_position[xx][yy] = chessposition;
				return true;
			}
			if (xx - 3 >= 0 && yy + 3 < BOARD_DIMENSION && arr_havechess[xx - 3][yy+3] == 0 && isLiveFour(xx - 3, yy+3, currentChess, windowType))
			{
				arr_havechess[xx][yy] = havechess;
				arr_position[xx][yy] = chessposition;
				return true;
			}
			arr_havechess[xx][yy] = havechess;
			arr_position[xx][yy] = chessposition;
			return false;
		}
		if (windowType == 4)
		{//��������
			if (xx + 1 < BOARD_DIMENSION && yy + 1 < BOARD_DIMENSION && arr_havechess[xx + 1][yy+1] == 0 && isLiveFour(xx + 1, yy+1, currentChess, windowType))
			{
				arr_havechess[xx][yy] = havechess;
				arr_position[xx][yy] = chessposition;
				return true;
			}
			if (xx + 2 < BOARD_DIMENSION && yy + 2 < BOARD_DIMENSION && arr_havechess[xx + 2][yy+2] == 0 && isLiveFour(xx + 2, yy+2, currentChess, windowType))
			{
				arr_havechess[xx][yy] = havechess;
				arr_position[xx][yy] = chessposition;
				return true;
			}
			if (xx + 3 < BOARD_DIMENSION && yy + 3 < BOARD_DIMENSION && arr_havechess[xx + 3][yy+3] == 0 && isLiveFour(xx + 3, yy+3, currentChess, windowType))
			{
				arr_havechess[xx][yy] = havechess;
				arr_position[xx][yy] = chessposition;
				return true;
			}
			if (xx - 1 >= 0 && yy - 1 >= 0 && arr_havechess[xx - 1][yy-1] == 0 && isLiveFour(xx - 1, yy-1, currentChess, windowType))
			{
				arr_havechess[xx][yy] = havechess;
				arr_position[xx][yy] = chessposition;
				return true;
			}
			if (xx - 2 >= 0 && yy - 2 >= 0 && arr_havechess[xx - 2][yy-2] == 0 && isLiveFour(xx - 2, yy-2, currentChess, windowType))
			{
				arr_havechess[xx][yy] = havechess;
				arr_position[xx][yy] = chessposition;
				return true;
			}
			if (xx - 3 >= 0 && yy - 3 >= 0 && arr_havechess[xx - 3][yy-3] == 0 && isLiveFour(xx - 3, yy-3, currentChess, windowType))
			{
				arr_havechess[xx][yy] = havechess;
				arr_position[xx][yy] = chessposition;
				return true;
			}
			arr_havechess[xx][yy] = havechess;
			arr_position[xx][yy] = chessposition;
			return false;
		}
		arr_havechess[xx][yy] = havechess;
		arr_position[xx][yy] = chessposition;
		return false;
	}
	else
	{
		arr_havechess[xx][yy] = havechess;
		arr_position[xx][yy] = chessposition;
		return false;
	}
}

bool CChessBoard::isLiveFour(int xx, int yy, bool currentChess, int windowType)
{//�ǲ��ǻ��ģ��ô�СΪ6�Ĵ��ڼ��
	//�����������ĸ����������ӣ�����������ǿ�

	if (currentChess)
	{
		//���򻬶�����xx yy Ϊ����������
		if (windowType == 1)
		{
			if (xx - 4 >= 0 && xx - 3 >= 0 && xx - 2 >= 0 && xx - 1 >= 0 && xx + 1 < BOARD_DIMENSION)
				if (arr_havechess[xx - 4][yy] == 0 && arr_position[xx - 3][yy] == 9 && arr_position[xx - 2][yy] == 9 && arr_position[xx - 1][yy] == 9 && arr_havechess[xx + 1][yy] == 0)
					return true;
			if (xx - 3 >= 0 && xx - 2 >= 0 && xx - 1 >= 0 && xx + 1 < BOARD_DIMENSION && xx + 2 < BOARD_DIMENSION)
				if (arr_havechess[xx - 3][yy] == 0 && arr_position[xx - 2][yy] == 9 && arr_position[xx - 1][yy] == 9 && arr_position[xx + 1][yy] == 9 && arr_havechess[xx + 2][yy] == 0)
					return true;
			if (xx - 2 >= 0 && xx - 1 >= 0 && xx + 1 < BOARD_DIMENSION && xx + 2 < BOARD_DIMENSION && xx + 3 < BOARD_DIMENSION)
				if (arr_havechess[xx - 2][yy] == 0 && arr_position[xx - 1][yy] == 9 && arr_position[xx + 1][yy] == 9 && arr_position[xx + 2][yy] == 9 && arr_havechess[xx + 3][yy] == 0)
					return true;
			if (xx - 1 >= 0 && xx + 1 < BOARD_DIMENSION && xx + 2 < BOARD_DIMENSION && xx + 3 < BOARD_DIMENSION && xx + 4 < BOARD_DIMENSION)
				if (arr_havechess[xx - 1][yy] == 0 && arr_position[xx + 1][yy] == 9 && arr_position[xx + 2][yy] == 9 && arr_position[xx + 3][yy] == 9 && arr_havechess[xx + 4][yy] == 0)
					return true;
			return false;
		}
		//���򻬶����� ��xx yyΪ����ߵ�����
		//�����������ö�ٰ�
		if (windowType == 2)
		{
			if (yy - 1 >= 0 && yy + 1 < BOARD_DIMENSION && yy + 2 < BOARD_DIMENSION && yy + 3 < BOARD_DIMENSION && yy + 4 < BOARD_DIMENSION)
				if (arr_havechess[xx][yy - 1] == 0 && arr_position[xx][yy + 1] == 9 && arr_position[xx][yy + 2] == 9 && arr_position[xx][yy + 3] == 9 && arr_havechess[xx][yy + 4] == 0)
					return true;
			if (yy - 2 >= 0 && yy - 1 >= 0 && yy + 1 < BOARD_DIMENSION && yy + 2 < BOARD_DIMENSION && yy + 3 < BOARD_DIMENSION)
				if (arr_havechess[xx][yy - 2] == 0 && arr_position[xx][yy - 1] == 9 && arr_position[xx][yy + 1] == 9 && arr_position[xx][yy + 2] == 9 && arr_havechess[xx][yy + 3] == 0)
					return true;
			if (yy - 3 >= 0 && yy - 2 >= 0 && yy - 1 >= 0 && yy + 1 < BOARD_DIMENSION && yy + 2 < BOARD_DIMENSION)
				if (arr_havechess[xx][yy - 3] == 0 && arr_position[xx][yy - 2] == 9 && arr_position[xx][yy - 1] == 9 && arr_position[xx][yy + 1] == 9 && arr_havechess[xx][yy + 2] == 0)
					return true;
			if (yy - 4 >= 0 && yy - 3 >= 0 && yy - 2 >= 0 && yy - 1 >= 0 && yy + 1 < BOARD_DIMENSION)
				if (arr_havechess[xx][yy - 4] == 0 && arr_position[xx][yy - 3] == 9 && arr_position[xx][yy - 2] == 9 && arr_position[xx][yy - 1] == 9 && arr_havechess[xx][yy + 1] == 0)
					return true;
			return false;
		}

		//��������
		if (windowType == 3)
		{
			if (xx + 1 < BOARD_DIMENSION && yy - 1 >= 0 && xx - 1 >= 0 && xx - 2 >= 0 && xx - 3 >= 0 && xx - 4 >= 0 && yy + 1 < BOARD_DIMENSION && yy + 2 < BOARD_DIMENSION && yy + 3 < BOARD_DIMENSION && yy + 4 < BOARD_DIMENSION)
				if (arr_havechess[xx + 1][yy - 1] == 0 && arr_position[xx - 1][yy + 1] == 9 && arr_position[xx - 2][yy + 2] == 9 && arr_position[xx - 3][yy + 3] == 9 && arr_havechess[xx - 4][yy + 4] == 0)
					return true;
			if (xx + 1 < BOARD_DIMENSION && xx + 2 < BOARD_DIMENSION && yy - 1 >= 0 && yy - 2 >= 0 && xx - 1 >= 0 && xx - 2 >= 0 && xx - 3 >= 0 && yy + 1 < BOARD_DIMENSION && yy + 2 < BOARD_DIMENSION && yy + 3 < BOARD_DIMENSION)
				if (arr_havechess[xx + 2][yy - 2] == 0 && arr_position[xx + 1][yy - 1] == 9 && arr_position[xx - 1][yy + 1] == 9 && arr_position[xx - 2][yy + 2] == 9 && arr_havechess[xx - 3][yy + 3] == 0)
					return true;
			if (xx + 1 < BOARD_DIMENSION && xx + 2 < BOARD_DIMENSION && xx + 3 < BOARD_DIMENSION && yy - 1 >= 0 && yy - 2 >= 0 && yy - 3 >= 0 && xx - 1 >= 0 && xx - 2 >= 0 && yy + 1 < BOARD_DIMENSION && yy + 2 < BOARD_DIMENSION)
				if (arr_havechess[xx + 3][yy - 3] == 0 && arr_position[xx + 2][yy - 2] == 9 && arr_position[xx + 1][yy - 1] == 9 && arr_position[xx - 1][yy + 1] == 9 && arr_havechess[xx - 2][yy + 2] == 0)
					return true;
			if (xx + 1 < BOARD_DIMENSION && xx + 2 < BOARD_DIMENSION && xx + 3 < BOARD_DIMENSION && xx + 4 < BOARD_DIMENSION && yy - 1 >= 0 && yy - 2 >= 0 && yy - 3 >= 0 && yy - 4 >= 0 && xx - 1 >= 0 && yy + 1 < BOARD_DIMENSION)
				if (arr_havechess[xx + 4][yy - 4] == 0 && arr_position[xx + 3][yy - 3] == 9 && arr_position[xx + 2][yy - 2] == 9 && arr_position[xx + 1][yy - 1] == 9 && arr_havechess[xx - 1][yy + 1] == 0)
					return true;
			return false;
		}
		//��������
		if (windowType == 4)
		{
			if (xx + 1 < BOARD_DIMENSION && yy + 1 < BOARD_DIMENSION && xx - 1 >= 0 && xx - 2 >= 0 && xx - 3 >= 0 && xx - 4 >= 0 && yy - 1 >= 0 && yy - 2 >= 0 && yy - 3 >= 0 && yy - 4 >= 0)
				if (arr_havechess[xx + 1][yy + 1] == 0 && arr_position[xx - 1][yy - 1] == 9 && arr_position[xx - 2][yy - 2] == 9 && arr_position[xx - 3][yy - 3] == 9 && arr_havechess[xx - 4][yy - 4] == 0)
					return true;
			if (xx + 2 < BOARD_DIMENSION && yy + 2 < BOARD_DIMENSION && xx + 1 < BOARD_DIMENSION && yy + 1 < BOARD_DIMENSION && xx - 1 >= 0 && xx - 2 >= 0 && xx - 3 >= 0 && yy - 1 >= 0 && yy - 2 >= 0 && yy - 3 >= 0)
				if (arr_havechess[xx + 2][yy + 2] == 0 && arr_position[xx + 1][yy + 1] == 9 && arr_position[xx - 1][yy - 1] == 9 && arr_position[xx - 2][yy - 2] == 9 && arr_havechess[xx - 3][yy - 3] == 0)
					return true;
			if (xx + 3 < BOARD_DIMENSION && yy + 3 < BOARD_DIMENSION && xx + 2 < BOARD_DIMENSION && yy + 2 < BOARD_DIMENSION && xx + 1 < BOARD_DIMENSION && yy + 1 < BOARD_DIMENSION && xx - 1 >= 0 && xx - 2 >= 0 && yy - 1 >= 0 && yy - 2 >= 0)
				if (arr_havechess[xx + 3][yy + 3] == 0 && arr_position[xx + 2][yy + 2] == 9 && arr_position[xx + 1][yy + 1] == 9 && arr_position[xx - 1][yy - 1] == 9 && arr_havechess[xx - 2][yy - 2] == 0)
					return true;
			if (xx + 4 < BOARD_DIMENSION && yy + 4 < BOARD_DIMENSION && xx + 3 < BOARD_DIMENSION && yy + 3 < BOARD_DIMENSION && xx + 2 < BOARD_DIMENSION && yy + 2 < BOARD_DIMENSION && xx + 1 < BOARD_DIMENSION && yy + 1 < BOARD_DIMENSION && xx - 1 >= 0 && yy - 1 >= 0)
				if (arr_havechess[xx + 4][yy + 4] == 0 && arr_position[xx + 3][yy + 3] == 9 && arr_position[xx + 2][yy + 2] == 9 && arr_position[xx + 1][yy + 1] == 9 && arr_havechess[xx - 1][yy - 1] == 0)
					return true;
			return false;
		}

		//���û�úÿ���һ��ѭ����
		//û�����ôѭ��
		//ö����������
		return false;//����������û��
	}
	else
		return false;
	
}

bool CChessBoard::isDoubleThree(int xx, int yy, bool currentChess)
{//�ǲ���˫����
	int liveNum = 0;
	if (isLiveThree(xx, yy, currentChess, 1))
		liveNum++;
	if (isLiveThree(xx, yy, currentChess, 2))
		liveNum++;
	if (isLiveThree(xx, yy, currentChess, 3))
		liveNum++;
	if (isLiveThree(xx, yy, currentChess, 4))
		liveNum++;

	if (liveNum >= 2)
		return true;
	else
		return false;
}

bool CChessBoard::isDoubleFour(int xx, int yy, bool currentChess)
{//�ǲ���˫����
	int liveNum = 0;
	if (isLiveFour(xx, yy, currentChess, 1))
		liveNum++;
	if (isLiveFour(xx, yy, currentChess, 2))
		liveNum++;
	if (isLiveFour(xx, yy, currentChess, 3))
		liveNum++;
	if (isLiveFour(xx, yy, currentChess, 4))
		liveNum++;

	if (liveNum >= 2)
		return true;
	else
		return false;
}

bool CChessBoard::isLongString(int xx, int yy, bool currentChess)
{
	int chessNum = 0;//������
	if (currentChess)
	{
		//���λ���Ǻ���
		//********************************************
		// 1 �ж����� ���³���
		// 1.1 ����
		for (int i = 1; i < 6; i++)//�����λ�þ͹���
		{
			if (xx - i  >= 0 && arr_position[xx - i][yy] == 9)
			{
				//ûԽ�磬���Ǻ���
				chessNum++;
			}
			else
				break;
		}
		//1.2 ����
		for (int i = 1; i < 6; i++)
		{
			if (xx + i < BOARD_DIMENSION && arr_position[xx + i][yy] == 9)
			{
				//����ûԽ�磬���Ǻ���
				chessNum++;
			}
			else
				break;
		}
		if (chessNum >= 5)//���ڵ���5���������λ�õľ�һ������5�ˣ��ǳ�������
			return true;
		chessNum = 0;


		//********************************************
		// 2 �жϺ��� ���ҳ���
		// 2.1 ����
		for (int i = 1; i < 6; i++)//�����λ�þ͹���
		{
			if (yy - i >= 0 && arr_position[xx ][yy - i] == 9)
			{
				//ûԽ�磬���Ǻ���
				chessNum++;
			}
			else
				break;
		}
		//2.2 ����
		for (int i = 1; i < 6; i++)
		{
			if (yy + i < BOARD_DIMENSION && arr_position[xx ][yy + i] == 9)
			{
				//����ûԽ�磬���Ǻ���
				chessNum++;
			}
			else
				break;
		}
		if (chessNum >= 5)//���ڵ���5���������λ�õľ�һ������5�ˣ��ǳ�������
			return true;
		chessNum = 0;


		//********************************************
		// 3 �ж��������ϳ���
		// 3.1 ������
		for (int i = 1; i < 6; i++)//�����λ�þ͹���
		{
			if (yy - i >= 0 && xx + i < BOARD_DIMENSION && arr_position[xx + i][yy - i] == 9)
			{
				//ûԽ�磬���Ǻ���
				chessNum++;
			}
			else
				break;
		}
		//3.2 ������
		for (int i = 1; i < 6; i++)
		{
			if (xx - i >= 0 && yy + i < BOARD_DIMENSION && arr_position[xx - i][yy + i] == 9)
			{
				//����ûԽ�磬���Ǻ���
				chessNum++;
			}
			else
				break;
		}
		if (chessNum >= 5)//���ڵ���5���������λ�õľ�һ������5�ˣ��ǳ�������
			return true;
		chessNum = 0;



		//********************************************
		// 4 �ж��������³���
		// 4.1 ������
		for (int i = 1; i < 6; i++)//�����λ�þ͹���
		{
			if (yy - i >= 0 && xx - i >= 0 && arr_position[xx - i][yy - i] == 9)
			{
				//ûԽ�磬���Ǻ���
				chessNum++;
			}
			else
				break;
		}
		//4.2 ������
		for (int i = 1; i < 6; i++)
		{
			if (xx + i < BOARD_DIMENSION && yy + i < BOARD_DIMENSION && arr_position[xx + i][yy + i] == 9)
			{
				//����ûԽ�磬���Ǻ���
				chessNum++;
			}
			else
				break;
		}
		if (chessNum >= 5)//���ڵ���5���������λ�õľ�һ������5�ˣ��ǳ�������
			return true;
		chessNum = 0;



		//������漸�������û��
		return false;//û�г�������
	}
	else
	{
		//���λ���ǰ���
		return false;//���Ӳ�����
	}
}

bool CChessBoard::isForbidden(bool currentChess, CPosition position)
{
	if (currentChess)
	{
		//�Ǻ��ӣ��н���
		if (isDoubleThree(position.getX(), position.getY(), currentChess))
			return true;
		if (isDoubleFour(position.getX(), position.getY(), currentChess))
			return true;
		if (isLongString(position.getX(), position.getY(), currentChess))
			return true;
		return false;
	}
	else
		return false;//����û�н���
}

bool CChessBoard::checkVectorIsEmpty()
{
	if (!vec_black_chess.empty() && !vec_white_chess.empty())
		return true;
	else
		return false;
}
