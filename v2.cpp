#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>

using namespace std;

#pragma GCC optimize("Ofast")

#define rep(i,a,b) for(__typeof(b) i=a;i<b;++i)

#define endl "\n"
#define fs first
#define sc second
#define pb emplace_back

typedef long long ll;
typedef pair<ll,ll> pl;
typedef vector<ll> vl;

const ll inf = ~((ll)1<<(ll)63);

ll n,s,q,e,l,t=0;
vector<vector<pl>> edg,jmp;
vl dist, mem;
vector<pl> when,enx;
vector<bool> shop;

bool inTree(ll a, ll b) // check if b is in subtree of a
{
	return enx[a].fs<=enx[b].fs&&enx[b].fs<=enx[a].sc;
}

ll dfs(ll at, ll p, ll w)
{
	enx[at].fs = t++;
	dist[at] = w;
	mem[at] = (shop[at]?0:inf);
	ll ans = (shop[at]?w:inf);
	rep(i,0,edg[at].size())
	{
		if(edg[at][i].sc != p)
		{
			ll tmp = dfs(edg[at][i].sc, at, w+edg[at][i].fs);
			if(tmp!=inf && tmp < ans)
			{
				ans = tmp;
				mem[at] = tmp - w;
			}
		}
	}
	enx[at].sc = t++;
	return ans;
}

void buildLifting(ll at, ll p, ll w)
{
	jmp[at][0].fs = p;
	jmp[at][0].sc = min(mem[at],(mem[p]==inf?inf:w+mem[p]));

	rep(i,1,l+1)
	{
		pl nxt = jmp[jmp[at][i-1].fs][i-1];
		jmp[at][i].fs = nxt.fs;
		jmp[at][i].sc = min(jmp[at][i-1].sc, (nxt.sc==inf?inf:dist[at]-dist[nxt.fs]+mem[nxt.fs]));
	}
	rep(i,0,edg[at].size())
		if(edg[at][i].sc != p)buildLifting(edg[at][i].sc,at,edg[at][i].fs);
}

ll minPath(ll f, ll r)
{
	ll at = f, ans = mem[f];
	for(ll i = l+1;i--;)
	{
		pl nxt = jmp[at][i];
		if(inTree(r,nxt.fs))
		{
			ans = min(ans,(nxt.sc==inf?inf:dist[f]-dist[at]+nxt.sc));
			if(nxt.fs == r)break;
			i = l+1;
			at = nxt.fs;
		}

	}
	return ans;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> s >> q >> e;
	e--;
	l=ceil(log2(n));
	edg.resize(n);
	jmp.resize(n,vector<pl>(l+1));
	dist.resize(n);
	shop.resize(n,false);
	mem.resize(n, inf);
	enx.resize(n);
	when.resize(n-1);

	rep(i,0,n-1)
	{
		ll a,b,w;
		cin >> a >> b >> w;
		a--,b--;
		edg[a].pb(pl{w,b});
		edg[b].pb(pl{w,a});
		when[i]=pl{a,b};
	}

	rep(i,0,s)
	{
		ll tmp;
		cin >> tmp;
		shop[tmp-1] = true;
	}

	dfs(e,e,0);
	buildLifting(e,e,0);

	rep(i,0,n)
	{
		cout << "Jmp " << i+1;
		rep(j,0,l+1)
		{
			cout << " " << jmp[i][j].fs + 1 << "," << jmp[i][j].sc;
		}
		cout << endl;
	}

	rep(i,0,q)
	{
		ll r,f;
		cin >> r >> f;
		r--,f--;
		r = (inTree(when[r].fs,when[r].sc)?when[r].sc:when[r].fs); // make r the lower node
		if(inTree(r,f))
		{
			ll ans = minPath(f,r);
			if(ans > 100000000000000) cout << "oo" << endl;
			else cout << ans << endl;
		}
		else cout << "escaped" << endl;
	}
}
