#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

const int NODES_COUNT = 100001;
// const int NODES_COUNT = 11;

struct Node {
  vec<int> rels;
};

vec<int> primes;
vec<bool> sito(NODES_COUNT, true);
vec<Node> graph(NODES_COUNT);

void prepare_sito() {
  sito[0] = false;
  sito[1] = false;
  // primes.push_back(1); // maybe comment this out
  for(int i = 2; i < NODES_COUNT; i++) {
    if(!sito[i]) continue;
    primes.push_back(i);
    for(int j = i + i; j < NODES_COUNT; j += i) {
      sito[j] = false;
    }
  }
  primes.push_back(1e6 + 7);
}

void prepare_graph() {
  for(int i = 0; i < NODES_COUNT; i++) {
    int p_ind = 0;
    if(sito[i]) {
      graph[i].rels.push_back(1);
      graph[1].rels.push_back(i);
    }
    while(primes[p_ind] * primes[p_ind] <= i) {
      if(i % primes[p_ind] == 0) {
        int divided = i / primes[p_ind];
        if(sito[divided] && divided != primes[p_ind]) {
          graph[i].rels.push_back(primes[p_ind]);
          graph[primes[p_ind]].rels.push_back(i);
        }
        graph[i].rels.push_back(divided);
        graph[divided].rels.push_back(i);
      }
      p_ind++;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  prepare_sito();
  prepare_graph();

  // for(int i = 1; i < NODES_COUNT; i++) {
  //   cout<<i<<": ";
  //   for(auto r : graph[i].rels) {
  //     cout<<r<<" ";
  //   }
  //   cout<<"\n";
  // }

  vec<int> ds(NODES_COUNT, INT_MAX); // odleglosc
  vec<int> ms(NODES_COUNT, -1); // poprzedni wierzcholek
  queue<int> q;

  int n;
  cin>>n;

  vec<int> S(n);

  for(int i = 0, t; i < n; i++) {
    cin>>t;
    ds[t] = 0;
    ms[t] = t;
    S[i] = t; 
    q.push(t);
  }

  while(!q.empty()) {
    int v = q.front();
    q.pop();
    for(auto w : graph[v].rels) {
      if(ds[w] == INT_MAX) {
        ds[w] = ds[v] + 1;
        ms[w] = ms[v];
        q.push(w);
      } else if(ds[v] + 1 == ds[w] && ms[v] < ms[w]) {
        ms[w] = ms[v];
      }
    }
  }

  vec<int> dsv(NODES_COUNT, INT_MAX);
  vec<int> msv(NODES_COUNT, -1);
  for(int vp = 1; vp < graph.size(); vp++) {
    for(auto wp : graph[vp].rels) {
      int v = ms[vp];
      int w = ms[wp];
      if(v != w) {
        int d = ds[vp] + 1 + ds[wp];
        if(d < dsv[v] || (d == dsv[v] && w < msv[v])) {
          dsv[v] = d;
          msv[v] = w;
        }
      }
    }
  }

  for(auto v : S) {
    cout<<msv[v]<<"\n";
  }

  cout.flush();
}
