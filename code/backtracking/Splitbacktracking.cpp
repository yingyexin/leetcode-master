#include <iostream>
#include <vector>
#include <string.h>
#include <boost/algorithm/string.hpp> // split
#include <unordered_set>
#include <unordered_map>

using namespace std;

class SplitSolution {
public:
    //131M
    vector<vector<string>> partition(string s) {
        vector<string> path;
        vector<vector<string>> res;
        backtracking131(s, 0, path, res);
        return res;
    }
    void backtracking131(string s, int start, vector<string>& path, vector<vector<string>>& res){
        if(start >= s.size()){
            res.push_back(path);
            return;
        }
        string str;
        for(int i=start; i<s.size(); i++){
            str += s[i]; //TODO:substr(start, i) 
            if(isPalindrome(str))
                path.push_back(str);
            else
                continue;
            backtracking131(s, i+1, path, res);
            path.pop_back();
        }
    }
    bool isPalindrome(string str){
        for(int i=0, j=str.size()-1; i<=j; i++, j--){
            if(str[i]!=str[j])
                return false;
        }
        return true;
    }

    // 93M
    vector<string> restoreIpAddresses(string s) {
         vector<string> path;
        vector<string> res;
        backtracking93(s, 0, path, res);
        return res;
    }
    void backtracking93(string s, int start, vector<string>& path, vector<string>& res){
        if(start < s.size() && path.size()>=4)
            return;
        else if(start >= s.size()&& path.size()==4){
            string strPath;
            for(auto& ch:path)
                strPath += ch + ".";
            strPath.pop_back();
            res.push_back(strPath);
            return;
        }
        for(int i=start; i<s.size(); i++){
            string str = s.substr(start, i-start+1);
            if(isIP(str)){
                path.push_back(str);
            }
            else
                continue;
            backtracking93(s, i+1, path, res);
            path.pop_back();
        }
    }
    bool isIP(string str){
        if(str[0]=='0' && str.size()>1)
            return false;  
        else if(str.size()>3 || stoi(str)>255 || stoi(str)<0)
            return false;
        else   
            return true;
    }
};

class SubsetSolution {
public:
    // 78M
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> path;
        vector<vector<int>> res;
        res.push_back({});
        backtracking78(nums, 0, path, res);
        return res;
    }
    void backtracking78(vector<int> nums, int start, vector<int>& path, vector<vector<int>>& res){
        if(start >= nums.size())
            return;
        
        for(int i=start; i<nums.size(); i++){
            path.push_back(nums[i]);
            res.push_back(path);
            backtracking78(nums, i+1, path, res);
            path.pop_back();
        }
    }

    // 90M
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<int> path;
        vector<vector<int>> res;
        res.push_back({});
        sort(nums.begin(), nums.end());
        backtracking90(nums, 0, path, res);
        return res;
    }
    void backtracking90(vector<int> nums, int start, vector<int>& path, vector<vector<int>>& res){
        if(start >= nums.size())
            return;
        
        for(int i=start; i<nums.size(); i++){
            if(i>start && nums[i]==nums[i-1])
                continue;
            path.push_back(nums[i]);
            res.push_back(path);
            backtracking90(nums, i+1, path, res);
            path.pop_back();
        }
    }
};

class ArraySolution {
public:
    // 46M
    vector<vector<int>> permute(vector<int>& nums) {
        vector<int> path;
        vector<vector<int>> res;
        vector<bool> used(nums.size(), false);
        backtracking46(nums, path, res);
        backtracking(nums, used, path, res);
        return res;
    }
    void backtracking46(vector<int> nums, vector<int>& path, vector<vector<int>>& res){
        if(path.size() == nums.size()){
            res.push_back(path);
            return;
        }
        
        for(int i=0; i<nums.size(); i++){
            if(find(path.begin(), path.end(), nums[i]) != path.end())
                continue;
            path.push_back(nums[i]);
            backtracking46(nums, path, res);
            path.pop_back();
        }
    }
    void backtracking(vector<int> nums, vector<bool>& used, vector<int>& path, vector<vector<int>>& res){
        if(path.size() == nums.size()){
            res.push_back(path);
            return;
        }
        
        for(int i=0; i<nums.size(); i++){
            if(used[i])
                continue;
            used[i] = true;
            path.push_back(nums[i]);
            backtracking(nums, used, path, res);
            used[i] = false;
            path.pop_back();
        }
    }

    // 47M
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<int> path;
        vector<vector<int>> res;
        vector<bool> used(nums.size(), false);
        sort(nums.begin(), nums.end());
        backtracking47(nums, used, path, res);
        return res;
    }
    void backtracking47(vector<int> nums, vector<bool>& used, vector<int>& path, vector<vector<int>>& res){
        if(path.size() == nums.size()){
            res.push_back(path);
            return;
        }
        for(int i=0; i<nums.size(); i++){
            if(i>0 && nums[i]==nums[i-1] && !used[i-1])
                continue;
            if(used[i])
                continue;
            used[i] = true;
            path.push_back(nums[i]);
            backtracking47(nums, used, path, res);
            used[i] = false;
            path.pop_back();
        }
    }
    void backtracking1(vector<int> nums, vector<int>& path, vector<vector<int>>& res){//used!
        if(path.size() == nums.size()){
            res.push_back(path);
            return;
        }
        //unordered_set<int> uset;
        int used[100] = {0};
        for(int i=0; i<nums.size(); i++){
            // if(uset.count(nums[i]))
            //     continue;
            // uset.insert(nums[i]);
            if(used[nums[i]]==1)
                continue;
            used[nums[i]] = 1;
            path.push_back(nums[i]);
            backtracking1(nums, path, res);
            path.pop_back();
        }
    }

};

