#include <iostream>
#include <list>
using namespace std;

class Point
{
public:
	Point(int a = 0, int b = 0)
	{
		x = a;
		y = b;
	}

	void Change(int a, int b)
	{
		x += a;
		y += b;
	}

	bool operator ==(Point temp)
	{
		if (x == temp.x&&y == temp.y)
			return true;
		else
			return false;
	}

	Point operator =(Point temp)
	{
		Point pt(temp.x, temp.y);
		return pt;
	}

	int x;
	int y;
};

#define mapsize 4
#define mapwidth 4
#define mapheight 4
int num = 0;
bool beg = true;
Point temp1;
list <Point> roads;
int jump[8][2] = { {2,1},{1,2},{-1,2},{-2,1},{-2,-1},{-1,-2},{1,-2},{2,-1} };

bool In(Point horse)
{
	if ((horse.x < mapwidth&&horse.x>=0) && (horse.y < mapheight&&horse.y>=0))
		return true;
	else
		return false;
}

void PrintRoads(list <Point> roads)
{
	for (list <Point>::iterator it = roads.begin(); it != roads.end(); it++)
	{
		cout << "(" << it->x + 1 << "," << it->y + 1 << ") ";
	}
}

int Jump(Point horse,Point temp,int _x,int _y,int points[][mapheight])
{
	horse.Change(_x, _y);

	if (In(horse) == false)
	{
		horse.Change(-_x, -_y);
		return 1;
	}
	if (horse == temp1)
	{
		horse.Change(-_x, -_y);
		return 1;
	}
	else
		temp1 = horse;
	if (beg == false && horse == temp)
	{
		num++;
		cout << "road:" << num << " ";
		PrintRoads(roads);
		cout << "(" << temp.x + 1 << "," << temp.y + 1 << ")" << endl;
		horse.Change(-_x, -_y);
		return 0;
	}
	if (points[horse.x][horse.y] == 1)
	{
		horse.Change(-_x, -_y);
		return 1;
	}
	else
		points[horse.x][horse.y] = 1;

	beg = false;
	roads.push_back(horse);

	for (int i = 0; i < 8; i++)
	{
		int points1[mapwidth][mapheight];
		for (int x = 0; x < mapwidth; x++)
			for (int y = 0; y < mapheight; y++)
				points1[x][y] = points[x][y];
		Jump(horse, temp, jump[i][0], jump[i][1],points1);
	}

	roads.pop_back();
	horse.Change(-_x, -_y);
	return 0;
}

int main()
{
	int width, height, posw, posh;
	cout<<"Input maze size"<<endl;
	cin>>width;
	cin>>height;
	//mapwidth = width;
	//mapheight = height;
	cout<<"Input point position:"<<endl;
	cin>>posw;
	cin>>posh;
	Point horse(posh, posw);
	Point temp = horse;
	temp1 = horse;
	int points[mapwidth][mapheight] = { 0 };
	Jump(horse, temp, 0, 0, points);
    return 0;
}

