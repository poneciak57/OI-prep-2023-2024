#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

const ll MOD1 = 1e9 + 7;
const ll MOD2 = 1000992299;

ll powm(ll a, ll n, ll MOD);
ll multm(ll a, ll b, ll MOD);
ll divm(ll a, ll b, ll MOD);

inline int rand_range(int from, int to) {
  return (rand() % (to - from + 1)) + from;
}

struct Node {
  int sss {-1};
  vec<int> rels;
};

vec<Node> graph;
vec<vec<int>> rev_graph;

vec<bool> visited;
vec<int> order;

void dfs(int v) {
  if(visited[v]) return;
  visited[v] = true;

  for(auto e : graph[v].rels) {
    dfs(e);
  }
  order.push_back(v);
}

void set_sss(int v, int sss) {
  if(graph[v].sss != -1) return;
  graph[v].sss = sss;
  for(auto e : rev_graph[v]) {
    set_sss(e, sss);
  }
}


int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);
  srand(time(nullptr));

  int n, k, m;
  cin>>n>>k;

  graph = vec<Node>(n + 1);
  rev_graph = vec<vec<int>>(n + 1);

  while(k--) {
    int a, b;
    cin>>a>>b;
    graph[a].rels.push_back(b);
    rev_graph[b].push_back(a);
  }

  visited = vec<bool>(n + 1, false);

  for(int i = 1; i <= n; i++) {
    dfs(i);
  }

  int sss = 1;
  for(int i = order.size() - 1; i >= 0; i--) {
    if(graph[order[i]].sss == -1) {
      // cout<<"starting sss at "<<order[i]<<"\n";
      set_sss(order[i], sss);
      sss++;
    }
  }

  // for(int i = 1; i <= n; i++) {
  //   cout<<"node: "<<i<<"  sss: "<<graph[i].sss<<"\n";
  // }

  cout<<sss - 1<<"\n";
  cin>>m;
  while(m--) {
    int a, b;
    cin>>a>>b;
    if(a > n || b > n) {
      cout<<"SCAM\n";
      break;
    }
    if(graph[a].sss == graph[b].sss) {
      cout<<"TAK\n";
    } else {
      cout<<"NIE\n";
    }
  }

  

  cout.flush();
}





ll powm(ll a, ll n, ll MOD) {
  ll w = 1;

  while (n > 0) {
    if (n % 2 == 1)
      w = (w * a) % MOD;
      a = (a * a) % MOD;
      n /= 2;
  }
  return w;
}

ll multm(ll a, ll b, ll MOD) {
  return (a * b) % MOD;
}

ll divm(ll a, ll b, ll MOD) {
  return multm(a, powm(b, MOD - 2, MOD), MOD);
}