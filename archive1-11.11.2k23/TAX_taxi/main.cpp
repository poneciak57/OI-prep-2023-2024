#include <bits/stdc++.h>
#include <iostream>
typedef long long ll;
typedef std::string str;

template <typename T>
using vec = std::vector<T>;

struct Node {
  ll pre_order { 0 };
  ll post_order { 0 };

  vec<ll> rels;
};

vec<Node> graf;
vec<bool> visited;

ll post { 0 };
ll pre { 0 };

void dfs (ll n) {
  graf[n].pre_order = pre;
  pre++;
  visited[n] = true;
  for (ll r : graf[n].rels) {
    if(!visited[r]) {
      dfs(r);
    }
  }
  graf[n].post_order = post;
  post++;
}


/**
 * Ustawiamy `post_order` i `pre_order` dla kazdego nodea od ratusza stad mozemy sprawdzic 
 * czy najkrotsza droga z ratusza do `x` i `y` przechodzi przez punkt `z`
 */
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);
  
  ll n;
  std::cin>>n;
  
  graf = vec<Node>(n + 1);
  visited = vec<bool>(n + 1, false);

  while (--n) {
    ll from, to;
    std::cin>>from>>to;
    graf[from].rels.push_back(to);
    graf[to].rels.push_back(from);
  }

  dfs(1);

  ll q;
  std::cin>>q;
  while (q--) {
    ll z, x, y;
    std::cin>>z>>x>>y;
    if(
      (graf[z].pre_order <= graf[x].pre_order) &&
      (graf[z].post_order >= graf[x].post_order) &&
      (graf[z].pre_order <= graf[y].pre_order) &&
      (graf[z].post_order >= graf[y].post_order)
    ) {
      std::cout<<"TAK"<<"\n";
    } else {
      std::cout<<"NIE"<<"\n";
    }
  }

  std::cout.flush();
}
