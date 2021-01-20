#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for (auto i=(a); i<(b); ++i)
#define iter(it,c) for (auto it = (c).begin(); it != (c).end(); ++it)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef long long ll;
const int INF = 2147483647;

struct string_rx {
    string s;
    bool is_singleton;
    string_rx(string _s="", bool _is_singleton=true): s(_s), is_singleton(_is_singleton) { }
    string_rx as_singleton() const {
        if (is_singleton) {
            return *this;
        } else {
            return string_rx("(" + s + ")", true);
        }
    }
    string_rx unite(const string_rx &other) {
        return string_rx(s + "|" + other.s, false);
    }
    string_rx concat(const string_rx &other) {
        return string_rx(as_singleton().s + other.as_singleton().s, true);
    }
};

struct len_rx {
    int l;
    bool is_singleton;
    len_rx(int _l=0, bool _is_singleton=true): l(_l), is_singleton(_is_singleton) { }
    len_rx as_singleton() const {
        if (is_singleton) {
            return *this;
        } else {
            return len_rx(1 + l + 1, true);
        }
    }
    len_rx unite(const len_rx &other) {
        return len_rx(l + 1 + other.l, false);
    }
    len_rx concat(const len_rx &other) {
        return len_rx(as_singleton().l + other.as_singleton().l, true);
    }
};

template <class rx>
rx to_regex(list<tuple<int, rx, int> > edges, vi elim_order) {
    for (int elim : elim_order) {
        map<int, rx> left, right;
        for (auto [from,val,to] : edges) {
            if (to == elim) {
                left[from] = val;
            } else if (from == elim) {
                right[to] = val;
            }
        }
        map<ii,rx> res;
        for (auto [from,val,to] : edges) {
            if (left.find(from) != left.end() && right.find(to) != right.end()) {
                res[ii(from,to)] = val;
            }
        }
        iter(lt,left) {
            iter(rt,right) {
                ii key(lt->first, rt->first);
                rx here = lt->second.concat(rt->second);
                if (res.find(key) == res.end()) {
                    res[key] = here;
                } else {
                    res[key] = res[key].unite(here);
                }
            }
        }
        for (auto it = edges.begin(); it != edges.end(); ) {
            auto [from,val,to] = *it;
            if (from == elim || to == elim || (left.find(from) != left.end() && right.find(to) != right.end())) {
                auto jt = it;
                ++it;

                edges.erase(jt);
            } else {
                ++it;
            }
        }
        iter(it,res) {
            edges.push_back({ it->first.first, it->second, it->first.second });
        }
    }
    assert(edges.size() == 1);
    return get<1>(edges.front()).as_singleton();
}

const double seconds = 10.0;
double curtime() {
  return static_cast<double>(clock()) / CLOCKS_PER_SEC;
}

int main(int argc, char *argv[]) {
    default_random_engine rng;
    rng.seed(1341);

    int n, m, start, final_count;
    cin >> n >> m >> start >> final_count;
    assert(final_count == 1);

    map<ii, vector<string> > edges;
    rep(i,0,m) {
        int from, to;
        string digit;
        cin >> from >> digit >> to;
        edges[ii(from,to)].push_back(digit);
    }

    list<tuple<int, string_rx, int> > string_edges;
    list<tuple<int, len_rx, int> > len_edges;
    iter(it,edges) {
        stringstream ss;
        for (size_t i = 0; i < it->second.size(); i++) {
            ss << it->second[i];
        }

        string s = ss.str();
        if (s.size() > 1) {
            s = "[" + s + "]";
        }

        string_edges.push_back({it->first.first, string_rx(s), it->first.second});
        len_edges.push_back({it->first.first, len_rx(s.size()), it->first.second});
    }

    int end;
    cin >> end;

    vi perm;
    rep(i,0,n) {
        if (i != start && i != end) {
            perm.push_back(i);
        }
    }

    int mn = INF;
    vi best_perm;
    shuffle(perm.begin(), perm.end(), rng);

    uniform_real_distribution<double> randfloat(0.0, 1.0);
    uniform_int_distribution<int> randint(0, n - 4);
    int score = to_regex(len_edges, perm).l;
    int iters = 0;

    double T0 = 1e4, T1 = 1e-3,
           progress = 0, temp = T0,
           starttime = curtime();
    while (true) {
        if (!(iters & ((1 << 4) - 1))) {
            progress = (curtime() - starttime) / seconds;
            temp = T0 * pow(T1 / T0, progress);
            if (progress > 1.0) {
                break;
            }
        }
        int a = randint(rng),
            b = randint(rng);
        if (a == b) continue;
        swap(perm[a], perm[b]);
        int delta = to_regex(len_edges, perm).l - score;
        if (delta <= 0 || randfloat(rng) < exp(-delta / temp)) {
            score += delta;
        } else {
            swap(perm[a], perm[b]);
        }
        if (score < mn) {
            mn = score;
            best_perm = perm;
        }
        iters++;
    }

    cout << to_regex(string_edges, best_perm).s << endl;

    return 0;
}

