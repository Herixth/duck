/*************************************************************************
    > File Name: crontab.cpp
    > Author: Herixth
    > Mail: 17361019875@163.com 
    > Created Time: 2018年09月11日 星期二 12时43分41秒
 ************************************************************************/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <map>
#include <cmath>
#include <string>
#include <cstring>
#include <algorithm>
#include <cctype>
using namespace std;


struct Commandline {
	string line;
	int order;
	
	Commandline (string line, int order) : line(line), order(order) { }

	bool operator < (const Commandline obj) const {
		return this->line < obj.line || (this->line == obj.line && this->order < o
bj.order);
	}
};

//
map<Commandline, string> records;
string begin_, end_;

map<string, int> Month_name;
map<string, int> Week_name;

vector<int>group[5];

int mon_list[12] = {
	31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30 ,31
};

#define IT vector<int>::iterator
//vector<int> minutes, hours, day_of_mon, month, day_or_week;
//

void init() {
	Month_name["JAN"] = 1, Month_name["FEB"] = 2;
	Month_name["MAR"] = 3, Month_name["APR"] = 4;
	Month_name["MAY"] = 5, Month_name["JUN"] = 6;
	Month_name["JUL"] = 7, Month_name["AUG"] = 8;
	Month_name["SEP"] = 9, Month_name["OCT"] = 10;
	Month_name["NOV"] = 11, Month_name["DEC"] = 12;

	Week_name["SUN"] = 0;
	Week_name["MON"] = 1;
	Week_name["TUE"] = 2;
	Week_name["WED"] = 3;
	Week_name["THU"] = 4;
	Week_name["FRI"] = 5;
	Week_name["SAT"] = 6;
}

inline bool is_leapyear(int year) {
	return !(year % 400) || (!(year % 4) && year % 100); 
}


void read_parts(string &parts, int li) {
	int loc_head = 0, loc_last = 0;
	int len = parts.length();
	while (loc_head < len) {
		loc_last = parts.find(',', loc_head + 1);
		loc_last = loc_last == string::npos ? len : loc_last;
		string sin = parts.substr(loc_head, loc_last - loc_head);
		
		if (sin.find('-', 0) != string::npos) {
			int loc = sin.find('-');
			string begins = sin.substr(0, loc);
			string ends   = sin.substr(loc + 1);
			int bb = 0;
			int cc = 0;
			if (isalpha(begins[0])) {
				transform(begins.begin(), begins.end(), begins.begin(), ::
toupper);
				bb = li == 3 ? Month_name[begins] : Week_name[begins];
			}
			else {
				bb = atoi(begins.c_str());
			}
			if (isalpha(ends[0])) {
				transform(ends.begin(), ends.end(), ends.begin(), ::touppe
r);
				cc = li == 3 ? Month_name[ends] : Week_name[ends];

			}
			else {
				cc = atoi(ends.c_str());
			}
			for (int locs = bb; locs <= cc; locs ++) {
				group[li].push_back(locs);
			}
		}
		else {
			if (isalpha(sin[0])) { //month
				transform(sin.begin(), sin.end(), sin.begin(), ::toupper);
				group[li].push_back(li == 3 ? Month_name[sin] : Week_name[
sin]);
			}
			else {
				sin == "*" ? group[li].push_back(-1) : group[li].push_back
(atoi(sin.c_str()));
			}
		}
		loc_head = loc_last + 1;
	}

}

void standard(int li, int be, int en) {
	if (group[li].back() != -1) 
		return;
	group[li].clear();
	for (int num = be; num <= en; num ++) 
		group[li].push_back(num);
}

/**
 * return true not picked
 */
