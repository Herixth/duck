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
	map<string,int>mp;//�������������second���Ϊ1
	mp.clear();//�����һ�εĻ���
	queue<pair<string,int> >que;//�ö���������������·��
	que.push(make_pair(s,0));//����һ��string���
	while(!que.empty())//�������������string,����-1
	{
		pair<string,int> now=que.front();
		que.pop();//��ͷ��string����
		string str=now.first;
		if(judge(str))
			return now.second;
		if(mp[str])//����������Ѿ�judge������������һ������
			continue;
		mp[str]=1;//���û�оͱ��Ϊ�ѱ�����
		for(int i=0;i<n-1;i++)//�����µ�����
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
