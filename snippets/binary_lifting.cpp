#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

// max_depth = 1048576
const int LOG = 20;

struct Node {
  int parrent;
  int up[LOG];
  int depth;
  vec<int> rels;
};

// root parrent should be himself
vec<Node> tree;

int get_kth_ancestor(int node, int k) {
  // if kth ancestor does not exist
  if(k > tree[node].depth) return -1;

  for(int i = 0; i < LOG; i++) {
    // check if bits are on so it travels up using up in binary format
    if(k & (1 << i)) node = tree[node].up[i];
  }
  return node;
}

/**
 * dfs for computing parrents, depth and up ofc
 * root parrent should be himself VERY IMPORTANT !!!
 * Time complexity O(n logn);
*/
void compute_up(int node, int parrent, int depth) {
  tree[node].parrent = parrent;
  tree[node].depth = depth;
  tree[node].up[0] = parrent;

  // computing up table
  for(int i = 1; i < LOG; i++) {
    tree[node].up[i] = tree[tree[node].up[i - 1]].up[i - 1];
  }

  // dfs continues for each child
  for(auto rel : tree[node].rels) {
    if(rel != parrent) compute_up(rel, node, depth + 1);
  }
}


int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  /**
   * Root is always node 1
   * Input:
   * n -> number of nodes
   * n - 1 lines of relations of type: a b
   * q -> number of questions
   * q lines of questions about nodes kth ancestor 
   * of type: node k
   * 
   * In:
16
1 8
9 1
10 9
14 9
9 3
6 8
6 7
6 5
13 14
15 3
12 15
15 16
13 2
13 11
13 4
7
13 3
13 1
12 2
16 5
6 2
5 2
11 3
  * Out:
1
14
3
-1
1
8
9
  */
  int n;
  cin>>n;
  tree = vec<Node>(n + 1);

  for(int i = 1, a, b; i < n; i++) {
    cin>>a>>b;
    tree[a].rels.push_back(b);
    tree[b].rels.push_back(a);
  }

  compute_up(1, 1, 0);

  int q;
  cin>>q;
  while(q--) {
    int node, k;
    cin>>node>>k;
    cout<<get_kth_ancestor(node, k)<<"\n";
  }


  cout.flush();
}
