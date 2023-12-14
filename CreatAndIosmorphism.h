#define ll long long
#include<iostream>
#include<vector>
#include<queue>
using namespace std;
struct Edge
{
	ll Begin, End, Key;
	Edge(ll input_Begin, ll input_End, ll input_Key) :Begin(input_Begin), End(input_End), Key(input_Key) {};


	bool operator==(const Edge& e)const
	{
		return (Begin == e.Begin && End == e.End && Key == e.Key);
	}
};


struct Compare
{
	bool operator()(const Edge e1, const Edge e2)
	{
		return e1.Key < e2.Key;
	}
};
class CreateMST
{
private:
	ll V, E;
	vector<Edge> Edges;
	vector<Edge> MST;

	ll FindParent(ll i, vector<ll>& Parent);
	void Union(ll BeginParent, ll EndParent, vector<ll>& Parent, vector<ll>& Rank);//辅助构建MST（并查集）
	void Kruskal(vector<Edge> &Edges, ll V, ll E);
public:
	CreateMST(ll input_V, ll input_E) :V(input_V), E(input_E) {};
	void InputEdges(ll Begin, ll End, ll Key);
	void Kruskal() { Kruskal(Edges, V, E); };
	vector<Edge> GetMST() { return MST; };
	vector<Edge> GetEdges() { return Edges; };

};
class Iosmorphism
{
private:
	ll V, E;
	vector<Edge> MST;
	vector<Edge> Edges;
	vector<vector<Edge>> IosList;
	ll PrintCount;

	ll GetEdgePosInEdges(ll i);
	ll FindParent(ll i, vector<ll>& Parent);
	void Union(ll BeginParent, ll EndParent, vector<ll>& Parent, vector<ll>& Rank);//辅助构建MST（并查集）
	bool IsReat(vector<Edge> ChangedMST);
	bool AreEqualGraphs(vector<Edge>MST1, vector<Edge>MST2);
	void CutAndAddEdge(ll CutPos);
	bool IsMST(vector<Edge> ChangedMST);
	void printMST(vector<Edge> MST);
public:
	Iosmorphism(ll input_V, ll input_E, vector<Edge> Input_MST, vector<Edge> Input_Edges) :V(input_V), E(input_E),MST(Input_MST), PrintCount(0), Edges(Input_Edges) {IosList.push_back(MST);};
	void FindIosmorphism();

};