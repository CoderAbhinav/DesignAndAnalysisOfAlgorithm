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
};

/**
 * @brief 
 * this function solves the cp 
 * questions and handles the 
 * input too
 */
void Solver::solve(int caseNo){
    logd(caseNo);

    int n; cin >> n;
    
}

int main()
{
    FAST_IO;
    std::cout << std::fixed;
    std::cout << std::setprecision(6);
    int testCases = 1;
    cin >> testCases;
    Solver cp_solver = Solver();
    
    for (int i = 0; i < testCases; i++)
    {
        cp_solver.solve(i+1);
    }

    return 0;
}
