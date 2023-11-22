#include <bits/stdc++.h>
#define INF 10000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

ll n;

// {zapotrzebowanie, dystans do nastepnego}
vec<llPair> dane;

ll i = 0, r = 0, l = 1, C = 0, Cmin = INF;
// zapotrzebowanie na piwo po lewej/prawej stronie miasta i
ll Zl = 0, Zr = 0;
// odleglosc z miasta i do miast po lewej/prawej stronie
ll Dl = 0, Dr = 0;

void poprawGranice() {
  while((Dr + dane[r].second) < Dl) {
    auto [zr, dr] = dane[r];
    auto [zl, dl] = dane[l];

    C = C + zl * (Dr + dr) - zl * Dl;
    Zr += zl;
    Zl -= zl;
    Dr += dr;
    Dl -= dl;

    r = (r + 1) % n;
    l = (l + 1) % n;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  std::cin>>n;

  for(int j = 0, z, d; j < n; j++) {
    std::cin>>z>>d;
    dane.push_back({z, d});
  }


  // obliczamy dane startowe po lewej stronie
  for(int j = (n - 1); j >= 1; j--) {
    auto [z, d] = dane[j];
    Dl += d;
    Zl += z;
    C += Dl * z;
  }

  poprawGranice();
  Cmin = std::min(C, Cmin);
  
  // obliczamy najlepsza dlugosc dla browaru w kazdym miescie wiec przesuwamy sie w 
  // lewa strone i poprawiamy granice
  for(int j = 1; j < n; j++) {
    int prev_D = dane[j - 1].second;
    C = C - Zr*prev_D + (Zl + dane[j-1].first)*prev_D;
    Zr -= dane[j].first;
    Zl += dane[j - 1].first;
    Dr -= prev_D;
    Dl += prev_D;
    poprawGranice();
    Cmin = std::min(C, Cmin);
  }

  std::cout<<Cmin;

  std::cout.flush();
}
