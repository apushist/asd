#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

int main()
{

    int n;
    cin >> n; cin.ignore();


    vector<long long> v;
    for (int i = 0; i < n; i++) {
        long long housevalue;
        cin >> housevalue; cin.ignore();
        v.push_back(housevalue);
    }
    if (n == 1) {
        cout << v[0] << endl;

    }
    else {
        std::vector<long long> res(n);
        res[0] = std::max(0LL, v[0]);
        res[1] = std::max(res[0], v[1]);

        for (int i = 2; i < n; ++i) {
            res[i] = std::max(res[i - 1], v[i] + res[i - 2]);
        }
        cout << res[n - 1] << endl;
    }
}