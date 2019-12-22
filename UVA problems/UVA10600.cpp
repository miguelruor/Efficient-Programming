#include <bits/stdc++.h>

using namespace std;

struct UnionFind
{
	int N;
	int *p, *rank;

	UnionFind(int _N){
		N = _N;
		p = new int[N+1];
		rank = new int[N+1];

		for(int i=1; i<=N; i++){
			p[i] = i;
			rank[i] = 0;
		}
	}

	~UnionFind(){
		delete p;
		delete rank;
	}

	int findSet(int i){
		if(p[i] == i)
			return i;

		p[i] = findSet(p[i]);

		return p[i];
	}

	bool isSameSet(int i, int j){
		return findSet(i) == findSet(j);
	}

	void unionSet(int i, int j){
		if(!isSameSet(i, j)){

			int x = findSet(i), y = findSet(j);

			if(rank[x]>rank[y]){
				p[y] = x;
			}
			else{
				p[x] = y;

				if(rank[x] == rank[y]) 
					rank[y]++;
			}
		}
	}
};

struct edge{
	int u, v, cost;

	edge(){
		cost = 0;
	}

	edge(int _u, int _v, int _cost){
		u = _u;
		v = _v;
		cost = _cost;
	}
};

bool compare(edge a1, edge a2){
	if(a1.cost < a2.cost)
		return true;

	return false;
}

vector <int> inMST;

int costMST(edge a[10000], int N, int M){

	UnionFind UF(N);

	int min=0;
	int i=0, size=0;

	int A, B, C;

	while(size<N-1 && i<M){
		A = a[i].u; B = a[i].v; C = a[i].cost;

		if(UF.isSameSet(A,B)){
			i++;
			continue;
		}

		UF.unionSet(A,B);
		inMST.push_back(i++);
		size++;
		min += C;
	}

	if(size < N-1)
		return -1;

	return min;
}


int main(){
	int T;
	cin >> T;

	while(T-- > 0){
		int N, M;

		cin >> N >> M;
		edge a[M];

		int A, B, C;

		for(int i=0; i<M; i++){
			cin >> A >> B >> C;
			a[i] = edge(A, B, C);
		}

		sort(a, a+M, compare);

		cout << costMST(a, N, M) << " ";

		vector<int> inMSTcopy(inMST);
		int aux, temp, min2 = INT_MAX;

		for(int i=0; i<N-1; i++){
			edge b[M];

			int j=0;
			for(int k=0; k<M; k++)
				if(k != inMSTcopy[i])
					b[j++] = a[k];

			sort(b, b+M-1, compare);

			temp = costMST(b, N, M-1);
			if(temp != -1 && temp < min2)
				min2 = temp;
		}

		cout << min2 << endl;
		
		inMST.clear();
	}

	return 0;
		
}