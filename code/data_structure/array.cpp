#include <iostream>
#include <vector>
#include <memory>
#include <stack>
#include <queue>
#include <limits>
#include <set>
#include <chrono>
#include <ctime>

using namespace std;

class BinarySearch {
public:
    // Problem 704E: binary search in ordered array
    int search1(vector<int>& nums, int target) {
        int left = 0, right = nums.size()-1;
        int middle;
        while(left <= right){
            int middle = left + ((right - left) / 2);
            if (nums[middle] < target)  {
                left = middle+1;
            }
            else if (nums[middle] > target)  {
                right = middle-1;
            }
            else return middle;
        }
        return -1;
    }
    int search2(vector<int>& nums, int target) {
        int left = 0, right = nums.size();
        int middle;
        while(left < right){
            int middle = left + ((right - left) / 2);
            if (nums[middle] < target)  {
                left = middle+1;
            }
            else if (nums[middle] > target)  {
                right = middle;
            }
            else return middle;
        }
        return -1;
    }

    // Problem 35E
    int searchInsert(vector<int>& nums, int target) {
        int left = 0, right = nums.size()-1;
        int middle;
        while(left <= right){
            middle = left + (right-left)/2;
            if (nums[middle] > target)  right = middle-1;
            else if (nums[middle] < target) left = middle+1;
            else return middle;
        }
        // 分别处理如下四种情况
        // 目标值在数组所有元素之前  [0, -1]
        // 目标值等于数组中某一个元素  return middle;
        // 目标值插入数组中的位置 [left, right]，return  right + 1
        // 目标值在数组所有元素之后的情况 [left, right]， 因为是右闭区间，所以 return right + 1
        return right+1;// return left
    }

