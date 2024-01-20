#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

/**
 * Najdluzszy podciag rosnacy (patrz zadanie SPO_sponsor)
 * Najpierw tworzymy liste ktora bedzie pamietala minimalna wartosc ktora moze stac na danym miejscu w ciagu o danej dlugosci
 * p[i] = minimalna wartosc na ostatnim indeksie ciagu dlugosci i
 * potem uzywajac binsearcha dostajemy maksymalna wartosc po ktorej mozemy dostawic obecna 
 * 
 * Alt:
 * To samo mozna osiagnac drzewem przedzialowym w kilku krokach (patrz zadanie KLO_klocki2 i KLO_TESTS)
 * - drzewo budujemy na wartosciach elementow
 * - wezly przechowuja tuple (maks_wartosc, poprzedni), wartosc ta jest maksymalnym wynikiem kiedy wartosc wezla jest ostatnia
 * - aby znalezc maks dla danej wartosci ai bierzemy sobie maks_wartosc z przedzialu [1, ai] i dodajemy jeden
 * - updatujemy wynik dla ai na drzewie 
 * - O(n logn)
*/
int podciag_rosnacy1(vec<int> inp) {
  set<int> p;
  for(auto i : inp) {
    // wyszukiwanie binarne pierwszego elementu rownego badz wiekszego od obecnego
    auto lb = lower_bound(p.begin(), p.end(), i);
    if(lb != p.end()) {
      p.erase(lb);
    }
    p.insert(i);
  }
  return p.size();
}

/**
 * Opcja z backtrackingiem
*/
vec<int> podciag_rosnacy2(vec<int> inp) {

}