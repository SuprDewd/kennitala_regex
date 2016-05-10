#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
template <class T> int size(const T &x) { return x.size(); }
const int INF = 2147483647;
#define rep(i,a,b) for (__typeof(a) i=(a); i<(b); ++i)
#define iter(it,c) for (__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)

struct node {
    int down[10];
    bool end;
} nds[20000000];
int cnt = 1;

int main() {
    memset(nds,-1,sizeof(nds));
    string s;
    while (cin >> s) {
        int at = 0;
        rep(i,0,size(s)) {
            int cur = s[i] - '0';
            if (nds[at].down[cur] == -1) {
                nds[at].down[cur] = cnt++;
                nds[at].end = false;
            }
            at = nds[at].down[cur];
        }
        nds[at].end = true;
    }
    int endcnt = 0, edgecnt = 0;
    rep(i,0,cnt) {
        if (nds[i].end) {
            endcnt++;
        }
        rep(j,0,10) {
            if (nds[i].down[j] != -1) {
                edgecnt++;
            }
        }
    }
    printf("%d %d %d %d\n", cnt, edgecnt, 0, endcnt);
    rep(i,0,cnt) {
        rep(j,0,10) {
            if (nds[i].down[j] != -1) {
                printf("%d %d %d\n", i, j, nds[i].down[j]);
            }
        }
    }
    rep(i,0,cnt) {
        if (nds[i].end) {
            printf("%d\n", i);
        }
    }
    return 0;
}

