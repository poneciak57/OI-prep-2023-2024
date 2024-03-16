#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

struct Move { char op; int a; int b; };
vec<vec<int>> G;
vec<Move> moves;
vec<pair<int,int>> ans;
vec<pair<int,int>> my_ans;
bitset<30007> vis;

void read();
bool is_ans_ok() {
    for(int i = 0; i < ans.size(); i++) {
        if(ans[i].first != my_ans[i].first || ans[i].second != my_ans[i].second) return false;
    }
    return true;
}
void make_move(int m_id) {
    auto [op, a, b] = moves[m_id];
    if(op == '+') {
        G[a].push_back(b);
        G[b].push_back(a);
    } else {
        G[a].erase(find(G[a].begin(), G[a].end(), b));
        G[b].erase(find(G[b].begin(), G[b].end(), a));
    }
}
void make_moves() {
    for(int i = 0; i < moves.size(); i++) make_move(i);
}
void bfs_get_anses() {
    queue<int> q;
    q.push(1);
    vis[1] = true;
    while(!q.empty()) {
        int v = q.front();
        q.pop();

        for(auto e : G[v]) {
            if(vis[e]) continue;
            vis[e] = true;
            my_ans.push_back({min(e, v), max(e, v)});
            q.push(e);
        }
    }
    sort(my_ans.begin(), my_ans.end());
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  read();
  make_moves();
  bfs_get_anses();

  if(is_ans_ok) {
    cout<<"OK";
  } else {
    cout<<"ERROR";
  }

  cout.flush();
}

void read() {
    ifstream inp("./input.in");
    ifstream out("./output.out");

    int mc;
    out >> mc;
    while(mc--) {
        char op;
        int a, b;
        out >> op >> a >> b;
        moves.push_back({op, a, b});
    }

    int n, m;
    inp >> n;
    inp >> m;
    while(m--) {
        int a, b;
        inp >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    inp >> m;
    while(m--) {
        int a, b;
        inp >> a >> b;
        ans.push_back({min(a, b), max(a, b)});
    }
    sort(ans.begin(), ans.end());
}
