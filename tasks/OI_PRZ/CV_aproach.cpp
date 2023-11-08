#include <bits/stdc++.h>

typedef int ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

struct B {
  ll row;
  ll col;
  bool active = true;
};

ll n, m;
vec<B> buttons;
vec<vec<ll>> rows;
vec<vec<ll>> cols;

vec<bool> rows_done;
vec<bool> cols_done;

// checks if row has single button
// if so it deletes this button from row and col and decrement the buttons avaible
// and adds the button to selected
bool check_row(ll i, vec<ll> &selected);

// checks if col has single button
// if so it deletes this button from row and col and decrement the buttons avaible
// and adds the button to selected
bool check_col(ll i, vec<ll> &selected);

void print_mat();

bool check_ones() {
  vec<ll> selected;

  bool go = true;
  while(go) {
    go = false;
    for(ll i = 1; i <= n; i++) {
      go |= check_row(i, selected);
      go |= check_col(i, selected);
    }
  }

  bool done = true;
  for(ll i = 1; i <= n; i++) {
    done &= cols_done[i] && rows_done[i];
  }
  if(done) {
    std::cout<<"TAK\n";
    std::cout<<selected.size()<<"\n";
    for(auto s : selected) {
      std::cout<<s<<" ";
    }
  }

  return done;
}


void print_for_even() {
  // sorting for searching of cycles
  for(int i = 1; i <= n; i++) {
    std::sort(rows[i].begin(), rows[i].end(), [](ll &l1, ll &l2){ return buttons[l1].col < buttons[l2].col; });
    std::sort(cols[i].begin(), cols[i].end(), [](ll &l1, ll &l2){ return buttons[l1].row < buttons[l2].row; });
  }


  B bb1, bb2;
  B be1, be2;
  std::set<ll> selected;

  // we find first and last from bottom site
  for(ll i = 1; i <= n; i++) {
    if(rows[i].size() > 0) {
      bb1 = buttons[rows[i].front()];
      bb2 = buttons[rows[i].back()];
      selected.insert(rows[i].front());
      selected.insert(rows[i].back());
      break;
    }
  }

  // we find first and last from top site
  for(ll i = n; i >= 1; i--) {
    if(rows[i].size() > 0) {
      be1 = buttons[rows[i].front()];
      be2 = buttons[rows[i].back()];
      selected.insert(rows[i].front());
      selected.insert(rows[i].back());
      break;
    }
  }

  // now i need to find the convex hull of the set of buttons
  // we know it always exists and it is the even solution for our problem
  // we need to search for a path from bb1 to be1 or be2
  
  vec<bool> visited_row1(n + 1, false); // if we visited row
}

// Zadanie PRZ Kacper Poneta
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin.tie(nullptr);

  std::cin>>n>>m;

  buttons.push_back({-1, -1});

  rows = vec<vec<ll>>(n + 1);
  cols = vec<vec<ll>>(n + 1);

  rows_done = vec<bool>(n + 1, false);
  cols_done = vec<bool>(n + 1, false);

  ll mloop = m;
  while(mloop--) {
    ll tr, tc;
    std::cin>>tr>>tc;
    cols[tc].push_back(buttons.size());
    rows[tr].push_back(buttons.size());
    buttons.push_back({tr, tc});
  }

  bool odd = check_ones();


  if(odd) {
    return 0;
  }

  // print_mat();

  // if not odd we need to check if we have any buttons left
  // if we don't have any buttons left it means we can't solve this
  // if we do have it means they will give even solution
  if(m == 0) {
    std::cout<<"NIE\n";
    return 0;
  } else {
    std::cout<<"TAK\n";
    print_for_even();
  }


  std::cout.flush();
}

bool check_row(ll i, vec<ll> &selected) {
  if(rows[i].size() == 1) {
    B t_b = buttons[rows[i][0]];
    buttons[rows[i][0]].active = false;
    if(!rows_done[i]) {
      // select the button and switch done_state on rows and cols
      selected.push_back(rows[i][0]);
      rows_done[t_b.row] = !rows_done[t_b.row];
      cols_done[t_b.col] = !cols_done[t_b.col];
    } 
    // remove the button from column
    cols[t_b.col].erase(std::remove(cols[t_b.col].begin(), cols[t_b.col].end(), rows[i][0]), cols[t_b.col].end());

    // remove the button from row and from count
    rows[i].pop_back();
    m--;
    return true;
  }
  return false;
}

bool check_col(ll i, vec<ll> &selected) {
  if(cols[i].size() == 1) {
    B t_b = buttons[cols[i][0]];
    buttons[cols[i][0]].active = false;
    if(!cols_done[i]) {
      // select the button and switch done_state on rows and cols
      selected.push_back(cols[i][0]);
      rows_done[t_b.row] = !rows_done[t_b.row];
      cols_done[t_b.col] = !cols_done[t_b.col];
    }

    // remove the button from column
    rows[t_b.row].erase(std::remove(rows[t_b.row].begin(), rows[t_b.row].end(), cols[i][0]), rows[t_b.row].end());
        
    // remove the button from row and from count
    cols[i].pop_back();
    m--;
    return true;
  }
  return false;
}

void print_mat() {
  vec<vec<bool>> mat(n, vec<bool>(n, false));
  for(int i = 1; i < buttons.size(); i++) {
    auto &[r, c, a] = buttons[i];
    if(a) {
      mat[r - 1][c - 1] = true;
    }
  }

  for(const auto &r : mat) {
    for(auto v : r) {
      if(v) {
        std::cout<<"X";
      } else {
        std::cout<<".";
      }
    }
    std::cout<<"\n";
  }
}