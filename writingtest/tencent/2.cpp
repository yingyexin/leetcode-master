#include <iostream>
#include <vector>
#include <iomanip>
#include <math.h>
using namespace std;

vector<double> matrixVec(vector<vector<double>>& A, vector<double> v){
    int n = A.size();
    vector<double> res(n, 0.0);
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            res[i] += A[i][j] * v[j];

    return res;
}

void normalize(vector<double>& v){
    double sum = 0.0;
    for(double x:v)
        sum+= x*x;
    double mag = sqrt(sum);
    for(double& x:v)
        x = x/mag;
}

double func(vector<vector<double>>& A, vector<double>& x){
    int iter = 1000; //k
    int n = A.size();
    double epsilon = 1e-6; //limits
    
    for(int k=0; k<iter; k++){
        vector<double> Ax = matrixVec(A, x);
        double lambda = 0.0;

        for(int i=0; i<n; i++)
            lambda += x[i] * Ax[i];

        normalize(x);

        vector<double> diff(n);
        for(int i=0; i<n; i++)
            diff[i] = Ax[i] -lambda * x[i];

        double error = 0.0;
        for(int i=0; i<n; i++)
            error += diff[i] * diff[i];
        
        if(sqrt(error) < epsilon)
            return lambda;
    }
}


int main(){
    int n;
    cin >> n;
    vector<vector<double>> A(n, vector<double>(n));
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++){
            cin >> A[i][j];
        }
    vector<double> v(n);
    for(int i=0; i<n; i++)
        cin >> v[i];
    
    cout << setiosflags(ios::fixed) << setprecision(2);
    cout << func(A, v) << endl;
    
}