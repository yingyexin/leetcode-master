#include <iostream>
#include <vector>
using namespace std;

/*
判断是否满足 an 递增， bi = ai+1 - ai 递减
*/

bool isValid(vector<int>& a, vector<int>& b){

    for(int i=0; i<a.size()-1; i++)
        if(a[i] >= a[i+1]) return false;
    
    for(int i=0; i<b.size()-1; i++)
        if(b[i] <= b[i+1]) return false;

    return true;
}


int main(){
    int n;
    cin >> n;

    vector<int> a(n);
    for(int i=0; i<n; i++)
        cin >> a[i];

    vector<int> b;
    for(int i=0; i<n-1; i++)
        b.push_back(a[i+1] - a[i]);

    bool res = isValid(a, b);
    if(res) cout << "Yes" << endl;
    else cout << "No" << endl;

    return 0;
}