#include <bits/stdc++.h>
#define LLINF 100000000000000007

using namespace std;
typedef long long ll;
typedef string str;
template <typename T> using vec = vector<T>;


// Floyd-Waschall
// problem: wyznaczenie długości najkrótszej sciezki między każdą parą wierzchołków
// d[i][j] - długość najkrótszej ścieżki od i do j
// początkowo: 
// - d[i][i] = 0
// - d[i][j] = w[ij] (jesli w grafie istnieje krawedz od i do j)
// - d[i][j] = INF (jeśli nie powyższe)


const int INF = 1e9 + 7;
int n, m;
vec<vec<int>> d;


void FW() {
	for(int u = 1; u <= n; u++) {
		for(int v1 = 1; v1 <= n; v1++) {
			for(int v2 = 1; v2 <= n; v2++) {
				if(d[v1][v2] > d[v1][u] + d[u][v2])
					d[v1][v2] = d[v1][u] + d[u][v2];
			}
 		}
	}
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	

	cin>>n>>m;
	d = vec<vec<int>>(n + 1, vec<int>(n + 1, INF));
	for(int i = 0; i <= n; i++) d[i][i] = 0;
	while(m--) {
		int f, t, w;
		cin>>f>>t>>w;
		d[f][t] = w;
	}

	FW();
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			cout<<d[i][j]<<" ";
		}
		cout<<"\n";
	}

	cout.flush();
	return 0;
}