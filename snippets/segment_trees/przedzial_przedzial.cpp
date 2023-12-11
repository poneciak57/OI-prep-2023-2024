#include <bits/stdc++.h>
#define LL_INF 10000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

/**
 * Zadanie:
 * W pierwszej lini wejscia sa podane dwie liczby n i q. Oznaczajace nastepujaco dlugosc ciagu
 * i ilosc zapytan. Nastepnie jest podane n liczb sa to poczatkowe wartosci ciagu. W kolejnych q wierszach
 * wejscia jest podany znak 'S' lub 'M' oznaczajace i majace postac:
 * S a b -> zwroc sume z przedzialu [a, b]
 * M a b c -> zmodyfikuj (dodaj) przedział [a, b] o c
 * 
 * Wejście:
 * 10 6
 * 1 2 2 3 4 1 2 5 3 2
 * S 3 7
 * M 1 5 3
 * M 3 7 -2
 * S 3 7
 * M 1 3 2
 * S 1 10
 * 
 * Wyjscie:
 * 12
 * 11
 * 36
*/

/**
 * Omowienie:
 * f -> zwraca sume konkretnego przedzialu
 * G -> operacja modyfikacji
 * A -> drzewo wynikowe
 * B -> drzewo operacji
*/

vec<int> tree_A;
vec<int> tree_B;

int n, n_inp;

void create_trees();

/**
 * @return ilość wierzchołków w danym przedziale
*/
inline int get_count_under(int curr) {
  return n / (1 << (int)log2(curr));
}

/**
 * Spycha operacje w dół z konkretnego przedziału.
 * Dodatkowo aktualizuje wartość w wierzchołku A[cur]
*/
void propagate(int cur) {
  // aktualizuje drzewo wynikowe
  int k = get_count_under(cur);
  tree_A[cur] += tree_B[cur] * k;

  // aktualizuje drzewo z modyfikacjami
  tree_B[2*cur] += tree_B[cur];
  tree_B[2*cur + 1] += tree_B[cur];
  tree_B[cur] = 0;
}

/**
 * Schodzimy do przedziałów bazowych wykonując spychanie. Gdy jesteśmy w odpowiednim przedziale bazowym v
 * aplikujemy operacje G(B[v]) => A[v], to jest wynik dla tego przedziału bazowego. Wszystkie te wyniki łączymy funkcją f.
 * Wracając wyliczamy nowe wartości A[v]]
 * 
 * cur - id obecnego wierzchołka (initially 1)
 * [left, right] - szukany przedział
 * [lOb, rOb] - przedział obecnego wierzchołka (initially [0, n])
*/
int get_sum(int cur, int left, int right, int lOb, int rOb) {
  // jeśli przedział wierzchołka odpowiada szukanemu przedziałowi
  if(left == lOb && right == rOb) {
    int k = get_count_under(cur);
    return tree_A[cur] + k * tree_B[cur];
  }

  // spychamy operacje
  propagate(cur);

  int mid = (lOb + rOb) / 2;

  if(right <= mid) {
    // jesli szukany przedzial zawiera sie w lewym dziecku
    return get_sum(2*cur, left, right, lOb, mid);
  } else if(left > mid) {
    // jesli szukany przedzial zawiera sie w prawym dziecku
    return get_sum(2 * cur + 1, left, right, mid + 1, rOb);
  }

  // jesli szukany przedzial zawiera sie pomiedzy
  int sum_left = get_sum(2*cur, left, mid, lOb, mid);
  int sum_right = get_sum(2 * cur + 1, mid + 1, right, mid + 1, rOb);

  return sum_left + sum_right;
}

void update(int cur, int left, int right, int lOb, int rOb, int mod) {
  // jeśli przedział wierzchołka odpowiada szukanemu przedziałowi
  if(left == lOb && right == rOb) {
    tree_B[cur] += mod;

    // aktualizowanie wyników wyżej
    int k = get_count_under(cur);
    cur /= 2;
    while(cur > 0) {
      tree_A[cur] += k * mod;
      cur /= 2;
    }
    return;
  }

  // spychamy operacje
  propagate(cur);

  int mid = (lOb + rOb) / 2;

  if(right <= mid) {
    // jesli szukany przedzial zawiera sie w lewym dziecku
    return update(2*cur, left, right, lOb, mid, mod);
  } else if(left > mid) {
    // jesli szukany przedzial zawiera sie w prawym dziecku
    return update(2 * cur + 1, left, right, mid + 1, rOb, mod);
  }

  // jesli szukany przedzial zawiera sie pomiedzy
  update(2*cur, left, mid, lOb, mid, mod);
  update(2 * cur + 1, mid + 1, right, mid + 1, rOb, mod);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  int q;
  cin>>n_inp>>q;

  create_trees();
  
  while (q--) {
    char op;
    int a, b, c;
    cin>>op;

    if(op == 'S') {
      // sum
      cin>>a>>b;
      cout<<get_sum(1, a, b, 1, n)<<"\n";
    } else {
      // modification
      cin>>a>>b>>c;
      update(1, a, b, 1, n, c);
    }
  }
  

  std::cout.flush();
}

void create_trees() {
  // ustalanie najblizszej potegi 2 od dlugosci ciagu
  int log_n = log2(n_inp);
  int true_n = 1 << log_n;
  if(true_n < n_inp) {
    true_n *= 2;
  }
  n = true_n;

  // tworzenie drzew A i B
  tree_A = vec<int>(2*n, 0);
  tree_B = vec<int>(2*n, 0);

  // wczytywanie danych pocztkowych
  for(int i = n, tmp; i < n + n_inp; i++) {
    cin>>tmp;
    tree_A[i] = tmp;
  }
  // obliczanie poczatkowych sum
  for(int i = n - 1; i > 0; i--) {
    tree_A[i] = tree_A[2 * i] + tree_A[2 * i + 1];
  }
}