    // Problem 34M: search and range (duplicate array)
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> range;
        int leftBorder = searchLeftBorder(nums, target);
        int rightBorder = searchRightBorder(nums, target);
        if (leftBorder!=-1 && nums[leftBorder] == target) //TODO:(note) empty vector
            range.push_back(leftBorder);
        else    
            range.push_back(-1);
        if(rightBorder!=-3 && nums[rightBorder] == target)   
            range.push_back(rightBorder);
        else    
            range.push_back(-1);
        return range;
        /*if (leftBorder==-1 || rightBorder==-3)  return {-1,-1};
        if (rightBorder - leftBorder >= 0)  return {leftBorder, rightBorder};
        else return {-1,-1};*/
    }
    int searchRightBorder(vector<int>& nums, int target){
        int left = 0, right = nums.size()-1;
        int middle, Rborder = -2;
        while(left<=right){
            middle = left + (right-left)/2;
            if (nums[middle] > target)
                right = middle-1;
            else {
                left = middle+1;
                Rborder = left;
            }      
        }
        return Rborder-1;
    }
    int searchLeftBorder(vector<int>& nums, int target){
        int left = 0, right = nums.size()-1;
        int middle, Lborder = -2;
        while(left<=right){
            middle = left + (right-left)/2;
            if (nums[middle] >= target) {
                right = middle-1;
                Lborder = right;
            }
            else left = middle+1;      
        }
        return Lborder+1;
    }

    // Problem 69E
    int mySqrt(int x) {
        int left = 0, right = x;
        int middle;
        while(left <= right){
            middle = left + (right-left)/2;
            if ((long long) middle*middle > x)  right = middle-1;
            else if (middle*middle < x) left = middle+1;
            else return middle;
        }
        return right;
    }
    
    // Problem 367E
    bool isPerfectSquare(int num) {
        int left = 0, right = num;
        int middle;
        while(left <= right){
            middle = left + (right-left)/2;
            if ((long long) middle*middle > num)  right = middle-1;
            else if (middle*middle < num) left = middle+1;
            else return true;
        }
        return false;
    }
    
    // Problem 74M or convert to one-dim
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(), n = matrix[0].size();
        vector<int> left{0,0};
        vector<int> right{m-1, n-1};
        while(left[0]*n+left[1] <= right[0]*n+right[1]){
            vector<int> middle(2,0);
            int inter = left[0]*n+left[1] + ((right[0]-left[0])*n+right[1]-left[1])/2;
            middle[0] = inter/n;
            middle[1] = inter%n;
            // cout<<middle[0]<<" "<<middle[1]<< endl;
            if(matrix[middle[0]][middle[1]]<target){
                left[0] = middle[1]==n-1 ? middle[0]+1 : middle[0];
                left[1] = middle[1]==n-1 ? 0 : middle[1]+1;
            }
            else if(matrix[middle[0]][middle[1]]>target){
                right[0] = middle[1]==0 ? middle[0]-1 : middle[0];
                right[1] = middle[1]==0 ? n-1 : middle[1]-1;
            }
            else return true;
        }
        return false;
    }
    
    //Problem 33M rotated ordered array
    int search(vector<int>& nums, int target) {
        int n = (int)nums.size();
        if (!n) {
            return -1;
        }
        if (n == 1) {
            return nums[0] == target ? 0 : -1;
        }
        int l = 0, r = n - 1;
        while (l <= r) {
            int mid = (l+r)/2;
            if(nums[mid]==target) return mid;
            if(nums[l]<=nums[mid]){
                if(nums[l]<=target && target<=nums[mid]) r=mid;
                else l=mid+1;
            }else{
                if(nums[mid]<=target && target<=nums[r]) l=mid;
                else r=mid-1;
            }
        }
        return -1;
    }
    
    // Problem 81M rotated ordered array with duplicate nums
    bool search(vector<int>& nums, int target) {
        int n=nums.size();
        int l = 0, r = n - 1;
        while (l <= r) {
            int mid = (l+r)/2;
            if(nums[mid]==target) return true;
            if(nums[l]==nums[mid] && nums[mid]==nums[r]){
                l++; r--; //hard to decide which side is ordered, delete two
            }else if(nums[l]<=nums[mid]){
                if(nums[l]<=target && target<=nums[mid]) r=mid;
                else l=mid+1;
            }else{
                if(nums[mid]<=target && target<=nums[r]) l=mid;
                else r=mid-1;
            }
        }
        return false;
    }
    // Problem 153M min of rotated ordered array
    int findMin(vector<int>& nums) {
        int n = (int)nums.size();
        if (n == 1)
            return nums[0];
        
        int l = 0, r = n - 1;
        while (l < r) {
            int mid = (l+r)/2;
            if(nums[mid]<nums[r])
                r=mid;
            else
                l=mid+1;
        }
        return nums[l];
    }
    
    // Problem 4D 
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n=nums2.size();
        if((m+n)%2==1)
            return getMedium(nums1, nums2, int((m+n)/2)+1);
        else return (getMedium(nums1, nums2, int((m+n)/2)) + getMedium(nums1, nums2, int((m+n)/2)+1))/2.0;
    }
    int getMedium(vector<int> nums1, vector<int> nums2, int k){
        if(k==1){
            if(nums1.size()==0) return nums2[0];
            else if(nums2.size()==0) return nums1[0];
            return nums1[0]<nums2[0] ? nums1[0] : nums2[0];
        }
        int m=min<int>(int(k/2), nums1.size()), n=min<int>(int(k/2), nums2.size());
        // if(n==0){
        //     nums1.erase(nums1.begin(), nums1.begin()+m);
        //     return getMedium(nums1, nums2, k-m);
        // } else if(m==0){
        //     nums2.erase(nums2.begin(), nums2.begin()+n);
        //     return getMedium(nums1, nums2, k-n);
        // }
        if(n==0) return nums1[k-1];
        else if (m==0) return nums2[k-1];

        if(nums1[m-1] < nums2[n-1]){
            nums1.erase(nums1.begin(), nums1.begin()+m);
            return getMedium(nums1, nums2, k-m);
        } else {
            nums2.erase(nums2.begin(), nums2.begin()+n);
            return getMedium(nums1, nums2, k-n);
        }
    }
};

