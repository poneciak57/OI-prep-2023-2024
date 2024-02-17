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

int k, p, q;

struct Lower {
  bool operator()(pair<int,int> &p1, pair<int,int> &p2) {
    if(p1.first == p2.first) {
      if(p1.second == q) return false;
      return true;
    }
    return p1.first < p2.first;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);
  srand(time(nullptr));

  int lider = -1;
  int l_c = 0;
  int n = 0;

  // {count, v}
  priority_queue<pair<int,int>, vec<pair<int,int>>, Lower> pq;
  cin>>k>>p>>q;
  bool has_p = false, has_q = false;
  if(k == 2) {
    cin>>lider;
    pq.push({lider - (p == 1) - (q == 1), 1});
    if((lider - (p == 1) - (q == 1)) < 0) {
      cout<<0; return 0;
    }
    cin>>l_c;
    pq.push({l_c - (p == 2) - (q == 2), 2});
    if((l_c - (p == 2) - (q == 2)) < 0) {
      cout<<0; return 0;
    }
    n = lider + l_c;
  } else {
    for(int i = 1, t; i <= k; i++) {
      cin>>t;
      n += t;
      if(t > l_c) {
        lider = i;
        l_c = t;
      }
      if(p == i) {
        has_p = true;
        t--;
      }
      if(q == i) {
        has_q = true;
        t--;
      }
      if(t < 0) {
        cout<<0;
        return 0;
      }
      pq.push({t, i});
    }
    if(!has_p || !has_q) {
      cout<<0;
      return 0;
    }
  }

  // sprawdzanie czy lider jest ok i czy da sie ulozyc klocki ze startowymi
  // edge case dla k = 2 klocki na koncu i poczatku musza sie roznic albo byc takie same jesli jest jednoznaczny lider
  if(k == 2) {
    if(l_c == lider && p == q) {
      cout<<0;
      return 0;
    } 
    if(l_c > (n / 2) + 1 || lider > (n / 2) + 1) {
      cout<<0;
      return 0;
    }
    if(l_c > lider && (p != 2 || q != 2)) {
      cout<<0;
      return 0;
    }
    if(lider > l_c && (p != 1 || q != 1)) {
      cout<<0;
      return 0;
    }
  } else {
    // rozwazamy kilka przypadkow
    // ilosc parzysta l_c rowne polowa -> p lub q
    // ilosc parzysta l_c rowne polowa + 1 -> p i q
    // ilosc nieparzysta l_c rowne wieksza polowa -> p i q
    if(l_c == (n / 2) + 1 && (p != lider || q != lider)) {
      cout<<0;
      return 0;
    }
    if(l_c > (n / 2) + 1) {
      cout<<0;
      return 0;
    }
    if(l_c == n / 2 && n % 2 == 0 && p != lider && q != lider) {
      cout<<0;
      return 0;
    }
  }

  // wypisujemy pierwszy klocek nastepnie wypisujemy reszte 
  cout<<p<<" ";
  int last = p;
  for(int i = 1; i < n - 1; i++) {
    auto [count, v] = pq.top();
    pq.pop();
    if(v == last) {
      auto [ncount, nv] = pq.top();
      pq.pop();
      last = nv;
      if(count != 1) pq.push({ncount - 1, nv});
      pq.push({count, v});
    } else {
      last = v;
      if(count != 1) pq.push({count - 1, v});
    }
    cout<<last<<" ";
  }
  cout<<q<<" ";
  // nie odejmowalismy z kolejki ostatniego klocka co sprawia ze jest go wiecej i mamy pewnosc ze ten sam klocek ktory jest na koncu
  // nie zostanie wypisany na przedostatnim miejscu

  cout.flush();
}
