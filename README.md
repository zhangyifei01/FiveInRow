# Game FiveInRow (Gobang? Gomoku? Five in a Row)

# How to Play

Hello, welcome to my game, you need to known that:

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

According to my previous position *position1* and others' previous position *position2*, there are **5 points** for each of position on **8 directions**, then scoring every point. If one point has a chess, its score is 0.

For whole 15*15 chessboard, there are 572 5-tuples, the score of scoring point is the sum of all 5-tuples which including this point.

Suppose I'm black, so the scoring situation of the 5-tuple is:
1. Both black and white, scoring 0;
2. Only one black chess, scoring 50;
3. Only two black chesses, scoring 1000;
4. Only three black chesses, scoring 150000;
5. Only four black chesses, scoring 8000000;
6. Only one white chess, scoring 25;
7. Only two white chesses, scoring 500;
8. Only three white chesses, scoring 100000;
9. Only four white chesses, scoring 2000000;
10. No chess in these 5-tuple, scoring 5.

# Forbidden Hands
### 1. Judgment live four
The judgment conditions are four types: horizontal, vertical, diagonal and diagonal, as long as the six board positions satisfy that the two on the most side have no pieces, and the middle four are black pieces.
### 2. Judgment live three
The judgment condition is to judge whether a live four is formed after the piece is put down.
### 3. Three three forbidden hands
Determine if there are more than one live three in each direction.
### 4. Four four forbidden hands
Determine if there are more than one live four in each direction.
### 5. Long chain forbidden hands
After putting down the chess pieces, go up-down, left-right, upper left-lower right, and lower left-upper right to determine if there are more than five consecutive black chess pieces.

# Playing Show
You can see my playing.

![Show1](https://img-blog.csdnimg.cn/20200720235528639.png)

![Show2](https://img-blog.csdnimg.cn/20200720235544918.png)

![Show3](https://img-blog.csdnimg.cn/20200720235627378.png)

