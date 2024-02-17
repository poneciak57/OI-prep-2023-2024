#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

int n, inp_n;
vec<char> inp;
vec<int> default_mod = {0, 1, 2, 3, 4};

struct Modification {
  bool is_def{true};
  vec<int> mod = {0, 1, 2, 3, 4};
};

// drzewo wynikowe
// ilosc liter [count_a, count_b, ...]
// posiada ono wyniki rowniez z nalozonymi na nie modyfikacjami
vec<vec<int>> tree_A;

// drzewo operacji
vec<Modification> tree_B;

void prepare_all_mods();
void create_trees();
void merge_mod_nodes(int upper, int lower);
void propagate(int cur);

/**
 * cur - obecny wierzcholek
 * from - indeks litery z której ma nastąpić zamiana
 * to - indeks litery na który ma nastąpić zamiana
 * count - ilość liter na których ma nastąpić zamiana
*/
void modify(int cur, int from, int to, int count) {
  if(tree_A[cur][from] == count) {
    // jesli obecny wierzcholek posiada dobra ilosc danych liter mozemy dodac modyfikacje

    tree_B[cur].is_def = false;

    for(int i = 0; i < 5; i++) {
      if(tree_B[cur].mod[i] == from) {
        tree_B[cur].mod[i] = to;
      }
    } 

    // aby zaktualizowac ilosci idziemy do gory i odejmujemy count od 'from' i dodajemy count do 'to'
    while(cur > 0) {
      tree_A[cur][from] -= count;
      tree_A[cur][to] += count;
      cur /= 2;
    }
    return;
  }

  propagate(cur);

  // jesli caly wynik znajduje sie w lewym synu
  if(tree_A[2*cur][from] >= count) {
    return modify(2*cur, from, to, count);
  }

  // bierzemy cala lewa strone a takze czesc prawej
  int count_left = tree_A[2*cur][from];
  modify(2*cur, from, to, count_left);
  modify(2*cur + 1, from ,to, count - count_left);

}

void propagate_all_and_print() {
  for(int i = 0; i < inp_n; i++) {

    int cur = inp[i] - 'a';
    int v = i + n;
    while(v > 0) {
      if(!tree_B[v].is_def) {
        cur = tree_B[v].mod[cur];
      }
      v /= 2;
    }
    cout<<char(cur + 'a');
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  int q;
  cin>>inp_n>>q;

  create_trees();

  while(q--) {
    int c;
    char from, to;
    cin>>c>>from>>to;
    modify(1, from - 'a', to - 'a', c);
  }

  propagate_all_and_print();

  cout.flush();
}

// zlacza gorny wierzcholek z dolnym NIE usuwa modyfikacji na wierzcholku gornym
void merge_upper_into_lower(int upper, int lower) {
  if(tree_B[upper].is_def) return;

  vec<int> nA = {0, 0, 0, 0, 0};
  if(!tree_B[lower].is_def) {
    vec<int> snapB = tree_B[lower].mod;
    for(int i = 0; i < 5; i++) {
      // laczenie przedzialow
      tree_B[lower].mod[i] = tree_B[upper].mod[snapB[i]];

      // aktualizowanie ilosci
      nA[tree_B[upper].mod[i]] += tree_A[lower][i];
    }
  } else {
    tree_B[lower].is_def = false;
    tree_B[lower].mod = tree_B[upper].mod;
    for(int i = 0; i < 5; i++) {
      nA[tree_B[upper].mod[i]] += tree_A[lower][i];
    }
  }
  tree_A[lower] = nA;
}

void propagate(int cur) {
  // jesli obecny wierzcholek nie posiada rzadnej modyfikacji nie ma co spychac
  if(tree_B[cur].is_def) return;

  merge_upper_into_lower(cur, 2*cur);
  merge_upper_into_lower(cur, 2*cur + 1);

  tree_B[cur].is_def = true;
  tree_B[cur].mod = default_mod;
}

void create_trees() {
  int log_n = log2(inp_n);
  n = 1 << log_n;
  if(n < inp_n) {
    n *= 2;
  }

  tree_A = vec<vec<int>>(2*n, vec<int>(5, 0));
  tree_B = vec<Modification>(2*n);
  inp = vec<char>(inp_n);

  // inicjalizacja pierwszego poziomu drzewa
  char c;
  for(int i = n; i < n + inp_n; i++) {
    cin>>c;
    tree_A[i][c - 'a']++;
    inp[i - n] = c;
  }

  // wyliczenie sum początkowych dla calego drzewa z iloscia
  for(int i = n - 1; i > 0; i--) {
    for(int j = 0; j < 5; j++) {
      tree_A[i][j] = tree_A[2*i][j] + tree_A[2*i + 1][j];
    }
  }
}