#include <bits/stdc++.h>
#define INF 1000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;


/**
 * Closest Equals (Codeforces)
 * https://codeforces.com/contest/522/problem/D
 * 
 * Pomysł:
 * korzystając z algorytmu Mo segregujemy zapytania
 * aby odpowiadać na zapytania przechowujemy mapę
 * [wartosc, kolejka dwukierunkowa]
 * kolejka dwukierunkowa pomoze nam usuwac elementy z przodu lub z tylu
 * i odpowiadac na zapytania dotyczace dystansu miedzy nimi
 * poniewaz jesli mamy dodac element z przodu to wiemy ze minimalny dystans 
 * bedzie tworzyl z elementem uprzednio dodanym z przodu 
 * 
 * problematyczne natomiast wydaje sie obecnie przechowywanie wyników i usuwanie ich poniewaz obliczanie ich 
 * za kazdym razem moze byc czasochlonne mozna zastosowac vector do ktorego bedziemy dodawac elementy insertem 
 * przy uzyciu lower_bounda i usuwać wartości gdy je usuwamy
*/
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);


  std::cout.flush();
}
