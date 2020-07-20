# Game Rules

Hello, welcome to my game, you need to follow the following rules:

1. Black is first;
2. There are two rounds to play, **winner** get **2** points, **loser** get **0** point, and **1** point for other state;
3. You can choose **person** *vs.* **person** or **person** *vs.* **AI**;
4. If you choose  **person** *vs.* **AI**, then choose person first or AI first;
5. If the considered time exceeds **15s**, it is judged as a loser.

# Development Environment
1. **Visual Studio 2015**
2. **Windows10 64bit**

# Chessboard Design
1. #define BOARD_DIMENSIN 15
The size of checkerboard is 15*15

![Chessboard Design](https://img-blog.csdnimg.cn/2020072023171333.png)
# Involved Classes
1. **Chessboard Class:** CChessBoard
2. **Position Class:** CPosition
3. **Monitor Class:** CMonitor
4. **Player Class:** CChessPlayer
5. **AI Class:** CAIPlayer
6. **Timer Class:** CTimer

# AI Scoring Strategy
![AI scoring strategy](https://img-blog.csdnimg.cn/20200720232245396.png)

