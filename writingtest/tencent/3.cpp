#include <iostream>
#include <vector>
#include <iomanip>
#include <math.h>
#include <sstream>
#include <set>
#include <unordered_map>
#include <math.h>
using namespace std;

bool func(vector<vector<string>>& matrix, unordered_map<string, int>& n, vector<set<string>>& wordset, double t){
     // word in all
    unordered_map<string, int> idf; // word in all article
    int w = matrix.size() * matrix[0].size();

    for(int i=0; i<wordset.size(); i++){
        for(auto word:wordset[i]){
            idf[matrix[i][j]]++;
            w++;
        }
    }

    int d = matrix.size();
    for(auto word:wordset){
        double tf = n[word]* 1.0 / w * 1.0;
        double id = log(d * 1.0 / (idf[word] + 1) *1.0);

        if (tf*id > t) return true;
    }

    return false;
}


int main(){
    int T;
    cin >> T;

    int d, w;
    double t;
    string str;
    
    vector<bool> res(T);
    for(int i=0; i<T; i++){
        cin >> d >> w >> t;
        vector<vector<string>> matrix(d, vector<string>(w));
        unordered_map<string, int> n;
        set<string> words;
        vector<set<string>> wordset;
        for(int j=0; j<d; j++){
            words.clear();
            for(int k=0; k<w; k++){
                cin >> matrix[j][k];
                words.insert(matrix[j][k]);
                n[matrix[i][j]]++;
            }
            wordset.push_back(words);
        }
        
        res[i] = func(matrix, n, wordset, t);
    }

    for(int i=0; i<T; i++)
        cout << res[i] << endl;
        
}

//2
// 3 3 0.3
// df df rtfds
// fsaf fg df
// oo df df
// 3 3 0.6
// fsdfa fasdfsfsdfsf tetaszgag
// sssssssssssssss fdsfsaf gsagfsafasdfgasge
// hahahahah ewrsafadfad sssssssssssssss