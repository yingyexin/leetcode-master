#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;


class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param s string字符串 
     * @return bool布尔型
     */
    bool isValid(string s) {
        // write code here
        stack<char> st;
        for(int i=0; i<s.size(); i++){
            if(s[i]==')' ||s[i]==']' ||s[i]=='}' ){
                char c = st.top();
                st.pop();
                if(s[i]==')' && c!='(' ) return false;
                if(s[i]==']' && c!='[' ) return false;
                if(s[i]=='}' && c!='{' ) return false;
            }else
                st.push(s[i]);
        }
        return st.empty();
    }
};