#include <bits/stdc++.h>
#define LL_INF 10000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

struct QEntry {
  int node_init;
  int node_rev;
  str s;
  bool is_move_rev;
};

struct Rel {
  int dest;
  char c;
};

struct Node {
  vec<Rel> rels;
};

vec<Node> graph_init;
vec<Node> graph_rev;

void bfs(int start, int end) {
  queue<QEntry> q;
  q.push({start, end, "", false});

  while (!q.empty())
  {
    auto [node_init, node_rev, s, is_move_rev] = q.front();
    q.pop();

    if(is_move_rev) {
      // if move on reversed graph
      if(node_init == node_rev) {
        cout<<s.size()*2 - 1<<" ";
        for(int i = 0; i < s.size(); i++) {
          cout<<s[i];
        }
        for(int i = s.size() - 2; i >= 0; i--) {
          cout<<s[i];
        }
        cout<<"\n";
        return;
      }

      for(auto rel : graph_rev[node_rev].rels) {
        if(rel.c == s.back()) {
          q.push({node_init, rel.dest, s, false});
        }
      }
    } else {
      // if move on initial graph
      if(node_init == node_rev) {
        cout<<s.size()*2<<" ";
        for(int i = 0; i < s.size(); i++) {
          cout<<s[i];
        }
        for(int i = s.size() - 1; i >= 0; i--) {
          cout<<s[i];
        }
        cout<<"\n";
        return;
      }
      for(auto rel : graph_init[node_init].rels) {
        q.push({rel.dest, node_rev, s + rel.c, true});
      }
    }
  }
  
  cout<<"-1\n";
};

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  int n, m;
  cin>>n>>m;

  graph_init = vec<Node> (n + 1);
  graph_rev = vec<Node> (n + 1);

  while(m--) {
    int from, to;
    char c;
    cin>>from>>to>>c;
    graph_init[from].rels.push_back({to, c});
    graph_rev[to].rels.push_back({from, c});
  }

  int q, cur, prev;
  cin>>q;
  cin>>prev;
  for(int i = 1; i < q; i++) {
    cin>>cur;
    bfs(prev, cur);
    prev = cur;
  }

  cout.flush();
}