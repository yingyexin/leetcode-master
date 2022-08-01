#include <iostream>
#include <string.h>
#include <vector>
using namespace std;


struct TreeNode
{
public:
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(): val(int(0)), left(nullptr), right(nullptr) {}
    TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* L, TreeNode* R): val(x), left(L), right(R) {}
};

class BSTsolution{
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return constructBST(0, nums.size()-1, nums);
    };
    TreeNode* constructBST(int left, int right, vector<int>& nums){
        if(left>right)
            return nullptr;
        int mid = left + (right-left)/2;
        TreeNode* cur = new TreeNode(nums[mid]);

        cur->left = constructBST(left, mid-1, nums);
        cur->right = constructBST(mid+1, right, nums);

        return cur;
    };
};

int main(){
    int val;
    string s1;
    char c;
    cin >> s1;
    cout << "no. "<< s1;
    cin >> s1;
    cout << "no. "<< s1;
    cin >> c;
    while(cin >> val)
    {
        cout << "nums" << val;
        cin >> c;
        if(c=='\n') break;
    }
    printf("done");
    
    return 0;
}
