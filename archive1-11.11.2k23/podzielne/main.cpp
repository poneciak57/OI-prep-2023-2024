#include <bits/stdc++.h>
typedef long long ll;
typedef std::string str;

template <typename T>
using vec = std::vector<T>;


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    ll a, b, k;
    std::cin>>a>>b>>k;

    ll from = a - a % k;
    ll to = b - b % k;

    ll result = ((to - from) / k) + !(a % k);

    std::cout<<result;


    std::cout.flush();
}