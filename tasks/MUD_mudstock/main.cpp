#include <bits/stdc++.h>
#define LL_INF 10000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

struct Entry {
  int dist;
  int count;
  int count_sum;
};


int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  int n, stolica_count;
  std::cin>>n>>stolica_count;

  // {dist, count}
  vec<vec<Entry>> koleje;
  vec<int> koleje_base_count;
  ll overall_base_count = 0;
  ll overall_count_sum = 0;

  // wczytanie danych kolei i obliczenie wyników dla festivalu w stolicy
  for(int i = 0; i < n; i++) {
    int k;
    std::cin>>k;

    vec<Entry> temp;
    temp.push_back({0, stolica_count, 0});
    int d_sum = 0;
    int count_sum = 0;
    int c_sum = 0;
    for(int j = 0, dist, count; j < k; j++) {
      std::cin>>dist>>count;
      d_sum += dist;
      count_sum += count;
      c_sum += d_sum * count;
      temp.push_back({dist, count_sum, count_sum});
    }
    koleje.push_back(temp);
    koleje_base_count.push_back(c_sum);  
    overall_base_count += c_sum;
    overall_count_sum += count_sum;
  }


  // for(auto k : koleje) {
  //   for(auto [dist, count, count_sum] : k) {
  //     std::cout<<"{ "<<dist<<", "<<count<<", "<<count_sum<< " }, ";
  //   }
  //   std::cout<<"\n";
  // }

  int cur_min = overall_base_count;
  int cur_k = 0, cur_n = 0;

  for(int i = 0; i < n; i++) {
    auto k = koleje[i];

    int sum_left = overall_base_count - koleje_base_count[i];
    int sum_right = koleje_base_count[i];
    int count_sum_left = overall_count_sum - k.back().count_sum;

    if(k.back().count_sum <= count_sum_left) {
      continue;
    }

    // std::cout<<"kolej: "<<i<<" sum: "<<sum_right<<"\n";
    for(int j = 1; j < k.size(); j++) {
      auto [dist, count, count_sum] = k[j];
      sum_right -= (k.back().count_sum - k[j - 1].count_sum) * dist;
      count_sum_left += k[j - 1].count;
      sum_left += count_sum_left * dist;
      // std::cout<<"sum_left: "<<sum_left<<" sum_right: "<<sum_right<<"\n";
      if((sum_left + sum_right) <= cur_min) {
        cur_min = (sum_left + sum_right);
        cur_k = i + 1;
        cur_n = j;
      }
    }
  }

  std::cout<<cur_min<<std::endl;
  std::cout<<cur_k<<" "<<cur_n;

  std::cout.flush();
}
