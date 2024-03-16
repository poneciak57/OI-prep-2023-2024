#include <bits/stdc++.h>
#define LLINF 100000000000000007

using namespace std;
typedef long long ll;
typedef string str;
template <typename T> using vec = vector<T>;

/**
 * Jak wyznaczyc najwiekszy zestaw skojarzen w grafie dwudzielnym
 * Time Complexity: O(n * m)
 * 
 * 
 * 
 * Teoria
 * MATCHING - skojarzenie w grafie
 * MVC - minimal vertex cover
 * MIS - maximal independent set
 * 
 * Jesli ilosc krawedzi maksymalnego skojarzenia okreslimy jako S to:
 * - MIS lb >= n - S
 * - MVC = S
*/

const int LIM = 1e5 + 7;
vec<int> graph[LIM];
int L, R, M;
bool odwiedzony[LIM]; // odwiedzony z lewej strony
int matching[LIM]; // indeks skojarzonego wierzcholka dla prawego do lewego
bool skojarzony[LIM]; // czy dany wierzcholek lewy jest skojarzony

bool DFS(int v) {
	if(odwiedzony[v]) return false;
	odwiedzony[v] = true;
	for(auto e : graph[v]) {
		if(matching[e] == -1 || DFS(matching[e])) {
			matching[e] = v;
			return true;
		}
	}
	return false;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin>>L>>R>>M;
	while(M--) {
		int a, b;
		cin>>a>>b;
		graph[a].push_back(b);
	}

	for(int i = 0; i < LIM; i++) matching[i] = -1;
	
	while(true) {
		for(int i = 0; i < L; i++) odwiedzony[i] = 0;
		bool ok = false;
		for(int i = 0; i < L; i++) {
			if(!odwiedzony[i] && !skojarzony[i]) {
				if(DFS(i)) {
					skojarzony[i] = true;
					ok = true;
					break;
				}
			}
		}
		if(!ok) break;
	}

	vec<pair<int,int>> ans;
	for(int i = 0; i < R; i++) {
		if(matching[i] != -1) {
			ans.push_back({matching[i], i});
		}
	}

	cout<<ans.size()<<"\n";
	for(auto a : ans) {
		cout<<a.first<<" "<<a.second<<"\n";
	}


	cout.flush();
	return 0;
}