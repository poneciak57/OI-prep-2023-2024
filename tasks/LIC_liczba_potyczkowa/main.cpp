#include <bits/stdc++.h>
typedef long long ll;
typedef std::string str;

template <typename T>
using vec = std::vector<T>;

ll count = 0;

ll fighting_number(ll n) {
    ll first = n % 10;

    str num = std::to_string(n);
    std::set<char> nums(num.begin(), num.end());

    for(char unum: nums) {
        switch (unum)
        {
            case '0': return 1; break;
            case '1': break;
            case '2': if(first%2 == 1) return 1; break;
            // case '3': if(sum%3 != 0) return 1; break;
            case '5': if(first == 0 || first == 5) return 1; break;
            // case '6': if(first%2 != 0 || sum%3 != 0) return 1; break;
            // case '9': if(sum%9 != 0) return 1; break;
            default: if(n%((int)unum - 48) != 0) return 1; break;
        }
    }
    count++;
    return 1;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    ll from, to;
    std::cin>>from>>to;

    ll i = from;
    while (i <= to)
    {
        i += fighting_number(i);
    }
    
    std::cout<<count;

    std::cout.flush();
}