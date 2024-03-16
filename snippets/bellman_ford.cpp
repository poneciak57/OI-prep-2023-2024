#include <bits/stdc++.h>
#define LLINF 100000000000000007

using namespace std;
typedef long long ll;
typedef string str;
template <typename T> using vec = vector<T>;


// Bellman-Ford algorithm
// problem: wyznacz najkrótsza scieżke od wierzcholka v do wszystkich pozostałych wierzchołków
// specs: n wierzchołków, m wierzchołków
//
// każda najkrótsza scieżka ma co najwyżej n - 1 krawędzi
// dziala dla ujemnych krawedzi, nie moze istniec ujemny cykl 
//
// Time Complexity O(n * m)


const int INF = 1e9 + 7;
int n, m;

struct Rel { int from; int to; int weight; };
vec<Rel> rels;
vec<int> d;

// false if negative cycle exists
bool BF(int v) {
	for(int i = 0; i <= n; i++) d[i] = INF;
	d[v] = 0;
	for(int i = 1; i < n; i++) {
		for(auto e : rels) {
			if(d[e.to] > d[e.from] + e.weight) {
				d[e.to] = d[e.from] + e.weight;
			}
		}
	}

	for(auto e : rels) if(d[e.to] > d[e.from] + e.weight) return false;

	return true;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	

	cin>>n>>m;
	d = vec<int>(n + 1, INF);
	while(m--) {
		int f, t, w;
		cin>>f>>t>>w;
		rels.push_back({f, t, w});
	}

	if(BF(1)) {
		for(auto a : d) cout<<a<<" ";
		cout<<"\n";
		cout<<"Brak ujemnego cyklu";
	} else {
		cout<<"Ujemny cykl";
	}
	

	cout.flush();
	return 0;
}