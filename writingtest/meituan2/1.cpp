#include <iostream>
#include "string.h"
#include <unordered_map>
using namespace std;

int main() {
    int k;
    string str;
    cin >> str;
    cin >> k;

    unordered_map<char, string> umap;
    umap['a'] = "bc";
    umap['b'] = "ca";
    umap['c'] = "ab";

    string new_str;
    while(k>0){
        new_str="";
        for(int i=0; i<str.size(); i++)
            new_str += umap[str[i]];
        k--;
        str = new_str;
    }

    cout << new_str;

    return 0;
}