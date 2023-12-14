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
	cout << "��" << PrintCount + 1 << "����С������Ϊ��";
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
}//���鼯find����
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
}//���鼯�ϲ�����
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
	}//�ò��鼯����Parent����
	ll ParentOfOne = FindParent(Parent[1], Parent);
	for (int i = 2; i < V; i++)
	{
		ll TempParent = FindParent(i, Parent);
		if (TempParent != ParentOfOne)
			return false;
	}//���Ҹ��ڵ��Ƿ���ͬ����ͬ��˵��ͼΪ��ͨͼ
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
}//MST1��MST2������
bool Iosmorphism::IsReat(vector<Edge> ChangedMST)
{
	for (int i = 0; i < IosList.size(); i++)
	{
		if (AreEqualGraphs(ChangedMST, IosList[i]))
			return true;
	}//�����֮ǰͼ�Ƿ�����ظ�
	return false;
}
void Iosmorphism::CutAndAddEdge(ll CutPos)
{
	ll PosInEdges = GetEdgePosInEdges(CutPos);//��ȡMST�����i����Keyֵ��ͬ�ĵ�һ��λ����Edges�е�λ��
	ll IosLength = IosList.size();//��CutPos��δ��ӱ�ʱ��Ĵ�С

	for (ll i = 0; i < IosLength; i++)
	{
		ll KeyOfCutEdge = IosList[i][CutPos].Key;//�������ߵ�Keyֵ

		vector<Edge> TempToCut= IosList[i];//�������߶�Ӧ��ͬ����

		for (ll CurrPos = PosInEdges; CurrPos < E && Edges[CurrPos].Key == KeyOfCutEdge; CurrPos++)
		{
			if (Edges[CurrPos] == IosList[i][CutPos])//Ϊ�����ʱ�򲻽��м���
				continue;

			TempToCut[CutPos] = Edges[CurrPos];//�滻����Ӧ�ı�

			if (IsMST(TempToCut) && !IsReat(TempToCut))//����滻��������ܴﵽ���нڵ����֮ǰͼ�ظ�
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
	printMST(MST);//��ӡ��һ����С������
	for (int i = 0; i < MST.size(); i++)
	{
		CutAndAddEdge(i);//�滻�������е�i��λ��
	}

	cout << "һ����" << PrintCount << "��MST" << endl;//Ѱ����ɺ����һ���ж��ٿ�������
}
