#include <iostream>
#include <vector>
#include <memory>
#include <limits>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <array>


using namespace std;

class Solution {
public:
    // Problem 242E
    bool isAnagram(string s, string t) {
        int record[26] = {0};//TODO: note initialization
        for(int i=0; i<s.size(); i++)
            record[s[i]-'a']++;
        for(int i=0; i<t.size(); i++)
            record[t[i]-'a']--;
        for(int i=0; i<26; i++)
            if (record[i]!=0)
                return false;
        return true;
    }
    bool isAnagram2(string s, string t) {
        if (s.size() != t.size()) return false;
        int record[26] = {0};//TODO: note initialization
        for(auto& ch:s)
            record[ch-'a']++;
        for(auto& ch:t){
            record[ch-'a']--;
            if (record[ch-'a']<0)
                return false;
        }
        return true;
    }

    // Problem 49M TODO:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<int>> record(strs.size(), vector<int>(26,0));
        vector<vector<string>> res;
        for(int i=0; i<strs.size(); i++){
            for(auto& ch:strs[i])
                record[i][ch-'a']++;
            


        }
        return res;

    }
    // 438M TODO:
    vector<int> findAnagrams(string s, string p) {

    }

    // Problem 383E
    bool canConstruct(string ransomNote, string magazine) {
        if (magazine.size() < ransomNote.size()) return false;
        int record[26] = {0};
        for(auto& ch:magazine)
            record[ch-'a']++;
        for(auto& ch:ransomNote){
            record[ch-'a']--;
            if (record[ch-'a']<0)
                return false;
        }
        return true;
    }

    // Problem 349E
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> num_set(nums1.begin(), nums1.end()), res_set;// TODO: note simple way to map
        for(auto& n:nums2)
            if(num_set.count(n))
                res_set.insert(n);
        return vector<int>(res_set.begin(), res_set.end());
    }
    // Problem 350E
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        multiset<int> num_set(nums1.begin(), nums1.end());
        vector<int> res;
        for(int num:nums2){
            auto it = num_set.find(num);
            if(it!=num_set.end()){
                num_set.erase(it);
                res.push_back(num);
            }
        }
        return res;
    }

    // 202E
    bool isHappy(int n) {
        unordered_set<int> sum_set;
        int sum = 0, num = n;
        while(1){
            while(num>0){
                sum += (num%10)*(num%10);
                num /= 10;
            }
            if(sum==1)
                return true;
            else if(sum_set.count(sum))
                return false;
            else
                sum_set.insert(sum);
            
            num = sum;
            sum = 0; //TODO: note every iteration sum is new;
        }    
    }

    // Problem 1E
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> num_map;
        for(int i=0; i<nums.size(); i++){
            auto it = num_map.find(target-nums[i]);
            if(it!=num_map.end())
                return {it->second, i};// TODO: it->first, it->second
            else
                num_map.insert(make_pair(nums[i],i));
        }
        return {};
    }

    // 454M
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
        unordered_map<int,int> sumAB;
        int times=0;
        for(int i=0; i<nums1.size(); i++)
            for(int j=0; j<nums2.size(); j++){
                int sum = nums1[i] + nums2[j];
                if(sumAB.count(sum))
                    sumAB[sum]++;
                else
                    sumAB.insert(make_pair(sum,1));
            }
        for(int i=0; i<nums3.size(); i++)
            for(int j=0; j<nums4.size(); j++){
                int sum = nums3[i] + nums4[j];
                auto it = sumAB.find(0-sum);
                if(it!=sumAB.end()){
                    times += it->second;
                }
            }
        return times;
    }

    // 15M
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        std::sort(nums.begin(), nums.end());
        for(int i=0; i<nums.size(); i++){
            if (i>0 && nums[i] == nums[i - 1]) 
                continue;
            int left = i+1, right = nums.size()-1;
            while(left<right){
                int sum = nums[i]+nums[left]+nums[right];
                if(sum>0){
                    right--;
                    while (left < right && nums[right] == nums[right + 1]) right--;
                }
                else if(sum<0){
                    left++;
                    while (left < right && nums[left] == nums[left - 1]) left++;
                }
                else{
                    res.push_back(vector<int>{nums[i], nums[left], nums[right]});
                    while (left < right && nums[right] == nums[right - 1]) right--;
                    while (left < right && nums[left] == nums[left + 1]) left++;
                    right--;
                    left++;
                }
            }
        }   
        return res;    
    }

    // 18M TODO:note too big numbers
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> res;
        std::sort(nums.begin(), nums.end());
        for(int i=0; i<nums.size(); i++){
            if (nums[i] > target && (nums[i] >= 0 || target >= 0))
            	break;
            if (i>0 && nums[i]==nums[i-1])
                continue;

            for(int j=i+1; j<nums.size(); j++){
                if (nums[i] + nums[j] > target && (nums[i] + nums[j] >= 0 || target >= 0))
		            break;
                if(j>i+1 && nums[j]==nums[j-1])
                    continue;
                
                int left = j+1, right = nums.size()-1;
                while(left<right){
                    if(nums[i]+nums[j]>target-nums[left]-nums[right]){
                        right--;
                        while(left<right && nums[right]==nums[right+1]) right--;
                    } else if(nums[i]+nums[j]<target-nums[left]-nums[right]){
                        left++;
                        while(left<right && nums[left]==nums[left-1]) left++;
                    } else {
                        res.push_back(vector<int>{nums[i],nums[j],nums[left],nums[right]});
                        while(left<right && nums[right]==nums[right-1]) right--;
                        while(left<right && nums[left]==nums[left+1]) left++;
                        right--;
                        left++;
                    }
                }
            }
        }
        return res; 
    }
    // Problem 128M O(n)
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> nset(nums.begin(), nums.end());
        int longest=0, cur=0;
        for(int i=0; i<nums.size(); i++){
            if(!nset.count(nums[i]-1)){
                int n = nums[i];
                cur = 1;
                while(nset.count(n+1)){
                    cur++;
                    n++;
                }
                longest = max(cur, longest);
            }
        }
        return longest;
    }

};


int main() {
    //std::vector<int> num = {3,3,3,1,2,1,1,2,3,3,4};
    vector<vector<int>> num1 = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};
    vector<int> num2 = {-1,0,1,2,-1,-4};
    int target;
    
    Solution sol;
    vector<vector<int>> result = sol.threeSum(num2);
    for(int i=0; i<result.size(); i++)
        cout << result[i][0] << "," << result[i][1] << "," << result[i][2] << endl;
   
    return 0;
}
