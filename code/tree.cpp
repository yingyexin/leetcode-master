#include <iostream>
#include <vector>
#include <memory>
#include <stack>
#include <queue>
#include <limits>
#include <unordered_map>

using namespace std;

template <typename T>
class TreeNode
{
public:
    T val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(): val(T(0)), left(nullptr), right(nullptr) {}
    TreeNode(T x): val(x), left(nullptr), right(nullptr) {}
    TreeNode(T x, TreeNode* L, TreeNode* R): val(x), left(L), right(R) {}
};

//N child Node
template<typename T>
class NTreeNode
{
public:
    T val;
    vector<NTreeNode*> children;
    NTreeNode(): val(T(0)), children(vector<nullptr>){}
    NTreeNode(T x): val(x), children(vector<nullptr>){}
    NTreeNode(T x, vector<NTreeNode*> node): val(x), children(node) {}
};

// next node
template <typename T>
class Node
{
public:
    T val;
    Node* left;
    Node* right;
    Node* next;
    Node(): val(T(0)), left(nullptr), right(nullptr), next(nullptr) {}
    Node(T x): val(x), left(nullptr), right(nullptr), next(nullptr) {}
    Node(T x, TreeNode* L, TreeNode* R, TreeNode* N): val(x), left(L), right(R), next(N){}
};

class TraversalSolution{
public:
    // Problem 144, 509: preorderTraversal
    vector<int> preorderTraversalR(TreeNode<int>* root){
        vector<int> result;
        preorder(root, result);
        return result;
    }
    void preorder(TreeNode<int>* node, vector<int> &vec){ //TODO:(note) & to change vec
        if (node == nullptr) return; // TODO:(note) return result if output is vec

        vec.emplace_back(node->val);
        preorder(node->left, vec);
        preorder(node->right, vec);
    }
    vector<int> preorderTraversalI(TreeNode<int>* root){
        stack<TreeNode<int>*> st;
        vector<int> result;
        if (root!=nullptr) st.push(root);  // TODO:(note) root is nullptr
        while(!st.empty()){
            TreeNode<int>* node = st.top();
            st.pop();
            result.emplace_back(node->val);
            if (node->right != nullptr) st.push(node->right);
            if (node->left != nullptr) st.push(node->left);
        }
        return result;
    }

    // Problem 145. 590: postorderTraversal
    vector<int> postorderTraversalR(TreeNode<int>* root){
        vector<int> result;
        postorder(root, result);
        return result;
    }
    void postorder(TreeNode<int>* node, vector<int>& vec){
        if (node == nullptr) return;

        postorder(node->left, vec);
        postorder(node->right, vec);
        vec.emplace_back(node->val);
    }
    vector<int> postorderTraversalI(TreeNode<int>* root){
        stack<TreeNode<int>*> st;
        vector<int> result;
        if (root != nullptr) st.push(root);
        while(!st.empty()){
            TreeNode<int>* node = st.top();
            st.pop();
            result.emplace_back(node->val);
            if(node->left != nullptr) st.push(node->left);
            if(node->right != nullptr) st.push(node->right);
        }
        std::reverse(result.begin(), result.end());//vector reverse
        return result;
    }

    // Problem 94: inorderTraversal
    vector<int> inorderTraversalR(TreeNode<int>* root){
        vector<int> result;
        inorder(root, result);
        return result;
    }
    void inorder(TreeNode<int>* node, vector<int>& vec){
        if(node == nullptr) return;
        inorder(node->left, vec);
        vec.emplace_back(node->val);
        inorder(node->right, vec);
    }
    vector<int> inorderTraversalI(TreeNode<int>* root){
        stack<TreeNode<int>*> st;
        vector<int> result;
        //if(root==nullptr) return result;
        TreeNode<int>* cur = root;
        while(cur!=nullptr || !st.empty()){
            if (cur != nullptr){
                st.push(cur);
                cur = cur->left;
            } else {
                TreeNode<int>* node = st.top();
                st.pop();
                result.emplace_back(node->val);
                cur = node->right;
            }
        }
        return result;
    }

