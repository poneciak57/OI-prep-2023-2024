#include <bits/stdc++.h>
#define LL_INF 10000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

vec<ll> silnie;
vec<ll> sums;

void make_silnie() {
  ll i = 1;
  ll silnia = 1;
  silnie.push_back(0);
  while (silnia <= 10000000000000)
  {
    for(int j = silnie.size()-1; j >= 0; j--) {
      if(silnia + silnie[j] <= 10000000000000) {
        silnie.push_back(silnia + silnie[j]);
      }
    }
    i++;
    silnia*=i;
  }
  std::sort(silnie.begin(), silnie.end());

  sums = vec<ll>(silnie.size());
  sums[0] = 0;
  for(int i = 1; i < silnie.size(); i++) {
    sums[i] = sums[i - 1] + silnie[i];
  }
  // std::cout<<"silnia count: "<<silnie.size();
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  make_silnie();

  // for(int i = 0; i < 20; i++) {
  //   std::cout<<silnie[i]<<" ";
  // }
  // cout<<"\n";

  // for(int i = 0; i < 20; i++) {
  //   std::cout<<sums[i]<<" ";
  // }
  // cout<<"\n";

  int q;
  std::cin>>q;

  while(q--) {
    ll from, to;
    std::cin>>from>>to;
    int b = -1, e = silnie.size();
    int m;
    while(b + 1 < e) {
      m = (b + e) / 2;
      if(silnie[m] >= from) {
        e = m;
      } else {
        b = m;
      }
    }
    ll sum = 0;
    int begin = e;

    b = -1; e = silnie.size();
    while(b + 1 < e) {
      m = (b + e) / 2;
      if(silnie[m] > to) {
        e = m;
      } else {
        b = m;
      }
    }
    int end = b;
    // std::cout<<"begin: "<<begin<<"\n";
    // cout<<"end: "<<end<<"\n";
    std::cout<<sums[end] - sums[begin - 1]<<"\n";
  }


  cout.flush();
}
