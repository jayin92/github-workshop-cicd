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

void solve(){
    int n;
    cin >> n;
    vector<string> a(n);
    vector<bool> valid(n, true);
    for(auto &i: a) cin >> i;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i != j and a[i].size() >= a[j].size()){
                int szi = a[i].size();
                int szj = a[j].size();
                for(int k=0;k<=szi-szj;k++){
                    debug(a[i].substr(k, szj), a[j]);
                    if(a[i].substr(k, szj) == a[j]){
                        valid[j] = false;
                    }
                }
            }
        }
    }
    vector<string> b;
    for(int i=0;i<n;i++){
        if(valid[i]) b.push_back(a[i]);
    }
    debug(a);
    a = b;
    n = a.size();
    sort(ALL(a));
    debug(a);
    vector<vector<int>> overlap(n, vector<int>(n, 0));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i != j){
                int k = 0;
                int sz = min(a[i].size(), a[j].size());
                int szi = a[i].size();
                for(k=sz;k>=0;k--){
                    if(a[i].substr(szi-k, szi) == a[j].substr(0, k)){
                        overlap[i][j] = k;
                        break;
                    }                    
                }
            }
        }
    }
    debug(overlap);
    vector<vector<int>> dp(1 << n, vector<int>(n, 0));
    vector<vector<int>> par(1 << n, vector<int>(n, -1));
    int lim = (1 << n);
    for(int mask=1;mask<lim;mask++){
        for(int j=0;j<n;j++){
            if((mask >> j) & 1){
                int prev = mask ^ (1 << j);
                if(prev == 0) continue;
                for(int k=0;k<n;k++){
                    if((prev >> k) & 1){
                        int val = dp[prev][k] + overlap[k][j];
                        if(val > dp[mask][j]){
                            dp[mask][j] = val;
                            par[mask][j] = k;
                        }
                    }
                }
            }
        }
    }
    int tmp = 0;
    int mask = (1 << n) - 1;
    for(int i=0;i<n;i++){
        if(dp[mask][i] > tmp){
            tmp = dp[mask][i];
        }
    }
   
    vector<pair<string, int>> comb;
    for(int i=0;i<n;i++){
        mask = (1 << n) - 1;
        if(dp[mask][i] == tmp){
            int idx = i;
            vector<int> ans_idx;
            while(idx != -1){
                ans_idx.push_back(idx);
                int tidx = idx;
                idx = par[mask][idx];
                mask = mask ^ (1 << tidx);
            }
            reverse(ALL(ans_idx));
            int cnt = ans_idx.size();
            string stmp = a[ans_idx[0]];
            int ii;
            for(ii=1;ii<cnt;ii++){
                int o = overlap[ans_idx[ii-1]][ans_idx[ii]];
                stmp += a[ans_idx[ii]].substr(o);
            }
            comb.emplace_back(stmp, i);
        }
    }
    sort(ALL(comb));
    debug(comb);
    vector<int> ans_idx;
    int idx = comb[0].second;
    mask = (1 << n) - 1;
    while(idx != -1){
        ans_idx.push_back(idx);
        int tidx = idx;
        idx = par[mask][idx];
        if(idx == -1) break;
        mask = mask ^ (1 << tidx);
    }
    int cnt = ans_idx.size();
    debug(ans_idx);
    reverse(ALL(ans_idx));
    vector<bool> vis(n, false);
    for(auto i: ans_idx) vis[i] = true;
    for(int i=0;i<n;i++){
        if(!vis[i]){
            ans_idx.push_back(i);
        }
    }
    debug(ans_idx);
    string stmp = a[ans_idx[0]];
    int ii;
    for(ii=1;ii<cnt;ii++){
        int o = overlap[ans_idx[ii-1]][ans_idx[ii]];
        stmp += a[ans_idx[ii]].substr(o);
    }
    vector<string> ans = {stmp};
    for(;ii<n;ii++){
        ans.push_back(a[ans_idx[ii]]);
    }
    sort(ALL(ans));
    for(auto i: ans) cout << i;
    cout << endl;
}

/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();
    int t = 1;
    while(t--){
        solve();
    }

    return 0;
}

