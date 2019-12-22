#include <bits/stdc++.h>

using namespace std;

struct Point{
	int x, y, z;

	Point(int _x=0, int _y=0, int _z=0){
		x = _x; y =_y; z = _z;
	}
};

Point stars[10001];

bool compare(Point p1, Point p2){
	if(p1.x <= p2.x){
		return true;
	}
	else 
		return false;
}

double distance(Point p1, Point p2){
	double dx = (double) (p1.x-p2.x);
	double dy = (double) (p1.y-p2.y);
	double dz = (double) (p1.z-p2.z);

	return sqrt(dx*dx+dy*dy+dz*dz);
}

class QuadTree{
public:

	deque<int> points;

	pair<int, int> y, z;// border

	QuadTree *tLeft, *tRight, *bLeft, *bRight;

	QuadTree(){
		y.first = 0; y.second = 2000;
		z.first = 0; z.second = 2000;
		tLeft = NULL;
		tRight = NULL;
		bLeft = NULL;
		bRight = NULL;
	}

	void insertar(int s){

		//cout << "(" << y.first << ", " << y.second << ")x(" << z.first << ", " << z.second << ")" << endl;

		points.push_back(s);

		if(y.first == y.second && z.first == z.second){
			return;
		}

		int ym = (y.second+y.first)/2, zm = (z.second+z.first)/2;

		if(stars[s].y <= ym){
			if(stars[s].z <= zm){//cout << "bLeft" << endl;
				if(bLeft == NULL){
					bLeft = new QuadTree();
					bLeft->y.first = y.first; bLeft->y.second = ym;
					bLeft->z.first = z.first; bLeft->z.second = zm;
				}
				bLeft->insertar(s);
			}
			else{//cout << "tLeft" << endl;
				if(tLeft == NULL){
					tLeft = new QuadTree();
					tLeft->y.first = y.first; tLeft->y.second = ym;
					tLeft->z.first = zm+1; tLeft->z.second = z.second;
				}
				tLeft->insertar(s);			
			}
		}
		else{
			if(stars[s].z <= zm){//cout << "bRight" << endl;
				if(bRight == NULL){
					bRight = new QuadTree();
					bRight->y.first = ym+1; bRight->y.second = y.second;
					bRight->z.first = z.first; bRight->z.second = zm;
				}
				bRight->insertar(s);
			}
			else{//cout << "tRight" << endl;
				if(tRight == NULL){
					tRight =  new QuadTree();
					tRight->y.first = ym+1; tRight->y.second = y.second;
					tRight->z.first = zm+1; tRight->z.second = z.second;
				}
				tRight->insertar(s);
			}
		}

		//cout << s << " se inserto correctamente" << endl;
	}

	void query(pair<int,int> yq, pair<int, int> zq, deque<int> &ans){
		if(yq.second < y.first || yq.first > y.second || zq.second < z.first || zq.first > z.second)
			return;
		
		if(yq.first <= y.first || y.second <= yq.second || zq.first <= z.first || z.second <= zq.second){
			for(int i=0; i<points.size(); i++)
				ans.push_back(points[i]);

			return;
		}

		if(tLeft!=NULL)
	 		tLeft->query(yq, zq, ans);
		if(tRight!=NULL)
			tRight->query(yq, zq, ans);
		if(bLeft!=NULL)
			bLeft->query(yq, zq, ans);
		if(bRight!=NULL)	
			bRight->query(yq, zq, ans);

		//cout << "Se contesto query correctamente" << endl;
	}

	void erase(int s){
		if(points.size()>0 && s != points.front())
			return;

		points.pop_front();

		if(y.first==y.second && z.first == z.second){
			return;
		}

		if(tLeft != NULL){
			tLeft->erase(s);
			if(tLeft->points.size() == 0){
				delete tLeft;
				tLeft = NULL;			
			}
		}
		if(tRight != NULL){
			tRight->erase(s);
			if(tRight->points.size() == 0){
				delete tRight;
				tRight = NULL;
			}
		}
		if(bLeft != NULL){
			bLeft->erase(s);
			if(bLeft->points.size() == 0){
				delete bLeft;
				bLeft = NULL;
			}
		}
		if(bRight != NULL){
			bRight->erase(s);
			if(bRight->points.size() == 0){
				delete bRight;
				bRight = NULL;
			}
		}

		//cout << s << " se elimino correctamente" << endl;
	}

	~QuadTree(){
		deque<int> allpoints = points;

		for(int i=0; i<allpoints.size(); i++)
			erase(allpoints[i]);

		//cout << "QuadTree destruido correctamente" << endl;
	}

};

double sixDist[10];

int main(){

 	int N;

	while(1){

		cin >> N;

		if(N == 0)
			break;

		for(int i=1; i<=N; i++){
			cin >> stars[i].x >> stars[i].y >> stars[i].z ;	
			stars[i].x += 1000;
			stars[i].y += 1000;
			stars[i].z += 1000;
		}

		/*for(int i=1; i<=N; i++){
			stars[i].x = rand()%2001;
			stars[i].y = rand()%2001;
			stars[i].z = rand()%2001;
		}*/

		sort(stars+1, stars+N+1, compare);

		QuadTree root;

		for(int i=1; i<=4; i++){
			root.insertar(i);
		}

		int k=0;

		for(int i=1; i<4; i++){
			for(int j=i+1; j<=4; j++)
				sixDist[k++] = distance(stars[i], stars[j]);
		}

		int next=0;

		sort(sixDist, sixDist+6);
		double dm = sixDist[5];

		deque<int> ans;

		for(int i=5; i<=N; i++){
			while(next<i && stars[next].x <= stars[i].x-dm){
				root.erase(next++);
			}

			pair<int, int> yq((int)(stars[i].y-dm)-1, (int)(stars[i].y+dm)+1), zq((int)(stars[i].z-dm)-1, (int)(stars[i].z+dm)+1);
			ans.clear();
			root.query(yq, zq, ans);
			
			for(int i=0; i<ans.size(); i++){
				sixDist[6] = distance(stars[i], stars[ans[i]]);
				sort(sixDist, sixDist+7);
			}
			dm = sixDist[5];

			root.insertar(i);
		}

		double sum = 0;

		for(int i=0; i<6; i++)
			sum += sixDist[i];

		printf("%.2lf \n", sum);

	}

	return 0;
}