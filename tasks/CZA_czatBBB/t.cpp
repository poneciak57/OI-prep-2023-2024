#include <bits/stdc++.h>

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

// nexts[13] = index of last ocurence
struct Node
{
  std::map<char, int> nexts;
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

  tree.push_back({});
  str s = "";

  // taking input to the size of prefix
  while(s.length() < k) {
    std::cin>>c;
    s += c;
    tn--;
  }
  
  // taking the rest of input processing the prefixes
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

  p = 0;
  bool found = true;
  bool looped = false;
  // std::cout<<s<<"\n";
  str pref = s.substr(n - k, k);
  for(ll i = 0; i < b - n; i++) {
    ll cur_leaf = 0;
    found = true;
    for(ll j = p; j < pref.length(); j++) {
      ll next_leaf = tree[cur_leaf].nexts[pref[j]];

      if(next_leaf == -1) {
        found = true;
        break;
      }

      if(!next_leaf) {
        tree[cur_leaf].nexts[pref[j]] = -1;
        tree[cur_leaf].nexts[13] = p + 1;
        pref += 'a';
        found = false;
        break;
      } else {
        cur_leaf = next_leaf;
      }
    }

    if(found) {
      if(tree[cur_leaf].nexts[13]) {
        // prefixes start looping
        std::cout<<pref<<"\n";
        looped = true;
        ll loop_s = tree[cur_leaf].nexts[13] - 1;
        ll point_in_generated = n - k + loop_s;
        ll l_to_a = a - point_in_generated;
        ll j = 0;
        ll loop_lenght = pref.length() - k - loop_s;
        while(l_to_a < 0) {
          std::cout<<pref[pref.length() - 3 - loop_lenght + l_to_a];
          l_to_a++;
          j++;
        }
        ll start = (l_to_a - 1) % loop_lenght;

        while (j <= b - a)
        {
          std::cout<<pref[loop_s + start];
          start++;
          start %= loop_lenght;
          j++;
        }

        break;
      } else {
        ll count = 0;
        char cur = 'a';

        for(auto kv : tree[cur_leaf].nexts) {
          // std::cout<<"c: "<<kv.first<<" v: "<<kv.second<<"\n";
          if(kv.second > count) {
            count = kv.second;
            cur = kv.first;
          } 
        }

        tree[cur_leaf].nexts[13] = p + 1;
        pref += cur;
      }
    }
    p++;
  }

  if(!looped) {
    for(ll i = a - n + k - 1; i < b - n + k; i++) {
      std::cout<<pref[i];
    }
  }

  std::cout.flush();
}