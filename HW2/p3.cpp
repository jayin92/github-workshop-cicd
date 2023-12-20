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

vector<int> deg;
vector<vector<int>> adj;
vector<bool> vis;
vector<vector<int>> joint_end;


void dfs(int par, int cur, int dep){
    debug(par, cur);
    vis[cur] = true;
    if(deg[cur] == 1){
        joint_end[par].pb(dep);
        return;
    } else if(deg[cur] == 3){
        for(auto i: adj[cur]){
            if(!vis[i]){
                dfs(cur, i, 1);
            }
        }
    } else if(deg[cur] == 2){
        for(auto i: adj[cur]){
            if(!vis[i]){
                dfs(par, i, dep+1);
            }
        }
    }
}

void dfs_order(vector<int>& order, int start, int cur, int end){
    vis[cur] = true;
    if(cur == end){
        return;
    }
    if(deg[cur] == 3 and cur != start){
        order.push_back(cur);
    }
    for(auto i: adj[cur]){
        if(!vis[i]){
            dfs_order(order, start, i, end);
        }
    }
}


bool check(int x, vector<int> order, int y, vector<int>& tar){
    int sz = tar.size();
    if(x == tar[0] && y == tar.back()){
        bool flag = true;
        for(int i=1;i<sz-1;i++){
            if(order[i-1] != tar[i]){
                flag = false;
                break;
            }
        }
        if(flag) return true;
    }
    reverse(ALL(order));
    // y -> 
    if(y == tar[0] && x == tar.back()){
        bool flag = true;
        for(int i=1;i<sz-1;i++){
            if(order[i-1] != tar[i]){
                flag = false;
                break;
            }
        }
        if(flag) return true;
    }

    return false;
}

void solve(){
    int n;
    cin >> n;
    adj.resize(n);
    deg.resize(n, 0); // 0: leaf, 1: connect, 2: joint
    vis.resize(n, false);
    joint_end.resize(n);
    vector<int> joint;
    int u, v;
    for(int i=0;i<n-1;i++){
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
        deg[u] ++;
        deg[v] ++;
    }
    for(int i=0;i<n;i++){
        if(deg[i] == 3) joint.push_back(i);
    }
    int jsz = joint.size();
    
    int m;
    cin >> m;
    vector<int> tar(m);
    for(int i=0;i<m;i++){
        cin >> tar[i];
    }
    if(jsz != m){
        cout << "NO" << endl;
        return;
    }
    dfs(-1, joint[0], 0);
    int start, end;
    start = end = -1;
    for(auto i: joint){
        if(joint_end[i].size() == 2){
            if(start == -1) start = i;
            else end = i;
        }
    }
    debug(start, end);
    debug(joint_end[start], joint_end[end]);
    fill(ALL(vis), false);
    vector<int> order;
    dfs_order(order, start, start, end);
    vector<int> cnt;
    for(auto i: order){
        assert(joint_end[i].size() == 1);
        cnt.push_back(joint_end[i][0]);
    }
    debug(cnt);
    for(int i=0;i<4;i++){
        int x = joint_end[start][i & 1];
        int y = joint_end[end][(i >> 1) & 1];
        if(check(x, cnt, y, tar)){
            cout << "YES" << endl;
            return;
        }
    }
    cout << "NO" << endl;

    return;

    
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


