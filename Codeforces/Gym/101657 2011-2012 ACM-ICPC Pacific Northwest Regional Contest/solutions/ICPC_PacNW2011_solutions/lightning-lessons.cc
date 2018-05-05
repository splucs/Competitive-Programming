#include <iostream>
#include <string>

using namespace std;

template <class It>
bool any(It i, It end)
{
    for (; i != end; ++i)
        if (*i)
            return true;
    return false;
}

int main()
{
    int n; cin >> n;
    for (int _ = 0; _ < n; ++_)
    {
        int bolt[20];
        int m; cin >> m;
        for (int i = 0; i < m; ++i)
            cin >> bolt[i];

        int z = 0;
        for (; any(bolt, bolt + m - z); ++z)
            for (int i = 1; i < m - z; ++i)
                bolt[i - 1] = bolt[i] - bolt[i - 1];

        if (bolt[0] > 0)
            cout << "*fizzle*\n";
        else if (bolt[0] < 0)
            cout << "*bunny*\n";
        else
            cout << string(z, 'z') << "ap!\n";
    }

    return 0;
}
