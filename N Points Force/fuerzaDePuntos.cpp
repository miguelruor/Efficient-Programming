#include <bits/stdc++.h>

using namespace std;

void bruteForce(pair< pair<float, float>, int >  *points, int *force, int N){
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			if(j==i)
				continue;
			if(points[i].first.first <= points[j].first.first && points[i].first.second <= points[j].first.second)
				force[points[i].second]++;
		}
	}
}

void forceOfPoints(pair< pair<float, float>, int >  *points, int *force, int i, int j){
	if(i == j)
		return;

	int m=(i+j)/2;

	forceOfPoints(points, force, i, m);
	forceOfPoints(points, force, m+1, j);

	pair< pair<float, float>, int > aux[j-i+1];

	int s=m+1, r=i;

	for(int k=i; k<=j; k++){ //merge
		if(r > m)
			aux[k-i] = points[s++];
		else if(s>j)
			aux[k-i] = points[r++];
		else{
			if(points[r].first.second <= points[s].first.second){
				aux[k-i] = points[r];
				force[points[r].second] += j-s+1;
				r++;
			}
			else{	
				aux[k-i] = points[s++];
			}
		}
	}

	for(int k=i; k<=j; k++)
		points[k] = aux[k-i];

	return;
}

int main(){
	int N;

	cin >> N;

	pair< pair<float, float>, int >  points[N];

	for(int i=0; i<N; i++){
		cin >> points[i].first.first >> points[i].first.second;
		points[i].second = i;
	}

	sort(points, points+N);

	int force[N], force2[N];

	for(int i=0; i<N; i++){
		force[i] = 0;
		force2[i] = 0;
	}

	forceOfPoints(points, force, 0, N-1);
	bruteForce(points, force2, N);

	for(int i=0; i<N; i++){
		cout << force[i] << " ";
	}
	cout << endl;

	for(int i=0; i<N; i++){
		cout << force2[i] << " ";
	}
	cout << endl;

	return 0;
}