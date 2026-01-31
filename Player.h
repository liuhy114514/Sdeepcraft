#pragma once
#include <iostream>
#include <conio.h>
#include "constants.h"
#include "SaveSystem.h"
using namespace std;

// 游戏处理

//这是玩家体
class Player {
	private:
		int x = 3, y = 2;
	public:
		// 返回值对应消耗时间
		double FindFood(Survivor& player) {
			player.inventory.food = player.inventory.food > 10 ? 10 : player.inventory.food;
			if (!TimerStruct1.isFindFood || time(NULL) - Timer[0] >= 5) {	//计算开始时间与现在时间相差是否大于10s
				if (player.inventory.food < player.inventory.capacity) {
					if (!TimerStruct1.isFindFood) {
						TimerStruct1.isFindFood = 1;
						Timer[0] = time(NULL);
					} else Timer[0] = time(NULL);
					player.inventory.food += 3;
					cout << "收集到食物存入背包！\n";
					player.feel.HungerLevel -= 3;
					player.feel.ThirstLevel -= 2;
					return 1;
				} else {
					cout << "背包已满！\n";
					temp1 = 1;
					return 0;
				}
			} else {	//CD没过
				system("cls");
				cout << "你找过食物了！";
				Sleep(1000);
				system("cls");
				temp1 = 1;
				return 0;
			}

		}
		double CuttingDownTrees(Survivor& player) {
			if (!TimerStruct1.isCuttingDownTrees || time(NULL) - Timer[1] >= 3) {
				if (!TimerStruct1.isCuttingDownTrees) {
					TimerStruct1.isCuttingDownTrees = 1;
					Timer[1] = time(NULL);
				} else Timer[1] = time(NULL);
				player.inventory.wood += 2 + rand() % 3;
				cout << "获得木材！\n";
				player.feel.HungerLevel -= 3;
				player.feel.ThirstLevel -= 2;
				return 0.3;
			} else {
				system("cls");
				cout << "这棵树已经被砍完了";
				Sleep(1000);
				system("cls");
				temp1 = 1;
				return 0;
			}

		}
		double FindWater(Survivor& player) {
			if (!TimerStruct1.isFindWater || time(NULL) - Timer[2] >= 5) {
				if (player.inventory.water < player.inventory.capacity) {
					if (!TimerStruct1.isFindWater) {
						TimerStruct1.isFindWater = 1;
						Timer[2] = time(NULL);
					} else Timer[2] = time(NULL);
					player.inventory.water += 5;
					cout << "收集到水存入水壶！\n";
					player.feel.HungerLevel -= 3;
					player.feel.ThirstLevel -= 2;
					return 0.3;
				} else {
					cout << "水壶已满！\n";
					temp1 = 1;
					return 0;
				}
			} else {
				system("cls");
				cout << "你已经找过水了！";
				Sleep(1000);
				system("cls");
				temp1 = 1;
				return 0;
			}
		}
		double Shelters(Survivor& player) {
			if (player.inventory.wood >= 10 && !player.state.hasShelter) {
				player.inventory.wood -= 10;
				player.state.hasShelter = true;
				cout << "庇护所建造完成！\n";
				player.feel.HungerLevel -= 3;
				player.feel.ThirstLevel -= 2;
				return 1;
			} else {
				cout << "材料不足";
				return 0;
			}
		}
		double Shelters() {
			while (1) {
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 5; j++) {
						if (i == x && j == y) {
							cout << '*';
						} else {
							cout << Shelter[i][j];
						}
					}
					cout << endl;
				}
				switch (_getch()) {
					case 'w':
					case 'W':
						if (y > 0 && Shelter[y - 1][x] != '#') y--;
						break;
					case 's':
					case 'S':
						if (y < 4 && Shelter[y + 1][x] != '#') y++;
						break;
					case 'a':
					case 'A':
						if (x > 0 && Shelter[y][x - 1] != '#') x--;
						break;
					case 'd':
					case 'D':
						if (x < 4 && Shelter[y][x + 1] != '#') x++;
						break;
				}
				if (x == 3 && y == 2) {
					temp1 = 1;
					return 0;
				}
			}
			temp1 = 1;
			return 0;
		}
		double eat(Survivor& player) {
			if (!TimerStruct1.isEat || time(NULL) - Timer[3] >= 3) {
				if (player.inventory.food > 0 && player.feel.HungerLevel < 100) {
					if (!TimerStruct1.isEat) {
						TimerStruct1.isEat = 1;
						Timer[3] = time(NULL);
					} else Timer[3] = time(NULL);
					player.feel.HungerLevel = min(100, player.feel.HungerLevel + 20);
					player.inventory.food--;
					cout << "食用背包中的食物\n";
					player.feel.ThirstLevel -= 3;
					return 0.1;
				} else if (player.feel.HungerLevel >= 100) {
					system("cls");
					cout << "你已经吃饱了";
					Sleep(1000);
					system("cls");
					temp1 = 1;
					return 0;
				} else {
					cout << "背包中没有食物\n";
					player.feel.HungerLevel -= 1;
					return 0;
				}
			} else {
				system("cls");
				cout << "你刚才吃过东西了！";
				Sleep(1000);
				system("cls");
				temp1 = 1;
				return 0;
			}
		}
		double drink(Survivor& player) {
			if (!TimerStruct1.isDrink || time(NULL) - Timer[4] >= 3) {
				if (player.inventory.water > 0) {
					if (!TimerStruct1.isDrink) {
						TimerStruct1.isDrink = 1;
						Timer[4] = time(NULL);
					} else Timer[4] = time(NULL);
					player.feel.ThirstLevel = min(100, player.feel.ThirstLevel + 30);
					player.inventory.water--;
					cout << "饮用壶中的水\n";
					player.feel.HungerLevel -= 2;
					return 0.05;
				} else if (player.feel.ThirstLevel >= 100) {
					system("cls");
					cout << "你已经不渴了";
					Sleep(1000);
					system("cls");
					temp1 = 1;
					return 0;
				} else {
					cout << "水壶中没有水\n";
					return 0;
				}
			} else {
				system("cls");
				cout << "你刚才喝过水了！";
				Sleep(1000);
				system("cls");
				temp1 = 1;
				return 0;
			}
		}
		double rest(Survivor& player) {
			if (!TimerStruct1.isRest || time(NULL) - Timer[5] >= 4) {
				if (player.feel.HealthLevel < 100) {
					if (!TimerStruct1.isRest) {
						TimerStruct1.isRest = 1;
						Timer[5] = time(NULL);
					} else Timer[5] = time(NULL);
					player.feel.HealthLevel = min(100, player.feel.HealthLevel + (player.state.hasShelter ? 25 : 15));
					cout << "休息恢复体力\n";
					player.feel.HungerLevel -= 2;
					player.feel.ThirstLevel -= 1;
					return 0.5;
				} else {
					system("cls");
					cout << "你已经不累了";
					Sleep(1000);
					system("cls");
					return 0;
				}
			} else {
				system("cls");
				cout << "你刚才休息过了！";
				Sleep(1000);
				system("cls");
				temp1 = 1;
				return 0;
			}
		}
};
