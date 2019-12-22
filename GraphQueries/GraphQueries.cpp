#include <bits/stdc++.h>

using namespace std;

struct Query{
	int index, L, R, block;
};

struct Edge{
	int U, V;
};

bool compare(Query q1, Query q2){
	if (q1.block != q2.block) 
        return (q1.block < q2.block); 
  
    return (q1.R < q2.R); 
}

struct UnionFind
{
	int N;
	int *p, *rank, *past;
	int noOfSets, noOfSetsPast, Fix;

	stack<int> modified;

	UnionFind(int _N){
		N = _N;
		noOfSets = N;
		Fix = 0;
		p = new int[N+1];
		rank = new int[N+1];
		past = new int[N+1];

		for(int i=1; i<=N; i++){
			p[i] = i;
			rank[i] = 0;
			past[i] = 0;
		}
	}

	~UnionFind(){
		delete p;
		delete rank;
		delete past;
	}

	void fix(){
		Fix = 1;
		noOfSetsPast = noOfSets;
	}

	void rewind(){
		int s = modified.size();

		for(int i=0; i<s; i++){
			int top = modified.top();
			p[top] = past[top];
			past[top] = 0;
			modified.pop();
		}

		noOfSets = noOfSetsPast;
		Fix=0;
	}

	int findSet(int i){
		if(p[i] == i)
			return i;

		int k = p[i];
		p[i] = findSet(p[i]);

		if(Fix == 1 && past[i]==0){
			past[i] = k;
			modified.push(i);
		}

		return p[i];
	}

	bool isSameSet(int i, int j){
		return findSet(i) == findSet(j);
	}

	void unionSet(int i, int j){
		if(!isSameSet(i, j)){
			noOfSets--;

			int x = findSet(i), y = findSet(j);
			if(rank[x]>rank[y]){
				int k = p[y];
				p[y] = x;
				if(Fix == 1 && past[y]==0){
					past[y] = k;
					modified.push(y); 
				}
			}
			else{
				int k = p[x];
				p[x] = y;
				if(Fix == 1 && past[x]==0){
					past[x] = k;
					modified.push(x); 
				}

				if(rank[x] == rank[y]) 
					rank[y]++;
			}
		}
	}
};

void answerqueries(int N, int M, int Q, Edge *edges, Query *queries, int *answers){

	sort(queries+1, queries+Q+1, compare);

	int BS=(int) sqrt(M);
	int cur=1;

	for(int i=queries[1].block; i<=queries[Q].block; i++){ 
		if(queries[cur].block>i)
			continue;

		UnionFind connectedComp(N);

		int lastR = BS*(i+1);

		while(queries[cur].block == i){

			if(queries[cur].R < BS*(i+1)){
				UnionFind aux(N);

				for(int k=queries[cur].L; k<= queries[cur].R; k++){
					aux.unionSet(edges[k].U, edges[k].V);
				}

				answers[queries[cur].index] = aux.noOfSets;
				cur++;

				continue;
			}

			for(int k=lastR; k<=queries[cur].R; k++){
				connectedComp.unionSet(edges[k].U, edges[k].V);
			}
			connectedComp.fix();
			lastR = queries[cur].R;

			for(int k=queries[cur].L; k<BS*(i+1); k++){
				connectedComp.unionSet(edges[k].U, edges[k].V);
			}
			answers[queries[cur].index] = connectedComp.noOfSets;
			connectedComp.rewind();

			cur++;
		}
	}
}

int main(){

	int T;
	cin >> T;

	for(int Case=0; Case<T; Case++){
		int N, M, Q;

		cin >> N >> M >> Q;

		int blockSize = (int) sqrt(M);

		Query queries[Q+1];
		Edge Edges[M+1];

		for(int i=1; i<=M; i++){
			cin >> Edges[i].U >> Edges[i].V;
		}

		for(int i=1; i<=Q; i++){
			cin >> queries[i].L >> queries[i].R;
			queries[i].index = i;
			queries[i].block = (int) queries[i].L/blockSize;
		}

		/*UnionFind s(N);
		for(int k=queries[4].L; k<=queries[4].R; k++)
			s.unionSet(Edges[k].U, Edges[k].V);
		cout << s.noOfSets;*/

		/*UnionFind s(N); 
		for(int j=1; j<=Q; j++){
			s.fix();
			for(int k=queries[j].L; k<=queries[j].R; k++)
				s.unionSet(Edges[k].U, Edges[k].V);
			cout << s.noOfSets <<endl;
			s.rewind();	
		}*/

		int ans[Q+1];

		answerqueries(N, M, Q, Edges, queries, ans);

		for(int j=1; j<=Q; j++){
			cout << ans[j] << endl;
		}

	}
	
	return 0;
}