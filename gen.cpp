#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
const int INF = 2147483647;
#define rep(i,a,b) for (__typeof(a) i=(a); i<(b); ++i)
#define iter(it,c) for (__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)

bool is_leap_year(int y) {
    if (y % 4 != 0) return false;
    if (y % 100 != 0) return true;
    if (y % 400 != 0) return false;
    return true;
}

int month_len(int y, int m) {
    switch (m) {
        case 1: return 31;
        case 2: return is_leap_year(y) ? 29 : 28;
        case 3: return 31;
        case 4: return 30;
        case 5: return 31;
        case 6: return 30;
        case 7: return 31;
        case 8: return 31;
        case 9: return 30;
        case 10: return 31;
        case 11: return 30;
        case 12: return 31;
    }
    assert(false);
}

int main() {
    for (int y = 1800; y <= 2099; y++) {
        for (int m = 1; m <= 12; m++) {
            int len = month_len(y,m);
            for (int d = 1; d <= len; d++) {
                for (int x = 20; x <= 99; x++) {
                    stringstream ss;
                    if (d < 10) ss << "0";
                    ss << d;
                    if (m < 10) ss << "0";
                    ss << m;
                    if (y % 100 < 10) ss << "0";
                    ss << y % 100;
                    ss << x;
                    string cur = ss.str();
                    int v = 0;
                    for (int i = 0; i < cur.size(); i++) {
                        v += (cur[i] - '0') * ((7-i%6)%6 + 2);
                    }
                    v = (11 - v % 11) % 11;
                    if (v == 10) continue;
                    ss << v;
                    ss << (y / 100 % 10);
                    printf("%s\n", ss.str().c_str());
                }
            }
        }
    }

    return 0;
}