class SubseqSolution {
public:
    // 491M
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        vector<int> path;
        vector<vector<int>> res;
        backtracking491(nums, 0, path, res);
        return res;
    }
    void backtracking491(vector<int> nums, int start, vector<int>& path, vector<vector<int>>& res){
        if(path.size()>=2)
            res.push_back(path);

        int used[201]={0}; // no order, use the value [-100,100]
        for(int i=start; i<nums.size(); i++){
            if(!path.empty() && path.back()>nums[i])
                continue;
            if(i>start && used[nums[i]+100]==1)
                continue;
            used[nums[i]+100] = 1;
            path.push_back(nums[i]);
            backtracking491(nums, i+1, path, res);
            path.pop_back();
        }
    }

    // 332D TODO:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        unordered_map<string, pair<string, int>> flightmap;
        vector<string> res;
        if(tickets.empty()) return res;
        for(int i=0; i<tickets.size(); i++)
            if(flightmap.find(tickets[i][0])==flightmap.end())
                flightmap[tickets[i][0]] = make_pair(tickets[i][1], 1);
            else
                flightmap[tickets[i][0]].second++;
        res.push_back("JFK");
        backtracking332(flightmap, tickets.size(), res);
        return res;
    }
    bool backtracking332(unordered_map<string, pair<string, int>>& flightmap, int numTic, vector<string>& res){
        if(res.size() >= numTic+1)
            return true;
        
        for (int i=0; i<numTic; i++) {
            auto it = flightmap.find(res.back());
            if(it!=flightmap.end() && it->second.second>0){
                it->second.second--;
                res.push_back(it->second.first);
                if(backtracking332(flightmap, numTic, res))
                    return true;
                it->second.second++;
                res.pop_back();
            }
        }
        return false;
    }

};

class ChessSolution {
public:
    // 51D
    vector<vector<string>> solveNQueens(int n) {
        string str(n,'.');
        vector<vector<string>> res;
        vector<string> chess(n, str);
        backtracking51(n, 0, chess, res);
        return res;
    }
    void backtracking51(int n, int row, vector<string>& chess, vector<vector<string>>& res){
        if(row==n){
            res.push_back(chess);
            return;
        }
        for(int col=0; col<n; col++){
            if(isValid(chess, n, col, row)){
                chess[row][col] = 'Q';
                backtracking51(n, row+1, chess, res);
                chess[row][col] = '.';
            }
        }
    }
    bool isValid(vector<string> chess, int n, int col, int row){
        for(int i=0; i<row; i++){
            if(chess[i][col]=='Q')
                return false;
            if(col-(row-i)>=0 && chess[i][col-(row-i)]=='Q')
                return false;
            if(col+(row-i)<n && chess[i][col+(row-i)]=='Q')
                return false;
        }
        return true;
    }

    // 37D
    void solveSudoku(vector<vector<char>>& board) {
        backtracking37(board);
    }
    bool backtracking37(vector<vector<char>>& board){
        for(int row=0; row<board.size(); row++){
            vector<char> nums;
            for(int col=0; col< board[0].size(); col++){
                if(board[row][col]!='.'){
                    nums.push_back(board[row][col]);
                    continue;
                }
                for(char k='1'; k<='9'; k++){
                    if (find(nums.begin(), nums.end(), k)!=nums.end())
                        continue;
                    if(isValid37(row, col, board, k)){
                        board[row][col] = k;
                        if(backtracking37(board))   return true;
                        board[row][col] = '.';
                    }
                }
                return false;
            }
        }
        return true;
    }
    bool isValid37(int row, int col, vector<vector<char>>board, char k){
        for(int i=0; i<board.size();i++)
            if(board[i][col]==k)
                return false;
        for(int j=0; j<board[0].size(); j++)
            if(board[row][j]==k)
                return false;
        
        int startRow = (row / 3) * 3;
        int startCol = (col / 3) * 3;
        for (int i = startRow; i < startRow + 3; i++) { // 判断9方格里是否重复
            for (int j = startCol; j < startCol + 3; j++) {
                if (board[i][j] == k ) {
                    return false;
                }
            }
        }
        return true;
    }
};

void printStr(vector<string> res){
    cout<< "[" <<endl;
    for(int i=0; i<res.size(); i++)
        cout << "[" << res[i] << "]" << endl;
    cout <<"]" <<endl;
}
void printInt(vector<vector<int>> res){
    if(res.empty())
        return;
    cout<< "[" <<endl;
    for(int i=0; i<res.size(); i++){
        cout<< "[" ;
        for(int j=0; j<res[i].size();j++)
            cout << res[i][j] << " ";
        cout<< "]"<<endl;
    }
    cout <<"]" <<endl;
}

int main(){
    // string str;
    // cin >> str;
    vector<int> nums = {1,2,1,1};
    int n=3;
    ChessSolution sol;
    vector<vector<string>> result = sol.solveNQueens(n);
    for(vector<string> str:result)
        printStr(str);

    return 0;
}