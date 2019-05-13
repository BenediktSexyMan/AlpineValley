#include <iostream>
#include <cstdlib>
#include <vector>
#include <time.h>

using namespace std;

#define rep(i,a,b) for(__typeof(b) i = a; i < b; ++i)

/*void connect(vector<int>& l, int e)
{
	int ca = rand() % (l.size()+1);
	vector<int> l2(ca);
	rep(i,0,ca)
	{
		int c = l[i];
		cout << e + 1 << " " << c + 1 << " " << rand() % 5 + 1 << endl;
		l2.emplace_back(c);
	}
	l.erase(l.begin(),l.begin()+ca);
	rep(i,0,ca)
	{
		connect(l,l2[i]);
	}
}*/

int main()
{
	time_t t;
	srand((unsigned) time(&t));
	/*int n,s,q,e;
	n = rand() % 99999 + 2;
	s = rand() % 100 + 1;
	q = rand() % 99999 + 2;
	e = rand() % n;
	vector<int> l;
	l.reserve(n-1);
	vector<int> shop;
	vector<vector<int>> edg(n);
	shop.reserve(n);
	
	rep(i,0,n)
	{
		if(i != e)
		{
			l.emplace_back(i);
			if((rand() % 100 + 1) >= s)shop.emplace_back(i+1);
		}
	}
	if(!shop.size())shop.emplace_back(1);

	cout << n << " " << shop.size() << " " << q << " " << e + 1 << endl;

	while(l.size()) connect(l,e);

	rep(i,0,shop.size())
	{
		cout << shop[i] << endl;
	}

	rep(i,0,q)
	{
		cout << rand() % (n-1) + 1 << " " << rand() % n + 1 << endl;
	}
	cout.flush();*/

	int n,s,q,e;
	n = rand() % 10 + 2;
	s = rand() % (n-1) + 1;
	q = rand() % 10 + 2;
	e = rand() % n + 1;

	cout << n << " " << s << " " << q << " " << e << endl;

	rep(i,2,n+1)
	{
		cout << i - 1 << " " << i << " " << rand() % 1000 + 1 << endl;
	}

	vector<int> l;
	l.reserve(n);
	rep(i,0,n)
	{
		if(i != e-1)l.emplace_back(i+1);
	}
	rep(i,0,s)
	{
		int c = rand() % l.size();
		cout << l[c] << endl;
		l.erase(l.begin()+c);
	}
	rep(i,0,q)
	{
		cout << rand() % (n-1) + 1 << " " << rand() % n + 1 << endl;
	}


	return 0;
}
