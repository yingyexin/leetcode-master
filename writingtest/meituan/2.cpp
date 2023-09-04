#include <iostream>
#include <vector>
#include "string.h"
using namespace std;

/*
每行取一个字符，判断是否有子串为meituan的组合
abc//def -> NO
nm//ex//it//td//ul//qu//ac//nt ->YES
*/

bool isValid(vector<vector<char>>& matrix, int n, int m){
    string str = "meituan";
    int p1=0, p2=0;

    while(p2<n){
        for(int j=0; j<m; j++)
            if(str[p1]==matrix[p2][j]){
                p1++;
                break;
            }
        p2++;
    }   

    return p1==str.size();
}


int main(){
    int m, n;
    cin >> n >> m;
    vector<vector<char>> matrix(n, vector<char>(m));
    
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            cin >> matrix[i][j];
           
    bool res = isValid(matrix, n, m);
    if(res) cout << "YES" << endl;
    else cout << "NO" << endl;
        
    return 0;

}