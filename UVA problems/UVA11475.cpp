#include <bits/stdc++.h>

using namespace std;

void LPS(string s, int *lps){
	int len = 0;
	lps[0] = 0;
	int M = s.size()-1;

	string rs;

	for(int i=0; i<M; i++)
		rs += s[M-1-i];

	int i=1;

	while(i<=M){
		if(s[i] == rs[M-i+len]){
			len++;
			lps[i] = len;
			i++;
		}
		else{
			if(len != 0)
				len = lps[len-1];
			else{
				lps[i++]=0;
			}
		}
	}
}

int main(){
	string s;
	int M;

	while(cin >> s){

		int M = s.size();

		int lps[100000];

		LPS(s, lps);

		int len = M - lps[M-1];

		cout << s;

		if(len == 1 && s[0] == s[M-1])
			continue;

		for(int i=len-1; i>=0; i--)
			cout << s[i];

		cout << endl;
	}
	
	return 0;
}