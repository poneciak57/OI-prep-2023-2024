#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;


int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  ll d, m;
  int n;
  std::cin>>m>>d>>n;

  // {range, num}
  vec<pair<ll, int>> tab(n);

  for(int i = 1; i <= n; i++) {
    ll x;
    std::cin>>x;
    tab[i - 1] = {x, i};
  }

  sort(tab.begin(), tab.end(), [](pair<ll, int> &p1, pair<ll, int> &p2) { return p1.first > p2.first;} );

  int min_ind = -1;

  ll from_station_to_dest = m - d;

  for(int i = 0; i < tab.size(); i++) {
    if(tab[i].first >= from_station_to_dest) {
      min_ind = i;
    }
  }

  // its imposible to get from taxi station to dest
  if(min_ind == -1) {
    std::cout<<0;
    return 0;
  }

  // distance from station
  ll cur_dist = d;
  int count = 0;
  bool did = false;
  for(int i = 0; i < tab.size(); i++) {

    // next taxi cant even reach current position
    if(tab[i].first <= cur_dist) {
      continue;
    }
    if(i == min_ind) {
      continue;
    }
    
    if(cur_dist > 0) {
      cur_dist -= (tab[i].first - cur_dist);
      count++;
      if(cur_dist <= 0) {
        if(from_station_to_dest + cur_dist <= 0) {
          did = true;
          break;
        }
      }
    }
  }

  if(did) {
    std::cout<<count;
  } else if(cur_dist <= 0 || (tab[min_ind].first - 2*cur_dist - from_station_to_dest) >= 0) {
    std::cout<<count+1;
  } else {
    std::cout<<0;
  }


  cout.flush();
}
