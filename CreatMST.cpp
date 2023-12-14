#include"CreatAndIosmorphism.h"
#include<algorithm>
using namespace std;
Compare CompareKey;
void CreateMST::InputEdges(ll Begin, ll End, ll Key)
{
	Edges.push_back(Edge(Begin, End, Key));
}
ll CreateMST::FindParent(ll i, vector<ll>& Parent)
{
	if (Parent[i] == -1)
		return i;
	return FindParent(Parent[i], Parent);
}
void CreateMST::Union(ll BeginParent, ll EndParent, vector<ll>& Parent, vector<ll>& Rank)
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
}

void CreateMST::Kruskal(vector<Edge>& Edges, ll V, ll E)
{
	sort(Edges.begin(), Edges.end(), CompareKey);//排序以便于贪心算法
	vector<ll> Parent(V + 1, -1);
	vector<ll> Rank(V + 1, 0);

	ll EdgeCount = 0;
	ll index = 0;
	while (EdgeCount < V - 1 && index < E)
	{
		Edge e = Edges[index];


		ll BeginParent = FindParent(e.Begin, Parent);
		ll EndParent = FindParent(e.End, Parent);

		if (BeginParent != EndParent)
		{
			Union(BeginParent, EndParent, Parent, Rank);
			MST.push_back(e);
			EdgeCount++;
		}

		index++;
	}

	sort(MST.begin(), MST.end(), CompareKey);//排序以便于后续的找同构操作

}