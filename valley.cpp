#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

#pragma GCC optimize("Ofast")

#define rep(i,a,b) for(__typeof(b) i=a;i<b;++i)
#define iter(it,c) for(auto i=c.begin();i!=c.end();++i)

//#define endl "\n"
#define fs first
#define sc second
#define pb emplace_back

typedef long long ll;
typedef unsigned long long ul;
typedef pair<ll,ll> pl;
typedef pair<ul,ul> pu;
typedef vector<ll> vl;
typedef vector<ul> vu;
typedef vector<vl> vl2;
typedef vector<vu> vu2;


/*ul n,s,q,e;

vector<vector<ul>> up;
vector<pair<pu,vector<pu>>> tree;
vu dist;
vu d;
vector<vector<pu>> edg;
vector<pu> occ;
vector<ul> en;
vector<ul> ex;
ul timer = 0, l;

void make_tree(ul at, ul w)
{
	en[at]=timer;
	timer++;
	cout << at << " ";
	dist[at]=w;
	rep(i,0,edg[at].size())
	{
		pu nxt = edg[at][i];
		if(nxt.sc != tree[at].fs.sc)
		{
			tree[at].sc.pb(nxt);
			tree[nxt.sc].fs = pu{nxt.fs,at};
			make_tree(nxt.sc,w + nxt.fs);
		}
	}
	ex[at]=timer;
	timer++;
	cout << at << " ";
}

void shop(ul at, ul w)
{
	d[at] = min(d[at],w);
	if(at!=e)shop(tree[at].fs.sc, w + tree[at].fs.fs);
}


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> s >> q >> e;
	e--;
	tree.resize(n);
	dist.resize(n);
	occ.resize(n-1);
	edg.resize(n);
	en.resize(n);
	ex.resize(n);
	d.resize(n,(n+1)*1000000000);
	l = ceil(log2(n));
	up.resize(l+1,vector<ul>(n));

	rep(i,0,n-1)
	{
		ul a,b,w;
		cin >> a >> b >> w;
		a--;
		b--;
		edg[a].pb(pu{w,b});
		edg[b].pb(pu{w,a});
		occ[i]=pu{a,b};
	}

	tree[e] = pair<pu,vector<pu>>{pu{0,e},vector<pu>()};

	make_tree(e,0);
	cout << endl;

	rep(i,0,s)
	{
		ul tmp;
		cin >> tmp;
		shop(tmp-1,0);
	}

	rep(i,0,l+1)
	{
		rep(j,0,n)
		{
			if(i==0)
			{
				up[i][j] = min(d[j],tree[j].fs.fs + d[tree[j].fs.sc]);
			}
			else
			{
				//traverse up tree
				ul jmp = j;
				rep(k,0,i)
				{
					jmp = tree[jmp].fs.sc;
				}
				up[i][j] = min(up[i-1][j],dist[j]-dist[jmp]+up[i-1][jmp]);
			}
		}
	}

	rep(i,0,n)
	{
		cout << i << " " << d[i] << "\n\tparent: " << tree[i].fs.sc << "," << tree[i].fs.fs << "\n\tchildren:";
		rep(j,0,tree[i].sc.size())
		{
			cout << " " << tree[i].sc[j].sc << "," << tree[i].sc[j].fs;
		}
		cout << "\n\tjumps:";
		rep(j,0,l+1)
		{
			cout << " " << j << "," << up[j][i];
		}
		cout << endl;
	}

	rep(i,0,q)
	{
		ul r,f;
		cin >> r >> f;
		r--;
		f--;
		r = (en[occ[r].fs]>en[occ[r].sc]?occ[r].fs:occ[r].sc);
		if(en[r]<=en[f]&&en[f]<=ex[r])cout << 0 << endl;
		else cout << "escaped" << endl;
	}

	return 0;
}*/

const ll inf = ~((ll)1<<(ll)63);

ll n,s,q,e,l,timer=0;

vector<vector<pl>> edg;
vector<vector<ll>> jmpv,jmpm;
vector<ll> magic,en,ex,dist;
vector<pl> when;
vector<bool> shop;

bool inTree(ll a, ll b)
{
	return en[a]<=en[b]&&en[b]<=ex[a];
}

