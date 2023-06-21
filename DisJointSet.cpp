#include<iostream>
#include<vector>
using namespace std;

class DisjointSet
{
private:
	vector<int> parent, rank, size;

public:
	// Constructor to initialize the disjoint set with size n
	DisjointSet(int n){
		rank.resize(n+1, 0);
		parent.resize(n+1);
		size.resize(n+1, 1);
		for(int i=0;i<=n;i++) parent[i]=i;
	}

	// Find the representative (root) of the set to which node belongs (with path compression)
	int findUp(int node){
		if(node == parent[node]) return node;
		
		// Path compression by updating the parent of the node
		return parent[node] = findUp(parent[node]);
	}

	// Union two sets based on rank
	void unionByRank(int u, int v){
		if(parent[u] == parent[v]) return;

		int usp = findUp(u); // Find representative of u's set
		int vsp = findUp(v); // Find representative of v's set

		if(rank[usp] > rank[vsp]){
			parent[vsp] = usp; // Set v's representative's parent as u's representative
		}
		else if(rank[vsp] > rank[usp]){
			parent[usp] = vsp; // Set u's representative's parent as v's representative
		}
		else{
			parent[usp] = vsp; // Set u's representative's parent as v's representative
			rank[vsp]++; // Increment the rank of v's representative
		}
	}

	// Union two sets based on size
	void unionBySize(int u, int v){
		if(parent[u] == parent[v]) return;

		int usp = findUp(u); // Find representative of u's set
		int vsp = findUp(v); // Find representative of v's set

		if(size[usp] > size[vsp]){
			parent[vsp] = usp; // Set v's representative's parent as u's representative
			size[usp] += size[vsp]; // Update the size of u's set
		}
		else{
			parent[usp] = vsp; // Set u's representative's parent as v's representative
			size[vsp] += size[usp]; // Update the size of v's set
		}
	}
};

int main(){
	DisjointSet dp(7);

	// UnionByRank Testing
	dp.unionByRank(1,2);
	dp.unionByRank(2,3);
	dp.unionByRank(4,5);
	dp.unionByRank(6,7);
	dp.unionByRank(5,6);

	// Check whether nodes 3 and 7 are in the same component or separate components
	if(dp.findUp(3) == dp.findUp(7)) cout<<"In Same Component\n";
	else cout<<"In Separate Component\n";

	dp.unionByRank(3, 7);

	// Check whether nodes 3 and 7 are in the same component or separate components
	if(dp.findUp(3) == dp.findUp(7)) cout<<"In Same Component\n";
	else cout<<"In Separate Component\n";

	// Same testing, but with UnionBySize
	dp.unionBySize(1,2);
	dp.unionBySize(2,3);
	dp.unionBySize(4,5);
	dp.unionBySize(6,7);
	dp.unionBySize(5,6);

	// Check whether nodes 3 and 7 are in the same component or separate components
	if(dp.findUp(3) == dp.findUp(7)) cout<<"In Same Component\n";
	else cout<<"In Separate Component\n";

	dp.unionBySize(3, 7);

	// Check whether nodes 3 and 7 are in the same component or separate components
	if(dp.findUp(3) == dp.findUp(7)) cout<<"In Same Component\n";
	else cout<<"In Separate Component\n";

	return 0;
}
