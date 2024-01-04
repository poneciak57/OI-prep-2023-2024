#include <bits/stdc++.h>
#define LL_INF 1000000000000000007

typedef long long ll;
typedef std::string str;
typedef std::pair<ll, ll> llPair;

template <typename T>
using vec = std::vector<T>;

using namespace std;

struct Node {
  // int parrent;
  vec<int> childs;
};

vec<Node> tree;


/**
 * Aby rozwiazac zadanie najpierw musimy znalezc wszystkie cykle w grafie i dodac ich wierzcholki do listy (lub od razu dodac wierzcholki ktore sa korzeniami odstajacych drzew)
 * zamienic 
*/
int main() {
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  
  
  cout.flush();
}
