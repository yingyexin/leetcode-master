#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "string.h"
using namespace std;

// vector<int> computeLPS(string str){
//     int n = 0;
//     int i=1;
//     vector<int> lps(str.size(), 0);
//     while(i < str.size()){
//         if(str[i] == str[n]){
//             n++;
//             lps[i] = n;
//             i++;
//         }else {
//             if(n!=0){
//                 n = lps[n-1];
//             } else{
//                 lps[i]=0;
//                 i++;
//             }
//         }
//     }
//     for(int i=0; i<lps.size(); i++)
//         cout << lps[i] << " ";
//     return lps;
// }

//     string newstr = s+"/"+ t;
//     vector<int> lps = computeLPS(newstr);
//     return t.size() - lps.back() + s.size();

/*
每次都可以将任意字符移动到末尾，使S变成T最少需要几步，不可变则返回-1

s=acdk, t=ckad, cost=2

*/


int minOper(string s, string t){
    // if(s.size() != t.size()) return -1;
    
    // check whether it can fullfill the requirements
    unordered_map<char, int> umap;
    for(int i=0; i<s.size(); i++)
        umap[s[i]] ++;
    for(int j=0; j<t.size(); j++)
        umap[t[j]] --;
    for(auto u:umap)
        if(u.second!=0) return -1;

    int p1 = 0, p2 = 0;
    while(p2 < s.size()){
        if(t[p1] == s[p2]){
            p1++;
            p2++;
        }else p2++;
    }
    return t.size()-p1;
}


int main(){
    string s, t;
    cin >> s >> t;
    
    int res = minOper(s, t);

    cout << res << endl;

    return 0;
}