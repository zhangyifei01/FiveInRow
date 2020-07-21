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
	
	//初始化arr_havechess数组
	for (int i = 0; i < BOARD_DIMENSION; i++)
		for (int j = 0; j < BOARD_DIMENSION; j++)
			arr_havechess[i][j] = 0;//刚开始都没有棋子
									
	//下面画棋盘，初始化arr_position数组
	//第一行
	arr_position[0][0] = 0;
	for (int i = 0; i < BOARD_DIMENSION - 2; i++)
		arr_position[0][i + 1] = 1;
	arr_position[0][BOARD_DIMENSION - 1] = 2;
	//中间行
	for (int j = 0; j < BOARD_DIMENSION - 2; j++)
	{
		arr_position[j + 1][0] = 3;
		for (int i = 0; i < BOARD_DIMENSION; i++)
			arr_position[j + 1][i + 1] = 4;
		arr_position[j + 1][BOARD_DIMENSION - 1] = 5;
	}
	//最后一行
	arr_position[BOARD_DIMENSION - 1][0] = 6;
	for (int i = 0; i < BOARD_DIMENSION - 2; i++)
		arr_position[BOARD_DIMENSION - 1][i + 1] = 7;
	arr_position[BOARD_DIMENSION - 1][BOARD_DIMENSION - 1] = 8;
}

void CChessBoard::drawChessBoard()
{
	char x_label[BOARD_DIMENSION];//横向字母标识A到O
	for (int i = 0; i < BOARD_DIMENSION; i++)
		x_label[i] = 65 + i;

	system("cls");//先清空一下输出界面
	system("color 02");//黑底绿字
	std::cout << "     --   Game FiveInRow   --" << std::endl;
	for (int i = 0; i < BOARD_DIMENSION; i++)
	{
		std::cout << std::setw(2) << BOARD_DIMENSION - i;//y_label
		for (int j = 0; j < BOARD_DIMENSION; j++)
			std::cout << m_symbol[arr_position[i][j]];//画出各位置符号
		std::cout << std::endl;
	}
	std::cout << " ";
	for (int i = 0; i < BOARD_DIMENSION; i++)
		std::cout << std::setw(2) << x_label[i];
	std::cout << std::endl;
}

int CChessBoard::getPositionValue(int xx, int yy)
{//返回符号位置
	if (xx >= 0 && xx < BOARD_DIMENSION && yy >= 0 && yy < BOARD_DIMENSION)
		return arr_position[xx][yy];
	else
	{
		std::cout << "input position out of bound!!!" << std::endl;
		return 13;//那个数组最大是12
	}
}

void CChessBoard::changePositionValue(bool chesstype, CPosition & position)
{
	if (chesstype)//是黑子
	{
		arr_position[position.getX()][position.getY()] = 11;//黑子三角
		arr_havechess[position.getX()][position.getY()] = 1;

		if (vec_black_chess.size() > 0)
		{
			//把上一步棋置圆形
			arr_position[vec_black_chess[vec_black_chess.size() - 1].getX()][vec_black_chess[vec_black_chess.size() - 1].getY()] = 9;
		}

		//存储当前位置
		vec_black_chess.push_back(position);
	}
	else
	{//是白子
		arr_position[position.getX()][position.getY()] = 12;//白子三角
		arr_havechess[position.getX()][position.getY()] = 1;

		if (vec_white_chess.size() > 0)
		{
			//把上一步棋置圆形
			arr_position[vec_white_chess[vec_white_chess.size() - 1].getX()][vec_white_chess[vec_white_chess.size() - 1].getY()] = 10;
		}

		//存储当前位置
		vec_white_chess.push_back(position);
	}
}