bool week_pick(int year, int mon, int day) {
	if (group[4].back() == -1) 
		return false;
	int cnt = 4;
	for (int yy = 1970; yy < year; yy ++) {
		cnt = (cnt + 365 + is_leapyear(yy)) % 7;
	}
	for (int mm = 1; mm < mon; mm ++) {
		cnt = (cnt + mon_list[mm - 1] + (mm == 2 && is_leapyear(year))) % 7;
	}
	cnt = (cnt + day - 1) % 7;
	
	for (IT tm = group[4].begin(); tm != group[4].end(); tm ++) {
		if (*tm == cnt) 
			return false;
	}

	return true;

}

string int_to_string(int num) {
	string nums;
	if (num == 0) {
		nums = "0";
		return nums;
	}
	while (num) {
		nums.append(1, char('0' + num % 10));
		num /= 10;
	}
	reverse(nums.begin(), nums.end());
	return nums;
}

void read_command(int order) {
	string commline;
	getline(cin, commline);
	
	int len = commline.length();
	
	for (int inc = 0; inc < 5; inc ++) 
		group[inc].clear();

	int loc_head = 0, loc_last = 0;
	int li = 0;
	bool flg = false;
	string commands;
	while (loc_head < len) {
		loc_last = commline.find(' ', loc_head + 1);
		loc_last = loc_last == string::npos ? len : loc_last;
		string tmp = commline.substr(loc_head, loc_last - loc_head);
		if (tmp.empty() || tmp[0] == ' ') 
			continue;
		if (li == 5) {
			commands = tmp;
			break;
		}
		read_parts(tmp, li ++);

		loc_head = loc_last + 1;
	}
	
	int be_y = atoi(begin_.substr(0, 4).c_str());
	int en_y = atoi(end_.substr(0, 4).c_str());

	standard(3, 1, 12);
	standard(1, 0, 23);
	standard(0, 0, 59);
	//yyyy mm dd HH MM 
	for (int years = be_y; years <= en_y; years ++) { //yyyy
		bool _is_leap = is_leapyear(years);

		for (IT mon_it = group[3].begin(); mon_it != group[3].end(); mon_it ++) { 
//mm
			if (group[2].back() == -1 || flg) {
				group[2].clear();
				flg = true;
				int level = mon_list[*mon_it - 1];
				if (*mon_it == 2) level += _is_leap;
				for (int num = 1; num <= level; num ++)
					group[2].push_back(num);
			}

			for (IT day_it = group[2].begin(); day_it != group[2].end(); day_i
t ++) { //dd
					if (week_pick(years, *mon_it, *day_it)) 
						continue;	

					for (IT hour_it = group[1].begin(); hour_it != gro
up[1].end(); hour_it ++) { //HH
						
						for (IT min_it = group[0].begin(); min_it 
!= group[0].end(); min_it ++) { //MM
 							string lines = int_to_string(years
);
 							if (*mon_it < 10) lines.append("0"
);
 							lines += int_to_string(*mon_it);
 							if (*day_it < 10) lines.append("0"
);
 							lines += int_to_string(*day_it);
 							if (*hour_it < 10) lines.append("0
");
 							lines += int_to_string(*hour_it);
 							if (*min_it < 10) lines.append("0"
);
 							lines += int_to_string(*min_it);
							if (lines >= begin_ && lines < end
_)
							records[Commandline(lines, order)]
 = commands;
							//MM
						}
						
						//HH
					}

					//dd
			}

			//mm
		}


		//yyyy
	}


}


void read_process() {
	int N = 0;
	char tmp_begin[13] = { 0 };
	char tmp_end[13]   = { 0 };
	scanf("%d%s%s\n", &N, tmp_begin, tmp_end);
	begin_ = tmp_begin, end_ = tmp_end;   //begin and end
	
	for (int order = 1; order <= N; order ++) {
		read_command(order);
	}

	for (map<Commandline, string>::iterator ans = records.begin(); ans != records.end(
); ans ++) {
		printf ("%s %s\n", (ans->first).line.c_str(), (ans->second).c_str());
	}

}


int main() {

	init();

	read_process();

	return 0;
}
