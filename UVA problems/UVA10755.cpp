#include <bits/stdc++.h>

#define ll long long

using namespace std;

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
		for(ll j=i; j<n; j++){
			ll aux[m];

			for(ll r=0; r<m; r++)
				aux[r] =acum[r][j]-acum[r][i-1];

			DP[i][j] = kadane(aux, m);

			if(DP[i][j] > MAX)
				MAX = DP[i][j];
		}

	return MAX;
}

ll kadane3d(ll ***a, ll A, ll B, ll C){
	ll acum[A][B][C];

	for(ll i=0; i<A; i++)
		for(ll j=0; j<B; j++)
			acum[i][j][0] = a[i][j][0];
	
	for(ll i=0; i<A; i++)
		for(ll j=0; j<B; j++)
			for(ll k=1; k<C; k++)
				acum[i][j][k] = acum[i][j][k-1] + a[i][j][k];

	ll DP[C][C], **aux; //DP[k1, k2] = maxima suma de subcubo en el cubo a[][][k1,...,k2]
	ll MAX = a[0][0][0];

	aux = new ll*[A];
	for(ll i=0; i<A; i++)
		aux[i] = new ll[B];

	for(ll k2=0; k2<C; k2++){

		for(ll i=0; i<A; i++)
			for(ll j=0; j<B; j++)
				aux[i][j] = acum[i][j][k2];

		DP[0][k2] = kadane2d(aux, A, B);
		
		if(DP[0][k2] > MAX)
			MAX = DP[0][k2];	
	}

	for(ll k1=1; k1<C; k1++)
		for(ll k2=k1; k2<C; k2++){

			for(ll i=0; i<A; i++)
				for(ll j=0; j<B; j++)
					aux[i][j] = acum[i][j][k2] - acum[i][j][k1-1];

			DP[k1][k2] = kadane2d(aux, A, B);
			
			if(DP[k1][k2] > MAX)
				MAX = DP[k1][k2];	
	}
	

	for(ll i=0; i<A; i++)
		delete[] aux[i];
	delete[] aux;

	return MAX;
}

int main(){

	ll T;
	cin >> T;

	ll ***M; 

	M = new ll**[20];

	for(ll i=0; i<20; i++)
		M[i] = new ll*[20];

	for(ll i=0; i<20; i++)
		for(ll j=0; j<20; j++)
			M[i][j] = new ll[20];

	for(ll t=0; t<T; t++){

		ll A, B, C;

		cin >> A >> B >> C;

		for(ll i=0; i<A; i++)
			for(ll j=0; j<B; j++)
				for(ll k=0; k<C; k++)
					cin >> M[i][j][k];

		if(t<T-1)
			cout << kadane3d(M, A, B, C) << endl << endl;
		else 
			cout << kadane3d(M, A, B, C) << endl;
	}


	for(ll i=0; i<20; i++)
		for(ll j=0; j<20; j++)
			delete[] M[i][j];

	for(ll i=0; i<20; i++)
		delete[] M[i];

	delete[] M;
	
	return 0;
}