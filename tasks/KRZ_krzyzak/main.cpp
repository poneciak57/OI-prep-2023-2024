#include <bits/stdc++.h>
#define LLINF 100000000000000007

using namespace std;
typedef long long ll;
typedef string str;
template <typename T> using vec = vector<T>;

struct P { ll x; ll y; ll z; };

P get_vector(P A, P B) {
  return {B.x - A.x, B.y - A.y, B.z - A.z};
}

P iloczyn(P A, P B) {
  return {A.y * B.z - A.z * B.y, -1LL * (A.x * B.z - A.z * B.x), A.x * B.y - A.y * B.x};
}

bool check_if_parallel(P A, P B) {
  return (A.x * B.y == A.y * B.x) && (A.y * B.z == A.z * B.y) && (A.x * B.z == A.z * B.x);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	std::cout.tie(nullptr);

  int n;
  cin>>n;
  if(n <= 3) {
    cout<<"TAK";
    return 0;
  }
  vec<P> points(n);
  for(int i = 0; i < n; i++) cin>>points[i].x>>points[i].y>>points[i].z;

  bool ok = true;
  P AB = get_vector(points[0], points[1]);
  P AC = get_vector(points[0], points[2]);
  P ABxAC = iloczyn(AB, AC);
  // cout<<"ABxAC: ("<<ABxAC.x<<","<<ABxAC.y<<","<<ABxAC.z<<")\n";
  for(int i = 3; i < n; i++) {
    P V = get_vector(points[0], points[i]);
    P ABxV = iloczyn(AB, V);
    // cout<<"i: "<<i<<" il: ("<<ABxV.x<<","<<ABxV.y<<","<<ABxV.z<<")\n";
    if(!check_if_parallel(ABxAC, ABxV)) {
      ok = false;
      break;
    }
  }
  if(ok) cout<<"TAK";
  else cout<<"NIE";
  
	std::cout.flush();
	return 0;
}