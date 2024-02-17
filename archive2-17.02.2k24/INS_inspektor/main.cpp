#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

const ll MOD1 = 1e9 + 7;
const ll MOD2 = 1000992299;

ll powm(ll a, ll n, ll MOD);
ll multm(ll a, ll b, ll MOD);
ll divm(ll a, ll b, ll MOD);

inline int rand_range(int from, int to) {
  return (rand() % (to - from + 1)) + from;
}

struct Zeznanie {
  int t;
  int zeznajacy;
  int ile; // z uzwglednionym juz zeznajacym
};

int n, m, z;

int przed, po, poza_biurem, zeznajacy, spiacy;
vec<Zeznanie> zeznania;
struct Info {
  int pierwsze{-1};
  int ostatnie;
};
vec<Info> info;
vec<bool> po_zeznawaniu;

void print_all() {
  cout<<"przed: "<<przed<<", po: "<<po<<", poza: "<<poza_biurem<<", zeznajacy: "<<zeznajacy<<", spiacy: "<<spiacy<<"\n";
}

void ustaw_zeznania(int b, int e) {
  for(int i = b; i <= e; i++) {
    int zez = zeznania[i].zeznajacy;
    int t = zeznania[i].t;
    if(info[zez].pierwsze == -1) {
      info[zez].pierwsze = i;
    }
    info[zez].ostatnie = i;
  }
}

bool sprawdz_zeznania(int b, int e) {
  // cout<<"b: "<<b<<", e: "<<e<<"\n";
  for(int i = b; i <= e; i++) {
    auto [t, zez, ile] = zeznania[i];
    int obecnie = przed + po + zeznajacy;
    int diff = abs(ile - obecnie);
    if(ile > obecnie) {
      spiacy -= diff;
      przed += diff;
      if(spiacy < 0) {
        return false;
      }
    } else if(ile < obecnie) {
      if(po - diff < 0) {
        przed -= abs(po - diff);
        po = 0;
        if(przed < 0) {
          return false;
        }
      } else {
        po -= diff;
      }
    }

    if(info[zez].pierwsze == i) {
      if(przed > 0) {
        przed--;
      } else if(spiacy > 0) {
        spiacy--;
        po--;
        if(po < 0) {
          return false;
        }
      } else {
        return false;
      }
      zeznajacy++;
    }
    if(info[zez].ostatnie == i) {
      zeznajacy--;
      po++;
    }
  }
  return true;
}

void zeruj_ilosci() {
  info = vec<Info>(n + 1);
  przed = 0;
  po = 0;
  poza_biurem = 0;
  zeznajacy = 0;
  spiacy = n;
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);
  srand(time(nullptr));

  cin>>z;

  while(z--) {
    cin>>n>>m;
    zeznania.clear();
    while(m--) {
      int t1, t2, t3;
      cin>>t1>>t2>>t3;
      zeznania.push_back({t1, t2, t3 + 1});
    }
    sort(zeznania.begin(), zeznania.end(), [](Zeznanie &z1, Zeznanie &z2){ return z1.t < z2.t; });

    int i = 0;
    for(i = 0;i < zeznania.size(); i++) {
      zeruj_ilosci();
      ustaw_zeznania(0, i);
      if(!sprawdz_zeznania(0, i)) {
        break;
      }
    }
    cout<<i<<"\n";
  }

  

  cout.flush();
}





ll powm(ll a, ll n, ll MOD) {
  ll w = 1;

  while (n > 0) {
    if (n % 2 == 1)
      w = (w * a) % MOD;
      a = (a * a) % MOD;
      n /= 2;
  }
  return w;
}

ll multm(ll a, ll b, ll MOD) {
  return (a * b) % MOD;
}

ll divm(ll a, ll b, ll MOD) {
  return multm(a, powm(b, MOD - 2, MOD), MOD);
}