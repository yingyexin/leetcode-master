#include <iostream>


class Solution {
public:
    // Problem 22M dfs backtracking
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        dfs(n, n, "", res);
        return res;
    }
    void dfs(int left, int right, string curStr, vector<string>& res) {
        if (left == 0 && right == 0) { // 左右括号都不剩余了，递归终止
            res.push_back(curStr);
            return;
        }
        if (left > 0) // 如果左括号还剩余的话，可以拼接左括号
            dfs(left - 1, right, curStr + "(", res);
        if (right > left) // 如果右括号剩余多于左括号剩余的话，可以拼接右括号
            dfs(left, right - 1, curStr + ")", res);
    }
    // Problem 22M too long run time
    // 第一点，能用引用的就用引用，这点很基础，是语法层面的，引用不会被拷贝。像string word，visited，都可以带上引用。
    // 第二点比较隐蔽，我的dfs || dfs || dfs || dfs这里，任何一个dfs满足了，因为或的性质，剩下的dfs就不会遍历了。这也是很多人单独进行4次dfs会额外花很多时间的原因。
    // 把 vector<pair<int, int>> directions{{0, 1}, {0, -1}, {1, 0}, {-1, 0}}; 移到dfs函数外面就好了
    bool dfs(vector<vector<char>>& board, vector<vector<bool>>& visited, const string& word, int str_idx, int i, int j) {//TODO: use &, avoid copy
        if (str_idx == word.size()) return true;
        if (i >= board.size() || i < 0 ||
            j >= board[0].size() || j < 0 ||
            visited[i][j] == true || board[i][j] != word[str_idx]) return false;

        visited[i][j] = true;
        if (dfs(board, visited, word, str_idx + 1, i + 1, j) ||
            dfs(board, visited, word, str_idx + 1, i - 1, j) ||
            dfs(board, visited, word, str_idx + 1, i, j + 1) ||
            dfs(board, visited, word, str_idx + 1, i, j - 1)) return true; //TODO: use ||, when one fulfill, stop explore
        visited[i][j] = false;
        return false;
    }
    bool exist(vector<vector<char>>& board, string word) {
        vector<vector<bool>> visit(board.size(), vector<bool>(board[0].size(), false));
        for(int i=0; i<board.size(); i++)
            for(int j=0; j<board[0].size(); j++)
                if(dfs(board, visit, word, 0, i, j)) return true;
        return false;
    }
    //Problem 332D 
    vector<string> path;
    bool dfs(unordered_map<string, vector<string>>& tickets_map, int n, string start, unordered_map<string, vector<bool>>& used_map){
        if(path.size()==n+1){
            return true;
        }
        vector<string> des = tickets_map[start];
        for(int i=0; i<des.size(); i++){
            if(used_map[start][i]) continue;
            // cout << start << des[i] << endl;
            used_map[start][i]=true;
            path.push_back(des[i]);
            if(dfs(tickets_map, n, des[i], used_map)) return true;
            path.pop_back();
            used_map[start][i]=false;
        }
        return false;
    }
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        unordered_map<string, vector<string>> tickets_map;
        unordered_map<string, vector<bool>> used_map;
        for(int i=0; i<tickets.size(); i++){
            tickets_map[tickets[i][0]].push_back(tickets[i][1]);
            used_map[tickets[i][0]].push_back(false);
        }
        for(auto& t:tickets_map){
            sort(t.second.begin(), t.second.end());
            // cout << t.first << t.second[0] << endl;
        }
        path.push_back("JFK");
        dfs(tickets_map, tickets.size(), "JFK", used_map);
        return path;
    }
}
