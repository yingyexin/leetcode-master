#include <iostream>
#include <algorithm> //sort
#include <vector>
using namespace std;

class BasicSolution {
public:
    // 509E
    int fib(int n) {
        if(n<=1) return n;
        int dp[n+1];
        dp[0]=0;
        dp[1]=1;
        for(int i=2; i<n; i++)
            dp[i] = dp[i-1] + dp[i-2];
        return dp[n];
    }

    // 70E
    int climbStairs(int n) {
        if(n<=2) return n;
        vector<int> dp(n+1,0);
        dp[1] = 1;
        dp[2] = 2;
        for(int i=3; i<=n; i++)
            dp[i] = dp[i-1] + dp[i-2];
        return dp[n];
    }

    // 746E
    int minCostClimbingStairs(vector<int>& cost) {
        vector<int> dp(cost.size(),0);
        int n = cost.size()-1;
        dp[0] = cost[0]; 
        if(cost.size()==1) return dp[0];
        dp[1] = cost[1];
        for(int i=2; i<cost.size(); i++){
            dp[i] = min(dp[i-1]+cost[i], dp[i-2]+cost[i]);
        }
        return min(dp[n], dp[n-1]);
    }

    // 62M
    int uniquePaths(int m, int n) {
        if(m<2 || n<2) return 1;
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
        dp[m-2][n-1]=1;
        dp[m-1][n-2]=1;
        for(int i=m-1; i>=0; i--)
            for(int j=n-1; j>=0; j--){
                if(dp[i][j]!=0)
                    continue;
                dp[i][j] = dp[i+1][j] + dp[i][j+1];
            }
        return dp[0][0];
    }

    // 63M
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));
        if (obstacleGrid[m-1][n-1] == 1 || obstacleGrid[0][0] == 1) //如果在起点或终点出现了障碍，直接返回0
            return 0;
        for(int i=0; i<m && obstacleGrid[i][0]==0; i++) dp[i][0]=1;
        for(int j=0; j<n && obstacleGrid[0][j]==0; j++) dp[0][j]=1;
        
        for(int i=1; i<m; i++)
            for(int j=1; j<n; j++){
                if(obstacleGrid[i][j]==1)
                    continue;
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        return dp[m-1][n-1];
    }

    //343M TODO:
    int integerBreak(int n) {

    }

    //96M
    int numTrees(int n) {
        vector<int> dp(n+1);
        dp[0] = 1;
        for(int i=1; i<=n; i++)
            for(int j=0; j<i; j++){
                dp[i] += dp[j]*dp[i-j-1];
            }
        return dp[n];
    }
};

class BagSolution {
public:
    // 416M
    bool canPartition(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int left=0, right=nums.size()-1;
        int suml=0, sumr=0;
        while(left<right){
            suml += nums[left];
            sumr += nums[right];
            if(suml<sumr)
                left++;
            else if(suml>sumr)
                right++;
            else if(suml==sumr && left!=right-1){
                left++;
                right++;
            } else
                return true;
        }
        return false;
    }
    bool canPartitionb(vector<int>& nums){
        int sum=0;
        for(int num:nums)
            sum += num;
        if(sum%2==1) return false;
        vector<int> dp(sum/2+1, 0);
        //sort(nums.begin(), nums.end()); //i order no matters
        dp[0]=0;
        for(int i=0; i<nums.size(); i++)
            for(int j=sum/2; j>=nums[i]; j--)//j-weight[i]>=0
                dp[j] = max(dp[j], dp[j-nums[i]]+nums[i]);
        if(dp[sum/2]==sum/2)
            return true;
        else return false;
    }

    //698M TODO: backtracking [2222345]
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int sum=0;
        for(int num:nums)
            sum += num;
        if(sum%k==1) return false;
        vector<int> dp(sum/k +1, 0);
        dp[0] = 0;
        for(int i=0; i<nums.size(); i++)
            for(int j=sum/k; j>=nums[i]; j--)
                dp[j] = max(dp[j], dp[j-nums[i]]+nums[i]);
        if(dp[sum/k]==sum/k)
            return true;
        else return false;
    }

    //1049M
    int lastStoneWeightII(vector<int>& stones) {
        int sum=0;
        for(int stone:stones)
            sum += stone;
        vector<int> dp(sum, 0);
        dp[0]=0;
        for(int i=0; i<stones.size(); i++)
            for(int j=sum/2; j>=stones[i]; j--)//j-weight[i]>=0
                dp[j] = max(dp[j], dp[j-stones[i]]+stones[i]);
        return sum-2*dp[sum/2];//(sum-dp[sum/2]) - dp[sum/2]
    }

    //494M
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum=0;
        for(auto num:nums)
            sum += num;
        if (sum<target ||-sum>target) return 0;
        if ((sum+target)%2==1) return 0;

        vector<vector<int>> dp(nums.size(), vector<int>(2*sum+1,0));
        if(nums[0]==0)
            dp[0][nums[0]+sum]=2;//+0,-0
        else{
            dp[0][nums[0]+sum]=1;
            dp[0][-nums[0]+sum]=1;
        }
        for(int i=1; i<nums.size(); i++)
            for(int j=0; j<2*sum+1; j++){
                int left = j-nums[i] < 0 ? 0 : dp[i-1][j-nums[i]];
                int right = j+nums[i] > 2*sum ? 0 : dp[i-1][j+nums[i]];
                dp[i][j] = left + right;
            }
        
        return dp[nums.size()-1][target+sum]; 
    }

    //474M
    int findMaxForm(vector<string>& strs, int m, int n) {
        vector<vector<int>> dp(m+1, vector<int>(n+1,0));
        for(auto str:strs){
            int zeroN=0, oneN=0;
            for(char ch:str){
                if(ch=='1') oneN++;
                else zeroN++;
            }
            for(int i=m; i>=zeroN; i--)
                for(int j=n; j>=oneN; j--)
                    dp[i][j] = max(dp[i][j], dp[i-zeroN][j-oneN]+1);
        }
        return dp[m][n];
    }

    //879D TODO:
    int profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit) {

    }
};

class ComBagSolution{
public:
    //518M
    int change(int amount, vector<int>& coins) {
        vector<int> dp(amount+1, 0);
        dp[0]=1;
        // for(int j=1; j<=amount; j++)
        //     if(j%coins[0]==0) dp[j]=1;
        for(int i=0; i<coins.size(); i++)
            for(int j=coins[i]; j<=amount; j++)
                dp[j] += dp[j-coins[i]];
                    
        return dp[amount];
    }

    // 377M
    int combinationSum4(vector<int>& nums, int target) {
        vector<int> dp(target+1, 0);
        int min = numeric_limits<int>::max();
        for(auto num:nums)
            min = min>num? num : min;
        if(min>target) return 0;
        dp[0]=1;
        for(int j=0; j<=target; j++)
            for(int i=0; i<nums.size(); i++)
                if(j-nums[i]>=0  && dp[j]<numeric_limits<int>::max()-dp[j-nums[i]]) 
                    dp[j] += dp[j-nums[i]];
        return dp[target];
    }
};


int main(){

    return 0;
}