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
#include <set>
using namespace std;

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
const int maxn = 1e4 + 10;

int N, M;

vector<int> source;
vector<int> endss;

struct NODE {
    set<int> path;
    set<int> back_pa;
    set<int> last;
    vector<int> edges;
	vector<int> back_ed;
    int order;
    bool not_head;
    bool not_ends;
    NODE(bool not_head = false, bool not_ends = false) : not_head(not_head), not_ends(not_ends) {
        path.clear();
        back_pa.clear();
        edges.clear();
        back_ed.clear();
        order = 0;
    }
} nodes[maxn];

void read_edges() {
    for (int inc = 0; inc < M; inc ++) {
        int A = 0, B = 0;
        scanf("%d%d", &A, &B);
        nodes[A - 1].not_ends = true;
        nodes[A - 1].edges.push_back(B - 1);
        nodes[B - 1].back_ed.push_back(A - 1);
        nodes[B - 1].not_head = true;
        nodes[A - 1].order = A - 1;
        nodes[B - 1].order = B - 1;
        nodes[A - 1].path.insert(A - 1);
        nodes[A - 1].back_pa.insert(A - 1);
        nodes[B - 1].path.insert(B - 1);
        nodes[B - 1].back_pa.insert(B - 1);
    }

    for (int inc = 0; inc < N; inc ++) {
        if (!nodes[inc].not_head) {
            source.push_back(inc);
        }
        if (!nodes[inc].not_ends) {
            endss.push_back(inc);
        }
    }
}

void bfs() {
	for (vector<int>::iterator it = source.begin(); it != source.end(); it ++) {
		for (vector<int>::iterator tmp = nodes[*it].edges.begin(); tmp != nodes[*it].edges.end(); tmp ++) {
			queue<NODE> Q;
			nodes[*tmp].path.insert(*it);
			Q.push(nodes[*tmp]);
			while (!Q.empty()) {
				int x = Q.front().order;
				Q.pop();
				for (vector<int>::iterator inc = nodes[x].edges.begin(); inc != nodes[x].edges.end(); inc ++) {
					for (set<int>::iterator snc = nodes[x].path.begin(); snc != nodes[x].path.end(); snc ++) {
						nodes[*inc].path.insert(*snc);
					}
					Q.push(nodes[*inc]);
				}
			}
		}
	}
	
	for (vector<int>::iterator it = endss.begin(); it != endss.end(); it ++) {
		for (vector<int>::iterator tmp = nodes[*it].back_ed.begin(); tmp != nodes[*it].back_ed.end(); tmp ++) {
			queue<NODE> Q;
			nodes[*tmp].back_pa.insert(*it);
			Q.push(nodes[*tmp]);
			while (!Q.empty()) {
				int x = Q.front().order;
				Q.pop();
				for (vector<int>::iterator inc = nodes[x].back_ed.begin(); inc != nodes[x].back_ed.end(); inc ++) {
					for (set<int>::iterator snc = nodes[x].back_pa.begin(); snc != nodes[x].back_pa.end(); snc ++) {
						nodes[*inc].back_pa.insert(*snc);
					}
					Q.push(nodes[*inc]);
				}
			}
		}
	}
	
}

int main() {
	int ans = 0;
    //FILE_READ(TXT);
    scanf("%d%d", &N, &M);

    read_edges();
	
	bfs();
	
	for (int inc = 0; inc < N; inc ++) {
		set_union(nodes[inc].path.begin(), nodes[inc].path.end(),
		nodes[inc].back_pa.begin(), nodes[inc].back_pa.end(), inserter(nodes[inc].last, nodes[inc].last.begin()));
		if (nodes[inc].last.size() == N) ans ++;
	}
	
	cout << ans << endl;
    return 0;
};
