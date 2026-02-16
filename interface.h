#include <conio.h>
#include "Event.h"
#include "Player.h"
#include "map.h"
using namespace std;

/*
当实现图形界面的时候关闭输入，把画面留给easyx
*/

//这是游戏系统，给玩家看的
class GameSys : public Event{
	private:
		Map map = Map();
		int playerx = 0, playery = 0; //当然，这里的player是光标
		bool isGameStart = false; 	//检测游戏是否开始
		double DrawAchievement(Survivor& pvp_dalao) {
			temp1 = 1;
			while (1) {
				system("cls");
				cout << "按q键退出，wsad上下左右" << endl;
				cout << "成就：游戏主线" << endl;
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 21; j++) {
						if (playerx == j && playery == i) {
							cout << "_";
							continue;
						}
						cout << Achievement[i][j];
					}
				}
				cout << "描述:";
				if (playerx == 2 && playery == 0) {
					cout << miaoshu[0];
					if (pvp_dalao.state.TenWood) cout << "（已解锁）";
					else cout << "（未解锁）";
					cout << endl;
					cout << "成就名：" << "“第一桶金(A)”" << endl << "难度：" << difficulty[0];
				} else if (playerx == 5 && playery == 0) {
					cout << miaoshu[1];
					if (pvp_dalao.state.TenStone) cout << "（已解锁）";
					else cout << "（未解锁）";
					cout << endl;
					cout << "成就名：" << "“我打水漂打的可多了！(B)”" << endl << "难度：" << difficulty[0];
				} else if (playerx == 8 && playery == 0) {
					cout << miaoshu[2];
					if (pvp_dalao.state.Live_for_a_day) cout << "（已解锁）";
					else cout << "（未解锁）";
					cout << endl;
					cout << "成就名：" << "感觉很轻松(C)" << endl << "难度：" << difficulty[0];
				} else if (playerx == 11 && playery == 0) {
					cout << miaoshu[3];
					if (pvp_dalao.state.Bowl_full_of_blood) cout << "（已解锁）";
					else cout << "（未解锁）";
					cout << endl;
					cout << "成就名：" << "钵满血满(D)" << endl << "难度：" << difficulty[1];
				} else if (playerx == 14 && playery == 0) {
					cout << miaoshu[4];
					if (pvp_dalao.state.Survival_expert) cout << "（已解锁）";
					else cout << "（未解锁）";
					cout << endl;
					cout << "成就名：" << "生存小能手！(E)" << endl << "难度：" << difficulty[0];
				} else {
					cout << "无" << endl;
				}
				// 获取按键输入
				switch (_getch()) {
					case 'w':case 'W':if (playery > 0) playery--;break;
					case 's':case 'S':if (playery < 2) playery++;break;
					case 'a':case 'A':if (playerx > 0) playerx--;break;
					case 'd':case 'D':if (playerx < 19) playerx++;break;
					case 'q':case 'Q':return 0;
				}
			}
		}

		
		//此函数使用了ai
		void showTime(double time) {
			// 分离整数和小数部分
			double intPart;
			double fractional = modf(time, &intPart);
			// 将小数部分转换为分钟
			int minutes = static_cast<int>(round(fractional * 100));
			// 处理进位
			int hours = static_cast<int>(intPart) + minutes / 60;
			minutes = minutes % 60;
			// 处理24小时制
			hours = hours % 24;
			// 格式化为HH:MM
			ostringstream oss;
			oss << setw(2) << setfill('0') << hours << ":"
			    << setw(2) << setfill('0') << minutes;

			cout << oss.str();
		}

		double showDate() {
			system("cls");
			setColor(6);
			cout << "---------------------------";
			cout << "季节：";
			if (TW.Season == 0)	cout << "春天" << endl;
			else if (TW.Season == 1)	cout << "夏天" << endl;
			else if (TW.Season == 2)	cout << "秋天" << endl;
			else				cout << "冬天" << endl;
			cout << "第" << TW.year << "年" << " " << "第" << TW.month << "月" << " " << "第" << TW.day << "天" << endl;
			cout << "当前时间：" << int(TW.date) << "月" << (TW.date - int(TW.date)) * 100 << "日" << " ";
			showTime(TW.time);
			cout << "---------------------------";
			if (_getch() == 'q' || _getch() == 'Q') return 0;
			cout << endl;
		}
		void StartChoice(Survivor& player) {
			string action;

			while (true) {
				system("cls");

				system("cls");
				cout << "★ 荒岛求生 ★\n";
				cout << "1.新游戏\n2.读取存档\n3.退出\n选择：";

				int startChoice;
				cin >> startChoice;
				cin.ignore();

				if (startChoice == 2) {
					string FileName;
					cout << "请输入你的存档名：";
					cin >> FileName;
					if (!loadGame(player, FileName)) {
						cout << "没有找到存档，开始新游戏\n";
						isGameStart = true;
						cout << "请输入玩家的名字：";
						cin >> player.name;
						Game();
					} else {
						isGameStart = true;
						Game();
					}
				} else if(startChoice == 1){
					isGameStart = true;
					cout << "请输入玩家的名字：";
					cin >> player.name;
					Game();
				} else exit(0);
			}
		}

		string GameChoice(Survivor& player) {
			cin.ignore();
			string choice;
			system("cls");
			setColor(14);
			cout << "\n========= ★ 荒岛求生 ★ =========\n";

			showProgressBar(player.feel.HealthLevel, 100, "生命");
			showProgressBar(player.feel.HungerLevel, 100, "饥饿");
			showProgressBar(player.feel.ThirstLevel, 100, "口渴");

			cout << endl;
			
			map.drawMap(TW.maps, player, player.px, player.py);

			setColor(11);
			cout << "资源：木材:" << player.inventory.wood
				<< " 石头:" << player.inventory.stone
				<< "\n背包：食物:" << player.inventory.food
				<< "/" << player.inventory.capacity
				<< " 水:" << player.inventory.water
				<< "/" << player.inventory.capacity << endl
				<< "等级:" << player.level;
			setColor(10);
			cout << "\n1.觅食 2.砍树 3.取水 "
				<< (!player.state.hasShelter ? "4.建庇护所(需要10个木头)" : "4.进入庇护所")
				<< "\n5.使用食物 6.饮用水 7.休息 8.查看手表"
				<< "\n9.保存游戏\n10.查看成就 11.退出游戏"
				<< "\nw.前 s.后 a.左 d.右"
				<< "\n选择：";
			cin >> choice;
			
			return choice;
		}
		double GameActions(Survivor& player) { // 玩家行动消耗的时间
			string temp = GameChoice(player);
			if (temp == "1") return FindFood(player);
			else if(temp == "2") return CuttingDownTrees(player);
			else if(temp == "3") return FindWater(player);
			else if(temp == "4"){
				if (!player.state.hasShelter) return Shelters(player);
				else return Shelters(); // 此处为函数重载
			}
			else if(temp == "5") return eat(player);
			else if(temp == "6") return drink(player);
			else if(temp == "7") return rest(player);
			else if(temp == "8") return showDate();
			else if(temp == "9"){
				string FileName;
				cout << "输入你的存档名：";
				cin >> FileName;
				saveGame(player, FileName);
				temp1 = 1;
				return 0;
			}
			else if(temp == "10") return DrawAchievement(player);
			else if(temp == "11"){
				temp1 = 1;
				isGameStart = 0;
				Game();
			}else if(temp == "w" || temp == "W" || temp == "s" || temp == "S" || temp == "a" || temp == "A" || temp == "d" || temp == "D"){
				map.player_move(temp[0], player);
			}else {
				temp1 = 1;
				cout << "输入错误";
				return 0;
			}
		}
		void self_check(Survivor& player) { // 游戏的自检查
			player.feel.HungerLevel = player.feel.HungerLevel > 100 ? 100 : player.feel.HungerLevel;
			player.feel.ThirstLevel = player.feel.ThirstLevel > 100 ? 100 : player.feel.ThirstLevel;
			player.feel.HealthLevel = player.feel.HealthLevel > 100 ? 100 : player.feel.HungerLevel;
			player.inventory.water = player.inventory.water > 10 ? 10 : player.inventory.water;
			player.inventory.food = player.inventory.food > 10 ? 10 : player.inventory.food;
		}
	public:
		void Game() {
			srand(time(0));

			Survivor player;
			setColor(11);

			if (player.state.first){
				if (!isGameStart) StartChoice(player);
				if (player.state.first) {
					map.generate_map(TW.maps);
					player.state.first = 0;
				}
			}
			while (player.feel.HealthLevel > 0) {
				temp1 = 0;
				setColor(15);
				self_check(player);
				OutDate(player);
				OutTime(player, GameActions(player));
				randomEvent(player);
				GameAchievement(player);
				cin.ignore();
				cout << "(按回车继续)";
				cin.get();
			}

			setColor(12);
			cout << "\n游戏结束！" << player.name << "生存了" << TW.day << "天";
			setColor(15);
			isGameStart = false;
		}
};
