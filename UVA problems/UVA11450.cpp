#include <bits/stdc++.h>

using namespace std;

//DP[m, c] = maxima cantidad de dinero que se puede gastar con m presupuesto y con los primeros c objetos
//         = max( DP[m-p_{c,i}, c-1] + p_{c,i} )_{i=1,...,noModels[c] ; m-prices[c][i] >= 0]}

int DPmat[300][30];
int C, M, num[30], price[30][30]; 

int DP(int m, int c){
	if(DPmat[m][c] != INT_MIN)
		return DPmat[m][c];

	if(m == 0 && c>0){
		DPmat[m][c] = -1;
		return -1;
	}

	if(c == 0){
		DPmat[m][c] = 0;
		return 0;
	}

	int max = -1;

	for(int i=1; i<=num[c]; i++){
		if(m-price[c][i] >= 0){
			int aux = DP(m-price[c][i], c-1);

			if(aux == -1)
				continue;

			aux += price[c][i];

			if(max < aux)
				max = aux;
		}
	}

	DPmat[m][c] = max;

	return max;
}

int main(){
	int N;
	int ans[1000];

	cin >> N;

	for(int k=0; k<N; k++){
		cin >> M >> C;

		for(int i=1; i<=C; i++){
			cin >> num[i];

			for(int j=1; j<=num[i]; j++)
				cin >> price[i][j];
		}

		for(int i=0; i<250; i++)
			for(int j=0; j<25; j++)
				DPmat[i][j] = INT_MIN;

		ans[k] = DP(M, C);
	}

	for(int i=0; i<N; i++){
		if(ans[i] == -1)
			cout << "no solution" << endl;
		else
			cout << ans[i] << endl;
	}

	return 0;
}