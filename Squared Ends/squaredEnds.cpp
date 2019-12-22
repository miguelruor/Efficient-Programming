#include <bits/stdc++.h>
#define ll long long

using namespace std;

//DP[m, i] = min(DP[m-1, k-1]+(A[k]-A[i])^2), m<=k<=i, el mínimo costo al partir A[1,..., i] en m subarreglos

ll A[10001];
ll DP[10001][10001];

ll LCTree[4*1000001];
ll curRow;

ll minl=0;
ll maxr=1000000;

ll evaluateF(ll m, ll k, ll x){ //f_{m,k}(x)
	return DP[m-1][k-1] + (A[k]-x)*(A[k]-x);
}

void build(ll k, ll cur = 1, ll l = minl, ll r = maxr){
    LCTree[cur] = k;

    if(l==r)
        return;

    ll m=(l+r)/2;
    build(k, 2*cur, l, m);
    build(k, 2*cur+1, m+1, r);

    return;
}

void insertfunc(ll newf, ll cur = 1, ll l = minl, ll r = maxr){
	ll m = (l+r)/2;
    ll curf = LCTree[cur];

    if(curf == newf)
    	return;

    ll curf_l = evaluateF(curRow, curf, l), curf_m = evaluateF(curRow, curf, m);
    ll newf_l = evaluateF(curRow, newf, l), newf_m = evaluateF(curRow, newf, m);

	bool lef = newf_l < curf_l;
	bool mid = newf_m < curf_m;

	if(mid){
		LCTree[cur] = newf;
		newf = curf;
	}

    if(l==r)
        return;
    
    if(lef != mid) // checamos si las funciones se intersectan en [l, m]
    	insertfunc(newf, 2*cur, l, m);
    else
    	insertfunc(newf, 2*cur+1, m+1, r);
}

ll minValue(ll x, ll ans=LCTree[1], ll cur=1, ll l = minl, ll r = maxr){
    ll curf = LCTree[cur];
    ll curf_x = evaluateF(curRow, curf, x), ans_x = evaluateF(curRow, ans, x);

    if(curf_x < ans_x){
        ans = curf;
    }

    if(l==r){
        return evaluateF(curRow, ans, x);
    }

   ll m = (l+r)/2;

    if(x<=m)
        return minValue(x, ans, 2*cur, l, m);
    else
        return minValue(x, ans, 2*cur+1, m+1, r);
}

int main(){

	ll N, K;

	cin >> N >> K;

	for(ll i=1; i<=N; i++){
		cin >> A[i];
	}

	ll min = A[1]; ll max = A[1];

	for(ll i=1; i<=N; i++){
		if(A[i] > max)
			max = A[i];
		if(A[i] < min)
			min = A[i];
	}

	maxr = max; minl = min;

	//ll slowDP[K+1][N+1];

	for(ll i=1; i<=N; i++){
		DP[1][i] = (A[1]-A[i])*(A[1]-A[i]);
		//slowDP[1][i] = DP[1][i];
	}

	for(ll m=2; m<=K; m++){
		curRow = m;
		build(m);

		for(ll i=m; i<=N; i++){
			if(i==m){
				DP[m][m] = 0;
				//slowDP[m][m] = 0;
			}
			else{
				insertfunc(i);

				DP[m][i] = minValue(A[i]);

				/*ll min = (A[m]-A[i])*(A[m]-A[i]);

				for(ll k=m; k<=i; k++){
					if( min > DP[m-1][k-1]+(A[k]-A[i])*(A[k]-A[i]) )
						min = DP[m-1][k-1]+(A[k]-A[i])*(A[k]-A[i]);
				}
				slowDP[m][i] = min;*/
			}
		}
	}
	
	cout << DP[K][N];
	//cout << DP[K][N] << " " << slowDP[K][N] << endl;

	return 0;
}