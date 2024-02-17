#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

ll a, b, n, k;
vec<ll> A;
vec<ll> B;


ll ile_mniej(ll pole) {
  ll count = 0;

  ll bi = B.size() - 1;
  for(ll i = 0; i < A.size(); i++) {
    while(bi >= 0 && A[i] * B[bi] < pole) {
      count += A.size() - i;
      bi--;
    }
    if(bi < 0) break;
  }
  return count;
}

void read_inp();

int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  cin>>a>>b>>n>>k;

  read_inp();

  ll need = (n + 1) * (n + 1) - k;
  ll b = 0, e = A[0] * B[0] + 10, m;
  // cout<<"need: "<<need<<"\n";
  while(b + 1 < e) {
    m = (b + e) / 2;
    ll tmp = ile_mniej(m);
    // cout<<"tmp: "<<tmp<<"  m: "<<m<<"\n";
    if(tmp > need) {
      e = m;
    } else {
      b = m;
    }
  }
  // cout<<"b: "<<b<<"\n";

  ll closest = -1;
  // now we need to find closest number to e from sequence
  for(int i = 0; i < A.size(); i++) {
    ll mult = b / A[i];
    if(mult * A[i] < b) mult++;


    ll p = 0, k = B.size(), s;
    while(p + 1 < k) {
      s = (p + k) / 2;
      if(B[s] >= mult) {
        p = s;
      } else {
        k = s;
      }
    }

    ll n_num = B[p] * A[i];
    if(abs(closest - b) > abs(b - n_num) && n_num >= b) {
      closest = n_num;
    }
  }
  cout<<closest;


  cout.flush();
}


void read_inp() {
  ll prev;
  A = vec<ll>(n + 1);
  prev = 0;
  for(ll i = 0, tmp; i < n; i++) {
    cin>>tmp;
    A[i] = tmp - prev;
    prev = tmp;
  }
  A[n] = a - prev;
  sort(A.begin(), A.end(), [](ll &i1, ll &i2) { return i1 > i2; });

  B = vec<ll>(n + 1);
  prev = 0;
  for(ll i = 0, tmp; i < n; i++) {
    cin>>tmp;
    B[i] = tmp - prev;
    prev = tmp;
  }
  B[n] = b - prev;
  sort(B.begin(), B.end(), [](ll &i1, ll &i2) { return i1 > i2; });
}