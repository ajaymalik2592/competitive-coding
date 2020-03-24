#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>
#include <map>
#include <list>
#include <time.h>
#include <math.h>
#include <random>
#include <deque>
#include <queue>
#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include <iomanip>
#include <bitset>
#include <sstream>
#include <chrono>
#include <cstring>
 
using namespace std;
 
typedef long long ll;
 
#ifdef iq
  mt19937 rnd(228);
#else
  mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());
#endif
 
const int N = 3e5 + 7;
 
int add[4 * N];
int t[4 * N];
 
void upd(int v, int x) {
  add[v] += x;
  t[v] += x;
}
 
void push(int v) {
  if (add[v]) {
    upd(v * 2 + 1, add[v]);
    upd(v * 2 + 2, add[v]);
    add[v] = 0;
  }
}
 
void upd(int v, int l, int r, int tl, int tr, int x) {
  if (tl >= r || tr <= l) {
    return;
  }
  if (tl >= l && tr <= r) {
    upd(v, x);
  } else {
    int tm = (tl + tr) / 2;
    push(v);
    upd(v * 2 + 1, l, r, tl, tm, x);
    upd(v * 2 + 2, l, r, tm, tr, x);
    t[v] = min(t[v * 2 +1 ], t[v * 2 + 2]);
  }
}
 
int main() {
#ifdef iq
  freopen("a.in", "r", stdin);
#endif
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin >> n;
  vector <int> p(n), q(n);
  vector <int> rev(n + 1);
  for (int i = 0; i < n; i++) {
    cin >> p[i];
    rev[p[i]] = i;
  }
  for (int i = 0; i < n; i++) {
    cin >> q[i];
    q[i]--;
  }
  auto decrease = [&] (int x) {
    upd(0, 0, rev[x] + 1, 0, n, -1);
    if (t[0] >= 0) {
      return true;
    } else {
      upd(0, 0, rev[x] + 1, 0, n, 1);
      return false;
    }
  };
  int x = n;
  for (int i = 0; i < n; i++) {
    while (decrease(x)) x--;
    cout << x << ' ';
    upd(0, 0, q[i] + 1, 0, n, 1);
  }
}
