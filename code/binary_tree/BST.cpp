#include <iostream>
#include <vector>
#include <stack>
#include <string.h>
#include <limits> //for numeric_limits
#include <queue>
#include <math.h> // for print tree
using namespace std;

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(): val(int(0)), left(nullptr), right(nullptr) {}
    TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
};

class Tree{
public:
    TreeNode* root;
    Tree(): root(nullptr){}
    ~Tree(){}

    TreeNode* buildTree(vector<string>& nums){
        vector<TreeNode*> vec_node;
        for(auto& str:nums)
            if(str!="null")
                vec_node.emplace_back(new TreeNode(stoi(str)));
            else
                vec_node.emplace_back(nullptr);
            
        root = vec_node[0];
        for (int i=0; 2*i+2 < vec_node.size();i++){
            if(vec_node[i]){
                vec_node[i]->left = vec_node[2*i+1];
                vec_node[i]->right = vec_node[2*i+2];
            }
        }
        return root;
    };
    void printTreeLevel(TreeNode* root, int n){
        queue<TreeNode*> q;
        if(root)
            q.push(root);
        int level = 1;
        while(!q.empty() && pow(2,level)-1 <= n){
            int size = q.size();
            for(int i=0; i<size; i++){
                TreeNode* node = q.front();
                q.pop();
                if(node) 
                    cout << (node->val) << " ";
                else 
                    cout << "null"<< " ";
                if(node) {
                    q.push(node->left);
                    q.push(node->right);
                }
            }
            level++;
        }
        cout << endl;
    }
};

class BSTsolution{
private:
    TreeNode* pre = nullptr;
public:
    // p700E
    TreeNode* searchBST(TreeNode* root, int val) {
        if(root==nullptr || root->val==val)
            return root;
        if(root->val > val)
            return searchBST(root->left, val);
        if(root->val < val)
            return searchBST(root->right, val);
        return nullptr;
    }
    TreeNode* searchBST1(TreeNode* root, int val) {
        while(root){
            if(root->val > val)
                root = root->left;
            else if (root->val < val)
                root = root->right;
            else return root;
        }
        return nullptr;
    }
    // P98M
    bool isValidBST(TreeNode* root) {
        if (root) 
            return traversalBST(root);     
        return true;
    }
    bool traversalBST(TreeNode* cur){
        bool left = true, right = true;
        if(cur->left)
            left = traversalBST(cur->left);
        
        if(pre!=nullptr && pre->val >= cur->val)
            return false;
        pre = cur;

        if(cur->right)
            right = traversalBST(cur->right);
         
        return left && right;
    }
    bool isValidBST1(TreeNode* root) {
        stack<TreeNode*> st;
        if(!root) return true;
        TreeNode* cur = root;
        TreeNode* pre = nullptr;
        while(cur!=nullptr || !st.empty()){
            if(cur!=nullptr){
                st.push(cur);
                cur = cur->left;
            } else {
                TreeNode* node = st.top();
                st.pop();
                if(pre!=nullptr && pre->val >= node->val)
                    return false;
                pre = node;
                cur = node->right;
            }
        }     
        return true;
    }
    
    // P530E
    int getMinimumDifference(TreeNode* root) {
        stack<TreeNode*> st;
        if(!root) return 0;
        TreeNode* cur = root;
        TreeNode* pre = nullptr;
        int res = std::numeric_limits<int>::max();
        while(cur!=nullptr || !st.empty()){
            if(cur!=nullptr){
                st.push(cur);
                cur = cur->left;
            } else {
                cur = st.top();
                st.pop();
                if(pre!=nullptr)
                    res = res > cur->val-pre->val ? cur->val-pre->val : res;
                pre = cur;
                cur = cur->right;
            }
        }
        return res;
    }

    // p501E
    vector<int> findMode(TreeNode* root) {
        vector<int> res;
        int count = 0;
        int max = std::numeric_limits<int>::min();
        if (root)
            traversalMode(root, res, max, count);
        return res;
    }
    void traversalMode(TreeNode* cur, vector<int>& res, int& max, int& count){
        if(!cur)
            return;
        traversalMode(cur->left, res, max, count);

        if(pre == nullptr)
            count = 1;
        else if(pre->val == cur->val)
            count++;
        else 
            count = 1;
        
        pre = cur; 
        if (max < count){
            max = count;
            while(!res.empty())
                res.pop_back();
            res.push_back(cur->val);    
        } else if(max == count){
            res.push_back(cur->val);
        }

        traversalMode(cur->right, res, max, count);
    }
    vector<int> findMode1(TreeNode* root) {
        stack<TreeNode*> st;
        vector<int> res;
        if(!root) return res;

        TreeNode* cur = root;
        TreeNode* pre = nullptr;
        int max = std::numeric_limits<int>::min();
        int count = 0;
        
        while(cur!=nullptr || !st.empty()){
            if(cur!=nullptr){
                st.push(cur);
                cur = cur->left;
            } else {
                cur = st.top();
                st.pop();
                if(pre == nullptr)
                    count = 1;
                else if(pre->val ==cur->val)
                    count++;
                else 
                    count = 1;
                
                pre = cur;
                if (max < count){
                    max = count;
                    while(!res.empty())
                        res.pop_back();
                    res.push_back(cur->val);    
                } else if(max == count){
                    res.push_back(cur->val);
                }
                cur = cur->right;
            }
        }
        return res;
    }