Class RemoveElement_doublePointer{
public:
    // Problem 27E
    int removeElement(vector<int>& nums, int val) {
        /*int slowIndex = 0;
        for (int fastIndex=0; fastIndex < nums.size(); fastIndex++){
            if (val != nums[fastIndex])
                nums[slowIndex++] = nums[fastIndex];
        }
        return slowIndex;*/
        int left = 0, right = nums.size();
        while(left<right){
            if (nums[left]==val){
                nums[left] = nums[right-1];
                right--;
            }
            else    
                left++;
        }
        return left;
    }

    // Problem 26E
    int removeDuplicates(vector<int>& nums) {
        if (nums.size() == 0) //TODO: note empty vector
            return 0;
        int slow = 0;
        for (int fast=1; fast<nums.size(); ){
            if (nums[fast] == nums[slow]){
                fast++;
            } else
                nums[++slow] = nums[fast];
        }
        return slow+1;
    }

    // Problem 283E
    void moveZeroes(vector<int>& nums) {
        /*int slow=0;
        for (int fast=0; fast<nums.size(); fast++){
            if(fast==slow && nums[fast]!=0)
                slow++;
            else if(fast!=slow && nums[fast]!=0){
                nums[slow++] = nums[fast];
                nums[fast] = 0;
            }
        }*/
        int n = nums.size(), left = 0, right = 0;
        while (right < n) {
            if (nums[right]) {
                swap(nums[left], nums[right]);
                left++;
            }
            right++;
        }
    }

    // Problem 844E
    bool backspaceCompare(string s, string t) {
        int left_s = 0, left_t=0, right_s = 0, right_t=0;
        while(right_s<s.size()){
            if(s[right_s]!='#'){
                s[left_s] = s[right_s];
                left_s++;
            }else{
                left_s--;
                if(left_s<0)    left_s=0;
            }
            right_s++;
        }
        while(right_t<t.size()){
            if(t[right_t]!='#'){
                t[left_t] = t[right_t];
                left_t++;
            }else{
                left_t--;
                if(left_t<0)    left_t=0;
            }
            right_t++;
        }
        if (s.substr(0, left_s)==t.substr(0, left_t))   return true;
        else return false;
    }

    // Problem 977E
    vector<int> sortedSquares(vector<int>& nums) {
        int left=0, right=nums.size()-1;
        vector<int> result(nums.size()); // TODO: note:initialize a vector size
        int k=right;
        while(left <= right){
            if((long long)nums[left]*nums[left] > (long long)nums[right]*nums[right]){
                result[k--]=nums[left]*nums[left];
                left++;
            } else {
                result[k--]=nums[right]*nums[right];
                right--;
            }
        }
        return result;
    }
};

Class SlidingWindow_min{
public:  
    // Problem 209M
    int minSubArrayLen(int target, vector<int>& nums) {
        int left = 0;
        int res=nums.size()+1, sublen=0;
        int sum=0;
        for(int right=0; right<nums.size(); right++){
            sum += nums[right];
            
            while(sum>=target){
                sublen = right - left + 1;
                res = res < sublen ? res : sublen;
                sum -= nums[left];
                left++;
            }
        }
        res = res > nums.size() ? 0 : res;
        return res;
    }

    // Problem 904M max sliding window
    int totalFruit(vector<int>& fruits) {
        int right=0, subsize=0, res=0;
        set<int> basket;
        int left=0;
        while(right < fruits.size()){
            subsize++;
            basket.insert(fruits[right]);
            right++;
            cout << basket.size() << " ";

            if(basket.size()>2){
                subsize--;
                basket.erase(fruits[left]);
                ++left;    
            }
            res = res<subsize ? subsize : res;
        }
        return res;
    }
    int totalFruit(vector<int>& fruits) {
        set<int> tree;
        map<int, int> nums;
        int j=0, i=0;
        int res=0;
        while(j<fruits.size()){
            nums[fruits[j]]++;
            tree.insert(fruits[j]);
            while(tree.size()>=3){
                nums[fruits[i]]--;
                if(nums[fruits[i]]==0)
                    tree.erase(fruits[i]);
                i++;
            }
            res = res>(j-i+1) ? res : j-i+1;
            j++;
        }
        return res;
    }
    // Problem 3M 
    int lengthOfLongestSubstring(string s) {
        int i=0, j=0, res=0;
        set<char> sset;
        while(j<s.size()){
            while(sset.count(s[j])>0){
                sset.erase(s[i]);
                i++;
            }
            sset.insert(s[j]);
            res = max(res, j-i+1);
            j++;
        }
        return res;
    }
    // Problem 1004M
    int longestOnes(vector<int>& nums, int k) {
        int i=0, j=0, res=0;
        int zero=0;
        while(j<nums.size()){
            if(nums[j]==0) zero++;
            while(zero>k){
                if(nums[i]==0) zero--;
                i++;
            }
            res = max(res, j-i+1);
            j++;
        }
        return res;
    }

    // TODO:Problem 76D
    string minWindow(string s, string t) {

    }
    
};

