// :80 <enter>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pil;
typedef pair<ll, int> pli;
typedef pair<double,double> pdd;
#define SQ(i) ((i)*(i))
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) int(i.size())
#define FOR(i, j, k, in) for (int i=j ; i<(k) ; i+=in)
#define RFOR(i, j, k, in) for (int i=j ; i>=(k) ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define REP1(i,j) FOR(i, 1, j+1, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define ALL(_a) _a.begin(),_a.end()
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define X first
#define Y second
#ifdef jayinnn
#define TIME(i) Timer i(#i)
#define debug(...) do{\
    fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);\
    _do(__VA_ARGS__);\
}while(0)
template<typename T>void _do(T &&_x){cerr<<_x<<endl;}
template<typename T,typename ...S> void _do(T &&_x,S &&..._t){cerr<<_x<<", ";_do(_t...);}
template<typename _a,typename _b> ostream& operator << (ostream &_s,const pair<_a,_b> &_p){return _s<<"("<<_p.X<<","<<_p.Y<<")";}
template<typename It> ostream& _OUTC(ostream &_s,It _ita,It _itb)
{
    _s<<"{";
    for(It _it=_ita;_it!=_itb;_it++)
    {
        _s<<(_it==_ita?"":",")<<*_it;
    }
    _s<<"}";
    return _s;
}
template<typename _a> ostream &operator << (ostream &_s,vector<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s,set<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s,deque<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a,typename _b> ostream &operator << (ostream &_s,map<_a,_b> &_c){return _OUTC(_s,ALL(_c));}
template<typename _t> void pary(_t _a,_t _b){_OUTC(cerr,_a,_b);cerr<<endl;}
#define IOS()
class Timer {
private:
    string scope_name;
    chrono::high_resolution_clock::time_point start_time;
public:
    Timer (string name) : scope_name(name) {
        start_time = chrono::high_resolution_clock::now();
    }
    ~Timer () {
        auto stop_time = chrono::high_resolution_clock::now();
        auto length = chrono::duration_cast<chrono::microseconds>(stop_time - start_time).count();
        double mlength = double(length) * 0.001;
        debug(scope_name, mlength);
    }
};
#else
#define TIME(i)
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const ll MAXN = 100005;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int check(vector<int>& a){
    int n = a.size();
    if(a[0] == 0 and a[n-1] == 0) return 1;
    else if(a[0] < 0) return -1;
    else return 0;
}

void solve(){
    ll n, m; // n: # of country, m: highway
    cin >> n >> m;
    vector<ll> a(n, 0);
    for(int i=0;i<n;i++){
        cin >> a[i];
    }
    int u, v;
    REP(i, m){
        cin >> u >> v;
        u --;
        v --;
        a[u] --;
        a[v] --;
    }
    sort(ALL(a));
    a.push_back(0);
    reverse(ALL(a));
    int cnt = 0;
    for(int i=1;i<=n;i++){
        if(a[i] >= n || a[i] < 0){
            cout << "No" << endl;
            return;
        }
        cnt += a[i];
    }
    debug(cnt);
    if(cnt & 1LL){
        cout << "No" << endl;
        return;
    }
    vector<ll> dp(n+1, 0);
    for(int i=1;i<=n;i++){
        dp[i] = dp[i-1] + a[i];
    }
    debug(dp);
    for(ll k=1;k<=n;k++){
        debug(a, k);
        // (idx - 1) - (k + 1) + 1
        ll idx = upper_bound(a.begin()+k+1, a.end(), k, greater<ll>()) - a.begin();
        if(dp[k] > k * (idx - 2LL)  + dp[n] - dp[idx-1]){
            cout << "No" << endl;
            return;
        }
    }   
    cout << "Yes" << endl;
    return;
    // while(true){
    //     int x = check(a);
    //     if(x == -1){
    //         cout << "No" << endl;
    //         return;
    //     } else if(x == 1){
    //         cout << "Yes" << endl;
    //         return;
    //     }
    //     int sz = a.size();
    //     for(int i=1;i<a[sz-1]+1;i++){
    //        a[sz-1-i] --;
    //     }
    //     vector<int> tmp;
    //     merge(a.begin(), a.begin()+(sz-1-a[sz-1]), a.begin()+(sz-1-a[sz-1]), a.end()-1, back_inserter(tmp));
    //     a = tmp;
    //     debug(a);+ (idx - 2LL) * k
    // }
    

}

/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();
    int t = 1;
    cin >> t;
    while(t--){
        solve();
    }

    return 0;
}

