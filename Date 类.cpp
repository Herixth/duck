#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
using namespace std;

int list[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

class Date {
	public:
	  Date(int y, int m, int d);
	  ~Date();
	
	  void nextDay();
	  void previousDay();
	  bool equal(Date other);
	  void show();
	  bool is_leapyear(int y);
	private:
	  int year;
	  int month;
	  int day;
};

Date::Date(int y, int m, int d) {
	year = y;
	month = m; 
	day = d;
}

bool Date::is_leapyear(int y) {
	return !(y % 400) || (!(y % 4) && (y % 100));
}

void Date::nextDay() {
	list[1] = 28 + is_leapyear(year);
	(day + 1) % (list[month - 1] + 1) ? day ++ : (day = 1, (month + 1) % 13 ? month ++ : (month = 1, year ++));
}

void Date::previousDay() {
	list[1] = 28 + is_leapyear(year);
	(day - 1) ? day -- : (day = list[(month - 1 ? -- month: month = 12) -1], year -= month == 12); 
}

bool Date::equal(Date other) {
	return other.day == day && other.month == month && other.year == year;
}

void Date::show() {
	printf("%d年%2d月%2d日\n", year, month, day);
}

Date::~Date() {
	printf("正在析构 %d年%2d月%2d日\n", year, month, day);
}

int main() {
  Date today(2018,3,20);
  Date day(2018,3,20);
  day.show();
  for(int i=0;i<30;i++)
    day.nextDay();
  day.show();
  for(int i=0;i<30;i++)
    day.previousDay();
  day.show();
  if(day.equal(today))
    printf("Very Good!\n");
  else
    printf("Very Bad!\n");
  return 0;
}
