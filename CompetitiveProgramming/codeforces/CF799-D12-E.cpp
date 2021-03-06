/*
 * Maintain a set of values available freely without any restriction
 * at every point. First, select x part from common likes
 * and remaining k - x part from 2 separate likes as
 * mandatory, choose the others greedily.
 * Do it for every x from 0 to k, updating costs after
 * each updation.
 */
#include<bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

template<typename T>
using ordered_set = __gnu_pbds::tree<T, __gnu_pbds::null_type, less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>; // find_by_order(), order_of_key()
using ll = long long int;
using i64 = long long int;
#define all(vec) (vec).begin(),(vec).end()
template <typename T> inline void ckmax(T &x, T y) {if (y > x) x = y; }
template <typename T> inline void ckmin(T &x, T y) {if (y < x) x = y; }
#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cerr << *it << " =: " << a << endl;
    err(++it, args...);
}
template <typename T1, typename T2>
inline std::ostream& operator << (std::ostream& os, const std::pair<T1, T2>& buf) {
    return os << "(" << buf.first << ": " << buf.second << ")";
}
template<typename T>
inline std::ostream &operator << (std::ostream & os,const std::vector<T>& v) {
    bool first = true;
    os << "[";
    for(unsigned int i = 0; i < v.size(); i++) {
        if(!first) os << ", ";
        os << v[i];
        first = false;
    }
    return os << "]";
}
template<typename T>
inline std::ostream &operator << (std::ostream & os,const std::multiset<T>& v) {
    bool first = true;
    os << "{";
    for (typename std::set<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii) {
        if(!first) os << ", ";
        os << *ii;
        first = false;
    }
    return os << "}";
}
template<typename T1, typename T2>
inline std::ostream &operator << (std::ostream & os,const std::map<T1, T2>& v) {
    bool first = true;
    os << "{";
    for (typename std::map<T1, T2>::const_iterator ii = v.begin(); ii != v.end(); ++ii) {
        if(!first) os << ", ";
        os << *ii ;
        first = false;
    }
    return os << "}";
}
template<typename T>
inline std::ostream &operator << (std::ostream & os,const vector<vector<T>>& v) {
    for (auto &u: v) os << '\n' << u;
    return os;
}
template<typename T>
void finish(T ans) {cout << ans << '\n'; exit(0);}
const int MOD = 1e9 + 7;
const long long INF = 1e18;
const double EPS = 1e-6;
#define PI 3.14159265358979323846
#define siz(v) (int((v).size()))
/***********************************************************************/

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m, k;
    cin >> n >> m >> k;
    vector<i64> c(n);
    for (i64 &i: c) cin >> i;
    vector<int> mask(n, 0);
    int xx;
    cin >> xx;
    for (int i = 0; i < xx; ++i) {
        int id;
        cin >> id; --id;
        mask[id] |= 1;
    }
    cin >> xx;
    for (int i = 0; i < xx; ++i) {
        int id;
        cin >> id; --id;
        mask[id] |= 2;
    }
    vector<vector<pair<i64,int>>> a(4);
    set<pair<i64,int>> avail;
    for (int i = 0; i < n; ++i) {
        a[mask[i]].emplace_back(c[i], i);
        avail.emplace(c[i], i);
    }
    for (auto &v: a) sort(all(v));
    i64 ans = INF, cost = 0;
    set<pair<i64,int>> have;
    int cnt = 0;
    int y = min({k, siz(a[1]), siz(a[2])}), x = k - y;
    if (x > siz(a[3])) finish(-1);
    for (int i = 0; i < x; ++i) {
        cost += a[3][i].first;
        cnt++;
        avail.erase(a[3][i]);
    }
    for (int j: {1, 2}) {
        for (int i = 0; i < y; ++i) {
            cost += a[j][i].first;
            cnt++;
            avail.erase(a[j][i]);
        }
    }
    while (cnt < m) {
        if (avail.empty()) finish(-1);
        cost += avail.begin()->first;
        cnt++;
        avail.erase(avail.begin());
    }
    if (cnt == m) ans = cost;
    
    for (++x; x <= k && x <= siz(a[3]); ++x) {
        if (avail.count(a[3][x - 1])) {
            cnt++;
            cost += a[3][x - 1].first;
            avail.erase(a[3][x - 1]);
        }
        cnt -= 2;
        --y;
        cost -= a[1][y].first + a[2][y].first;
        avail.insert(a[1][y]);
        avail.insert(a[2][y]);
        while (cnt < m) {
            assert(!avail.empty());
            cost += avail.begin()->first;
            cnt++;
            avail.erase(avail.begin());
        }
        if (cnt == m && cost < ans) ans = cost;
    }
    if (ans == INF) ans = -1;
    cout << ans << '\n';
    
    return 0;
}
