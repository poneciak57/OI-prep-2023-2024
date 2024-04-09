#include <bits/stdc++.h>
#define LLINF 100000000000000007

using namespace std;
typedef long long ll;
typedef string str;
typedef pair<ll,ll> llp;
template <typename T> using vec = vector<T>;

ll det(llp A, llp B, llp C) {
	return (B.first - A.first) * (C.second - A.second) - (B.second - A.second) * (C.first - A.first);
}

int n;
vec<llp> points;
vec<llp> otoczka;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin>>n;
	points = vec<llp>(n);
	for(int i = 0; i < n; i++) cin>>points[i].first>>points[i].second;

	sort(points.begin(), points.end(), [](llp p1, llp p2) {
		return p1.first < p2.first || (p1.first == p2.first && p1.second < p2.second);
	});

	otoczka.push_back(points[0]);
	otoczka.push_back(points[1]);
	for(int i = 2; i < n; i++) {
		while(otoczka.size() > 1 && det(otoczka[otoczka.size() - 2], otoczka[otoczka.size() - 1], points[i]) < 0) otoczka.pop_back();
		otoczka.push_back(points[i]);
	}
	for(int i = n - 2; i >= 0; i--) {
		while(otoczka.size() > 1 && det(otoczka[otoczka.size() - 2], otoczka[otoczka.size() - 1], points[i]) < 0) otoczka.pop_back();
		otoczka.push_back(points[i]);
	}

	otoczka.pop_back();
	cout<<otoczka.size()<<"\n";
	for(auto [x, y] : otoczka) cout<<x<<" "<<y<<"\n";

	cout.flush();
	return 0;
}