    // Problem 102,107: levelOrder 
    // Problem 639: averageOfLevels
    vector<vector<int>> levelOrderTraversalR(TreeNode<int>* root){
        vector<vector<int>> result;
        int depth = 0;
        levelorder(root, result, depth);
        return result;
    }
    void levelorder(TreeNode<int>* node, vector<vector<int>>& res, int depth){
        if (node == nullptr) return;
        if (res.size() == depth) res.emplace_back(vector<int>());

        res[depth].emplace_back(node->val);//TODO: Note for left&right, depth the same
        levelorder(node->left, res, depth+1);
        levelorder(node->right, res, depth+1);
    }
    vector<vector<int>> levelOrderTraversalI(TreeNode<int>* root){
        queue<TreeNode<int>*> q;
        vector<vector<int>> result;
        if(root!=nullptr) q.push(root);
        while(!q.empty()){
            vector<int> res;
            int size = q.size();
            for(int i=0; i<size; i++){
                TreeNode<int>* node = q.front();
                q.pop();
                res.emplace_back(node->val);
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
            result.emplace_back(res);
        }
        return result;
    }

    // Problem 199: level-rightSideView 
    vector<int> rightSideView(TreeNode<int>* root) {
        queue<TreeNode<int>*> q;
        vector<int> result;
        if(root) q.push(root);
        while(!q.empty()){
            //vector<int> level;
            int size = q.size();
            for(int i=0; i<size; i++){
                TreeNode<int>* node = q.front();
                q.pop();
                if(i==size-1) result.push_back(node->val);
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
        }
        return result;
    }

    // Problem 429: N tree
    vector<vector<int>> levelOrderTraversalI(NTreeNode<int>* root) {
        queue<NTreeNode<int>*> q;
        vector<vector<int>> result;
        if (root) q.push(root);
        while(!q.empty()){
            vector<int> res;
            int size = q.size();
            for(int i=0; i<size; i++){
                NTreeNode<int>* node = q.front();
                q.pop();
                res.emplace_back(node->val);
                /*for(int j=0; j<node->children.size(); j++)
                    if(node->children[j]) q.push(node->children[j]);*/
                for(auto child : node->children) //TODO:(note) traverse vector element
                    if(child) q.push(child);
            }
            result.emplace_back(res);
        }
        return result;
    }

    // Problem 515: largestValues
    vector<int> largestValues(TreeNode<int>* root) {
        queue<TreeNode<int>*> q;
        vector<int> result;
        if(root) q.push(root);
        while(!q.empty()){
            int max=std::numeric_limits<int>::min();
            int size = q.size();
            for(int i=0; i<size; i++){
                TreeNode<int>* node = q.front();
                q.pop();
                max = (max > node->val) ? max : node->val;
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
            result.push_back(max);
        }
        return result;
    }

    // Problem 116,117: find next node
    Node<int>* connect(Node<int>* root) {
        queue<Node<int>*> q;
        if(root) q.push(root);
        while(!q.empty()){
            int size = q.size();
            Node<int>* nodePre = q.front();
            Node<int>* node;
            for(int i=0; i<size; i++){
                node = q.front();
                q.pop();
                if (nodePre != node) nodePre->next = node;
                if (i == size-1) node->next = nullptr;
                
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
                nodePre = node;
            }
        }
        return root;
    }
    Node<int>* connect2(Node<int>* root) {
        queue<Node<int>*> q;
        if(root) q.push(root);
        while(!q.empty()){
            int size = q.size();
            Node<int>* nodePre;
            Node<int>* node;
            for(int i=0; i<size; i++){
                if (i==0){
                    nodePre = q.front();
                    q.pop();
                    node = nodePre;
                } else{
                    node = q.front();
                    q.pop();
                    nodePre->next = node;
                    nodePre = node;
                }
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
            node->next = nullptr;
        }
        return root;
    }

    // Problem 104,111: maxDepth,minDepth
    int maxDepth(TreeNode<int>* root) {
        queue<TreeNode<int>*> q;
        int depth = 0;
        if (root) q.push(root);
        while(!q.empty()){
            int size = q.size();
            depth++;
            for(int i=0; i<size; i++){
                TreeNode<int>* node = q.front();
                q.pop();
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
        }
        return depth;
    }
    int minDepth(TreeNode<int>* root){
        queue<TreeNode<int>*> q;
        int depth = 0;
        if (root) q.push(root);
        while(!q.empty()){
            int size = q.size();
            depth++;
            for(int i=0; i<size; i++){
                TreeNode<int>* node = q.front();
                q.pop();
                if(node->left == nullptr && node->right == nullptr) return depth;
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
        }
        return depth;
    }
    // P559E    
    int maxDepth(NTreeNode<int>* root) {
        queue<NTreeNode<int>*> q;
        if(root) q.push(root);
        int depth = 0;
        while(!q.empty()){
            int size = q.size();
            depth++;
            for(int i=0; i<size; i++){
                NTreeNode<int>* node = q.front();
                q.pop();
                for(auto& child:node->children)
                    if(child) q.push(child);
            }
        }
        return depth; 
    }
};

class PropertySolution{
public:
    // P101E
    bool isSymmetric(TreeNode<int>* root) {
        queue<TreeNode<int>*> q;
        TreeNode<int>* emp = new TreeNode<int>(numeric_limits<int>::min());
        if(root) q.push(root);
        bool sym = true;
        while(!q.empty()){
            vector<int> res;
            int size = q.size();
            for(int i=0; i<size; i++){
                TreeNode<int>* node = q.front();
                q.pop();
                res.push_back(node->val);
                if(node->left) q.push(node->left);
                else if(node->val!=numeric_limits<int>::min()) q.push(emp);
                
                if(node->right) q.push(node->right);
                else if(node->val!=numeric_limits<int>::min()) q.push(emp);
            }
            for(int j=0; j<res.size()/2; j++){
                if(res[j] == res[res.size()-1-j])
                    sym &=true;
                else
                    return false; 
            }
        }
        return sym;
    }
    bool isSymmetricI(TreeNode<int>* root){
        stack<TreeNode<int>*> st;
        st.push(root->right);
        st.push(root->left);
        while(!st.empty()){
            TreeNode<int>* L = st.top();
            st.pop();
            TreeNode<int>* R = st.top();
            st.pop();
            if (!L && !R)
                continue;
            if(!L || !R || L->val!=R->val)
                return false;
            st.push(L->right);
            st.push(R->left);
            st.push(L->left);
            st.push(R->right);
        }
        return true;
    }
    // P572E
    bool isSubtree(TreeNode<int>* root, TreeNode<int>* subRoot) {
        stack<TreeNode<int>*> st;
        if(root && subRoot) st.push(root);
        bool succ = false;
        while(!st.empty()){
            TreeNode<int>* node = st.top();
            st.pop();
            if(node && node->val == subRoot->val){
                succ = compare(node, subRoot);
                if(succ) return true;
            }
            
            if(node->right) st.push(node->right);
            if(node->left) st.push(node->left);
        }
        return false;
    }
    bool compare(TreeNode<int>* orig, TreeNode<int>* sub){
        if(!orig && !sub) return true;
        else if(!orig || !sub || (orig->val!=sub->val))
            return false;
        
        bool left = compare(orig->left, sub->left);
        bool right = compare(orig->right, sub->right);
        return left && right;
    }
    // P222M TODO:
    int countNodes(TreeNode<int>* root) {

    }
    // P110E
    int getHeight(TreeNode<int>* node){
        if(node==nullptr)   return 0;
        int left = getHeight(node->left);
        if (left==-1)   return -1;
        int right = getHeight(node->right);
        if(right==-1)   return -1;
        return abs(left - right)>1 ? -1 : 1 + max(left, right);
    }
    bool isBalanced(TreeNode<int>* root) {
        return getHeight(root) == -1 ? false: true;
    }

    // P257E
    vector<string> binaryTreePaths1(TreeNode<int>* root) {
        vector<string> res;
        vector<int> path;
        if(root) traversal1(root, path, res);
        return res;
    }
    void traversal1(TreeNode<int>* cur, vector<int>& path, vector<string>& res){
        path.push_back(cur->val);
        if(!cur->left && !cur->right){
            string sPath;
            for(int i=0; i<path.size(); i++){
                sPath += to_string(path[i]);
                if(i<path.size()-1) sPath += "->";
            }
            res.push_back(sPath);
            return;
        }
        if(cur->left){
            traversal1(cur->left, path, res);
            path.pop_back();
        }
        if(cur->right){
            traversal1(cur->right, path, res);
            path.pop_back();
        }
    }
    // optimized
    vector<string> binaryTreePaths(TreeNode<int>* root) {
        vector<string> res;
        string path;
        if(root) traversal(root, path, res);
        return res;
    }
    void traversal(TreeNode<int>* cur, string path, vector<string>& res){
        path += to_string(cur->val);
        if(!cur->left && !cur->right){
            res.push_back(path);
            return;
        }
        if(cur->left){
            traversal(cur->left, path + "->", res);
        }
        if(cur->right){
            traversal(cur->right, path + "->", res);
        }
    }

    //P404E
    int sumOfLeftLeaves(TreeNode<int>* root) {
        int sum=0;
        if(root) leftLeaves(root, sum, 0);
        return sum;
    }
    void leftLeaves(TreeNode<int>* cur, int& sum, bool flag){
        if(flag && !cur->left && !cur->right){
            sum += cur->val;
            return;
        }
        if(cur->left) leftLeaves(cur->left, sum, 1);
        if(cur->right) leftLeaves(cur->right, sum, 0);
    }

    // P513M
    int findBottomLeftValue(TreeNode<int>* root) {
        queue<TreeNode<int>*> que;
        if(root) que.push(root);
        int value;
        while(!que.empty()){
            int size = que.size();
            value = que.front()->val;
            for(int i=0; i<size; i++){
                TreeNode<int>* node = que.front();
                que.pop();
                if(node->left) que.push(node->left);
                if(node->right) que.push(node->right);
            }
        }
        return value;
    }

    // P112E
    bool hasPathSum(TreeNode<int>* root, int targetSum) {
        int sum=0;
        if(root) 
            return hasPath(root, sum, targetSum);
    }
    bool hasPath(TreeNode<int>* cur, int& sum, int target){
        sum += cur->val;
        if(!cur->left && !cur->right){
            if(sum == target)
                return true;
            else
                return false;
        }
        if(cur->left){
            bool left = hasPath(cur->left, sum, target);
            if(!left)
                sum -= cur->left->val;
            else
                return true;
        }
        if(cur->right){
            bool right = hasPath(cur->right, sum, target);
            if(!right)
                sum -= cur->right->val;
            else
                return true;
        }
    }

    // P113M
    vector<vector<int>> pathSum(TreeNode<int>* root, int targetSum) {
        vector<vector<int>> res;
        vector<int> path;
        if (root)
            getPath(root, targetSum, path, res);
        return res;
    }
    void getPath(TreeNode<int>* cur, int target, vector<int>& path, vector<vector<int>>& res){
        path.push_back(cur->val);
        if(!cur->left && !cur->right){
            int sum=0;
            for(auto i:path)
                sum += i;
            if(sum==target)
                res.push_back(path);
            return;
        }
        if(cur->left){
            getPath(cur->left, target, path, res);
            path.pop_back();
        }
        if(cur->right){
            getPath(cur->right, target, path, res);
            path.pop_back();
        }
    }


    
};

class ConstructionSolution{
public:
    // Problem 226: invertTree
    TreeNode<int>* invertTreeI(TreeNode<int>* root) {
        stack<TreeNode<int>*> st;
        if(root) st.push(root);
        while(!st.empty()){
            TreeNode<int>* node = st.top();
            st.pop();
            std::swap(node->left, node->right);//TODO:(note) also change the original
            if(node->right) st.push(node->right);
            if(node->left) st.push(node->left);
        }
        return root;
    }
    TreeNode<int>* invertTreeR(TreeNode<int>* root) {
        if(root == nullptr) return nullptr;
        std::swap(root->left, root->right);
        TreeNode<int>* left = invertTreeR(root->left);
        TreeNode<int>* right = invertTreeR(root->right);
        return root;
    }
    TreeNode<int>* invertTreeL(TreeNode<int>* root){
        queue<TreeNode<int>*> q;
        if(root!=nullptr) q.push(root);
        while(!q.empty()){
            int size = q.size();
            for(int i=0; i<size; i++){
                TreeNode<int>* node = q.front();
                q.pop();
                std::swap(node->left, node->right);
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
        }
        return root;
    }
        
    // P106M
    TreeNode<int>* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int idx=0;
        for(auto node:inorder)
            idx_map[node] = idx++;
        return buildHelper(0, inorder.size()-1, inorder, postorder);
    }
    TreeNode<int>* buildHelper(int in_left, int in_right, vector<int>& inorder, vector<int>& postorder){
        if(in_left>in_right)
            return nullptr;
        
        int rootVal_idx = idx_map[postorder.back()];
        postorder.pop_back();
        TreeNode<int>* rootNode = new TreeNode<int>(inorder[rootVal_idx]);
        
        rootNode->right = buildHelper(rootVal_idx+1, in_right, inorder, postorder);//TODO: note right tree first, for postorder.back()
        rootNode->left = buildHelper(in_left, rootVal_idx-1, inorder, postorder);

        return rootNode;
    }

    // P105M
    TreeNode<int>* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int idx=0;
        for(auto num:inorder)
            idx_map[num] = idx++;
        return buildHelper(0, inorder.size()-1, preorder, inorder);
    }
    TreeNode<int>* buildHelper(int in_left, int in_right, vector<int>& preorder, vector<int>& inorder){
        if(in_left>in_right)
            return nullptr;
        
        int rootVal_idx = idx_map[preorder.front()];
        preorder.erase(preorder.begin()); //not duplicate
        TreeNode<int>* rootNode = new TreeNode<int>(inorder[rootVal_idx]);
        
        rootNode->left = buildHelper(in_left, rootVal_idx-1, preorder, inorder);
         rootNode->right = buildHelper(rootVal_idx+1, in_right, preorder, inorder);

        return rootNode;
    }

    // P654M
    TreeNode<int>* constructMaximumBinaryTree1(vector<int>& nums) {
        if(nums.empty())
            return nullptr;
        
        auto max_iter = std::max_element(nums.begin(), nums.end());
        int max_idx = std::distance(nums.begin(), max_iter);

        TreeNode<int>* rootNode = new TreeNode<int>(nums[max_idx]);
        
        vector<int> num_left, num_right;
        for(int i=0; i<nums.size(); i++){
            if(i<max_idx)
                num_left.push_back(nums[i]);
            else if (i>max_idx)
                num_right.push_back(nums[i]);
        }
        
        rootNode->left = constructMaximumBinaryTree(num_left);
        rootNode->right = constructMaximumBinaryTree(num_right);

        return rootNode;
    }

    TreeNode<int>* constructMaximumBinaryTree(vector<int>& nums) {
        return construct(nums, 0, nums.size()-1);
    }
    TreeNode<int>* construct(vector<int>& nums, int left, int right) {
        if(left>right)
            return nullptr;
        
        int max_val=std::numeric_limits<int>::min();
        int max_idx=0;
        for(int i=left; i<right+1; i++)
            if(nums[i]>max_val){
                max_idx = i;
                max_val = nums[i];
            }
        
        TreeNode<int>* rootNode = new TreeNode<int>(nums[max_idx]);
        
        rootNode->left = construct(nums, left, max_idx-1);
        rootNode->right = construct(nums, max_idx+1, right);

        return rootNode;
    }

    // P617E
    TreeNode<int>* mergeTrees(TreeNode<int>* root1, TreeNode<int>* root2) {
        if(root1 && root2)
            root1->val = root1->val + root2->val;
        else if(!root1 && root2)
            return root2;
        else if(root1 && !root2)
            return root1;
        else if(!root1 && !root2)
            return nullptr;
        
        root1->left = mergeTrees(root1->left, root2->left);
        root1->right = mergeTrees(root1->right, root2->right);

        return root1;
    }

private:
    unordered_map<int,int> idx_map;
};

class BSTsolution{
private:
    TreeNode<int>* pre = nullptr;
public:
    // p700E
    TreeNode<int>* searchBST(TreeNode<int>* root, int val) {
        if(root==nullptr || root->val==val)
            return root;
        if(root->val > val)
            return searchBST(root->left, val);
        if(root->val < val)
            return searchBST(root->right, val);
        return nullptr;
    }
    TreeNode<int>* searchBST1(TreeNode<int>* root, int val) {
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
    bool isValidBST(TreeNode<int>* root) {
        if (root) 
            return traversalBST(root);     
        return true;
    }
    bool traversalBST(TreeNode<int>* cur){
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
    bool isValidBST(TreeNode<int>* root) {
        stack<TreeNode<int>*> st;
        if(!root) return true;
        TreeNode<int>* cur = root;
        TreeNode<int>* pre = nullptr;
        while(cur!=nullptr || !st.empty()){
            if(cur!=nullptr){
                st.push(cur);
                cur = cur->left;
            } else {
                TreeNode<int>* node = st.top();
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
    int getMinimumDifference(TreeNode<int>* root) {
        stack<TreeNode<int>*> st;
        if(!root) return 0;
        TreeNode<int>* cur = root;
        TreeNode<int>* pre = nullptr;
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
};

int main() {
    // build binary tree
    vector<int> inorder = {9,3,15,20,7};
    vector<int> postorder = {9,15,7,20,3};
    
    ConstructionSolution sol;
    TreeNode<int>* root = sol.buildTree(inorder, postorder);
    
    TraversalSolution tsol;
    vector<int> result = tsol.inorderTraversalI(root);
    for(auto num:result)
        cout<< num << " ";
    
    return 0;
}