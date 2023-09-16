#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 判断线段和直线是否相交
     * @param x1 double浮点型 线段起点x坐标
     * @param y1 double浮点型 线段起点y坐标
     * @param x2 double浮点型 线段终点x坐标
     * @param y2 double浮点型 线段终点y坐标
     * @param a double浮点型 直线参数a
     * @param b double浮点型 直线参数b
     * @param c double浮点型 直线参数c
     * @return bool布尔型
     */
    bool isLineSegmentIntersectant(double x1, double y1, double x2, double y2, double a, double b, double c) {
        // write code here
        double k = (y2 - y1) / (x2 - x1);
        if (k == -a / b) return false;
        double ans1 = a * x1 + b * y1 + c;
        double ans2 = a * x2 + b * y2 + c;

        return (ans1 * ans2 < 0);
    }
};

int main(){

    Solution sol;
    double x1, y1, x2, y2, a, b, c;
    cin >> x1 >> y1 >> x2 >> y2 >> a >> b >> c;

    cout << sol.isLineSegmentIntersectant(x1, y1, x2, y2, a, b, c) << endl;

}