void buildMagic(ll at, ll p, ll w)
{
	//cout << "at: " << at << ", p: " << p << ", w: " << w << endl;
	en[at] = timer++;
	dist[at] = w;
	rep(i,0,edg[at].size())
	{
		if(edg[at][i].sc != p) buildMagic(edg[at][i].sc,at,edg[at][i].fs + w);
	}
	if(shop[at])
	{
		//cout << " shop at: " << at << endl;
		magic[at]=dist[at];
	}
	else 
	{
		//cout << "!shop at: " << at << endl;
		magic[at] = inf;
	}
	//cout << "building magic at " << at << " " << magic[at] << endl;
	rep(i,0,edg[at].size())
	{
		if(edg[at][i].sc != p) magic[at] = min(magic[at],magic[edg[at][i].sc]);
	}
	ex[at] = timer++;
}

void buildLifting(ll at, ll p)
{
	jmpv[at][0] = p;
	jmpm[at][0] = magic[at];
	//cout << "Building lifting for " << at << " : " << jmpv[at][0] << "," << jmpm[at][0];
	rep(i,1,l+1)
	{
		jmpv[at][i] = jmpv[jmpv[at][i-1]][i-1];
		//cout << " " << jmpv[at][i];
		jmpm[at][i] = min(jmpm[at][i-1],jmpm[jmpv[at][i-1]][i-1]);
		//cout << "," << jmpm[at][i];
	}
	//cout << endl;
	rep(i,0,edg[at].size())
	{
		if(edg[at][i].sc != p) buildLifting(edg[at][i].sc,at);
	}
}

ll minPath(ll a, ll b)
{
	ll ans = inf;
	for(ll i = l+1;i--;)
	{
		if(inTree(b,jmpv[a][i]))
		{
			//cout << jmpv[a][i] << " is in subtree of " << b << endl;
			//cout << "min1 " << b << ", [" << a << "][" << i << "], " << ans << ", " << jmpm[a][i] << endl;
			ans = min(ans,jmpm[a][i]);
			a = jmpv[a][i];
		}
		//else cout << jmpv[a][i] << " is not in subtree of " << b << endl;
	}
	//cout << "min1 " << ans << ", " << magic[b] << endl;
	return min(ans,magic[b]);
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> s >> q >> e;
	e--;
	l=ceil(log2(n));
	edg.resize(n);
	jmpv.resize(n,vector<ll>(l+1));
	jmpm.resize(n,vector<ll>(l+1));
	magic.resize(n);
	en.resize(n);
	ex.resize(n);
	dist.resize(n);
	when.resize(n-1);
	shop.resize(n);

	rep(i,0,n-1)
	{
		ll a,b,w;
		cin >> a >> b >> w;
		a--,b--;
		edg[a].pb(pu{w,b});
		edg[b].pb(pu{w,a});
		when[i]=pu{a,b};
	}

	rep(i,0,s)
	{
		ll tmp;
		cin >> tmp;
		shop[tmp-1] = true;
	}

	buildMagic(e,e,0);
	rep(i,0,n)
	{
		//cout << "Dist at " << i << ": " << dist[i] << endl;
	}
	rep(i,0,n)
	{
		//cout << i << ", " << dist[i] << ", " << magic[i] << endl;
		cout << "Changing magic at " << i << " from " << magic[i] << " to " << magic[i] << " - 2 * " << dist[i] << endl;
		magic[i] = magic[i] - (2 * dist[i]);
	}
	rep(i,0,n)
    {
        //cout << i << ": " << en[i] << ", " << ex[i] << endl;
        cout << "Magic at " << i << ": " << magic[i] << endl;
    }
	buildLifting(e,e);

	rep(i,0,n)
	{
		//cout << "Lifting at " << i << ":";
		rep(j,0,l+1)
		{
		//	cout << " " << jmpv[i][j] << "," << jmpm[i][j];
		}
		//cout << endl;
	}

	rep(i,0,q)
	{
		ll r,f;
		cin >> r >> f;
		r--,f--;
		//cout << when[r].fs << ", " << when[r].sc << endl;
		//if(inTree(when[r].fs,when[r].sc)) r = when[r].sc;
		//else r = when[r].fs;
		//r = (en[when[r].fs]<en[when[r].sc]&&en[when[r].sc]<ex[when[r].fs]?when[r].sc:when[r].fs); // make r lower node
		r = (inTree(when[r].fs,when[r].sc)?when[r].sc:when[r].fs); // make r lower node
		//cout << r << endl;
		if(inTree(r,f))
		{
			ll ans = dist[f] + minPath(f,r);
			if(ans >= 100000000000001) cout << "oo" << endl;
			else cout << ans << endl;
		}
		else cout << "escaped" << endl;
	}


}


