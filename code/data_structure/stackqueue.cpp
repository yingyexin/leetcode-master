#include <stack>
#include <queue>
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <unordered_map>

using namespace std;

// 232E
class MyQueue {
public:
    MyQueue() {
    }
    
    void push(int x) {
        stIn.push(x);  
    }
    
    int pop() {
        int res;
        if (stOut.empty()){
            while(!stIn.empty()){
                stOut.push(stIn.top());
                stIn.pop();
            }
        } 
        res = stOut.top();
        stOut.pop();
        
        return res;
    }
    
    int peek() {
        if (stOut.empty()){
            while(!stIn.empty()){
                stOut.push(stIn.top());
                stIn.pop();
            }
        }

        return stOut.top();
    }
    
    bool empty() {
        return stIn.empty() && stOut.empty();
    }

private:
    stack<int> stIn;
    stack<int> stOut;
};

// 225E
class MyStack {
public:
    MyStack() {
    }
    
    void push(int x) {
        if(q1.empty() && q2.empty())
            q1.push(x);
        else if(q1.empty())
            q2.push(x);
        else if (q2.empty())
            q1.push(x);
    }
    
    int pop() {
        int res;
        if(q1.empty()){
            while(q2.size()>1){
                q1.push(q2.front());
                q2.pop();
            }
            res = q2.front();
            q2.pop();
        } else if(q2.empty()){
            while(q1.size()>1){
                q2.push(q1.front());
                q1.pop();
            }
            res = q1.front();
            q1.pop();
        }
        return res;
    }
    
    int top() {
        int num = this->pop();
        this->push(num);
        return num;
    }
    
    bool empty() {
        return q1.empty() && q2.empty();
    }
private:
    queue<int> q1;
    queue<int> q2;
};

// 225E one queue
class MyStack1 {
public:
    MyStack1() {
    }
    
    void push(int x) {
        q1.push(x);
    }
    
    int pop() {
        int size = q1.size()-1;
        while(size--){
            q1.push(q1.front());
            q1.pop();
        }
        int res = q1.front();
        q1.pop();
        return res;
    }
    
    int top() {
        return q1.back();
    }
    
    bool empty() {
        return q1.empty();
    }
private:
    queue<int> q1;
};

class Solution {
public:
    // Problem 20E
    bool isValid(string s) {
        stack<char> st;
        for(auto& ch:s){
            if(st.empty())
                st.push(ch);
            else{
                char c = st.top();
                if((c=='(' && ch ==')') || (c=='[' && ch==']') || (c=='{' && ch=='}'))
                    st.pop();
                else
                    st.push(ch);
            }
        }
        return st.empty();
    }
    
    // Problem 1047E
    string removeDuplicates(string s) {
        stack<char> st;
        for(auto& ch:s){
            if (st.empty() || st.top()!=ch)
                st.push(ch);
            else
                st.pop();
        }
        string res;
        while(!st.empty()){
            res.push_back(st.top());
            st.pop();
        }
        std::reverse(res.begin(), res.end());
        return res;
    }

    // Problem 150M
    int evalRPN(vector<string>& tokens) {
        stack<int> st;
        for(auto& ch: tokens){
            if(st.empty() || (ch!="+" && ch!="-" && ch!="*" && ch!="/"))
                st.push(stoi(ch));
            else {
                int num2 = st.top();
                st.pop();
                int num1 = st.top();
                st.pop();
                if (ch=="+") st.push(num1+num2);
                if (ch=="-") st.push(num1-num2);
                if (ch=="*") st.push(num1*num2);
                if (ch=="/") st.push(num1/num2);
            }
        }
        return st.top();
    }

    // Problem 239D TODO:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {

    }

    // Problem 347M
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> num_map;
        for(int num:nums){
            num_map[num]++;
        }
        auto cmp = [](const pair<int,int> a, const pair<int,int> b){
            return a.second > b.second;
        };
        priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(cmp)> q(cmp);
        for(auto [num, count]:num_map){
            if(q.size()<k)
                q.emplace(num, count);
            else
                if(q.top().second<count){
                    q.pop();
                    q.emplace(num, count);
                }
        }
        vector<int> res;
        while(!q.empty()){
            res.push_back(q.top().first);
            q.pop();
        }
        return res;
    }

};


int main(){
    string s="()[]{}";

    Solution sol;
    bool res = sol.isValid(s);
    cout<< res<<endl;
    return 0;
}