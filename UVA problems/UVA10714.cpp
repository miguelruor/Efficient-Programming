#include <bits/stdc++.h>

using namespace std;

int main(){

	int T, n, l;
	vector<int> pos;
	pos.resize(1000000);
	cin >> T;

	for(int k=0; k<T; k++){

		cin >> l >> n;

		for(int i=0; i<n; i++){
			cin >> pos[i];
		}

		if(n == 1){
			cout << min(pos[0], l-pos[0]) << " " << max(pos[0], l-pos[0]) << endl;
			continue;
		}

		sort(pos.begin(), pos.begin()+n);

		vector<int>::iterator mid = lower_bound(pos.begin(), pos.begin()+n, l/2);
		
		int Min, Max;

		if(mid != pos.end())
			Min = max(*(mid-1), l-*mid);
		else
			Min = pos[n-1];

		Max = max(l-pos[0], pos[n-1]);
		
		cout << Min << " " << Max << endl;
	}
	
	return 0;
}