#include "constants.h"
#include "gamemain.h"

using namespace std;
//采用彭++代码换行技术

int main() {
	Log.push_back({1, Log_time(), "游戏开始"});
	try {
		GameSystem gs = GameSystem();
		gs.Game();
	} catch(...){
		cout << "游戏出错，详细请查看日志";
		saveLog();
		system("pause");
		exit(0);
	}
	Log.push_back({1, Log_time(), "游戏结束"});
	saveLog();
	return 0;
}
