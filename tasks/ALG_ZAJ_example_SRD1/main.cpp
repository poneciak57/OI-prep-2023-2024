/**
 * Zadanie:
 * Tablica liczb a[i] z przedziału [1,k] gdzie i <= n, 
 * zapytania (x,y), 
 * odpowiedź na zapytanie, to min(|i-j|), gdzie a[i]=x, a[j]=y.
 * 
 * Wejscie: 
 * n - ilosc liczb
 * q - ilosc zapytan
 * an - kolejne n liczb postaci ai
 * aq - kolejne q zapytan postaci (x, y)
 * 
 * Wyjscie:
 * q kolejnych odpowiedzi na zapytania
 * 
 * Obserwacja: jest co najwyżej sqrt(n) liczb występujących w tablicy a co najmniej sqrt(n) razy.
 * 
*/

#include <bits/stdc++.h>

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

#define INF 1000000007

// max wartosc liczby + 1
const int K = 1007;

// tablica indeksow wystapien kazdej liczby z przedzialu 1 - K
vec<vec<int>> occurences(K);

// tablica liczb 
vec<int> nums;

// mapa liczb ktore pojawily sie wiecej niz sqrt(n) razy
std::map<int, vec<int>> map_of_big_counts;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  ll n, q, sqrt_n;
  std::cin>>n>>q;

  sqrt_n = sqrt(n);

  for(int i = 0; i < n; i++) {
    int t;
    std::cin>>t;
    nums.push_back(t);
    occurences[t].push_back(i);
  }

  // sprawdzamy ktore liczby wystepuja wiecej niz pierwiastek z n raza
  // i dla nich tworzymy entry w mapie z tablica wszystkich mozliwych wartosci (1 - K)
  // i obliczamy minimalna dlugosc dla kazdej z nich w zlozonosci O(2n)
  for(int i = 0; i < K; i++) {
    if(occurences[i].size() >= sqrt_n) {
      vec<int> occurs_of_i(K, INF);

      // we define min going from left to right
      int ind_of_i = -1; 
      for(int j = 0; j < n; j++) {
        if(nums[j] == i) ind_of_i = j;
        if(ind_of_i == -1) continue;
        occurs_of_i[nums[j]] = std::min(occurs_of_i[nums[j]], j - ind_of_i); 
      }

      // we define min going from right to left
      ind_of_i = -1;
      for(int j = n-1; j >= 0; j--) {
        if(nums[j] == i) ind_of_i = j;
        if(ind_of_i == -1) continue;
        occurs_of_i[nums[j]] = std::min(occurs_of_i[nums[j]], ind_of_i - j); 
      }

      // now we have somekind of global minimum
      map_of_big_counts[i] = occurs_of_i;
    }
  }

  // teraz rozpatrujemy zapytania
  while(q--) {
    int x, y;
    std::cin>>x>>y;

    auto x_key = map_of_big_counts.find(x);
    auto y_key = map_of_big_counts.find(y);

    // we found x in map of big counts so here we can find the dist from y
    if(x_key != map_of_big_counts.end()) {
      std::cout<<x_key->second[y]<<"\n";
      continue;
    }

    // we found y in map of big counts so here we can find the dist from x
    if(y_key != map_of_big_counts.end()) {
      std::cout<<y_key->second[x]<<"\n";
      continue;
    }

    // otherwise we know the number of occurences of both x and y is pretty small 
    // so we can just answer question with use of moving window on two arrays
    // it has time complexity of O(2*sqrt(n)) in worst case (sqrt(n) is max size of the occurences tab
    // thats not considered big)

    vec<int> &xvec = occurences[x];
    vec<int> &yvec = occurences[y];


    int minn = INF;
    
    int head = 0;
    int tail = 0;

    int last_dist = INF;

    while(head < xvec.size() && tail < yvec.size()) {
      int v = std::abs(xvec[head] - yvec[tail]);
      if(v < last_dist) {
        last_dist = v;
        minn = std::min(minn, v);
        if(tail == (yvec.size() - 1)) {
          head++;
        } else {
          tail++;
        }
      } else {
        last_dist = INF;
        tail--;
        head++;
      }
    }

    std::cout<<minn<<"\n";
  }

  std::cout.flush();
}




/* 
# INPUTS #

in1:
10 5
1 2 3 3 1 1 4 5 1 2
1 3
5 3
4 2
2 5
4 1
out1:
1
4
3
2
1

in2:
10 7
1 4 4 1 2 4 2 4 5 5
5 5
1 2
2 1
4 5
4 1
2 4
5 1
out2:
0
1
1
1
1
1
5



*/