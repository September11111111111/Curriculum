#include"CreatAndIosmorphism.h"
#include<unordered_set>
ll Iosmorphism::GetEdgePosInEdges(ll i)
{
	ll Key=MST[i].Key;
	for (int j = 0; j < Edges.size(); j++)
	{
		if (Edges[j].Key == Key)
			return j;
	}
}
void Iosmorphism::printMST(vector<Edge> MST)
{
	size_t sum = 0;
	cout << "第" << PrintCount + 1 << "颗最小生成树为：";
	PrintCount++;
	for (ll i = 0; i < MST.size(); i++)
	{
		cout << "(" << MST[i].Begin << "," << MST[i].End << ")" << " ";
		sum += MST[i].Key;
	}
	cout << endl;
	cout << "weight:" << sum << endl;
}
ll Iosmorphism::FindParent(ll i, vector<ll>& Parent)
{
	if (Parent[i] == -1)
		return i;
	return FindParent(Parent[i], Parent);
}//并查集find操作
void Iosmorphism::Union(ll BeginParent, ll EndParent, vector<ll>& Parent, vector<ll>& Rank)
{
	if (Rank[BeginParent] > Rank[EndParent])
		Parent[EndParent] = BeginParent;
	else if (Rank[BeginParent] < Rank[EndParent])
		Parent[BeginParent] = EndParent;
	else
	{
		Parent[BeginParent] = EndParent;
		Rank[EndParent]++;
	}
}//并查集合并操作
bool Iosmorphism::IsMST(vector<Edge> ChangedMST)
{
	vector<ll> Parent(V + 1, -1);
	vector<ll> Rank(V + 1, 0);
	for (int i = 0; i < V-1; i++)
	{
		ll BeginParent = FindParent(ChangedMST[i].Begin, Parent);
		ll EndParent = FindParent(ChangedMST[i].End, Parent);
		if (BeginParent == EndParent)
			return false;
		Union(BeginParent, EndParent, Parent, Rank);
	}//用并查集创建Parent数组
	ll ParentOfOne = FindParent(Parent[1], Parent);
	for (int i = 2; i < V; i++)
	{
		ll TempParent = FindParent(i, Parent);
		if (TempParent != ParentOfOne)
			return false;
	}//查找根节点是否相同，相同则说明图为连通图
	return true;
}
bool Iosmorphism::AreEqualGraphs(vector<Edge>MST1, vector<Edge>MST2)
{
		for (const Edge& edge1 : MST1) {
			bool found = false;
			for (const Edge& edge2 : MST2) {
				if (edge1 == edge2) {
					found = true;
					break;
				}
			}
			if (!found) {
				return false;
			}
		}
	return true;
}//MST1与MST2相等与否
bool Iosmorphism::IsReat(vector<Edge> ChangedMST)
{
	for (int i = 0; i < IosList.size(); i++)
	{
		if (AreEqualGraphs(ChangedMST, IosList[i]))
			return true;
	}//检查与之前图是否出现重复
	return false;
}
void Iosmorphism::CutAndAddEdge(ll CutPos)
{
	ll PosInEdges = GetEdgePosInEdges(CutPos);//获取MST中与第i条边Key值相同的第一个位置在Edges中的位置
	ll IosLength = IosList.size();//第CutPos次未添加边时候的大小

	for (ll i = 0; i < IosLength; i++)
	{
		ll KeyOfCutEdge = IosList[i][CutPos].Key;//被剪掉边的Key值

		vector<Edge> TempToCut= IosList[i];//被剪掉边对应的同构树

		for (ll CurrPos = PosInEdges; CurrPos < E && Edges[CurrPos].Key == KeyOfCutEdge; CurrPos++)
		{
			if (Edges[CurrPos] == IosList[i][CutPos])//为本身的时候不进行检验
				continue;

			TempToCut[CutPos] = Edges[CurrPos];//替换掉对应的边

			if (IsMST(TempToCut) && !IsReat(TempToCut))//如果替换后的树不能达到所有节点或与之前图重复
			{
				printMST(TempToCut);
				IosList.push_back(TempToCut);
			}

		}

	}
	return;

}

void Iosmorphism::FindIosmorphism()
{
	printMST(MST);//打印第一颗最小生成树
	for (int i = 0; i < MST.size(); i++)
	{
		CutAndAddEdge(i);//替换生成树中第i个位置
	}

	cout << "一共有" << PrintCount << "颗MST" << endl;//寻找完成后输出一共有多少颗生成树
}
