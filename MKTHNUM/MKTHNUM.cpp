#include <bits/stdc++.h>

using namespace std;

vector<int> ST[400000];
vector<int> a(100001,0);
vector<int> coords1(100001,0);
vector<int> coords(100001, 0);
int n;

vector<int> merge(vector<int> &a1, vector<int> &a2){
	int m1=a1.size(), m2=a2.size(), len=m1+m2;
	vector<int> merged (len, 0);
	
	int i=0, j=0;
	
	for(int k=0; k<len; k++){
		if(i<m1 && j<m2){
			if(a1[i]<=a2[j])
				merged[k]=a1[i++];
			else
				merged[k]=a2[j++];
		}
		else if(i==m1)
			merged[k]=a2[j++];
		else
			merged[k]=a1[i++];
	}
	
	return merged;
}

void build(int l, int r, int pos){
	if(l==r){
		ST[pos] = vector<int>(1, coords[l-1]);
		return;
	}
	
	int m=(l+r)/2;
	
	build(l, m, 2*pos);
	build(m+1, r, 2*pos+1);
	
	ST[pos] = merge(ST[2*pos], ST[2*pos+1]);
}

void Query(int startR, int endR, int startQ, int endQ, int pos, vector <int> &nodes){
	 if(endR < startQ || startR > endQ) 
        return;

    if(startQ <= startR && endR <= endQ){
    	nodes.push_back(pos);
    	return;
	}

    int m = (startR + endR)/2;
    Query(startR, m, startQ, endQ, 2*pos, nodes);
    Query(m+1, endR, startQ, endQ, 2*pos+1, nodes);
}

int Query(int l, int r, int k){
	vector <int> nodes; 
	Query(1, n, l, r, 1, nodes);
	
	int left=0, right=n, middle, noNodes=nodes.size(), sum, p;
	
	while(left!=right){
		sum=0;
		middle=(left+right)/2;
		
		for(int i=0; i<noNodes; i++){
			p = nodes[i];
			sum += upper_bound(ST[p].begin(), ST[p].end(), middle)-ST[p].begin();
		}
		
		if(k<=sum){
			right=middle;
		}
		else{
			left=middle+1;
		}
	}
	
	return coords1[left];
}


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int m;
	
	cin >> n >> m;
	
	int l[m], r[m], k[m];
	
	for(int i=0; i<n; i++){
		cin >> a[i];
		coords1[i]=a[i];
	}
	
	sort(coords1.begin(), coords1.begin()+n);
	
	for(int i=0; i<n; i++)
		coords[i]=lower_bound(coords1.begin(), coords1.begin()+n, a[i])-coords1.begin();
	
	for(int i=0; i<m; i++){
		cin >> l[i] >> r[i] >> k[i];
	}
	
	build(1, n, 1);

	for(int i=0; i<m; i++)
		cout << Query(l[i], r[i], k[i]) << endl;
	
	return 0;
}
