#include <iostream>
#include <vector>
#include <iomanip>
#include <math.h>
using namespace std;

int func(int n, int a, int b){
    if(abs(b-a)>n-1) return -1;
    else 
        return max(0, (n-1-abs(b-a))/2) + max(a, b);
}


int main(){
    int t;
    cin >> t;
    int n, a, b;
    vector<int> height(t);
    for(int i=0; i<t; i++){
        cin >> n >> a >> b;
        height[i] = func(n, a, b);
    }

    for(int i=0; i<t; i++)
        cout << height[i] << endl;
        
}