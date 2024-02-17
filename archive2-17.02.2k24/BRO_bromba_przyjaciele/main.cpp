#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

struct Node {
  int max_signal {0};
  vec<int> rels;
};

struct Higher {
  bool operator()(pair<int,int> &p1, pair<int,int> &p2) {
    return p1.first < p2.first;
  }
};

int max_signal = 0;
vec<Node> graph;

// {node, signal}
unordered_map<int, int> maxes;
bool done = true;

void postaw_routery() {
  done = true;
  // {signal, node}
  priority_queue<pair<int,int>, vec<pair<int,int>>, Higher> pq;

  for(auto [node, signal] : maxes) {
    graph[node].max_signal = signal;
    pq.push({signal, node});
  }

  maxes.clear();

  while(!pq.empty()) {
    auto [signal, node] = pq.top();
    pq.pop();

    // if(signal < graph[node].max_signal) continue;
    int nsignal = signal - 1;
    if(nsignal <= 0) continue;

    for(auto rel : graph[node].rels) {
      if(graph[rel].max_signal < nsignal) {
        graph[rel].max_signal = nsignal;
        pq.push({nsignal, rel});
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  cin.tie(nullptr);

  int n, m;
  cin>>n>>m;

  graph = vec<Node>(n + 1);

  while(m--) {
    int a, b;
    cin>>a>>b;
    graph[a].rels.push_back(b);
    graph[b].rels.push_back(a);
  }

  int q;
  cin>>q;

  while(q--) {
    char op;
    cin>>op;
    if(op == '?') {
      if(!done) postaw_routery();
      int v;
      cin>>v;
      std::cout<<graph[v].max_signal<<"\n";
    } else {
      int v, S;
      cin>>v>>S;
      if(graph[v].max_signal >= S) continue;
      done = false;
      maxes[v] = max(maxes[v], S);
    }
  }


  cout.flush();
}
