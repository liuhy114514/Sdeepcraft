#include "constants.h"
#include "gamemain.h"

using namespace std;
//采用彭++代码换行技术

int main() {
	try {
		GameSystem gs = GameSystem();
		gs.Game();
	} catch(...){
		cout << "游戏出错，详细请查看日志";
		system("pause");
		exit(0);
	}
	return 0;
}
