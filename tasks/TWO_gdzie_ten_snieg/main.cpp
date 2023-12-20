#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

vec<int> sniezki;

int solve(int k) {
  int max_sniezek = 0;

  // ustawiamy pierwsza platforme
  int sniezki_count1 = 0;
  int b_first = 0;
  int e_first = 0;
  while(e_first < sniezki.size() && sniezki[e_first] <= sniezki[b_first] + k) {
    sniezki_count1++;
    e_first++;
  }
  e_first--;
  max_sniezek = max(max_sniezek, sniezki_count1);
  if(e_first == sniezki.size() - 1) return max_sniezek;

  // tworzymy druga platforme tuz za pierwsza
  int b_second = e_first + 1;
  int e_second = b_second;
  int sniezki_count = 0;
  while(e_second < sniezki.size() && sniezki[e_second] <= sniezki[b_second] + k) {
    sniezki_count++;
    e_second++;
    // cout<<"s[bs]: "<<sniezki[b_second]<<"  s[es]: "<<sniezki[e_second]<<"\n";
    // cout<<"bs: "<<b_second<<"  es: "<<e_second<<"  sc: "<<sniezki_count<<"\n";
  }
  max_sniezek = max(max_sniezek, sniezki_count1 + sniezki_count);

  // {ilosc sniezek, poczatek}
  vec<pair<int,int>> pq;
  pq.push_back({sniezki_count, b_second});
  while(b_second < sniezki.size()) {
    b_second++;
    sniezki_count--;
    while(e_second < sniezki.size() && sniezki[e_second] <= sniezki[b_second] + k) {
      sniezki_count++;
      e_second++;
    }
    max_sniezek = max(max_sniezek, sniezki_count1 + sniezki_count);
    pq.push_back({sniezki_count, b_second});
  }
  sort(pq.begin(), pq.end(), [](pair<int,int> &p1, pair<int,int> &p2){ return p1.first > p2.first; });

  // teraz przesuwamy pierwsza platforme do konca i wybieramy z listy najlepsza druga platforme, 
  // jesli druga platforma zaczyna sie wczesniej niz konczy pierwsza to przesuwamy wskaznik drugiej platformy
  int pq_ind = 0;
  while(b_first < sniezki.size()) {
    b_first++;
    sniezki_count1--;
    while(e_first < sniezki.size() && sniezki[e_first] <= sniezki[b_first] + k) {
      sniezki_count1++;
      e_first++;
    }
    if(e_first >= sniezki.size()) {
      pq_ind = pq.size() - 1;
    } else {
      int pq_snap = pq_ind; 
      while(pq_ind < pq.size() && sniezki[e_first] > pq[pq_ind].second) {
        pq_ind++;
      }
      if(pq_ind >= pq.size()) pq_ind = pq.size();
      if(pq_ind != pq_snap) pq_ind--;
    }
    // cout<<"bs: "<<b_second<<"  es: "<<e_second<<"  sc: "<<sniezki_count<<"\n";
    max_sniezek = max(max_sniezek, sniezki_count1 + pq[pq_ind].first);
  }


  return max_sniezek;
}

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);
  
  int t;
  cin>>t;
  while(t--) {
    int n, k;
    cin>>n>>k;
    sniezki = vec<int>(n);
    for(int i = 0, tmp; i < n; i++) {
      cin>>tmp;
      sniezki[i] = tmp;
    }
    sort(sniezki.begin(), sniezki.end());
    for(int i = 0, tmp; i < n; i++) cin>>tmp;
    cout<<solve(k)<<"\n";
  }

  cout.flush();
}
