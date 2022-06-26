#include <iostream>
#include <vector>
#include <memory>
#include <stack>
#include <queue>
#include <limits>

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
    Node(T x, TreeNode* L, TreeNode* R): val(x), left(L), right(R), next(nullptr){}
};

template <typename T>
class Tree
{
public:
    TreeNode<T>* createTree(std::vector<string> vec, int index){
            
        if (vec[index] != "null"){

            TreeNode<T>* node = new TreeNode<T>();
            
            node->val = T(stoi(vec[index]));
            if (index+1 < vec.size())
                node->left = createTree(vec, index+1);
            if (index+2 < vec.size())
                node->right = createTree(vec, index+2);
            
        }
        return node;
    }
    TreeNode<T>* getRoot(){return root;}
    void setRoot(TreeNode<T>* node){
        root->val = node->val;
        root->left = node->left;
        root->right = node->right;
    }

private:
    TreeNode<T>* root;
};

class TraversalSolution{
public:
    // Problem 144: preorderTraversal
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

    // Problem 145: postorderTraversal
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

        res[depth].emplace_back(node->val);
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
            //vector<int> level; //TODO:(note) use if
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

    // TODO: Problem 116,117: find next node
    Node<int>* connect(Node<int>* root) {
        queue<Node<int>*> q;
        if(root) q.push(root);
        while(!q.empty()){
            int size = q.size();
            Node<int>* nodePre;
            Node<int>* node;
            
            for(int i=0; i<size; i++){
                nodePre = q.front();
                q.pop();
                if (size==1) nodePre->next = nullptr;
                else{
                    
                    if(node->left) q.push(node->left);
                    if(node->right) q.push(node->right);
                }
            }
            //result.push_back(max);
        }
        return cur;
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
};


int main() {
    // build binary tree
    std::vector<string> vec = {"1", "2", "null", "3"};
    Tree<int> t;
    TreeNode<int>* root = t.createTree(vec, 0);
    t.setRoot(root);

    TraversalSolution sol;
    vector<int> result = sol.preorderTraversalR(t.getRoot());
    
    for (int i=0; i<result.size(); i++) cout << result[i];
    
    return 0;
}