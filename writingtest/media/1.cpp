#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


int findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    // write code here
    if(nums1.size()==0 && nums2.size()==0) return 0;
    for(int i=0; i<nums2.size(); i++)
        nums1.push_back(nums2[i]);
    
    sort(nums1.begin(), nums1.end());
    int s = nums1.size();
    if(s%2==1)
        return nums1[s/2]*2;
    else 
        return nums1[s/2] + nums1[s/2-1];
}