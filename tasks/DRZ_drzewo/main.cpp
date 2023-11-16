#include <bits/stdc++.h>
#define INF 1000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

struct Node {
  int parrent{-1};
  int depth{-1};

  int left{-1};
  int right{-1};
};

vec<Node> tree;

void dfs(int n) {
  if(n == -1) {
    return;
  }
  std::cout<<"(";
  dfs(tree[n].left);
  dfs(tree[n].right);
  std::cout<<")";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  ll n;
  std::cin>>n;
  
  tree.push_back({-1});

  std::stack<int> stack;
  stack.push(0);

  bool flag = false;

  while(n--) {
    int t;
    std::cin>>t;

    if(stack.empty()) {
      flag = true;
      break;
    }

    int cur = stack.top();
    Node top = tree[cur];
    stack.pop();

    // if we get the depth lower than next place when we can place leaf
    if(t <= top.depth) {
      flag = true;
      break;
    }

    int i = t - top.depth - 2;
    int d = top.depth + 1;
    tree[cur].right = tree.size();
    tree.push_back({cur, d});
    cur = tree[cur].right;
    d++;

    if(i >= 0) {
      stack.push(cur);
      while(i--) {
        tree[cur].left = tree.size();
        stack.push(tree.size());
        tree.push_back({cur, d});
        cur = tree[cur].left;
        d++;
      }
      tree[cur].left = tree.size();
      tree.push_back({cur, d});
    }

  }
  // we have unused places for leaf
  flag = flag || !stack.empty();

  if(flag) {
    std::cout<<"NIE";
  } else {
    for(int i = 1; i < tree.size(); i++) {
      std::cout<<tree[i].parrent<<" ";
    }
    std::cout<<"\n";
    dfs(1);
  }

  std::cout.flush();
}
