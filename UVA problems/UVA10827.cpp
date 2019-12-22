#include <bits/stdc++.h>

using namespace std;

#define ll long long

ll kadane(ll *a, ll n){
	ll DP[n];

	DP[0] = a[0];

	for(ll i=1; i<n; i++)
		DP[i] = max(DP[i-1]+a[i], a[i]);

	ll ans = a[0];

	for(ll i=0; i<n; i++)
		if(DP[i]>ans)
			ans = DP[i];
	
	return ans;
}

ll kadane2d(ll **a, ll m, ll n){
	ll acum[m][n]; //columna j es el vector acumulado hasta la columna j

	for(ll r=0; r<m; r++)
		acum[r][0] = a[r][0];

	for(ll c=1; c<n; c++)
		for(ll r=0; r<m; r++)
			acum[r][c] = acum[r][c-1]+a[r][c];

	ll DP[n][n]; //DP[i,j] = suma maxima de submatriz que comienza en la columna i y termina en la columna j
	ll MAX = a[0][0];

	for(ll j=0; j<n; j++){
		ll aux[m];

		for(ll r=0; r<m; r++)
			aux[r] = acum[r][j];

		DP[0][j] = kadane(aux, m);

		if(DP[0][j] > MAX)
			MAX = DP[0][j];
	}

	for(ll i=1; i<n; i++)
		for(ll j=i; j<i+n/2; j++){
			ll aux[m];

			for(ll r=0; r<m; r++)
				aux[r] =acum[r][j]-acum[r][i-1];

			DP[i][j] = kadane(aux, m);

			if(DP[i][j] > MAX)
				MAX = DP[i][j];
		}

	return MAX;
}

int main(){

	int T; cin >> T;

	ll **torus;

	torus = new ll*[150];
	for(int i=0; i<150; i++)
		torus[i] = new ll[150];

	while(T--){
		int N;
		cin >> N;

		for(int i=0; i<N; i++){
			for(int j=0; j<N; j++)
				cin >> torus[i][j];

			for(int j=N; j<2*N; j++)
				torus[i][j] = torus[i][j-N];
		}

		for(int i=N; i<2*N; i++)
			for(int j=0; j<2*N; j++)
				torus[i][j] = torus[i-N][j];

		cout << kadane2d(torus, 2*N, 2*N) << endl;

	}

	for(int i=0; i<150; i++)
		delete[] torus[i];
	
	delete[] torus;

	return 0;
}