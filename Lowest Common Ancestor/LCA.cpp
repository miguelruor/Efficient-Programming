#include <bits/stdc++.h>

#define MAXNODES 100
#define LOGMAX 20
#define MAXCHILDS 10

using namespace std;

class tree{
	public:

	int noNodes;

	int noChilds[MAXNODES];
	vector<int> childs[MAXNODES];
	int parents[MAXNODES];
	int heights[MAXNODES];

	int visitedNodes[2*MAXNODES];
	int preordenNodes[2*MAXNODES];
	int preordenHeights[2*MAXNODES];

	int powers[MAXNODES];

	int countpreorden=0;

	int sparseTable[MAXNODES][LOGMAX];

	tree(int _noNodes, int *_parents){
		noNodes=_noNodes;

		for(int i=0; i<noNodes; i++){
			visitedNodes[i]=-1;
			noChilds[i]=0;
		}

		for(int i=1; i<noNodes; i++){
			parents[i]=_parents[i];
			noChilds[parents[i]]++;
			childs[parents[i]].push_back(i);
		}

		int k=0;
		int p=2;

		for(int i=1; i<2*noNodes; i++){
			if(i==p){
				k++;
				p=2*p;
			}
			powers[i]=k;
		}
	}


	void fillpreorden(int cur=0, int height=0){
		if(visitedNodes[cur]==-1){
			visitedNodes[cur]=countpreorden;
		}

		preordenHeights[countpreorden] = height;
		preordenNodes[countpreorden] = cur;
		heights[cur] = height;

		countpreorden++;

		for(int i=0; i<noChilds[cur]; i++){
			fillpreorden(childs[cur][i], height+1);
			preordenHeights[countpreorden] = heights[cur];
			preordenNodes[countpreorden] = cur;
			countpreorden++;
		}
	}

	void fillSparseTable(){
		int N = countpreorden;
		int k = log2(N);

		for(int i=0; i<N; i++){
			sparseTable[i][0] = i;
		}

		for(int j=1; j<=k; j++){
			for(int i=0; i+(1<<j)<N; i++){
				int min1 = sparseTable[i][j-1];
				int min2 = sparseTable[i+(1<<(j-1))][j-1];
				sparseTable[i][j] = (preordenHeights[min1] < preordenHeights[min2] ? min1 : min2);
			}
		}
	}

	void initTree(){
		fillpreorden();
		fillSparseTable(); 
		/*
		int k=log2(countpreorden);
		int N=countpreorden;

		cout << "Powers:" << endl;
		for(int i=0; i<2*noNodes; i++)
			cout << powers[i] << " ";
		cout << endl;	

		cout << "preordenNodes:" << endl;
		for(int i=0; i<N; i++)
			cout << preordenNodes[i] << " ";
		cout << endl << "preordenHeights:" << endl;
		for(int i=0; i<N; i++)
			cout << preordenHeights[i] << " ";
		cout << endl;

		cout << "sparseTable: " << endl;
		for(int j=0; j<=k; j++){
			cout << "Power " << j << endl;
			for(int i=0; i<N; i++){
				cout << sparseTable[i][j] << " ";
			}
			cout << endl;
		}
		*/

	}

	int bruteLCA(int a, int b){
		if(heights[a]<heights[b]){
			int diff = heights[b]-heights[a];
			for(int i=0; i<diff; i++)
				b=parents[b];
		}
		else{
			int diff = heights[a]-heights[b];
			for(int i=0; i<diff; i++)
				a=parents[a];
		}

		while(a!=b){
			a=parents[a];
			b=parents[b];
		}

		return a;
	}

	int LCA(int a, int b){
		int i = visitedNodes[a], j = visitedNodes[b];
		if(i>j){
			int aux = i;
			i = j;
			j = aux;
		}

		int d = j-i+1;
		int k = powers[d];
		int p = 1<<k;

		//cout << d << " " << k << " " << p << endl;

		int min1 = sparseTable[i][k], min2 = sparseTable[j-p+1][k];
		int min = (preordenHeights[min1] < preordenHeights[min2] ? min1 : min2);

		return preordenNodes[min];
	}
};

tree RandomTree(){
	srand(rand());

	int N = 0;
	while(N<=1)
		N=rand()%MAXNODES;

	int parents[N];
	int childs=0, cur=0, acumNodes=1;

	while(childs==0){
		childs = min(N-acumNodes, MAXCHILDS)+1;
		childs = abs(rand())%childs;
	}
	
	for(int j=acumNodes; j<acumNodes+childs; j++)
		parents[j] = cur;

	acumNodes += childs;
	cur++;

	while(acumNodes<N){
		childs = min(N-acumNodes, MAXCHILDS)+1;
		childs = abs(rand())%childs;

		for(int j=acumNodes; j<acumNodes+childs; j++)
			parents[j] = cur;

		acumNodes += childs;
		cur++;
	}

	cout << "Number of Nodes: " << N << endl;
	cout << "Parents:" << endl; 
	for(int i=1; i<N; i++)
		cout << parents[i] << " ";
	cout << endl;

	tree T(N, parents);

	return T;
}


int main(){

	int T, R; 
	cin >> T >> R;

	for(int j=0; j<T; j++){
		int N;
		cin >> N;

		int parents[N];
		for(int i=1; i<N; i++)
			cin >> parents[i];

		tree myTree(N, parents);

		myTree.initTree();

		int a, b;

		cin >> a >> b;

		cout << myTree.LCA(a, b) << endl;
		cout << myTree.bruteLCA(a,b) << endl;
	}

	
	for(int j=0; j<R; j++){
		tree RandTree = RandomTree();
		RandTree.initTree();

		int a = abs(rand())%RandTree.noNodes, b = abs(rand())%RandTree.noNodes;
		cout << endl << "LCA:" << a << " " << b << endl;
		cout << RandTree.LCA(a, b) << endl;
		cout << RandTree.bruteLCA(a, b) << endl;
	}

	cout << "OK";

    return 0;
}
