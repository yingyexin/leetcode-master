#include <iostream>
#include <vector>
#include <iomanip>
#include <math.h>
#include <unordered_set>
using namespace std;

int func(string s, string c){
    unordered_set<char> us;
    unordered_set<char> uc;
    for(char s_:s)
        us.insert(s_);
    for(char c_:c)
        uc.insert(c_);
    
    int res = 0;
    for(auto c_:uc)
        if(us.count(c_)) res++;

    return res;
}


int main(){
    int n, m;
    cin >> n >> m;
    
    string s, c;
    cin >> s;
    cin >> c;

    cout << func(s, c) << endl;

    
        
}