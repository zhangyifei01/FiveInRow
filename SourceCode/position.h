#pragma once
class CPosition
{
public:
	CPosition();
	~CPosition();

	void setX(int xx);
	void setY(int yy);
	int getX();
	int getY();
private:
	int m_x;
	int m_y;
};

