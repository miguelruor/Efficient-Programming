#include <bits/stdc++.h>
#define ll long long

using namespace std;

int main(){
	int C; 
	cin >> C;

	for(int t=0; t<C; t++){
		ll c[21], d, n=1;
		ll degree, k;

		cin >> degree;

		for(int i=0; i<=degree; i++)
			cin >> c[i];

		cin >> d >> k;	

		while((d*n*(n+1))/2 < k){
			n++;
		}

		ll i=degree;
		ll ans=c[i];
		i--;

		while(i>=0){
			ans = ans*n+c[i];
			i--;
		}

		cout << ans << endl;
	}


	return 0;
}