    // p236M
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root == p || root == q || root==nullptr)
            return root;
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);
        if(left && right)   return root;
        else if(left && !right) return left;
        else if(!left && right) return right;
        else return nullptr;
    }

    //P235E
    TreeNode* lowestCommonAncestorBST(TreeNode* root, TreeNode* p, TreeNode* q) {
        // if((root->val < p->val && root->val > q->val) || 
        //    (root->val > p->val && root->val < q->val))
        //         return root; //TODO: note [p,q] should be included!! root=p or q
        if(root->val < p->val && root->val < q->val)
            return lowestCommonAncestorBST(root->right, p, q);
        if(root->val > p->val && root->val > q->val)
            return lowestCommonAncestorBST(root->left, p, q);
        else return root;
    }

    // 701M
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if(!root){
            TreeNode* node = new TreeNode(val);
            return node;
        }
        
        if(root->val < val){
            root->right = insertIntoBST(root->right, val);
        //     if(node){
        //         root->right = node;
        //         return root;
        //     }
        }
        else if(root->val > val){
            root->left = insertIntoBST(root->left, val);
        }
        return root;
    }
    TreeNode* insertIntoBST1(TreeNode* root, int val) {
        if(!root)
            return new TreeNode(val); // TODO: NOTE:[]
        TreeNode* cur = root;
        TreeNode* pre = nullptr;
        while(cur != nullptr){
            pre = cur;
            if(cur->val < val){
                cur = cur->right;
                if(!cur)
                    pre->right = new TreeNode(val);
            }
            else if(cur->val > val){
                cur = cur->left;
                if(!cur)
                    pre->left = new TreeNode(val);
            }
        }
        return root;
    }

    // 450M
    TreeNode* deleteNode(TreeNode* root, int key) {
        if(!root) return root;
        if(root->val == key){
            if(!root->left){
                TreeNode* temp = root;
                root = root->right;
                delete temp;
                return root;
            }
            else if(!root->right){
                TreeNode* temp = root;
                root = root->left;
                delete temp;    
                return root; 
            }  
            else{
                TreeNode* cur = root->right;
                while(cur->left)
                    cur = cur->left;
                cur->left = root->left;
                TreeNode* temp = root;
                root = root->right;
                delete temp;
                return root;   
            }
        }

        if(root->left) root->left = deleteNode(root->left, key);
        if(root->right) root->right = deleteNode(root->right, key);

        return root;
    }

    // 108E
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return constructBST(0, nums.size()-1, nums);
    }
    TreeNode* constructBST(int left, int right, vector<int>& nums){
        if(left>right)
            return nullptr;
        int mid = left + (right-left)/2;
        TreeNode* cur = new TreeNode(nums[mid]);

        cur->left = constructBST(left, mid-1, nums);
        cur->right = constructBST(mid+1, right, nums);

        return cur;
    }

    // 669M
    TreeNode* trimBST(TreeNode* root, int low, int high) {
        if(!root) return nullptr;
        if(root->val < low)
            return trimBST(root->right, low, high);
        if(root->val > high)
            return trimBST(root->left, low, high);
        
        root->left = trimBST(root->left, low, high);
        root->right = trimBST(root->right, low, high);

        return root;
    }

    // 538M
    TreeNode* convertBST(TreeNode* root) {
        int pre = 0;
        convert(root, pre);
        return root;
    }
    void convert(TreeNode* cur, int& pre){
        if(!cur) return;
        convert(cur->right, pre);
        cur->val = cur->val + pre;
        pre = cur->val;
        convert(cur->left, pre);
    }
    TreeNode* convertBST1(TreeNode* root) {
        stack<TreeNode*> st;
        int pre = 0;
        TreeNode* cur = root;
        while(cur!=nullptr || !st.empty()){
            if(cur!=nullptr){
                st.push(cur);
                cur = cur->right;
            } else {
                cur = st.top();
                st.pop();
                cur->val = cur->val + pre;
                pre = cur->val;
                cur = cur->left;
            }
        }
        return root;
    }
};

int main(){
    int n, k;
    cin >> n >> k;
    string ch;
    vector<string> nums;
    for(int i=0; i<n; i++){
        cin >> ch;
        nums.push_back(ch);
    }
    Tree* tree = new Tree();
    tree->root = tree->buildTree(nums);

    BSTsolution sol;
    sol.deleteNode(tree->root, k);
    tree->printTreeLevel(tree->root, n);

    return 0;
}