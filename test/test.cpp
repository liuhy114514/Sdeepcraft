#include <bits/stdc++.h>

using namespace std;

string Log_time(){ // 此时间戳被转换成了一个16字节的字符串
	char nt[16];
	string _nt;
	time_t now = time(NULL);
	tm lt = *localtime(&now);
	int year = lt.tm_year + 1900;
	int month = lt.tm_mon + 1;
	int day = lt.tm_mday;
	int hour = lt.tm_hour,minute = lt.tm_min;
	sprintf(nt,"%d/%d/%d %d:%02d",year,month,day,hour,minute);
	copy(nt,nt+16,back_inserter(_nt));
	return _nt;
}

int main(){
	cout << Log_time();
	return 0;
}
