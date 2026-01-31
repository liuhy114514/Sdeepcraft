#pragma once
#include <fstream>
#include "constants.h"
using namespace std;
// 写关于玩家保存数据的，及后面云端上传

void saveGame(Survivor& player, string filename) {
	ofstream saveFile(filename);
	if (saveFile) {
		saveFile << player.name << endl;
		saveFile << TW.day << endl;
		saveFile << TW.time << endl;
		saveFile << TW.month << endl;
		saveFile << TW.date << endl;
		saveFile << player.feel.HealthLevel << endl;
		saveFile << player.feel.HungerLevel << endl;
		saveFile << player.feel.ThirstLevel << endl;
		saveFile << player.state.hasShelter << endl;
		saveFile << player.state.first << endl;
		saveFile << player.inventory.water << endl;
		saveFile << player.inventory.food << endl;
		saveFile << player.inventory.wood << endl;
		saveFile << player.inventory.stone << endl;
		cout << "游戏已保存！" << endl;
	} else {
		cout << "保存失败！" << endl;
	}
}

bool loadGame(Survivor& player, string filename) {
	ifstream saveFile(filename);
	if (saveFile) {
		saveFile >> player.name;
		saveFile >> TW.day;
		saveFile >> TW.time;
		saveFile >> TW.month;
		saveFile >> TW.date;
		saveFile >> player.feel.HealthLevel;
		saveFile >> player.feel.HungerLevel;
		saveFile >> player.feel.ThirstLevel;
		saveFile >> player.state.hasShelter;
		saveFile >> player.state.first;
		saveFile >> player.inventory.water;
		saveFile >> player.inventory.food;
		saveFile >> player.inventory.wood;
		saveFile >> player.inventory.stone;
		return true;
	}
	return false;
}
