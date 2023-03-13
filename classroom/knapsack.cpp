#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <iomanip>
#include <climits>
#define FAST_IO                       \
    ios_base::sync_with_stdio(false); \
    cin.tie(0);                       \
    cout.tie(0);
#define ll long long
#define __debugging__ false
#define logm(msg) if(__debugging__) cout<< __func__<<" ("<<__LINE__<<")\t: "<< msg <<endl;
#define logd(x) if(__debugging__) cout<<__func__<<" ("<<__LINE__<<")\t: "<<#x<<" = "<<x<<endl;
#define MOD 1000000007

using namespace std;

// bool __debugging__ = true;

class Solver
{
private:

public:
    Solver(){
        if (__debugging__) {
            // cout << "FILE: " << __FILE__ << "\nSTARTED EXECUTING AT: " << __TIMESTAMP__ << "\n";
            logm("Debugging is on.");
        }
    }
    ~Solver(){
        if (__debugging__) {
            logm("Exited");
            // cout <<"STOPED EXECUTING AT: " << __TIMESTAMP__ << "\n";
        }
    }

    void solve(int);
    int greedy(vector<pair<int, int> >&, int);
};

/**
     * @brief 
     * this function solves the cp 
     * questions and handles the 
     * input too
 */

bool compareKV(const pair<int, int>& a,const pair<int, int>& b) {
    double r1 = a.first/ a.second;
    double r2 = b.first/ b.second;

    return r1 < r2;
}

int Solver::greedy(vector<pair<int, int> >& kv, int k) {
    sort(kv.begin(), kv.end(), compareKV);

    for (int i = 0; i < kv.size(); i++) {
        cout << kv[i].first << "\t" << kv[i].second << "\n";
    }

    return 0;

}

void Solver::solve(int caseNo){
    logd(caseNo);

    int n, k; cin >> n >> k;

    vector<int> p(n);
    vector<int> w(n);

    for (int i = 0; i < n; i++) cin >> p[i];

    for (int i = 0; i < n; i++) cin >> w[i];

    vector<pair<int, int> > kv(n);
    for (int i = 0; i < n; i++) {
        kv[i] = make_pair(p[i], w[i]);
    }
}   

int main()
{
    FAST_IO;
    std::cout << std::fixed;
    std::cout << std::setprecision(6);
    int testCases = 1;
    // cin >> testCases;
    Solver cp_solver = Solver();
    
    for (int i = 0; i < testCases; i++)
    {
        cp_solver.solve(i+1);
    }

    return 0;
}
