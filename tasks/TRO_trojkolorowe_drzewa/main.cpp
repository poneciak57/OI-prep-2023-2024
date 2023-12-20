#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

struct Node {
  int parrent;
  vec<int> childs;
};

vec<Node> tree;
str s;

int create(int ind, int parrent) {
  int node_id = tree.size();
  tree.push_back({parrent});
  if(parrent != -1) {
    tree[parrent].childs.push_back(node_id);
  }
  int times = s[ind] - '0';
  for(int i = 0; i < times; i++) {
    ind = create(ind + 1, node_id);
  }
  return ind;
}

// {max_c, color}
pair<int, char> get_max(int node) {
  int c_green = 0;
  int sum = 0;
  for(auto child : tree[node].childs) {
    auto [maxc, prev_color] = get_max(child);
    c_green += (prev_color == 'Z');
    sum += maxc;
  }

  if(c_green == 2) return {sum - 1, 'B'};
  else if(c_green == 1) return {sum, 'B'};
  else return {sum + 1, 'Z'};
}

pair<int, char> get_min(int node) {
  int c_blue = 0;
  int sum = 0;
  for(auto child : tree[node].childs) {
    auto [min_c, prev_color] = get_min(child);
    c_blue += (prev_color == 'B');
    sum += min_c;
  }

  if(c_blue == 2) return {sum + 1, 'Z'};
  else return {sum, 'B'};
}

void print_tree();

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  cin>>s;

  create(0, -1);
  // print_tree();

  cout<<get_max(0).first<<" "<<get_min(0).first;

  cout.flush();
}


void print_tree() {
  for(auto node : tree) {
    cout<<"parent: "<<node.parrent<<" \t ";
    cout<<"childs: {";
    if(node.childs.size() == 2) {
      cout<<node.childs[0]<<","<<node.childs[1];
    } else if(node.childs.size() == 1) {
      cout<<node.childs[0];
    }

    cout<<"}\n";
  }
}