#include <bits/stdc++.h>

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

struct Node
{
  int depth = 0;
  vec<int> nexts = vec<int>(26, 0);
};

vec<Node> tree;


int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);


  ll n, k, a, b;
  std::cin>>n>>k>>a>>b;

  ll tn = n;
  char c;

  tree.push_back({0});
  str s = "";
  while(s.length() < k) {
    std::cin>>c;
    s += c;
    tn--;
  }
  
  ll p = 0;
  while (tn--) {
    std::cin>>c;
    ll cur_leaf = 0;
    for (ll i = p; i < s.length(); i++)
    {
      ll next_leaf = tree[cur_leaf].nexts[s[i] - 97];
      if(next_leaf == 0) {
        tree[cur_leaf].nexts[s[i] - 97] = tree.size();
        tree.push_back({tree[cur_leaf].depth + 1});
        cur_leaf = tree[cur_leaf].nexts[s[i] - 97];
      } else {
        cur_leaf = next_leaf;
      }
    }
    tree[cur_leaf].nexts[c - 97]++;
    p++;
    s += c;
  }

  p = 0;
  str pref = s.substr(n - k, k);
  for(ll i = 0; i < b - n; i++) {
    ll cur_leaf = 0;
    for(ll j = p; j < pref.length(); j++) {
      ll next_leaf = tree[cur_leaf].nexts[pref[j] - 97];
      if(next_leaf == 0) {
        pref += 'a';
        break;
      } else {
        cur_leaf = next_leaf;
      }
    }

    if(tree[cur_leaf].depth == k) {
      ll count = 0;
      int cur = 0;
      for(int j = 25; j >= 0; j--) {
        if(tree[cur_leaf].nexts[j] >= count) {
          cur = j;
          count = tree[cur_leaf].nexts[j];
        }
      }
      pref += (char)(cur + 97);
    }
    p++;
  }

  for(ll i = a - n + k - 1; i < b - n + k; i++) {
    std::cout<<pref[i];
  }

  std::cout.flush();
}