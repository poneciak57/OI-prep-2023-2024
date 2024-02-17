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

vec<ll> tab;
ll min_v, max_v;

bool has_leader() {
  ll last = -1, c = 0;
  for(auto i : tab) {
    if(c == 0) {
      last = i;
      c = 1;
    } else if(last == i) c++;
    else c--;
  }

  if(c == 0) return false;
  c = 0;
  for(auto i : tab) c += i == last;
  if(c < (tab.size()/2) + 1) return false;
  // tutaj ilosc lidera jest wieksza od polowy liczb
  // mozna zbudowac lolibrigide tylko jesli lider jest maksymalna lub minimalna wartoscia w ciagu
  // a takze wystepuje (polowa + 1) razy tylko dla ilosci nieparzystych dla ilosci parzystych ta zaleznosc NIE zachodzi
  if(c == (tab.size()/2) + 1 && (last == min_v || last == max_v) && tab.size() % 2 == 1) return false;
  return true;
}

/**
 * Konkluzja:
 * Aby dało się zbudować lolibrigide ciag nie moze posiadac lidera gdyz wtedy lider ten w ktoryms miejscu musialby stac obok samego siebie
*/
int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);
  srand(time(nullptr));

  int d;
  cin>>d;
  while(d--) {
    int n;
    cin>>n;
    tab = vec<ll>(n);
    max_v = 0;
    min_v = LL_INF;
    for(int i = 0; i < n; i++) {
      cin>>tab[i];
      min_v = min(tab[i], min_v);
      max_v = max(tab[i], max_v);
    }
    if(has_leader()) {
      cout<<"NIE\n";
    } else {
      cout<<"TAK\n";
    }
  }

  cout.flush();
}
