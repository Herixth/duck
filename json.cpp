/**
 * @FILE JSON查询
 *
 * @DATE 2018-05-26
 *
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

#define _STRING 1
#define _OBJECT 2
#define _MAXLEN 10000
#define _ROWLEN 100

string str_record;

typedef struct Node {
    int type = 0;
    string name;
    vector<Node*> next;
} Node;

int counts = 0;
void BuilNodeList(Node *tmp_node, int &idx) {
    while (true) {
        if (str_record[idx] == ' ') {             //空格符跳过
            idx ++;
            continue;
        }

        if (str_record[idx] == '}' || idx >= (int)str_record.length()) {  //结束标志
            idx ++;
            return;
        }

        if (str_record[idx] == '{' || str_record[idx] == ',') {            //对象序列的开始
            Node *new_tmp = new Node;
            idx = str_record.find('"', idx);          //定位字符串前点"
            int new_idx = str_record.find('"', idx + 1);
            while (str_record[new_idx - 1] == '\\') {      //定位字符串后点"
                new_idx = str_record.find('"', new_idx + 1);
            }

            new_tmp->name.assign(str_record, idx + 1, new_idx - idx - 1); 
            
            /*判断该对象键值是 字符串 还是 对象*/
            idx = str_record.find(':', idx) + 1;
            while (str_record[idx] == ' ') {
                idx ++;
            }
            if (str_record[idx] == '"') {
                new_tmp->type = _STRING;
                Node *next = new Node;
                new_idx = str_record.find('"', idx + 1);
                while (str_record[new_idx - 1] == '\\') {      //定位字符串后点"
                    new_idx = str_record.find('"', new_idx + 1);
                }
                next->name.assign(str_record, idx + 1, new_idx - idx - 1);
                new_tmp->next.push_back(next);
                tmp_node->next.push_back(new_tmp);
                idx = new_idx + 1;
            }
            else if (str_record[idx] == '{') {
                new_tmp->type = _OBJECT;
                tmp_node->next.push_back(new_tmp);
                BuilNodeList(new_tmp, idx);
            }
        }
    }
}

void SearchNode(Node *head, int n_find) {
    string buff;
    for (int inc = 0; inc < n_find; inc ++) {
        getline(cin, buff);
        for (int snc = 0; snc < buff.length(); snc ++) {
            if (buff[snc] == '\\' || buff[snc] == '"') {
                buff.insert(snc, "\\");
                snc ++;
            }
        }

        string mid;
        Node *tmp = new Node;
        int idx = 0;
        tmp = head;
        int flag = 1;
        while (buff.find('.', idx) != string::npos) {
            int last = buff.find('.', idx);
            mid.assign(buff, idx, last - idx);
            int flag2 = 0;
            /* 判断是否存在 */
            for (vector<Node*>::iterator it = tmp->next.begin(); it != tmp->next.end(); it ++) {
                if ((*it)->name == mid) {
                    flag2 = 1;
                    tmp = *it;
                    break;
                }
            }
            flag = flag2;
            if (!flag) {
                break;
            }
            else {
                idx = last + 1;
            }

        }
        if (!flag) {
            cout << "NOTEXIST" << endl;
            continue;
        }
        mid.assign(buff, idx, buff.length() - idx);
        int flag2 = 0;
        /* 判断是否存在 */
        for (vector<Node*>::iterator it = tmp->next.begin(); it != tmp->next.end(); it++) {
            if ((*it)->name == mid) {
                flag2 = 1;
                tmp = *it;
                break;
            }
        }
        flag = flag2;
        if (flag) {
            if (tmp->type == _STRING) {
                cout << "STRING ";
                for (int stat = 0; stat < (*tmp->next.begin())->name.length(); stat ++) {
                    if ((*tmp->next.begin())->name[stat] == '\\') {
                        cout << (*tmp->next.begin())->name[++ stat];
                    }
                    else {
                        cout << (*tmp->next.begin())->name[stat];
                    }
                }
                cout << endl;
            }
            else {
                cout << "OBJECT" << endl;
            }
        }
        else {
            cout << "NOTEXIST" << endl;
        }

        delete tmp;
    }
}

int main() {

#ifdef _DEBUG
    freopen("data.txt", "r", stdin);
#endif // _DEBUG


    Node *head = new Node;
    int m_row = 0, n_find = 0;
    cin >> m_row >> n_find;
    char mid = getchar();
    string buff;
    for (int row_inc = 0; row_inc < m_row; row_inc ++) {
        getline(cin, buff);
        str_record += buff;
    }

    int idx = 0;
    BuilNodeList(head, idx);

    SearchNode(head, n_find);


    delete head;
#ifdef _DEBUG
    system("pause");
#endif // _DEBUG

    return 0;
}