bool CChessBoard::isLegalPosition(CPosition & position)
{
	if (position.getX() >= 0 && position.getX() < BOARD_DIMENSION && position.getY() >= 0 && position.getY() < BOARD_DIMENSION && arr_havechess[position.getX()][position.getY()] == 0)
	{
		//没有越界，该位置也没有棋子
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
	//判断这个位置的棋子是哪种颜色
	if (arr_position[xx][yy] == 11)//黑子
	{
		chessvalue = 9;//黑色圆子
	}
	if (arr_position[xx][yy] == 12)//白子
	{
		chessvalue = 10;//白色圆子
	}

	int chessNum = 0;//连子数
	int x, y;
	
	//判断连子数
	
		//1纵向
		//1.1纵向向下
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
			return true;//加上当前棋子总共五个了
		//1.2纵向向上 
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
			return true;//加上当前棋子总共五个了
		chessNum = 0;

		//2横向
		//2.1横向向右
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
			return true;//加上当前棋子总共五个了
		//2.2横向向左
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
			return true;//加上当前棋子总共五个了
		chessNum = 0;
	


	
		//3右上45度
		//3.1右上45度 向右上
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
			return true;//加上当前棋子总共五个了
		//3.2 右上45度 向左下
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
			return true;//加上当前棋子总共五个了
		chessNum = 0;
	


	
		//4右下135度
		//4.1右下135度 向右下
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
			return true;//加上当前棋子总共五个了
		//4.2右下135度 向左上
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
			return true;//加上当前棋子总共五个了
		chessNum = 0;
	
	return false;
}

void CChessBoard::initPositionScore()
{
	for (int i = 0; i < BOARD_DIMENSION; i++)
		for (int j = 0; j < BOARD_DIMENSION; j++)
			arr_positionscore[i][j] = 0;//所有位置初始都是0分
}

void CChessBoard::setArrayPositionScore(int xx, int yy, int scoreValue)
{
	arr_positionscore[xx][yy] = scoreValue;
}

int CChessBoard::slideWindowScore(int xx, int yy, bool ismychess, int windowtype)
{
	//windowtype 1是上下，2是左右，3是左下右上，4是左上右下
	bool haveblack, havewhite;//判断这个窗口中有没有黑子，白子
	int blacknum, whitenum;//黑子白子数
	haveblack = false;
	havewhite = false;
	blacknum = 0;
	whitenum = 0;
	if (windowtype == 1)
	{//滑窗是上下的
		for (int i = 1; i < 5; i++)
		{
			
		    if (arr_position[xx - i][yy] == 9 || arr_position[xx - i][yy] == 11)//黑子
			{
				haveblack = true;
				blacknum++;
			}
			if (arr_position[xx - i][yy] == 10 || arr_position[xx - i][yy] == 12)//白子
			{
				havewhite = true;
				whitenum++;
			}
		}
		if (haveblack && havewhite)
			return 0;//黑白都有混合的打分0
		else if(haveblack && !havewhite)
		{//有黑没有白
			if (m_currentchess)//我是黑子
			{
				if (blacknum == 1)
					return 50;//我方有一个子 50分
				if (blacknum == 2)
					return 1000;//我方有两个子 1000分
				if (blacknum == 3)
					return 150000;
				if (blacknum == 4)
					return 8000000;
			}
			else
			{
				if (blacknum == 1)
					return 25;//对方有一个子 50分
				if (blacknum == 2)
					return 500;//对方有两个子 1000分
				if (blacknum == 3)
					return 100000;
				if (blacknum == 4)
					return 1000000;
			}
		}
		else if (!haveblack && havewhite)
		{//有白没有黑
			if (m_currentchess)//我是黑子
			{
				if (blacknum == 1)
					return 25;//对方有一个子 50分
				if (blacknum == 2)
					return 500;//对方有两个子 1000分
				if (blacknum == 3)
					return 100000;
				if (blacknum == 4)
					return 1000000;
				
			}
			else
			{
				if (blacknum == 1)
					return 50;//我方有一个子 50分
				if (blacknum == 2)
					return 1000;//我方有两个子 1000分
				if (blacknum == 3)
					return 150000;
				if (blacknum == 4)
					return 8000000;
			}
		}
		else//都没有
			return 5;//空位置打5分
	}

	if (windowtype == 2)
	{//滑窗是左右的
		for (int i = 1; i < 5; i++)
		{

			if (arr_position[xx][yy + i] == 9 || arr_position[xx][yy + i] == 11)//黑子
			{
				haveblack = true;
				blacknum++;
			}
			if (arr_position[xx][yy + i] == 10 || arr_position[xx][yy + i] == 12)//白子
			{
				havewhite = true;
				whitenum++;
			}
		}
		if (haveblack && havewhite)
			return 0;//黑白都有混合的打分0
		else if (haveblack && !havewhite)
		{//有黑没有白
			if (m_currentchess)//我是黑子
			{
				if (blacknum == 1)
					return 50;//我方有一个子 50分
				if (blacknum == 2)
					return 1000;//我方有两个子 1000分
				if (blacknum == 3)
					return 150000;
				if (blacknum == 4)
					return 8000000;
			}
			else
			{
				if (blacknum == 1)
					return 25;//对方有一个子 50分
				if (blacknum == 2)
					return 500;//对方有两个子 1000分
				if (blacknum == 3)
					return 100000;
				if (blacknum == 4)
					return 1000000;
			}
		}
		else if (!haveblack && havewhite)
		{//有白没有黑
			if (m_currentchess)//我是黑子
			{
				if (blacknum == 1)
					return 25;//对方有一个子 50分
				if (blacknum == 2)
					return 500;//对方有两个子 1000分
				if (blacknum == 3)
					return 100000;
				if (blacknum == 4)
					return 1000000;

			}
			else
			{
				if (blacknum == 1)
					return 50;//我方有一个子 50分
				if (blacknum == 2)
					return 1000;//我方有两个子 1000分
				if (blacknum == 3)
					return 150000;
				if (blacknum == 4)
					return 8000000;
			}
		}
		else//都没有
			return 5;//空位置打5分
	}

	if (windowtype == 3)
	{//滑窗是左下右上的
		for (int i = 1; i < 5; i++)
		{

			if (arr_position[xx - i][yy + i] == 9 || arr_position[xx - i][yy + i] == 11)//黑子
			{
				haveblack = true;
				blacknum++;
			}
			if (arr_position[xx - i][yy + i] == 10 || arr_position[xx - i][yy + i] == 12)//白子
			{
				havewhite = true;
				whitenum++;
			}
		}
		if (haveblack && havewhite)
			return 0;//黑白都有混合的打分0
		else if (haveblack && !havewhite)
		{//有黑没有白
			if (m_currentchess)//我是黑子
			{
				if (blacknum == 1)
					return 50;//我方有一个子 50分
				if (blacknum == 2)
					return 1000;//我方有两个子 1000分
				if (blacknum == 3)
					return 150000;
				if (blacknum == 4)
					return 8000000;
			}
			else
			{
				if (blacknum == 1)
					return 25;//对方有一个子 50分
				if (blacknum == 2)
					return 500;//对方有两个子 1000分
				if (blacknum == 3)
					return 100000;
				if (blacknum == 4)
					return 1000000;
			}
		}
		else if (!haveblack && havewhite)
		{//有白没有黑
			if (m_currentchess)//我是黑子
			{
				if (blacknum == 1)
					return 25;//对方有一个子 50分
				if (blacknum == 2)
					return 500;//对方有两个子 1000分
				if (blacknum == 3)
					return 100000;
				if (blacknum == 4)
					return 1000000;

			}
			else
			{
				if (blacknum == 1)
					return 50;//我方有一个子 50分
				if (blacknum == 2)
					return 1000;//我方有两个子 1000分
				if (blacknum == 3)
					return 150000;
				if (blacknum == 4)
					return 8000000;
			}
		}
		else//都没有
			return 5;//空位置打5分
	}
	if (windowtype == 4)
	{//滑窗是左上右下的
		for (int i = 1; i < 5; i++)
		{

			if (arr_position[xx - i][yy - i] == 9 || arr_position[xx - i][yy - i] == 11)//黑子
			{
				haveblack = true;
				blacknum++;
			}
			if (arr_position[xx - i][yy - i] == 10 || arr_position[xx - i][yy - i] == 12)//白子
			{
				havewhite = true;
				whitenum++;
			}
		}
		if (haveblack && havewhite)
			return 0;//黑白都有混合的打分0
		else if (haveblack && !havewhite)
		{//有黑没有白
			if (m_currentchess)//我是黑子
			{
				if (blacknum == 1)
					return 50;//我方有一个子 50分
				if (blacknum == 2)
					return 1000;//我方有两个子 1000分
				if (blacknum == 3)
					return 150000;
				if (blacknum == 4)
					return 8000000;
			}
			else
			{
				if (blacknum == 1)
					return 25;//对方有一个子 50分
				if (blacknum == 2)
					return 500;//对方有两个子 1000分
				if (blacknum == 3)
					return 100000;
				if (blacknum == 4)
					return 2000000;
			}
		}
		else if (!haveblack && havewhite)
		{//有白没有黑
			if (m_currentchess)//我是黑子
			{
				if (blacknum == 1)
					return 25;//对方有一个子 50分
				if (blacknum == 2)
					return 500;//对方有两个子 1000分
				if (blacknum == 3)
					return 100000;
				if (blacknum == 4)
					return 1000000;

			}
			else
			{
				if (blacknum == 1)
					return 50;//我方有一个子 50分
				if (blacknum == 2)
					return 1000;//我方有两个子 1000分
				if (blacknum == 3)
					return 150000;
				if (blacknum == 4)
					return 8000000;
			}
		}
		else//都没有
			return 5;//空位置打5分
	}
	return 0;
}

int CChessBoard::blankPositionScore(int xx, int yy, bool ishavechess, bool ismychess)
{
	
	int x, y;//窗口底部坐标
	int sumScore = 0;
	if (ishavechess)
		return 0;
	else
	{
		

		//**********************************************
		//上下滑动窗口
		if (xx - 4 >= 0 && xx + 4 < BOARD_DIMENSION)
		{
			//在中间位置，可以随便滑，不会越界
			x = xx;//先以xx, yy为底
			y = yy;
			for (int i = 0; i < 5; i++)
			{
				x = x + i;//底部是第几行
				sumScore += slideWindowScore(x, y, ismychess, 1);
			}
		}
		else
		{
			//不能随便滑动了
			if (xx - 4 < 0)
			{
				//有xx+1个滑窗
				x = 4;//先以xx, yy为底
				y = yy;
				for (int i = 0; i < xx + 1; i++)
				{
					x = x + i;
					sumScore += slideWindowScore(x, y, ismychess, 1);
				}
			}
			if (xx + 4 >= BOARD_DIMENSION)
			{
				//有BOARD_DIMENSION - xx个窗口
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
		//左右滑动窗口
		if (yy - 4 >= 0 && yy + 4 < BOARD_DIMENSION)
		{
			//在中间位置，可以随便滑，不会越界
			x = xx;//先以xx, yy为底
			y = yy;
			for (int i = 0; i < 5; i++)
			{
				y = y + i;//底部是第几行
				sumScore += slideWindowScore(x, y, ismychess, 2);
			}
		}
		else
		{
			//不能随便滑动了
			if (yy - 4 < 0)
			{
				//有yy+1个滑窗
				y = 4;//先以xx, yy为底
				x = xx;
				for (int i = 0; i < yy + 1; i++)
				{
					y = y + i;
					sumScore += slideWindowScore(x, y, ismychess, 2);
				}
			}
			if (yy + 4 >= BOARD_DIMENSION)
			{
				//有BOARD_DIMENSION - yy个窗口
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
		//左下右上滑动窗口
		x = xx;
		y = yy;
		for (int i = 0; i < 5; i++)//以该空位置为底滑动，保存没有越界的框
		{
			if (x + i < BOARD_DIMENSION && y - i >= 0 && x - 4 >= 0 && y + 4 < BOARD_DIMENSION)//滑窗左下和右上都没有越界
			{
				sumScore += slideWindowScore(x+i, y-i, ismychess, 3);
			}
		}
		//**********************************************
		//左上右下滑动窗口
		x = xx;
		y = yy;
		for (int i = 0; i < 5; i++)//以该空位置为底滑动，保存没有越界的框
		{
			if (x + i < BOARD_DIMENSION && y + i < BOARD_DIMENSION && x - 4 >= 0 && y - 4 >= 0)//滑窗右下和左上都没有越界
			{
				sumScore += slideWindowScore(x+i, y+i, ismychess, 4);
			}
		}
		
		return sumScore;
	}
}

void CChessBoard::moveWindow()
{
	CPosition myposition, position1;//我上次落子位置，对方上一步落子位置
	int x, y;//临时坐标值
	int tmp_doublescore = 0;//我方和对方都对这个位置打分
	if (m_currentchess )
	{
		//我是黑子
		myposition = vec_black_chess[vec_black_chess.size() - 1];
		position1 = vec_white_chess[vec_white_chess.size() - 1];
	}
	else
	{//我的白子
		position1 = vec_black_chess[vec_black_chess.size() - 1];
		myposition = vec_white_chess[vec_white_chess.size() - 1];
	}

	
	
	//*********************************************************************************
	//先找我上一步棋子周围位置进行打分
	x = myposition.getX();
	y = myposition.getY();
	for (int i = 0; i < 5; i++)
	{
		//向上找
		x--;
		if (x < 0)
			break;//越界
		if (arr_havechess[x][y] == 1)
			//已经有棋子了，就不用打分了，0分
			arr_positionscore[x][y] = blankPositionScore(x, y, true, true);
		else
		{
			tmp_doublescore = 0;
			if (arr_positionscore[x][y] > 0)
			{//说明对它打分过，取两次打分最高值
				tmp_doublescore = arr_positionscore[x][y];
				arr_positionscore[x][y] = 0;
			}

			arr_positionscore[x][y] = blankPositionScore(x, y, false, true);

			if (arr_positionscore[x][y] < tmp_doublescore)//如果最后这个位置打分比前一次打分还低，就用最高的打分值
				arr_positionscore[x][y] = tmp_doublescore;
		}
	}
	x = myposition.getX();
	for (int i = 0; i < 5; i++)
	{
		//向下找
		x++;
		if (x >= BOARD_DIMENSION)
			break;//越界
		if (arr_havechess[x][y] == 1)
			//已经有棋子了，就不用打分了，0分
			arr_positionscore[x][y] = blankPositionScore(x, y, true, true);
		else
		{
			tmp_doublescore = 0;
			if (arr_positionscore[x][y] > 0)
			{//说明对它打分过，取两次打分最高值
				tmp_doublescore = arr_positionscore[x][y];
				arr_positionscore[x][y] = 0;
			}

			arr_positionscore[x][y] = blankPositionScore(x, y, false, true);

			if (arr_positionscore[x][y] < tmp_doublescore)//如果最后这个位置打分比前一次打分还低，就用最高的打分值
				arr_positionscore[x][y] = tmp_doublescore;
		}
			
	}
	x = myposition.getX();
	for (int i = 0; i < 5; i++)
	{
		//向左找
		y--;
		if (y < 0)
			break;//越界
		if (arr_havechess[x][y] == 1)
			//已经有棋子了，就不用打分了，0分
			arr_positionscore[x][y] = blankPositionScore(x, y, true, true);
		else
		{
			tmp_doublescore = 0;
			if (arr_positionscore[x][y] > 0)
			{//说明对它打分过，取两次打分最高值
				tmp_doublescore = arr_positionscore[x][y];
				arr_positionscore[x][y] = 0;
			}

			arr_positionscore[x][y] = blankPositionScore(x, y, false, true);

			if (arr_positionscore[x][y] < tmp_doublescore)//如果最后这个位置打分比前一次打分还低，就用最高的打分值
				arr_positionscore[x][y] = tmp_doublescore;
		}
			
	}
	y = myposition.getY();
	for (int i = 0; i < 5; i++)
	{
		//向右找
		y++;
		if (y >= BOARD_DIMENSION)
			break;//越界
		if (arr_havechess[x][y] == 1)
			//已经有棋子了，就不用打分了，0分
			arr_positionscore[x][y] = blankPositionScore(x, y, true, true);
		else
		{
			tmp_doublescore = 0;
			if (arr_positionscore[x][y] > 0)
			{//说明对它打分过，取两次打分最高值
				tmp_doublescore = arr_positionscore[x][y];
				arr_positionscore[x][y] = 0;
			}

			arr_positionscore[x][y] = blankPositionScore(x, y, false, true);

			if (arr_positionscore[x][y] < tmp_doublescore)//如果最后这个位置打分比前一次打分还低，就用最高的打分值
				arr_positionscore[x][y] = tmp_doublescore;
		}
			
	}
	y = myposition.getY();
	for (int i = 0; i < 5; i++)
	{
		//向右上找
		x--;
		y++;
		if (y >= BOARD_DIMENSION || x < 0)
			break;//越界
		if (arr_havechess[x][y] == 1)
			//已经有棋子了，就不用打分了，0分
			arr_positionscore[x][y] = blankPositionScore(x, y, true, true);
		else
		{
			tmp_doublescore = 0;
			if (arr_positionscore[x][y] > 0)
			{//说明对它打分过，取两次打分最高值
				tmp_doublescore = arr_positionscore[x][y];
				arr_positionscore[x][y] = 0;
			}

			arr_positionscore[x][y] = blankPositionScore(x, y, false, true);

			if (arr_positionscore[x][y] < tmp_doublescore)//如果最后这个位置打分比前一次打分还低，就用最高的打分值
				arr_positionscore[x][y] = tmp_doublescore;
		}
	}
	x = myposition.getX();
	y = myposition.getY();
	for (int i = 0; i < 5; i++)
	{
		//向左下找
		y--;
		x++;
		if (x >= BOARD_DIMENSION || y < 0)
			break;//越界
		if (arr_havechess[x][y] == 1)
			//已经有棋子了，就不用打分了，0分
			arr_positionscore[x][y] = blankPositionScore(x, y, true, true);
		else
		{
			tmp_doublescore = 0;
			if (arr_positionscore[x][y] > 0)
			{//说明对它打分过，取两次打分最高值
				tmp_doublescore = arr_positionscore[x][y];
				arr_positionscore[x][y] = 0;
			}

			arr_positionscore[x][y] = blankPositionScore(x, y, false, true);

			if (arr_positionscore[x][y] < tmp_doublescore)//如果最后这个位置打分比前一次打分还低，就用最高的打分值
				arr_positionscore[x][y] = tmp_doublescore;
		}
	}
	x = myposition.getX();
	y = myposition.getY();
	for (int i = 0; i < 5; i++)
	{
		//向左上找
		y--;
		x--;
		if (x < 0 || y < 0)
			break;//越界
		if (arr_havechess[x][y] == 1)
			//已经有棋子了，就不用打分了，0分
			arr_positionscore[x][y] = blankPositionScore(x, y, true, true);
		else
		{
			tmp_doublescore = 0;
			if (arr_positionscore[x][y] > 0)
			{//说明对它打分过，取两次打分最高值
				tmp_doublescore = arr_positionscore[x][y];
				arr_positionscore[x][y] = 0;
			}

			arr_positionscore[x][y] = blankPositionScore(x, y, false, true);

			if (arr_positionscore[x][y] < tmp_doublescore)//如果最后这个位置打分比前一次打分还低，就用最高的打分值
				arr_positionscore[x][y] = tmp_doublescore;
		}
			
	}
	x = myposition.getX();
	y = myposition.getY();
	for (int i = 0; i < 5; i++)
	{
		//向右下找
		y++;
		x++;
		if (x >= BOARD_DIMENSION || y >= BOARD_DIMENSION)
			break;//越界
		if (arr_havechess[x][y] == 1)
			//已经有棋子了，就不用打分了，0分
			arr_positionscore[x][y] = blankPositionScore(x, y, true, true);
		else
		{
			tmp_doublescore = 0;
			if (arr_positionscore[x][y] > 0)
			{//说明对它打分过，取两次打分最高值
				tmp_doublescore = arr_positionscore[x][y];
				arr_positionscore[x][y] = 0;
			}

			arr_positionscore[x][y] = blankPositionScore(x, y, false, true);

			if (arr_positionscore[x][y] < tmp_doublescore)//如果最后这个位置打分比前一次打分还低，就用最高的打分值
				arr_positionscore[x][y] = tmp_doublescore;
		}
	}
	

	//*********************************************************************************
	//再找对方棋子周围的位置
	x = position1.getX();
	y = position1.getY();
	for (int i = 0; i < 5; i++)
	{
		//向上找
		x--;
		if (x < 0)
			break;//越界
		if (arr_havechess[x][y] == 1)
			//已经有棋子了，就不用打分了，0分
			arr_positionscore[x][y] = blankPositionScore(x, y, true, false);
		else
		{
			tmp_doublescore = 0;
			if (arr_positionscore[x][y] > 0)
			{//说明对它打分过，取两次打分最高值
				tmp_doublescore = arr_positionscore[x][y];
				arr_positionscore[x][y] = 0;
			}

			arr_positionscore[x][y] = blankPositionScore(x, y, false, false);

			if (arr_positionscore[x][y] < tmp_doublescore)//如果最后这个位置打分比前一次打分还低，就用最高的打分值
				arr_positionscore[x][y] = tmp_doublescore;
		}
			
	}
	x = position1.getX();
	for (int i = 0; i < 5; i++)
	{
		//向下找
		x++;
		if (x >= BOARD_DIMENSION)
			break;//越界
		if (arr_havechess[x][y] == 1)
			//已经有棋子了，就不用打分了，0分
			arr_positionscore[x][y] = blankPositionScore(x, y, true, false);
		else
		{
			tmp_doublescore = 0;
			if (arr_positionscore[x][y] > 0)
			{//说明对它打分过，取两次打分最高值
				tmp_doublescore = arr_positionscore[x][y];
				arr_positionscore[x][y] = 0;
			}

			arr_positionscore[x][y] = blankPositionScore(x, y, false, false);

			if (arr_positionscore[x][y] < tmp_doublescore)//如果最后这个位置打分比前一次打分还低，就用最高的打分值
				arr_positionscore[x][y] = tmp_doublescore;
		}
			
	}
	x = position1.getX();
	for (int i = 0; i < 5; i++)
	{
		//向左找
		y--;
		if (y < 0)
			break;//越界
		if (arr_havechess[x][y] == 1)
			//已经有棋子了，就不用打分了，0分
			arr_positionscore[x][y] = blankPositionScore(x, y, true, false);
		else
		{
			tmp_doublescore = 0;
			if (arr_positionscore[x][y] > 0)
			{//说明对它打分过，取两次打分最高值
				tmp_doublescore = arr_positionscore[x][y];
				arr_positionscore[x][y] = 0;
			}

			arr_positionscore[x][y] = blankPositionScore(x, y, false, false);

			if (arr_positionscore[x][y] < tmp_doublescore)//如果最后这个位置打分比前一次打分还低，就用最高的打分值
				arr_positionscore[x][y] = tmp_doublescore;
		}
			
	}
	y = position1.getY();
	for (int i = 0; i < 5; i++)
	{
		//向右找
		y++;
		if (y >= BOARD_DIMENSION)
			break;//越界
		if (arr_havechess[x][y] == 1)
			//已经有棋子了，就不用打分了，0分
			arr_positionscore[x][y] = blankPositionScore(x, y, true, false);
		else
		{
			tmp_doublescore = 0;
			if (arr_positionscore[x][y] > 0)
			{//说明对它打分过，取两次打分最高值
				tmp_doublescore = arr_positionscore[x][y];
				arr_positionscore[x][y] = 0;
			}

			arr_positionscore[x][y] = blankPositionScore(x, y, false, false);

			if (arr_positionscore[x][y] < tmp_doublescore)//如果最后这个位置打分比前一次打分还低，就用最高的打分值
				arr_positionscore[x][y] = tmp_doublescore;
		}
			
	}
	y = position1.getY();
	for (int i = 0; i < 5; i++)
	{
		//向右上找
		x--;
		y++;
		if (y >= BOARD_DIMENSION || x < 0)
			break;//越界
		if (arr_havechess[x][y] == 1)
			//已经有棋子了，就不用打分了，0分
			arr_positionscore[x][y] = blankPositionScore(x, y, true, false);
		else
		{
			tmp_doublescore = 0;
			if (arr_positionscore[x][y] > 0)
			{//说明对它打分过，取两次打分最高值
				tmp_doublescore = arr_positionscore[x][y];
				arr_positionscore[x][y] = 0;
			}

			arr_positionscore[x][y] = blankPositionScore(x, y, false, false);

			if (arr_positionscore[x][y] < tmp_doublescore)//如果最后这个位置打分比前一次打分还低，就用最高的打分值
				arr_positionscore[x][y] = tmp_doublescore;
		}
			
	}
	x = position1.getX();
	y = position1.getY();
	for (int i = 0; i < 5; i++)
	{
		//向左下找
		y--;
		x++;
		if (x >= BOARD_DIMENSION || y < 0)
			break;//越界
		if (arr_havechess[x][y] == 1)
			//已经有棋子了，就不用打分了，0分
			arr_positionscore[x][y] = blankPositionScore(x, y, true, false);
		else
		{
			tmp_doublescore = 0;
			if (arr_positionscore[x][y] > 0)
			{//说明对它打分过，取两次打分最高值
				tmp_doublescore = arr_positionscore[x][y];
				arr_positionscore[x][y] = 0;
			}

			arr_positionscore[x][y] = blankPositionScore(x, y, false, false);

			if (arr_positionscore[x][y] < tmp_doublescore)//如果最后这个位置打分比前一次打分还低，就用最高的打分值
				arr_positionscore[x][y] = tmp_doublescore;
		}
			
	}
	x = position1.getX();
	y = position1.getY();
	for (int i = 0; i < 5; i++)
	{
		//向左上找
		y--;
		x--;
		if (x < 0 || y < 0)
			break;//越界
		if (arr_havechess[x][y] == 1)
			//已经有棋子了，就不用打分了，0分
			arr_positionscore[x][y] = blankPositionScore(x, y, true, false);
		else
		{
			tmp_doublescore = 0;
			if (arr_positionscore[x][y] > 0)
			{//说明对它打分过，取两次打分最高值
				tmp_doublescore = arr_positionscore[x][y];
				arr_positionscore[x][y] = 0;
			}

			arr_positionscore[x][y] = blankPositionScore(x, y, false, false);

			if (arr_positionscore[x][y] < tmp_doublescore)//如果最后这个位置打分比前一次打分还低，就用最高的打分值
				arr_positionscore[x][y] = tmp_doublescore;
		}
			
	}
	x = position1.getX();
	y = position1.getY();
	for (int i = 0; i < 5; i++)
	{
		//向右下找
		y++;
		x++;
		if (x >= BOARD_DIMENSION || y >= BOARD_DIMENSION)
			break;//越界
		if (arr_havechess[x][y] == 1)
			//已经有棋子了，就不用打分了，0分
			arr_positionscore[x][y] = blankPositionScore(x, y, true, false);
		else
		{
			tmp_doublescore = 0;
			if (arr_positionscore[x][y] > 0)
			{//说明对它打分过，取两次打分最高值
				tmp_doublescore = arr_positionscore[x][y];
				arr_positionscore[x][y] = 0;
			}

			arr_positionscore[x][y] = blankPositionScore(x, y, false, false);

			if (arr_positionscore[x][y] < tmp_doublescore)//如果最后这个位置打分比前一次打分还低，就用最高的打分值
				arr_positionscore[x][y] = tmp_doublescore;
		}
			
	}
	//遍历完了，打分完毕
}

CPosition CChessBoard::getMaxScorePosition()
{
	CPosition bestPosition;//最佳位置
	CPosition position;
	int maxScore = -1;
	if (m_currentchess)
	{//我是黑子
		if (vec_black_chess.size() == 0)
		{
			//我是第一个下的
			bestPosition.setX(7);//选个靠中间的位置
			bestPosition.setY(7);
			return bestPosition;//刚开始下棋，位置可以随意点
		}
		else
		{//不是第一步，这里要给各位置打分了
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
	{//我是白子
		if (vec_white_chess.size() == 0)
		{
			//黑子先下了，我是第一次下
			position = vec_black_chess[0];
			if (position.getX() + 1 >= BOARD_DIMENSION)//如果越界了换对面位置
			{
				bestPosition.setX(position.getX() - 1);
				bestPosition.setY(position.getY());
				return bestPosition;//刚开始下棋，位置可以随意点
			}
			else
			{
				bestPosition.setX(position.getX() + 1);
				bestPosition.setY(position.getY());
				return bestPosition;//刚开始下棋，位置可以随意点
			}

		}
		else
		{//不是第一步，这里要给各位置打分了
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
{//是不是活三
	/**
	先把这个子放上，判断再加一个是不是活四
	*/
	int havechess, chessposition;//先保存这个信息，后面用于还原
	if (currentChess)
	{
		havechess = arr_havechess[xx][yy];
		chessposition = arr_position[xx][yy];//保存信息


		if (windowType == 1)
		{//上下窗口
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
		{//左右窗口
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
		{//左下右上
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
		{//左上右下
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
{//是不是活四，用大小为6的窗口检测
	//滑动窗口内四个连续的棋子，两侧的两个是空

	if (currentChess)
	{
		//纵向滑动，以xx yy 为最下面棋子
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
		//横向滑动，先 以xx yy为最左边的棋子
		//就四种情况，枚举吧
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

		//左下右上
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
		//左上右下
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

		//后悔没好好考虑一下循环了
		//没想出怎么循环
		//枚举起来好累
		return false;//上面的情况都没有
	}
	else
		return false;
	
}

bool CChessBoard::isDoubleThree(int xx, int yy, bool currentChess)
{//是不是双活三
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
{//是不是双活四
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
	int chessNum = 0;//连子数
	if (currentChess)
	{
		//这个位置是黑子
		//********************************************
		// 1 判断纵向 上下长连
		// 1.1 向上
		for (int i = 1; i < 6; i++)//找五个位置就够了
		{
			if (xx - i  >= 0 && arr_position[xx - i][yy] == 9)
			{
				//没越界，且是黑子
				chessNum++;
			}
			else
				break;
		}
		//1.2 向下
		for (int i = 1; i < 6; i++)
		{
			if (xx + i < BOARD_DIMENSION && arr_position[xx + i][yy] == 9)
			{
				//向下没越界，且是黑子
				chessNum++;
			}
			else
				break;
		}
		if (chessNum >= 5)//大于等于5，加上这个位置的就一定大于5了，是长连禁手
			return true;
		chessNum = 0;


		//********************************************
		// 2 判断横向 左右长连
		// 2.1 向左
		for (int i = 1; i < 6; i++)//找五个位置就够了
		{
			if (yy - i >= 0 && arr_position[xx ][yy - i] == 9)
			{
				//没越界，且是黑子
				chessNum++;
			}
			else
				break;
		}
		//2.2 向右
		for (int i = 1; i < 6; i++)
		{
			if (yy + i < BOARD_DIMENSION && arr_position[xx ][yy + i] == 9)
			{
				//向下没越界，且是黑子
				chessNum++;
			}
			else
				break;
		}
		if (chessNum >= 5)//大于等于5，加上这个位置的就一定大于5了，是长连禁手
			return true;
		chessNum = 0;


		//********************************************
		// 3 判断左下右上长连
		// 3.1 向左下
		for (int i = 1; i < 6; i++)//找五个位置就够了
		{
			if (yy - i >= 0 && xx + i < BOARD_DIMENSION && arr_position[xx + i][yy - i] == 9)
			{
				//没越界，且是黑子
				chessNum++;
			}
			else
				break;
		}
		//3.2 向右上
		for (int i = 1; i < 6; i++)
		{
			if (xx - i >= 0 && yy + i < BOARD_DIMENSION && arr_position[xx - i][yy + i] == 9)
			{
				//向下没越界，且是黑子
				chessNum++;
			}
			else
				break;
		}
		if (chessNum >= 5)//大于等于5，加上这个位置的就一定大于5了，是长连禁手
			return true;
		chessNum = 0;



		//********************************************
		// 4 判断左上右下长连
		// 4.1 向左上
		for (int i = 1; i < 6; i++)//找五个位置就够了
		{
			if (yy - i >= 0 && xx - i >= 0 && arr_position[xx - i][yy - i] == 9)
			{
				//没越界，且是黑子
				chessNum++;
			}
			else
				break;
		}
		//4.2 向右下
		for (int i = 1; i < 6; i++)
		{
			if (xx + i < BOARD_DIMENSION && yy + i < BOARD_DIMENSION && arr_position[xx + i][yy + i] == 9)
			{
				//向下没越界，且是黑子
				chessNum++;
			}
			else
				break;
		}
		if (chessNum >= 5)//大于等于5，加上这个位置的就一定大于5了，是长连禁手
			return true;
		chessNum = 0;



		//如果上面几种情况都没有
		return false;//没有长连禁手
	}
	else
	{
		//这个位置是白子
		return false;//白子不禁手
	}
}

bool CChessBoard::isForbidden(bool currentChess, CPosition position)
{
	if (currentChess)
	{
		//是黑子，有禁手
		if (isDoubleThree(position.getX(), position.getY(), currentChess))
			return true;
		if (isDoubleFour(position.getX(), position.getY(), currentChess))
			return true;
		if (isLongString(position.getX(), position.getY(), currentChess))
			return true;
		return false;
	}
	else
		return false;//白子没有禁手
}

bool CChessBoard::checkVectorIsEmpty()
{
	if (!vec_black_chess.empty() && !vec_white_chess.empty())
		return true;
	else
		return false;
}
