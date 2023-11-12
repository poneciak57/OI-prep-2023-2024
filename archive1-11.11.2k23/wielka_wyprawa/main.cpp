#include <bits/stdc++.h>
typedef long long ll;
typedef std::string str;

template <typename T>
using vec = std::vector<T>;

struct P {
  ll dist;
  ll height;
  ll sum_from_left;
  ll sum_from_right;
  ll step;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);
  
  ll n;
  std::cin>>n;
  vec<P> steps;
  ll step = 1;
  while (n--) {
    ll d, h;
    std::cin>>d>>h;
    steps.push_back({d, h, 0, 0, step});
    step++;
  }

  sort(steps.begin(), steps.end(), [](const P& l, const P& r) {
    return l.dist < r.dist;
  });
  for (ll i = 1; i < steps.size(); i++) {
    steps[i].sum_from_left = steps[i-1].sum_from_left 
      + (steps[i].height - steps[i-1].height) * (steps[i].height >= steps[i-1].height)
      + (steps[i].dist - steps[i-1].dist);
  }
  for (ll i = steps.size() - 2; i >= 0; i--) {
    steps[i].sum_from_right = steps[i+1].sum_from_right 
      + (steps[i].height - steps[i+1].height) * (steps[i].height >= steps[i+1].height)
      + (steps[i+1].dist - steps[i].dist);
  }

  sort(steps.begin(), steps.end(), [](const P& l, const P& r) {
    return l.step < r.step;
  });
  ll sum = 0;
  for (ll i = 1; i < steps.size(); i++) {
    if(steps[i].dist > steps[i-1].dist) {
      sum += steps[i].sum_from_left - steps[i-1].sum_from_left;
    } else {
      sum += steps[i].sum_from_right - steps[i-1].sum_from_right;
    }
  }

  std::cout<<sum;

  std::cout.flush();
}
