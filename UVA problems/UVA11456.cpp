#include <bits/stdc++.h>

using namespace std;

void LIS(int *A, int N, int *LIS){
	LIS[0] = 1;

	for(int i=1; i<N; i++){
		int max=0;

		for(int k=0; k<i; k++){
			if(A[k]<A[i] && max<LIS[k])
				max = LIS[k];
		}

		LIS[i] = 1+max;
	}
}

int main(){
	int T;
	cin >> T;

	for(int i=0; i<T; i++){
		int n;
		cin >> n;

		if(n==0){
			cout << 0 << endl;
			continue;
		}

		int a[n], DP[n];

		for(int i=0; i<n; i++)
			cin >> a[n-1-i];
		
		int lis[n], lds[n];

		LIS(a, n, lis);
		for(int i=0; i<n; i++)
			a[i] = -a[i];
		LIS(a, n, lds);

		int ans=0; 

		for(int i=0; i<n; i++){
			if(ans<lis[i]+lds[i])
				ans = lis[i]+lds[i]-1;
		}

		cout << ans << endl;

	}
	
	return 0;
}