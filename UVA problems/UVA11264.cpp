#include <bits/stdc++.h>

#define long long ll

using namespace std;

int main(){

	int T;
	cin >> T;

	while(T-- > 0){
		int n;
		cin >> n;

		ll C, X=0;

		for(int i=0; i<n; i++){
			cin >> C;
			X+=C;
		}

		cout << C << endl;
	}

	

	return 0;
}