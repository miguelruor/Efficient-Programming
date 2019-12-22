#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

int Map[8][8];
int n, m;
int noPaths;

void freeCells(int i, int j, vector<pair<int,int>> &free){

	if(i-1>=0 && Map[i-1][j] == 0)
		free.push_back(pair<int, int>(i-1, j));
	if(i+1<m && Map[i+1][j] == 0)
		free.push_back(pair<int, int>(i+1, j));
	if(j-1>=0 && Map[i][j-1] == 0)
		free.push_back(pair<int, int>(i, j-1));
	if(j+1<n && Map[i][j+1] == 0)
		free.push_back(pair<int, int>(i, j+1));

	return;
}

void printMap(){
	for(int i=0; i<m; i++){
		for(int j=0; j<n; j++)
			cout << Map[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}

int x[4], y[4], steps[4];

int norm(int i){
	return (i<0 ? -1*i : i);
}

void paths(int i, int j, int t, int Next){

	if(steps[Next]-t < norm(x[Next]-i) + norm(y[Next]-j)) // Si ya no llegamos a casilla objetivo siguiente o 
		return;									// ya nos pasamos en tiempo

	if(steps[Next] == t) // Se llego a casilla objetivo siguiente en tiempo correcto
		Next++;

	if(Next == 4){ // Nueva trayectoria
		noPaths++;
		return;
	}

	for(int k=Next; k<4; k++){ // Se llego a alguna casilla objetivo en tiempo incorrecto
		if(i == x[k] && j == y[k] && t!= steps[k])
			return;
	}
	
	if(j == 0 && i>0 && Map[i-1][0] == 0) //Toco orilla izquierda de forma incorrecta
		return;
	
	if(i == m-1 && j>0 && Map[m-1][j-1] == 0) //Toco orilla inferior de forma incorrecta
		return;

	if(j == n-1 && i<m-1 && Map[i+1][n-1] == 0) //Toco orilla derecha de forma incorrecta
		return;

	if(i == 0 && j>0 && j<n-1 && Map[0][j+1] == 0) //Toco orilla superior de forma incorrecta
		return;

	vector<pair<int,int>> free; 
	freeCells(i, j, free);

	if(free.size() == 2){ 

		int aux1 = norm(free[0].first-free[1].first), aux2 = norm(free[0].second-free[1].second);
		if(aux1 == 2 || aux2 == 2) // El robot se encerro el mismo
			return;
	} 

	Map[i][j] = t;
	//printMap();
	
	for(int k=0; k<free.size(); k++){
		paths(free[k].first, free[k].second, t+1, Next);
	}

	Map[i][j] = 0; 
}

void paths(){

	if(steps[1]-steps[0] < norm(x[1]-x[0])+norm(y[1]-y[0])) // No podemos llegar a la segunda casilla desde la primera
		return;

	if(steps[2]-steps[1] < norm(x[2]-x[1])+norm(y[2]-y[1])) // No podemos llegar a la tercera casilla desde la segunda
		return;

	if(steps[3]-steps[2] < norm(x[3]-x[2])+norm(y[3]-y[2])) // No podemos llegar a la casilla final desde la tercera
		return;

	paths(0, 0, 1, 0);
}

int main(){
	int test=0;
	while(1){
		cin >> m >> n;

		if(m==0)
			break;

		test++;

		cin >> x[0] >> y[0] >> x[1] >> y[1] >> x[2] >> y[2];

		x[3] = 0; y[3] = 1;

		steps[0] = (m*n)/4; steps[1] = (m*n)/2; steps[2] = (3*m*n)/4; steps[3] = m*n;

		noPaths = 0;

		for(int i=0; i<m; i++)
			for(int j=0; j<n; j++)
				Map[i][j] = 0;

		paths();

		cout << "Case " << test << ": " << noPaths << endl;
		//cout << noPaths << endl;
	}

	return 0;
}