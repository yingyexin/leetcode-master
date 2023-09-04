#include <math.h>
#include <iostream>
#include <vector>
using namespace std;

bool isValid(int A, int B, int x, int y){
   
    double dist = (A*x*1.0 - B*y*1.0) / sqrt(A*A*1.0 + B*B*1.0);
    // cout << x << " " << y << " " << dist << endl;
    return dist< sqrt(2) && dist>0;
}

int count(int n, int m){
    int A = m, B =n;
    int res=0;
    for(int i=1; i<=n; i++)
        for(int j=0; j<m; j++)
            if(isValid(A,B,i,j))
                res++;

    return res;
}

int main(){
    int n, m;
    cin >> n >> m;

    cout << count(n, m) << endl;

    return 0;
}