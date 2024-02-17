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
  int in{0};
  int time;
  int min_rels_time {0};
  int min_time {0};
  vec<int> rels;
};

vec<Node> graph;
vec<int> toposort;
queue<int> q;

vec<int> state;
bool has_cycle(int v) {
  if(state[v] == 1) return true;
  else if(state[v] == 2) return false;
  bool ret = false;
  state[v] = 1;
  for(auto e : graph[v].rels) {
    ret = ret || has_cycle(e);
  }

  state[v] = 2;
  return ret;
}

void print_graph(int n) {
  for(int i = 1; i <= n; i++) {
    cout<<"#"<<i<<": [ ";
    for(auto e : graph[i].rels) {
      cout<<e<<" ";
    }
    cout<<"]  in: "<<graph[i].in<<" time: "<<graph[i].time<<" mtime: "<<graph[i].min_time<<" mrelstime: "<<graph[i].min_rels_time<<"\n";
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);
  srand(time(nullptr));

  int n, Q;
  cin>>n;
  graph = vec<Node>(n + 1);
  state = vec<int>(n + 1);
  for(int i = 1, time, c, e; i <= n; i++) {
    cin>>time>>c;
    graph[i].time = time;
    while(c--) {
      cin>>e;
      graph[i].in++;
      graph[e].rels.push_back(i);
    }
  }
  
  for(int i = 1; i <= n; i++) {
    if(graph[i].in == 0) q.push(i);
    if(has_cycle(i)) {
      cout<<"CYKL";
      return 0;
    }
  }

  int min_time = 0;
  while(!q.empty()) {
    int v = q.front();
    q.pop();
    toposort.push_back(v);
    if(graph[v].rels.size() == 0) min_time = max(min_time, graph[v].min_time + graph[v].time);

    for(auto e : graph[v].rels) {
      graph[e].in--;
      if(graph[e].in == 0) q.push(e);
      graph[e].min_time = max(graph[e].min_time, graph[v].min_time + graph[v].time);
    }
  }
  cout<<min_time<<"\n";

  for(int i = toposort.size() - 1; i >= 0; i--) {
    int v = toposort[i];
    for(auto e : graph[v].rels) {
      graph[v].min_rels_time = max(graph[v].min_rels_time, graph[e].min_rels_time + graph[e].time);
    }
  }

  // print_graph(n);

  cin>>Q;
  while(Q--) {
    int m, d;
    cin>>m>>d;
    int new_time = graph[m].min_time + graph[m].time + d + graph[m].min_rels_time;
    if(new_time > min_time) {
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