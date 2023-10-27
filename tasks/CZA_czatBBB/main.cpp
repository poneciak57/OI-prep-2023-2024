#include <bits/stdc++.h>

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

// nexts[13] = index of last ocurence
// jesli nexts[c] == -1 znaczy ze juz tam bylismy i nie ma takiej opcji
struct Node
{
  std::map<char, int> nexts;
};

vec<Node> tree;
ll n, k, a, b;
str s = "";

void load_tree();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  std::cin>>n>>k>>a>>b;
  load_tree();

  // position on which the prefix starts
  ll pref_pos = n - k;
  ll pref_pos_end = b - k;

  for(ll i = pref_pos; i < pref_pos_end; i++) {

    //handle next char adding
    
    // handle looping skip
    // handle it correctly when we started printing earlier


    // print letter if we can start printing before loops
    if((i + k) > a) {
      std::cout<<s[i + k];
    }
  }


  

  std::cout.flush();
}

// loads the tree to the memory
void load_tree() {
  tree.push_back({});
  ll tn = n;
  char c;

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
      ll next_leaf = tree[cur_leaf].nexts[s[i]];
      if(!next_leaf) {
        tree[cur_leaf].nexts[s[i]] = tree.size();
        tree.push_back({});
        cur_leaf = tree[cur_leaf].nexts[s[i]];
      } else {
        cur_leaf = next_leaf;
      }
    }
    tree[cur_leaf].nexts[c]++;
    p++;
    s += c;
  }
}
