#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

#pragma GCC optimize("Ofast")

#define rep(i,a,b) for(__typeof(b) i=a;i<b;++i)

//#define endl "\n"
#define fs first
#define sc second
#define pb emplace_back

typedef long long ll;
typedef pair<ll,ll> pl;
typedef vector<ll> vl;

const ll inf = ~((ll)1<<(ll)63);

ll n,s,q,e,l,t=0;
vector<vector<pl>> edg,jmp;
vl magic,dist;
vector<pl> when,enx,md;
vector<bool> shop;

bool inTree(ll a, ll b) // check if b is in subtree of a
{
	return enx[a].fs<=enx[b].fs&&enx[b].fs<=enx[a].sc;
}

void buildMagic(ll at, ll p, ll w)
{
	enx[at].fs = t++;
	md[at].sc = w;
	rep(i,0,edg[at].size())
		if(edg[at][i].sc != p) buildMagic(edg[at][i].sc,at,edg[at][i].fs + w);
	if(shop[at]) md[at].fs=md[at].sc;
	else md[at].fs = inf;
	rep(i,0,edg[at].size())
		if(edg[at][i].sc != p) md[at].fs = min(md[at].fs,md[edg[at][i].sc].fs);
	enx[at].sc = t++;
}

void buildLifting(ll at, ll p)
{
	jmp[at][0].fs = p;
	jmp[at][0].sc = md[at].fs;
	
	rep(i,1,l+1)
	{
		jmp[at][i].fs = jmp[jmp[at][i-1].fs][i-1].fs;
		jmp[at][i].sc = min(jmp[at][i-1].sc,jmp[jmp[at][i-1].fs][i-1].sc);
	}
	rep(i,0,edg[at].size())
		if(edg[at][i].sc != p) buildLifting(edg[at][i].sc,at);
}

ll minPath(ll a, ll b)
{
	ll ans = inf;
	for(ll i = l+1;i--;)
	{
		if(inTree(b,jmp[a][i].fs))
		{
			ans = min(ans,jmp[a][i].sc);
			a = jmp[a][i].fs;
		}
	}
	return min(ans,md[b].fs);
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
	md.resize(n);
	enx.resize(n);
	when.resize(n-1);
	shop.resize(n);

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

	buildMagic(e,e,0);
	rep(i,0,n)
		md[i].fs = md[i].fs - (2 * md[i].sc);
	buildLifting(e,e);

	rep(i,0,q)
	{
		ll r,f;
		cin >> r >> f;
		r--,f--;
		r = (inTree(when[r].fs,when[r].sc)?when[r].sc:when[r].fs); // make r the lower node
		if(inTree(r,f))
		{
			ll ans = md[f].sc + minPath(f,r);
			if(ans >= 100000000000001) cout << "oo" << endl;
			else cout << ans << endl;
		}
		else cout << "escaped" << endl;
	}
}
