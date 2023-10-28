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

// Zadanie CZA Kacper Poneta
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

    ll cur_leaf = 0;
    bool found = true;

    for(ll j = i; j < s.length(); j++) {
      ll next_leaf = tree[cur_leaf].nexts[s[j]];
      
      // next leaf does not exist but it starts looping here
      if(next_leaf == -1) {
        break;
      }

      // next leaf does not exist
      if(!next_leaf) {
        tree[cur_leaf].nexts[s[j]] = -1; // we set the loop indicator
        tree[cur_leaf].nexts[13] = i; // we set the index of loop start
        s += 'a';
        found = false;
        break;
      } else {
        cur_leaf = next_leaf;
      }
    }

    // if the prefix is in the tree
    if(found) {
      // if its looping
      if(tree[cur_leaf].nexts[13]) {
        
        // here we need to display as many character as needed from the looping fragment
        // if a is lower than that point we have everything to this point displayed
        // if a is higher or equal we need to skip some letters
        ll print_pos = std::max(a, (ll)s.length() + 1);
        ll prefix_start = tree[cur_leaf].nexts[13];
        ll loop_lenght = i - prefix_start;
        ll print_pos_in_prefix = (print_pos - prefix_start - 1) % loop_lenght;

        // std::cout<<s<<"\n";
        // std::cout<<"i: "<<i<<"\n";
        // std::cout<<"pref_start: "<<prefix_start<<"\n";
        // std::cout<<s[prefix_start]<<s[prefix_start + 1]<<s[prefix_start + 2]<<"\n";
        // std::cout<<s[59]<<s[60]<<s[61]<<"\n";
        // std::cout<<"loop_len: "<<loop_lenght<<"\n";
        // std::cout<<"print_pos: "<<print_pos<<"\n";
        // std::cout<<"print_pos_in_prefix: "<<print_pos_in_prefix<<"\n";

        while (print_pos <= b)
        {
          std::cout<<s[prefix_start + print_pos_in_prefix];
          print_pos_in_prefix++;
          print_pos_in_prefix %= loop_lenght;
          print_pos++;
        }
        
        break;
      }

      // determine what is the next letter
      ll max_count = 0;
      char cur = 'a';

      for(auto &[c, count] : tree[cur_leaf].nexts) {
        if(count > max_count) {
          max_count = count;
          cur = c;
        }
      }

      tree[cur_leaf].nexts[13] = i;
      s += cur;
    }

    // print letter if we can start printing before loops
    if(s.length() >= a) {
      std::cout<<s.back();
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
