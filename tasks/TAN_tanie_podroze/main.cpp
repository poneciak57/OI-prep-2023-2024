#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

struct Hotel {
  int dist;
  int price;
};

vec<Hotel> hotels;

void solve() {
  vec<int> prices(hotels.size(), 0);
  vec<int> prices_counts(hotels.size(), 0);
  vec<int> counts(hotels.size(), 0);
  vec<int> prev_counts(hotels.size(), -1);
  vec<int> prev(hotels.size(), -1);

  for(int i = 1; i < prices.size(); i++) {
    int min_prev = INT_MAX;
    int min_prev_ind = -1;

    int min_prev_c = INT_MAX;
    int min_prev_price_counts = INT_MAX;
    int min_prev_ind_counts = INT_MAX;
    for(int j = i - 1; j >= 0; j--) {
      if(prices[j] < min_prev && (hotels[i].dist - 800) <= hotels[j].dist) {
        min_prev = prices[j];
        min_prev_ind = j;
      }
      if(((hotels[i].dist - 800) <= hotels[j].dist) && (counts[j] < min_prev_c || (counts[j] == min_prev_c && prices_counts[j] < min_prev_price_counts))) {
        min_prev_c = counts[j];
        min_prev_price_counts = prices_counts[j];
        min_prev_ind_counts = j;
      }
    }
    prev[i] = min_prev_ind;
    prices[i] = min_prev + hotels[i].price;

    prev_counts[i] = min_prev_ind_counts;
    prices_counts[i] = min_prev_price_counts + hotels[i].price;
    counts[i] = min_prev_c + 1;
  }

  int p = prev[hotels.size() - 1];
  vec<int> ans;
  while(p != 0) {
    ans.push_back(hotels[p].dist);
    p = prev[p];
  }
  for(int i = ans.size() - 1; i >= 0; i--) {
    std::cout<<ans[i]<<" ";
  }
  cout<<"\n";

  vec<int> ans_count;
  p = prev_counts[hotels.size() - 1];
  while(p != 0) {
    ans_count.push_back(hotels[p].dist);
    p = prev_counts[p];
  }
  for(int i = ans_count.size() - 1; i >= 0; i--) {
    std::cout<<ans_count[i]<<" ";
  }
  cout<<"\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  int d, n;

  cin>>d>>n;

  
  while(n--) {
    int dist, price;
    cin>>dist>>price;
    hotels.push_back({dist, price});
  }
  // starting&ending points
  hotels.push_back({0,0});
  hotels.push_back({d, 0});

  sort(hotels.begin(), hotels.end(), [](Hotel &h1, Hotel &h2) { return h1.dist < h2.dist; });

  solve();


  cout.flush();
}
