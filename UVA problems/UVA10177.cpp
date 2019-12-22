#include <bits/stdc++.h>

#define ll long long

using namespace std;

ll power(ll n, ll d){
	ll p = 1;

	for(ll i=0; i<d; i++)
		p *= n;

	return p;
}

int main(){
	ll n;

	ll c[5], r[5];

	while(cin >> n){

		for(ll d=2; d<5; d++){
			ll sum =  0;

			for(ll i=1; i<=n; i++)
				sum += power(i, d);
			

			c[d] = sum;
			r[d] = power(((n+1)*n)/2, d) - c[d];
		}	

		cout << c[2] << " " << r[2] << " " << c[3] << " " << r[3] << " " << c[4] << " " << r[4] << endl;
	}


	return 0;
}