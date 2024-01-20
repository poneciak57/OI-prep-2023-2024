#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

inline int rand_range(int from, int to) {
  return (rand() % (to - from + 1)) + from;
}

int n;
vec<int> klocki;
const int N = 1 << 10;
// {max, i}
vec<pair<int,int>> tree(2 * N, {0, 0});

pair<int, int> get_max_on_range(int cur, int left, int right, int lOb, int rOb) {
  if(right < left) return {0, 0};
  if(left == lOb && right == rOb) {
    return tree[cur];
  }
  int mid = (lOb + rOb) / 2;
  if(right <= mid) return get_max_on_range(cur * 2, left, right, lOb, mid);
  if(left > mid) return get_max_on_range(cur * 2 + 1, left, right, mid + 1, right);

  pair<int, int> lside = get_max_on_range(cur * 2, left, mid, lOb, mid);
  pair<int, int> rside = get_max_on_range(cur * 2 + 1, mid + 1, right, mid + 1, right);
  if(lside.first > rside.first) return lside;
  return rside;
}

void update(int i, int v, int ind) {
  if(v <= tree[i].first) return;
  tree[i] = {v, ind};
  i /= 2;
  while(i > 0) {
    if(tree[i * 2].first > tree[i * 2 + 1].first) tree[i] = tree[i * 2];
    else tree[i] = tree[i * 2 + 1];
    i /= 2;
  }
}

vec<int> seg_tree() {
  tree = vec<pair<int,int>>(2 * N, {0, 0});
  klocki[0] = 0;
  // {value, ind}
  vec<pair<int, int>> a(n);
  vec<int> t(n + 1, 0);
  vec<int> p(n + 1, 0);

  for(int i = 1; i <= n; i++) {
    a[i - 1] = {klocki[i], i};
  }
  sort(a.begin(), a.end(), [](pair<int, int> p1, pair<int,int> p2) { 
    if(p1.second - p1.first == p2.second - p2.first) {
      return p1.first < p2.first;
    }
    return p1.second - p1.first < p2.second - p2.first;
   });

  for(auto [v, ind] : a) {
    if(ind - v < 0) continue;
    auto [ct, cp] = get_max_on_range(1, 1, v - 1, 1, N);
    t[ind] = ct + 1;
    p[ind] = cp;
    update(N + v, t[ind], ind);
  }

  int k = tree[1].second;
  vec<int> ans;
  while(t[k] > 0) {
    int j = p[k];
    int ile_usunac = (k - j) - (klocki[k] - klocki[j]);
    for(int i = 1; i <= ile_usunac; i++) {
      ans.push_back(j + i);
    }
    k = j;
  }
  return ans;
}
void dynamik();

bool test() {
  vec<int> ans = seg_tree();
  vec<bool> deleted(n + 1, false);

  for(auto a : ans) {
    if(a > n || deleted[a]) {
      return false;
    }
    deleted[a] = true;
  }

  return true;
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);
  // srand(time(nullptr));

  for(int i = 1; i <= 1000; i++) {
    srand(i);
    n = rand_range(10, 20);
    klocki = vec<int>(n + 1);
    for(int i = 1; i <= n; i++) {
      klocki[i] = rand_range(1, n);
    }
    if(test() == false) {
      cout<<"BLAD\n";
      cout<<n<<"\n";
      for(auto k : klocki) {
        cout<<k<<" ";
      }
      cout<<"\n";
    } else {
      cout<<"TEST #"<<i<<": OK\n";
    }
  }

  // seg_tree();
  // dynamik();

  cout.flush();
}

/**
 * Rozwiazanie w zlozonosci O(n^2)
*/
void dynamik() {
  int n;
  cin>>n;
  vec<int> klocki(n + 1);
  klocki[0] = 0;

  for(int i = 1; i <= n; i++) {
    cin>>klocki[i];
  }
  vec<int> t(n + 1, 0);
  vec<int> p(n + 1, 0);
  int k = 0;
  int max_v = 0;
  for(int i = 1; i <= n; i++) {
    if(klocki[i] <= i) {
      t[i] = 1;
      p[i] = 0;
      for(int j = 1; j < i; j++) {
        if(klocki[j] < klocki[i] && j - klocki[j] <= i - klocki[i]) {
          if(t[j] + 1 > t[i]) {
            t[i] = t[j] + 1;
            p[i] = j;
          }
        }
      }
      if(t[i] > max_v) {
        k = i;
        max_v = t[i];
      }
    }
  }
  vec<int> ans;
  while(t[k] > 0) {
    int j = p[k];
    int ile_usunac = (k - j) - (klocki[k] - klocki[j]);
    for(int i = 1; i <= ile_usunac; i++) {
      ans.push_back(j + i);
    }
    k = j;
  }

  cout<<ans.size()<<"\n";
  for(auto a : ans) {
    cout<<a<<" ";
  }
}
