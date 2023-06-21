#include<iostream>
#include<vector>
using namespace std;
class DisjointSet
{
private:
	vector<int> parent, rank, size;

public:
	DisjointSet(int n){
		rank.resize(n+1, 0);
		parent.resize(n+1);
		size.resize(n+1, 1);
		for(int i=0;i<=n;i++) parent[i]=i;
	}

	int findUp(int node){
		if(node == parent[node]) return node;
		
		return parent[node] = findUp(parent[node]);
	}

	void unionByRank(int u, int v){
		if(parent[u] == parent[v]) return;

		int usp = findUp(u);
		int vsp = findUp(v);

		if(rank[usp] > rank[vsp]){
			parent[vsp] = usp;
		}
		else if(rank[vsp] > rank[usp]){
			parent[usp] = vsp;
		}
		else{
			parent[usp] = vsp;
			rank[vsp]++;
		}
	}

	void unionBySize(int u, int v){
		if(parent[u] == parent[v]) return;

		int usp = findUp(u);
		int vsp = findUp(v);

		if(size[usp] > size[vsp]){
			parent[vsp] = usp;
			size[usp]++;
		}
		else{
			parent[usp] = vsp;
			size[vsp]++;
		}
	}
};

int main(){

	DisjointSet dp(7);
	//  UnionByRank

	// dp.unionByRank(1,2);
	// dp.unionByRank(2,3);
	// dp.unionByRank(4,5);
	// dp.unionByRank(6,7);
	// dp.unionByRank(5,6);

	// // Check each of them are part of single component or not (Expected: Not Same)
	// if(dp.findUp(3) == dp.findUp(7)) cout<<"In Same Component\n";
	// else cout<<"In Seperate Component\n";
	// dp.unionByRank(3, 7);
	// // Check each of them are part of single component or not (Expected: In Same)
	// if(dp.findUp(3) == dp.findUp(7)) cout<<"In Same Component\n";
	// else cout<<"In Seperate Component\n";

	//  Same Testing But with UnionBySize
	dp.unionBySize(1,2);
	dp.unionBySize(2,3);
	dp.unionBySize(4,5);
	dp.unionBySize(6,7);
	dp.unionBySize(5,6);

	// Check each of them are part of single component or not (Expected: Not Same)
	if(dp.findUp(3) == dp.findUp(7)) cout<<"In Same Component\n";
	else cout<<"In Seperate Component\n";
	dp.unionBySize(3, 7);
	// Check each of them are part of single component or not (Expected: In Same)
	if(dp.findUp(3) == dp.findUp(7)) cout<<"In Same Component\n";
	else cout<<"In Seperate Component\n";

}











