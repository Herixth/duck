#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
#include <queue>
#include <iomanip>
#include <cmath>
#include <map>
using namespace std;

#define NONE 0x1 //do nothing

#define CLEAR(X) memset(X, 0, sizeof(X))
#define OB(X) cout << "debug_ob: " << (X) << endl 
#define MARK cout << "mark" << endl 
#define FILE_READ(X) freopen(X, "r", stdin)
#define FILE_WRITE(X) freopen(X, "w", stdout)
#define TXT ((string(__FILE__).erase(string(__FILE__).find_last_of('.')) + ".txt").c_str())
#define FOR_INC(X, BEGIN, END) for (int X = BEGIN; X < END; X ++)
#define FOR_DEC(X, BEGIN, END) for (int X = BEGIN; X >= END; X --)
typedef long long LL;

const int INF = 0X0FFFFFFF;
const int maxn = 1e2 + 10;

int ball_num;
int length;
int clocks;

int balls[maxn][2]; // ball[x][0] -> 小球x的位置, ball[x][1] -> 0 小球x向右 , -> 1 小球x向左 

void read_info() {
    scanf("%d%d%d", &ball_num, &length, &clocks);
    FOR_INC(inc, 0, ball_num) {
        scanf("%d", &balls[inc][0]);
    }
}

//模拟所有球在某一个时刻的操作
void balls_movestep() {
    //找出所有位置相同的球, 交换它们的方向
    FOR_INC(loc_first, 0, ball_num) {
        FOR_INC(loc_second, loc_first + 1, ball_num) {
            if (balls[loc_first][0] == balls[loc_second][0]) {
                swap(balls[loc_first][1], balls[loc_second][1]);
                break;
            }
        }
    }

    FOR_INC(idx, 0, ball_num) {
        //判断边界
        balls[idx][0] == length || !balls[idx][0] ? balls[idx][1] = !balls[idx][1] : NONE;
        //小球移动
        balls[idx][0] += balls[idx][1] ? -1 : 1;
    }
}


void ball_rolling() {
    //遍历每一个时刻
    FOR_INC(every_clock, 0, clocks) {
        balls_movestep();
    }

    //输出
    FOR_INC(inc, 0, ball_num) {
        printf("%d ", balls[inc][0]);
    }
    puts("\n");
}

int main() {
#ifdef _DEBUG_
    FILE_READ(TXT);
#endif

//读取信息
    read_info();

//模拟过程
    ball_rolling();

    return 0;
};