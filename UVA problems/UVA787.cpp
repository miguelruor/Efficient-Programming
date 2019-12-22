#include <bits/stdc++.h>

using namespace std;

int main(){

	int A[200];
	int N=0;

	while(cin >> A[N]){
		if(A[N] != -999999)
			N++;
		else{
			int DP[N], MAX = A[0];

			DP[0] = A[0];

			for(int i=1; i<N; i++){
				DP[i] = max(DP[i-1]*A[i], A[i]);

				if(MAX < DP[i])
					MAX = DP[i];
			}

			cout << MAX << endl;

			N=0;
		}
	}

	return 0;
}