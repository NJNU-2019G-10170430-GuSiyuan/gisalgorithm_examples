#include <iostream>
#include <list>
using namespace std;

class Work
{
public:
	Work(int I,int t,int l,int v)
	{
		ID = I;
		time = t;
		limit = l;
		value = v;
	}

	int ID;
	int time;
	int limit;
	int value;
};

list <Work> works;
list <int> result;
bool used[4] = { false };
int value_rest;
int value_rest_temp;

int num_true(bool uesd[4])
{
	int i;
	int j = 0;
	for (i = 0; i < 4; i++)
	{
		if (used[i] == false)
			j++;
	}
	return j;
}

int order(list<Work> works,int value_all,int time_all)
{
	int time_temp;
	int time;
	int temp=0;
	list<Work>::iterator it;
	for (it=works.begin();it!=works.end();it++)
	{
		if (used[(it->ID)-1]== true)
			break;
		value_rest_temp = value_all - (it->value);
		time_temp = (time_all + (it->time));
		if (time_temp > (it->limit))
			break;
		if (value_rest_temp < value_rest)
		{
			value_rest = value_rest_temp;
			temp = it->ID;
			time = time_temp;
		}
	}
	it = works.begin();
	if (temp != 0)
	{
		result.push_back(temp);
		for (int i = 0; i != (temp - 1); i++, it++);
		used[(it->ID)-1] = true;
	}
	else
		return 0;
	int num = num_true(used);
	if (num == 1)
	{
		for (int i=0;i<4;i++)
		{
			if (used[i] == false)
				result.push_back(i + 1);
		}
		return 0;
	}
	else
		order(works, value_rest, time);
}

int main()
{
	cout<<"Input number of work"<<endl;
	int n;
	cin>>n;
	int value_all;
	for (int i = 0; i < n; i++) {
		int a,b,c;
		cout<<"Input the time, limit, produce of the work"<<i<<endl;
		cin>>a;
		cin>>b;
		cin>>c;
		Work w(i+1, a, b, c);
		works.push_back(w);
		value_all += c;
	}
	//Work w1(1, 4, 10, 2);
	//Work w2(2, 3, 8, 3);
	//Work w3(3, 2, 4, 3);
	//Work w4(4, 1, 2, 6);
	//works.push_back(w1);
	//works.push_back(w2);
	//works.push_back(w3);
	//works.push_back(w4);
	value_rest = value_all;
	order(works,value_all,0);
	list<int>::iterator it;
	for (it = result.begin(); it != result.end(); it++)
		cout << *it<<" ";
    return 0;
}

