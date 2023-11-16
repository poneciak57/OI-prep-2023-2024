#include <bits/stdc++.h>
#define INF 1000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

ll n, k, sqrt_n;
int containers[100007];


int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  std::cin>>n>>k;
  sqrt_n = sqrt(n)/10;

  vec<vec<int>> segment_tree(sqrt_n + 1, vec<int>(n + 1 + sqrt_n, 0));
  
  while(k--) {
    // a - start positiom
    // l - containers count
    // d - space between containers
    ll a, l, d;
    std::cin>>a>>l>>d;

    if(d <= sqrt_n) {
      segment_tree[d][a]++;
      segment_tree[d][a + l*d]--;
    } else {
      for(int i = 0, j = a; i < l; i++, j += d) {
        containers[j]++;
      }
    }
  }

  for(int i = 1; i <= sqrt_n; i++) {
    for(int j = 0; j < i; j++) {
      // i is d the distance between the values
      // j is starting value
      // so now we need to iterate over the segment of the tree
      int incrementer = 0;
      for(int cont_ind = j; cont_ind <= n; cont_ind += i) {
        incrementer += segment_tree[i][cont_ind];
        containers[cont_ind] += incrementer;
      }
    }
  }
  for(int i = 1; i <= n; i++) {
    std::cout<<containers[i]<<" ";
  }

  std::cout.flush();
}
