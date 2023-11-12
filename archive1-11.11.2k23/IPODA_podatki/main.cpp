#include <bits/stdc++.h>

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

// z uwagi ze w zadaniu pomijamy liczby parzyste pomijamy je tez tutaj
bool isPrime(ll n) {
  for (ll i = 3; i * i <= n; i+=2) {
    if(n % i == 0) {
      return false;
    }
  }
  return true;
}

/**
 * Kazdą liczbe parzysta wieksza od 2 da sie zbudowac z dwoch liczb pierwszych zatem wynik dla niej zawsze bedzie rowny 2
 * Dla liczb nieparzystych wynik zatem moze byc rowny 1 lub 3
 * - 1 jesli jest ona pierwsza
 * - 3 jesli nie jest ona pierwsza (wynik dla n - 1 czyli liczby parzystej czyli 2 + 1 gdyz jedynka)
 * 
 * ** W niektorych przypadkach dla liczb nieparzystych istnieje opcja uzyskania 2 wyników dzieje sie tak gdyz 2 jest jedyna parzysta 
 * liczba pierwsza, zatem jezeli n - 2 jest pierwsze uzyskamy wynik 2. W tym celu musimy takze sprawdzic czy n - 2 jest pierwsza
 * 
 * Zatem musimy jedynie sprawdzic czy liczba n jest pierwsza i oprzec na tym wynik
 * */ 
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);
  
  ll n;
  std::cin>>n;

  // dla danych wejsciowych 2 otrzymalibysmy wynik 2 wiec trzeba to przeifowac
  if(n == 2) {
    std::cout<<1;
  }

  if(n % 2 == 0) {
    std::cout<<2;
  } else {
    if(isPrime(n)) {
      std::cout<<1;
    } else if(isPrime(n - 2)){
      std::cout<<2;
    } else {
      std::cout<<3;
    }
  }

  std::cout.flush();
}
