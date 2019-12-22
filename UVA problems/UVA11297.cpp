#include <bits/stdc++.h>

using namespace std;

struct node{
	int min, max;

	node(int a=INT_MIN, int b=INT_MAX){
		min = a;
		max = b;
	}
};

node ST[2100][2100];
int C[510][510];
int N;

int Min(int a, int b){
	return (a < b ? a : b);
}

int Max(int a, int b){
	return (a>b ? a : b);
}

void build_y(int curx, int lx, int rx, int cury=1, int ly=1, int ry=N){

	if(ly==ry){
		if(lx == rx){
			ST[curx][cury].min = C[lx][ly];
			ST[curx][cury].max = C[lx][ly];
		}
		else{
			ST[curx][cury].min = Min(ST[2*curx][cury].min, ST[2*curx+1][cury].min);
			ST[curx][cury].max = Max(ST[2*curx][cury].max, ST[2*curx+1][cury].max);
		}
	}
	else{
		int my = (ly+ry)/2;

		build_y(curx, lx, rx, 2*cury, ly, my);
		build_y(curx, lx, rx, 2*cury+1, my+1, ry);

		ST[curx][cury].min = Min(ST[curx][2*cury].min, ST[curx][2*cury+1].min);
		ST[curx][cury].max = Max(ST[curx][2*cury].max, ST[curx][2*cury+1].max);
	}
}

void build_x(int curx=1, int lx=1, int rx=N){

	if(lx != rx){
		int mx = (lx+rx)/2;
		build_x(2*curx, lx, mx);
		build_x(2*curx+1, mx+1, rx);
	}
	build_y(curx, lx, rx);
}

node Query_y(int y1, int y2, int curx, int cury=1, int ly=1, int ry=N){

	if(ry<y1 || y2<ly)
		return node(INT_MAX, INT_MIN);

	if(y1<=ly && ry<=y2)
		return ST[curx][cury];

	int my = (ly+ry)/2;
	node aux1 = Query_y(y1, y2, curx, 2*cury, ly, my), aux2 = Query_y(y1, y2, curx, 2*cury+1, my+1, ry);

	return node(Min(aux1.min, aux2.min), Max(aux1.max, aux2.max));
}

node Query_x(int x1, int x2, int y1, int y2, int curx=1, int lx=1, int rx=N){
	if(rx<x1 || x2<lx)
		return node(INT_MAX, INT_MIN);

	if(x1<=lx && rx<=x2)
		return Query_y(y1, y2, curx);
	
	int mx = (lx+rx)/2;
	node aux1 = Query_x(x1, x2, y1, y2, 2*curx, lx, mx), aux2 = Query_x(x1, x2, y1, y2, 2*curx+1, mx+1, rx);

	return node(Min(aux1.min, aux2.min), Max(aux1.max, aux2.max));
}	

void Query(int x1, int y1, int x2, int y2){
	node ans = Query_x(x1, x2, y1, y2);
	cout << ans.max << " " << ans.min << endl;
}

void update_y(int y, int val, int curx, int lx, int rx, int cury=1, int ly=1, int ry=N){
	if(ly == ry){
		if(lx == rx){
			ST[curx][cury].min = val;
			ST[curx][cury].max = val;
		}
		else{
			ST[curx][cury].min = Min(ST[2*curx][cury].min, ST[2*curx+1][cury].min);
			ST[curx][cury].max = Max(ST[2*curx][cury].max, ST[2*curx+1][cury].max);
		}
	}
	else{
		int my=(ly+ry)/2;
		if(y<=my)
			update_y(y, val, curx, lx, rx, 2*cury, ly, my);
		else 
			update_y(y, val, curx, lx, rx, 2*cury+1, my+1, ry);

		ST[curx][cury].min = Min(ST[curx][2*cury].min, ST[curx][2*cury+1].min);
		ST[curx][cury].max = Max(ST[curx][2*cury].max, ST[curx][2*cury+1].max);
	}
}

void update_x(int x, int y, int val, int curx=1, int lx=1, int rx=N){
	if(lx != rx){
		int mx = (lx+rx)/2;
		if(x <= mx)
			update_x(x, y, val, 2*curx, lx, mx);
		else
			update_x(x, y, val, 2*curx+1, mx+1, rx);
	}

	update_y(y, val, curx, lx, rx);
}

int main(){
	cin >> N;

	for(int i=1; i<=N; i++)
		for(int j=1; j<=N; j++)
			cin >> C[i][j];

	build_x();

	int Q; cin >> Q; 
	char s;

	int x1, y1, x2, y2, val;

	for(int i=0; i<Q; i++){
		cin >> s;

		if(s == 'q'){
			cin >> x1 >> y1 >> x2 >> y2;

			Query(x1, y1, x2, y2);
		}
		else{
			cin >> x1 >> y1 >> val;

			update_x(x1, y1, val);
		}
	}
	

	return 0;
}