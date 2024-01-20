#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

struct Node {
  int from {INT_MAX};
  int to {INT_MAX};
  ll mod {0};
};

vec<Node> seg_tree;

ll n, m, k, N;
// {owner, pos}
vec<pair<int, int>> sector_owners;
vec<ll> companies_need;
// {curr_sum, prev_sum}
vec<pair<ll,ll>> companies_sum;
struct Op {int l; int r; ll a;};
vec<Op> ops;

void init(vec<int> &sectors);
void merge(vec<int> &sectors);

/**
 * Trzeba przerobic to drzewo na drzewo na mapie bo sie mess robi i wyznaczac za kazdym razem lower upper boundy
*/


void add_on_range(int cur, int left, int right, ll mod) {
  int lOb = seg_tree[cur].from;
  int rOb = seg_tree[cur].to;

  // sprawdzamy czy przedzial miesci sie w drzewie i czy nie miesci sie w zmniejszonym drzewie
  // czyli najprosciej mowiac czy obecny przedzial to minimalny przedzial ktory pokrywa
  if(left <= lOb && right >= rOb) {
    seg_tree[cur].mod += mod;
    return;
  } else if(lOb == rOb) {
    return;
  }

  if(seg_tree[cur * 2].to >= right) return add_on_range(cur * 2, left, right, mod);
  if(seg_tree[cur * 2 + 1].from <= left) return add_on_range(cur * 2 + 1, left, right, mod);

  add_on_range(cur * 2, left, seg_tree[cur * 2].to, mod);
  add_on_range(cur * 2 + 1, seg_tree[cur * 2 + 1].from, right, mod);
}

void read_inp() {
  cin>>n>>m;
  sector_owners = vec<pair<int,int>>(m + 1);
  companies_need = vec<ll>(n + 1);
  companies_sum = vec<pair<ll, ll>>(n + 1, {0, 0});

  for(int i = 1, tmp; i <= m; i++) {
    cin>>tmp;
    sector_owners[i] = {tmp, i};
  }

  for(int i = 1; i <= n; i++) {
    cin>>companies_need[i];
  }

  cin>>k;
  ops = vec<Op>(k + 1);
  ops[0] = {1, 1, 0};
  for(int i = 1, l, r, a; i <= k; i++) {
    cin>>l>>r>>a;
    ops[i] = {l, r, a};
  }
}


int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);
  srand(time(nullptr));

  read_inp();
  struct QEntry {
    int b;
    int e;
    vec<int> sectors;
  };
  vec<int> ans(n + 1, 0);
  queue<QEntry> q;

  vec<int> start_sectors;
  for(int i = 1; i <= m; i++) {
    start_sectors.push_back(i);
  }

  q.push({0, k + 1, start_sectors});
  while(!q.empty()) {
    auto [b, e, sectors] = q.front();
    q.pop();
    int m = (b + e) / 2;
    // przypisujemy wynik jesli konczymy binsearch
    if(b + 1 >= e) {
      for(auto sec : sectors) {
        ans[sector_owners[sec].first] = e;
      }
      continue;
    }
    // tutaj tworzymy drzewo przedzialowe z sektorow
    // symulujemy na tym drzewie deszcze z przedzialu od `b` do `m`
    // nastepnie spychamy wszystkie wartosci po kolei i aktualizujemy wartosci w tablicy companies_sum
    // potem iterujemy sie po companies_sum 
    //  - jesli suma jest wieksza badz rowna potrzebnej => e = m, companies_sum[i].first = companies_sum[i].second
    //  - jesli suma jest mniejsza od potrzebnej => b = m, companies_sum[i].second = companies_sum[i].first
    init(sectors);
    
    // tutaj symulujemy deszcze
    // zastanowic sie nad `b`
    for(int i = b + 1; i <= m; i++) {
      if(ops[i].l > ops[i].r) {
        add_on_range(1, ops[i].l, seg_tree[2*N - 1].to, ops[i].a);
        add_on_range(1, seg_tree[N].from, ops[i].r, ops[i].a);
        continue;
      }
      add_on_range(1, ops[i].l, ops[i].r, ops[i].a);
    }
    // aktualizujemy cur_sum w tablicy companies_sum
    merge(sectors);

    // teraz mozemy zadecydowac ktore sektory wracaja do kolejki ze zmienionym `b` a ktore `e`
    vec<int> lewo;
    vec<int> prawo;
    for(int i = 0; i < sectors.size(); i++) {
      int company = sector_owners[sectors[i]].first;
      ll comp_sum = companies_sum[company].first;
      if(comp_sum >= companies_need[company]) lewo.push_back(sectors[i]);
      else prawo.push_back(sectors[i]);
    }
    for(auto s : lewo) {
      int company = sector_owners[s].first;
      companies_sum[company].first = companies_sum[company].second;
    }
    for(auto s : prawo) {
      int company = sector_owners[s].first;
      companies_sum[company].second = companies_sum[company].first;
    }
    if(!lewo.empty()) q.push({b, m, lewo});
    if(!prawo.empty()) q.push({m, e, prawo});
  }

  for(int i = 1; i <= n; i++) {
    if(ans[i] == k + 1 || ans[i] == 0) {
      cout<<"NIE\n";
      continue;
    }
    cout<<ans[i]<<"\n";
  }
  cout.flush();
}

ll sum_up(int cur) {
  ll sum = 0;
  while(cur > 0) {
    sum += seg_tree[cur].mod;
    cur /= 2;
  }
  return sum;
}

void merge(vec<int> &sectors) {
  for(int i = 0; i < sectors.size(); i++) {
    ll sum = sum_up(i + N);
    companies_sum[sector_owners[sectors[i]].first].first += sum;
    if(companies_sum[sector_owners[sectors[i]].first].first >= INT_MAX) companies_sum[sector_owners[sectors[i]].first].first = INT_MAX;
  }
}

void init(vec<int> &sectors) {
  N = 1;
  while(N < sectors.size()) {
    N *= 2;
  }
  seg_tree = vec<Node>(2*N);
  for(int i = 0; i < sectors.size(); i++) {
    int pos = sector_owners[sectors[i]].second;
    seg_tree[N + i] = {pos, pos, 0};
  }

  for(int i = N - 1; i > 0; i--) {
    seg_tree[i].from = seg_tree[i * 2].from;
    seg_tree[i].to = seg_tree[i * 2 + 1].to;
  }
}