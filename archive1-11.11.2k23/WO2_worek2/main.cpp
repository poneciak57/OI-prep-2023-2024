#include <bits/stdc++.h>
typedef long long ll;
typedef std::string str;

template <typename T>
using vec = std::vector<T>;


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    ll n, q, t;

    std::cin>>n;
    vec<ll> liczby;

    while (n--)
    {
        std::cin>>t;
        liczby.push_back(t);
    }
    std::sort(liczby.begin(), liczby.end());

    std::cin>>q;
    while (q--)
    {
        std::cin>>t;
        ll b = -1;
        ll e = liczby.size() - 1;
        ll m;

        while ((b + 1) < e) 
        {
            m = (e + b)/2;
            if (liczby[m] > t) {
                e = m;
            } else if(liczby[m] <= t) {
                b = m;
            }
        }

        ll ending = e;
        
        b = -1;
        e = liczby.size() - 1;
        while ((b + 1) < e) 
        {
            m = (e + b)/2;
            if (liczby[m] >= t) {
                e = m;
            } else if(liczby[m] < t) {
                b = m;
            }
        }

        ll begining = b;
        ll wynik = (ending - begining);
        std::cout<<wynik - (liczby[ending] != t)<<"\n";
    }
    
    

    std::cout.flush();
}