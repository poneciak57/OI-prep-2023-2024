#include <bits/stdc++.h>
typedef long long ll;
typedef std::string str;

template <typename T>
using vec = std::vector<T>;


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    ll n;
    std::cin>>n;

    vec<ll> sum(n+1, 0);

    for(int i = 1; i<n+1; i++)
    {
        ll s;
        std::cin>>s;
        sum[i] = sum[i-1] + s;
    }

    ll k;
    std::cin>>k;
    while (k--)
    {
        ll f, l;
        std::cin>>f>>l;
        std::cout<<sum[l] - sum[f-1]<<"\n";
    }
    
    

    std::cout.flush();
}