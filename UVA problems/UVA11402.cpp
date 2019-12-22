#include <bits/stdc++.h>

using namespace std;

int sTree[4*1024000];
char lazy[4*1024000];
int pirates[1024000];
int N=0;

void construct(int *pirates, int ss, int se, int cur){
	if(ss == se){
		sTree[cur] = pirates[ss-1];
		lazy[cur] = 0;
		return;
	}
	
	int mid=(ss+se)/2;
	construct(pirates, ss, mid, 2*cur);
	construct(pirates, mid+1, se, 2*cur+1);
	
	sTree[cur]=sTree[2*cur]+sTree[2*cur+1];
	lazy[cur]=0;
	
	return;
}

void updateNode(char s, int ss, int se, int cur){
	if(s == 'I'){
		sTree[cur]=se-ss+1-sTree[cur];
	}
	else if(s == 'F'){
		sTree[cur]=se-ss+1;
	}
	else{
		sTree[cur]=0;
	}
	
	return;
}

void lazyChild(char s, int cur){
	if(s != 'I'){
		lazy[cur] = s;
	}
	else{
		if(lazy[cur]==0){
			lazy[cur]='I';
		}
		else if(lazy[cur] == 'F'){
			lazy[cur]='E';
		}
		else if(lazy[cur]=='E'){
			lazy[cur]='F';
		}
		else{
			lazy[cur]=0;
		}
	}
	
	return;
}

int Query(int a, int b, int ss, int se, int cur){
	if(lazy[cur] != 0){
		
		updateNode(lazy[cur], ss, se, cur);
		
		if(ss!=se){
			lazyChild(lazy[cur], 2*cur);
			lazyChild(lazy[cur], 2*cur+1);
		}
		
		lazy[cur]=0;
	}
	
	if(b<ss || a>se)
		return 0;
		
	if(a<=ss && se<=b)
		return sTree[cur];
		
	int mid=(ss+se)/2;
	
	return Query(a, b, ss, mid, 2*cur) + Query(a, b, mid+1, se, 2*cur+1);
}

void update(int a, int b, int ss, int se, int cur, char s){
	if(lazy[cur] != 0){
		
		updateNode(lazy[cur], ss, se, cur);
		
		if(ss!=se){
			lazyChild(lazy[cur], 2*cur);
			lazyChild(lazy[cur], 2*cur+1);
		}
		
		lazy[cur]=0;
	}
	
	if(b<ss || a>se)
		return;
		
	if(a<=ss && se<=b){
		updateNode(s, ss, se, cur);
		
		if(ss!=se){
			lazyChild(s, 2*cur);
			lazyChild(s, 2*cur+1);
		}
		
		return;
	}
	
	int mid=(ss+se)/2;
	
	update(a, b, ss, mid, 2*cur, s);
	update(a, b, mid+1, se, 2*cur+1, s);
	
	sTree[cur]=sTree[2*cur]+sTree[2*cur+1];
	
	return;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int T, M, S, Q, a, b, noQ;
	string part;
	int m;
	char s;
	
	cin >> T;
	
	for(int i=0; i<T; i++){
		N=0; noQ=1;
		
		cin >> M;
		
		for(int j=0; j<M; j++){
			cin >> S >> part;
			m = part.size();
			
			for(int k=0; k<m*S; k++)
				pirates[N+k]=part[k%m]-'0';
			N = N+m*S;
		}
		 
		construct(pirates, 1, N, 1);
		
		cin >> Q;
		cout << "Case " << i+1 << ":" << endl;
		
		for(int j=0; j<Q; j++){
			cin >> s >> a >> b;
			
			if(s=='S'){
				cout << "Q" << noQ++ << ": " << Query(a+1, b+1, 1, N, 1) << endl;
			}
			else{
				update(a+1, b+1, 1, N, 1, s);
			}			
		}
	}
	
	return 0;
}
