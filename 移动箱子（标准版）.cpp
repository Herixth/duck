#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 1000000 + 1;
int right[maxn];
int left[maxn];

void link (int L, int R) {
	right[L] = R;
	left[R] = L;
}

int main() {
	int n, m, kase = 0;
	while (scanf("%d%d", &n, &m) == 2) {
		
		//建立双向链表 
		for (int i = 1; i <= n; i ++) {
			left[i] = i - 1;
			right[i] = (i + 1) % (n + 1);
		}
		right[0] = 1;
		left[0] = n;
		
		int op, X, Y, inv = 0;
		
		while (m --) {
			scanf("%d", &op);
			if (op == 4) inv = !inv;
			else {
				scanf("%d%d", &X, &Y);
				
				//对情况进行预处理 
				if (op == 3 && right[Y] == X) swap(X, Y);
				if (op != 3 && inv) op = 3 - op;
				if (op == 1 && X == left[Y]) continue;
				if (op == 2 && X == right[Y]) continue;
				
				//对功能分类
				int LX = left[X], LY = left[Y], RX = right[X], RY = right[Y];
				if (op == 1) {
					link(LX, RX);
			//right[left[X]] = right[X];  1、将X左边的右向指针与X断开；2、将X左边的右向指针与X右边的值相连   
			//left[right[X]] = left[X];
					link(LY, X); link(X, Y);
				} 
				else if (op == 2) {
					link(LX, RX); link(Y, X); link(X, RY);
				}
				else if (op == 3) {
					if (right[X] == Y) {
						link(LX, Y); link(X, RY); link(Y, X);
					} 
					else {
						link(LX, Y); link(Y, RX); link(LY, X); link(X, RY);
					}
				}
			}
		}
		
		long long ans = 0;
		
		//遍历链表 + 求和 
		for ( int cur = right[0], i = 1; cur != 0; cur = right[cur], i ++) {
		#ifdef DEBUG
			printf("%d ", cur);
		#endif
			if (i % 2) ans += cur;			
		}
		
		if (inv && ! (n % 2))
			ans = (long long) n * (n + 1) / 2 - ans;
		
		printf("\nCase %d: %lld\n", ++kase, ans);
	}
	
	return 0;
}
