#include<iostream>
#include<fstream>
#include"CreatAndIosmorphism.h"
using namespace std;

int main()
{
	fstream input("in.txt");
	if (!input.is_open())
	{
		cout << "文件打开出现问题";
		return 0;
	}

	ll V, E;//顶点和边
	input >> V >> E;
	CreateMST MST(V,E);//创建V个顶点E条边的图

	for (ll i = 0; i < E; i++)
	{
		ll Begin, End, Key;
		input >> Begin >> End >> Key;
		MST.InputEdges(Begin, End, Key);
	}//输入顶点和边

	input.close();

	MST.Kruskal();//用Kruskal算法算出第一个最小生成树

	Iosmorphism Ios(V, E, MST.GetMST(), MST.GetEdges());//存储第一颗最小生成树以便于后续寻找
	Ios.FindIosmorphism();//开始寻找刚刚生成的最小生成树的不同构情况

	return 0;
}
