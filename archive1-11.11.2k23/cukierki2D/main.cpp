#include <bits/stdc++.h>
typedef long long ll;
typedef std::string str;

template <typename T>
using vec = std::vector<T>;


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    ll n, m;
    std::cin>>n>>m;

    vec<vec<ll>> sumy(n + 1, vec<ll>(m + 1, 0));

    for (ll i = 1; i <= n; i++)
    {
        for (ll j = 1; j <= m; j++)
        {
            ll t;
            std::cin>>t;
            sumy[i][j] = sumy[i - 1][j] + sumy[i][j - 1] + t - sumy[i - 1][j - 1];
        }
    }

    ll q;
    std::cin>>q;
    while (q--)
    {
        ll x1, y1, x2, y2;
        std::cin>>x1>>y1>>x2>>y2;
        std::cout<<(sumy[x2][y2] - sumy[x2][y1-1] - sumy[x1 - 1][y2] + sumy[x1 - 1][y1 - 1])<<"\n";
    }
    
    


    std::cout.flush();
}