#include "constants.h"

class Map {
	public:
		void generate_map(MC gm[256][256]) {
			srand(time(0));
			for (int y = 0; y < 256; y++) {
				for (int x = 0; x < 256; x++) {
					gm[y][x].type = TypeMin + rand() % (TypeMax - TypeMin + 1);
					gm[y][x].c = boime[gm[y][x].type].c;
				}
			}
		}
		void player_move(char m, Survivor &player){
			switch (m) {
			case 'w':case 'W':
				switch (player.facing){
					case UP:if (player.py > 0) player.py--;break;
					case DOWN:if (player.py < 255) player.py++;break;
					case LEFT:if (player.px > 0) player.px--;break;
					case RIGHT:if (player.px < 255) player.px++;break;
				}
				break;
			case 's':case 'S':
				switch (player.facing){
					case UP:if (player.py < 255) player.py++;break;
					case DOWN:if (player.py > 0) player.py--;break;
					case LEFT:if (player.px < 255) player.px++;break;
					case RIGHT:if (player.px > 0) player.px--;break;
				}
				break;
			case 'a':case 'A':player.facing = L[(getLR(player.facing, 0) + 1) % 4];break;
			case 'd':case 'D':player.facing = R[(getLR(player.facing, 1) + 1) % 4];break;
			}
		}
		void drawMap(MC gm[256][256], Survivor &player,int px, int py){
			int fx = px + FC[player.facing][X];int fy = py + FC[player.facing][Y];
			for (int y = max(0, py - 1); y <= min(py + 1, 255); y++){
				for (int x = max(0, px - 5); x <= min(px + 5, 255); x++) { 
					if (y == py && x == px) {
						setColor(boime[PLAYER].color);
						cout << boime[PLAYER].c;
					}else if (y == fy && x == fx && fy >= 0 && fy < 256 && fx >= 0 && fx < 256){
						cout << "¨€";
						player.playerFacing = boime[gm[y][x].type].name;
					}else if((y == fy && x == fx) && !(fy >= 0 && fy < 256 && fx >= 0 && fx < 256)){
						player.playerFacing = boime[AIR].name;
					}else {
						setColor(gm[y][x].color);
						cout << gm[y][x].c;
					}
				}
				cout << endl;
			}
		}
};