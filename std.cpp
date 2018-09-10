/*************************************************************************
    > File Name: std.cpp
    > Author: Herixth
    > Mail: 17361019875@163.com 
    > Created Time: 2018年09月09日 星期日 15时08分32秒
 ************************************************************************/

#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;
//保存交易信息
struct Order {
    double price;
    int num, sell;
}order[5010];
vector<double>vec;//保存所有出现过的价格
int main() {
    char s[10];
    int num = 0, t;//num用于记录交易的数量
    while (cin >> s) {
        if (s[0] == 'c') {
            cin >> t;
            order[t - 1].sell = order[num++].sell = -1;
        }
        else {
            cin >> order[num].price >> order[num].num;
            vec.push_back(order[num].price);
            //判断是买入还是买出
            if (s[0] == 's')
                order[num].sell = 1;
            else
                order[num].sell = 0;
            num++;
        }
    }
    double ans = 0;//保存开盘价
    long long maxn = 0;//保存最大交易量,交易量可能超过int范围，所以使用long long保存
    for (int i = 0; i < vec.size(); i++) {
        long long num1 = 0, num2 = 0;//num1保存可卖出的股票数量，num2保存可买入的股票数量
        for (int j = 0; j < num; j++) {
            if (order[j].sell == 1 && order[j].price <= vec[i])
                num1 += (long long)order[j].num;
        }
        for (int j = 0; j < num; j++) {
            if (order[j].sell == 0 && order[j].price >= vec[i])
                num2 += (long long)order[j].num;
        }
        num1 = min(num1, num2);//num1保存交易数
        //更新答案
        if (num1 > maxn) {
            maxn = num1;
            ans = vec[i];
        }
        else if (num1 == maxn) {
            ans = max(ans, vec[i]);
        }
    }
    //答案可以用printf输出
    printf("%.2f %lld\n", ans, maxn);
}
