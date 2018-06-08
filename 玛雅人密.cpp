#include<iostream>
#include<string>
#include<map>
#include<queue>
using namespace std;
int n;
bool judge(string s)
{
	int l=s.size();
	for(int i=0;i<l-3;i++)
	{
		if(s[i]=='2'&&s[i+1]=='0'&&s[i+2]=='1'&&s[i+3]=='2')
		{
			return true;
		}
	}
	return false;
}
int bfs(string s)
{
	map<string,int>mp;//如果遍历过，将second标记为1
	mp.clear();//清空上一次的缓存
	queue<pair<string,int> >que;//用队列来保存搜索的路径
	que.push(make_pair(s,0));//将第一个string入队
	while(!que.empty())//如果遍历过所有string,返回-1
	{
		pair<string,int> now=que.front();
		que.pop();//队头的string出队
		string str=now.first;
		if(judge(str))
			return now.second;
		if(mp[str])//如果该排列已经judge过，则跳到下一个排列
			continue;
		mp[str]=1;//如果没有就标记为已遍历过
		for(int i=0;i<n-1;i++)//创建新的排列
		{
			swap(str[i],str[i+1]);
			que.push(make_pair(str,now.second+1));
			swap(str[i],str[i+1]);
		}
	}
	return -1;
}
int main()
{
	string s;
	while(cin>>n)
	{
		cin>>s;
		cout<<bfs(s)<<endl;
	}
	return 0;
}
