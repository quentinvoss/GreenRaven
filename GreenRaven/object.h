#pragma once
class object {
private:
	int x = 0;
	int y = 0;
	int scale = 4;
public:
	int getX();
	int getY();
	void setX(int s);
	void setY(int s);
	int getScale();
};