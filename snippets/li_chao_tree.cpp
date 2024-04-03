#include <bits/stdc++.h>
#define LLINF 100000000000000007

using namespace std;
typedef long long ll;
typedef string str;
template <typename T> using vec = vector<T>;



// Li Chao tree
// Problem: 
// Mamy podane funkcje liniowe chcemy odpowiedziec na zapytanie jaka najwieksza wartosc przyjmuje ktoras z funkcji w punkcie x
// 
// Rozwiazanie:
// Tworzymy drzewo przedzial-punkt, gdzie w kazdym wierzchołku przechowujemy funkcje liniową
// 
// Update:
// - Jesli dana funkcja jest wieksza na srodku w danym wierzcholku to zamieniamy ja z obecnie dodana tam funkcja
// - Jesli left == right znaczy ze jestesmy w lisciu drzewa przedzialowego i musimy zakonczyc rekurencje
// - Jesli funkcja line jest wieksza w lewej polowie to wywolujemy sie z nia w lewym synu
// - Jesli funkcja line jest wieksza w prawej polowie to wywolujemy sie z nia w prawym synu
// DISCLAIMER:
// - z uwagi ze na poczatku zamienilismy funkcje bedziemy rozwazac jako line ta ktora jest mniejsza na srodku,
//   dzieki temu wiemy ze wywolamy sie maksymalnie w jednym synu
//
// Query:
// - idziemy od syna w punkcie x w góre az do korzenia i maksymalizujemy odpowiedz sprawdzajac funkcje ze wszystkich wierzcholkow
const ll NINF = -1e9;
struct Line {
  ll a;
  ll b;
  ll operator()(ll x) { return a * x + b; }
};
int n, N;
vec<Line> seg_tree;
void init() {
  N = 1;
  while(N < n) N *= 2;
  seg_tree = vec<Line>(N * 2, {NINF, 0});
}
void add(int cur, int left, int right, Line line) {
  int mid = (left + right) / 2;
  if(seg_tree[cur](mid) < line(mid)) swap(seg_tree[cur], line);
  if(left == right) return;
  if(line(left) > seg_tree[cur](left)) add(cur * 2, left, mid, line);
  if(line(right) > seg_tree[cur](right)) add(cur * 2 + 1, mid + 1, right, line);
}
ll get_max(int x) {
  int v = x + N - 1;
  ll maxv = NINF;
  while(v > 0) {
    maxv = max(maxv, seg_tree[v](x));
    v /= 2;
  }
  return maxv;
} 

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

  

	cout.flush();
	return 0;
}