Class ArrayBase{
public:
    // Problem 59M
    vector<vector<int>> generateMatrix(int n) {
        int startx = 0, starty = 0, offset = 1;
        int end = 1;
        int mid = n/2;
        int i, j;
        vector<vector<int>>  res(n, vector<int>(n, 0)); //TODO: note initialize vector
        while(end <= n*n){
            i = startx;
            j = starty;

            for (j=starty; j<n-offset; j++)
                res[startx][j] = end++;
            
            for(i=startx; i<n-offset; i++)
                res[i][j] = end++;
            
            for(; j>starty; j--)
                res[i][j] = end++;
            
            for(; i>startx; i--)
                res[i][j] = end++;
            
            startx++;
            starty++;
            offset++;

            if(n%2==1 && end == n*n)
                res[mid][mid] = end++;
        }
        return res;
    }
    
    vector<vector<int>> generateMatrix2(int n) {
        vector<vector<int>> matrix(n, vector<int>(n,0));
        int start=1;
        int left=0, right=n-1, top=0, bottom=n-1;
        while(left<=right && top<=bottom){
            for(int j=left; j<=right; j++)
                matrix[top][j] = start++;
            
            for(int i=top+1; i<=bottom; i++)
                matrix[i][right] = start++;
            
            if (left < right && top < bottom){
                for(int j=right-1; j>left; j--)
                    matrix[bottom][j] = start++;
                
                for(int i=bottom; i>top; i--)
                    matrix[i][left] = start++;
            }
            left++;
            right--;
            top++;
            bottom--;
        }
        return matrix;
    
    }
    // Problem 54M / O29E
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
       
        if (matrix.size() == 0 || matrix[0].size() == 0) {
            return {};
        }
        int m = matrix.size(); // =3, 
        int n = matrix[0].size(); // =4
        vector<int> order;
        int left = 0, right = n - 1, top = 0, bottom = m - 1;
        while (left <= right && top <= bottom) {
            for (int j = left; j < right; j++) {
                order.push_back(matrix[top][j]);
            }
            for (int i = top; i < bottom; i++) {
                order.push_back(matrix[i][right]);
            }
            if (top < bottom && left < right){
                for (int j = right; j > left; j--) {
                    order.push_back(matrix[bottom][j]);
                }
                for (int i = bottom; i > top; i--) {
                    order.push_back(matrix[i][left]);
                }
            }
            else if (top == bottom ){
                order.push_back(matrix[top][right]);
            }
            else if (right == left)
                order.push_back(matrix[bottom][right]);
            
            left++;
            right--;
            top++;
            bottom--;

        }
        return order;
    }

    vector<int> spiralOrder2(vector<vector<int>>& matrix) {
        if (matrix.size() == 0 || matrix[0].size() == 0) {
            return {};
        }

        int startx = 0, starty = 0, offset = 0;
        int m = matrix.size(), n = matrix[0].size();
        int i, j;
        int count = 1;
        vector<int> res;
        while (count <= m*n){

            for(j=starty; j<n-offset; j++){
                if (res.size()>=m*n) break;
                res.emplace_back(matrix[startx][j]);
                count++;
            }
            for(i=startx; i<m-offset; i++){
                if (res.size()>=m*n) break;
                res.emplace_back(matrix[i][j]);
                count++;
            }
            for(; j>starty; j--){
                if (res.size()>=m*n) break;
                res.emplace_back(matrix[i][j]);
                count++;
            }
            for(; i>startx; i--){
                if (res.size()>=m*n) break;
                res.emplace_back(matrix[i][j]);
                count++;
            }

            startx++;
            starty++;
            offset++;

            if(m==n && m*n%2==1 && count == m*n){
                int mid = m/2;
                res.emplace_back(matrix[mid][mid]);
            }
        }
        return res;
    }

    vector<int> spiralOrder3(vector<vector<int>>& matrix) { //TODO: gut!
        if (matrix.size() == 0 || matrix[0].size() == 0) {
            return {};
        }
        int m = matrix.size(); // =3, 
        int n = matrix[0].size(); // =4
        vector<int> order;
        int left = 0, right = n - 1, top = 0, bottom = m - 1;
        while (left <= right && top <= bottom) {
            for (int j = left; j <= right; j++) { //TODO: note get all in the first two
                order.push_back(matrix[top][j]);
            }
            for (int i = top; i <= bottom; i++) {
                order.push_back(matrix[i][right]);
            }
            if (top < bottom && left < right){
                for (int j = right; j > left; j--) {
                    order.push_back(matrix[bottom][j]);
                }
                for (int i = bottom; i > top; i--) {
                    order.push_back(matrix[i][left]);
                }
            }
            
            left++;
            right--;
            top++;
            bottom--;
        }
    }
};

int main() {
    //std::vector<int> num = {3,3,3,1,2,1,1,2,3,3,4};
    vector<vector<int>> num1 = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};
    vector<vector<int>> num2 = {{1},{2},{3}};
    int target;
    
    Solution sol;
    //int res = sol.totalFruit(num);
    //cout << endl<< res <<endl;
    auto start_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    vector<int> result1 = sol.spiralOrder(num1);
    for (int i=0; i<result1.size();i++)
        cout << " " << result1[i] ;
    cout << endl;
    auto end_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    cout << "miliseconds: " << start_time.count() - end_time.count() << endl;
    
    vector<int> result2 = sol.spiralOrder(num2);
    for (int i=0; i<result2.size();i++)
        cout << " " << result2[i] ;
    
    return 0;
}
