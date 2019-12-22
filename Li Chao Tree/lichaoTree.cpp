#include <bits/stdc++.h>

using namespace std;

int LCTree[4*100000];
int A[10001], B[10001];

void pre_build(int cur=1, int l=0, int r=100000){
    LCTree[cur] = 1;

    if(l==r)
        return;

    int m=(l+r)/2;
    pre_build(2*cur, l, m);
    pre_build(2*cur+1, m+1, r);

    return;
}

void insertfunc(int k, int cur=1, int l=0, int r=100000){
    int f = LCTree[cur];
    int fl = A[f]*l+B[f], kl = A[k]*l+B[k];
    int fr = A[f]*r+B[f], kr = A[k]*r+B[k];

    if(l==r){
        if(fl < kl){
            LCTree[cur] = k;
        }
        return;
    }

    if((fl<=kl && fr>kr) || (fl>=kl && fr<kr)){
        int m=(l+r)/2;

        int fm = A[f]*m+B[f], km = A[k]*m+B[k];

        if((fl<=kl && fm>km) || (fl>=kl && fm<km)){
            insertfunc(k, 2*cur, l, m);
        }
        else{
            insertfunc(k, 2*cur+1, m+1, r);
        }
    }
    else{
        if(fl<kl)
            LCTree[cur] = k;
    }

    return;
}

void build(int n){
    pre_build();

    for(int i=1; i<=n; i++){
        insertfunc(i);
    }

    return;
}

int maxf(int x, int ans=LCTree[1], int cur=1, int l=0, int r=100000){
    int f = LCTree[cur];
    int fval = A[f]*x+B[f], ansval = A[ans]*x+B[ans];

    if(fval > ansval){
        ans = f;
    }

    if(l==r){
        return ans;
    }

    int m = (l+r)/2;

    if(x<=m){
        return maxf(x, ans, 2*cur, l, m);
    }
    else{
        return maxf(x, ans, 2*cur+1, m+1, r);
    }
}

int main(){
    int n;
    cin >> n;

    for(int i=1; i<=n; i++){
        cin >> A[i] >> B[i];
    }

    build(n);

    int Q;

    cin >> Q;

    for(int i=0; i<Q; i++){
        int x;

        cin >> x;

        cout << "La funcion " << maxf(x) << " maximiza " << x << endl;
    }


    return 0;
}