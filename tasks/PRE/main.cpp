#include <bits/stdc++.h>
#define INF 1000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

struct Node {
  char c;
  int left{ -1 };
  int right{ -1 };
};

str pre, in;
vec<Node> tree;

int ind_pre = 0;

void solve(int s, int e, int parrent_id, bool left) {
  // przedzial jest pusty
  if(s > e) {
    return;
  }

  int new_node_id = tree.size();
  tree.push_back({pre[ind_pre]});
  if(left) {
    tree[parrent_id].left = new_node_id;
  } else {
    tree[parrent_id].right = new_node_id;
  }
  ind_pre++;

  for(int i = s; i <= e; i++) {
    if(in[i] == tree[new_node_id].c) {
      solve(s, i - 1, new_node_id, true);
      solve(i + 1, e, new_node_id, false);
      break;
    }
  }

}

void dfs(int i) {
  if(i == -1){
    return;
  }

  dfs(tree[i].left);
  dfs(tree[i].right);
  std::cout<<tree[i].c;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  int q;
  std::cin>>q;

  while(q--) {
    std::cin>>pre>>in;
    tree = vec<Node>(1, {pre[0], -1, -1});
    ind_pre = 1;
    for(int i = 0; i < in.size(); i++) {
      if(in[i] == pre[0]) {
        solve(0, i - 1, 0, true);
        solve(i + 1, in.size() - 1, 0, false);
        break;
      }
    }

    // for(auto n : tree) {
    //   std::cout<<"c: "<<n.c;
    //   if(n.left == -1) {
    //     std::cout<<" left: -1";
    //   } else {
    //     std::cout<<" left: "<<tree[n.left].c;
    //   }
    //   if(n.right == -1) {
    //     std::cout<<" right: -1";
    //   } else {
    //     std::cout<<" right: "<<tree[n.right].c;
    //   }
      
    //   std::cout<<"\n";
    // }

    dfs(0);
    std::cout<<"\n";
  }

  std::cout.flush();
}
