#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <ctime>
using namespace std;

int main() {
    
    clock_t start, finish;
    long double constant = 0;
    long long int operate_num = 0;
    long long int acc = 0;

    cout << endl << "____________________________________________________" << endl;
    cout << "常数     Constant: ";
    cin >> constant;
    cout << endl;

    cout << "模拟次数 Oprate_num: ";
    cin >> operate_num;
    cout << endl;

    cout << "计算精度 Accuracy: ";
    cin >> acc;
    cout << endl;

    start = clock();
    long double ans = constant;
    for (int inc = 0; inc < operate_num; inc ++) {
        ans = 1 + 1.0 / ans;
        //cout << setw(6)<< setiosflags(ios::fixed) << setprecision(acc) << "op_order: " << inc + 1 << "   ans_now: "<< ans << endl;
    }
    finish = clock();

    cout << "____________________________________________________" << endl;
    cout <<  endl << "Golden_section: " << endl;
    cout << setiosflags(ios::fixed) << setprecision(acc) << ans << endl << endl;
    cout << "Time consuming: " << setprecision(3) << 1.0 * (finish - start) / CLOCKS_PER_SEC << "s" << endl;
    cout << "____________________________________________________" << endl << endl << endl;
    system("pause");
    return 0;
}