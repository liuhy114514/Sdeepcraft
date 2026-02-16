#include "Player.h"
#include "constants.h"
using namespace std;
//这是事件
class Event : public Player {
	protected:
		// 成就事件
		void GameAchievement(Survivor& player) {
			if (player.inventory.wood >= 10 && !player.state.TenWood) {
				player.state.TenWood = true;
				cout << "成就解锁：“第一桶金(A)”\n";
			} else if (player.inventory.stone >= 10 && !player.state.TenStone) {
				player.state.TenStone = true;
				cout << "成就解锁：“我打水漂打的可多了！(B)”\n";
			} else if (TW.day > 1 && !player.state.Live_for_a_day) {
				player.state.Live_for_a_day = true;
				cout << "成就解锁：感觉很轻松(C)\n";
			} else if ((player.inventory.food >= 10 && player.inventory.water >= 10) && !player.state.Bowl_full_of_blood) {
				player.state.Bowl_full_of_blood = true;
				cout << "成就解锁：钵满血满(D)\n";
			} else if (TW.day >= 10) {
				player.state.Survival_expert = true;
				cout << "生存小能手！(E)";
			}
		}
		// 随机事件
		void randomEvent(Survivor& s) {
			if (rand() % 100 < 25 && !temp1) {
				setColor(14);
				switch (rand() % 6) {
					case 0:
						s.feel.HealthLevel -= 10;
						cout << "[!] 被毒蛇咬伤了！\n";
						break;
					case 1:
						s.inventory.food += 2;
						cout << "[+] 在背包发现之前存的食物！\n";
						break;
					case 2:
						s.inventory.water += 3;
						cout << "[+] 水壶里还有存水！\n";
						break;
					case 3:
						s.inventory.stone += 2;
						cout << "[+] 捡到一些石头\n";
						break;
					case 4:
						s.feel.HealthLevel = min(100, s.feel.HealthLevel + 15);
						cout << "[+] 找到草药！\n";
						break;
					case 5:
						s.feel.HungerLevel += 10;
						cout << "[+] 发现野果！\n";
				}
				setColor(15);
			}else {
				temp1 = true;
			}
		}
		// 游戏时间变化事件
		void OutTime(Survivor& player, double time) {
			double temp;
			TW.time += time;
			if (fmod(time, 10) - int(time) % 10 * 100 >= 60) {
				time += 1;
				temp = time;
				time = int(time);
				time += ((fmod(temp, 10) - int(temp) % 10) * 100 - 60) / 100;
			}
			player.feel.HealthLevel -= max(player.feel.HungerLevel <= 20 ? 5 : 1, player.feel.ThirstLevel <= 15 ? 4 : 1);

			if (TW.time >= 24) {
				TW.day++;
				if (TW.time > 24) TW.time -= 24;
				else TW.time = 0;
			}
		}
		// 游戏日期变化事件
		void OutDate(Survivor& player) {
			TW.date = The_Four_Seasons0[TW.Season].start;

			if (TW.day > temp0) {
				temp0 = TW.day;
				TW.date = int(TW.date) + (double((TW.date - int(TW.date)) * 100 + 1)) / 100;
				if ((TW.date - int(TW.date)) * 100 > Month[TW.month]) {
					TW.date = int(TW.date) + 1;
					TW.month++;
				}
			}
			if (TW.date >= The_Four_Seasons0[TW.Season].end) {
				TW.date = The_Four_Seasons0[TW.Season].end;
				TW.Season = (TW.Season + 1) % 4;
			}
		}
};

//这是天气系统
class WeatherAndSeasonSystem : Player { // and SeasonSystem
	public:
		Survivor player;
		WeatherAndSeasonSystem(Survivor& player) {
			this->player = player;
		}
	public:
		enum Season { SPRING, SUMMER, AUTUMN, WINTER };
		enum Weather { SUNNY, RAINY, CLOUDY };

	private:
		Weather current = SUNNY;
		Season currentSeason = SPRING;
		float temp = 20.0f;
		float humidity = 50.0f;
		int dayCounter = 0;

		// 季节基础温度
		const float seasonBaseTemp[4] = { 18.0f, 28.0f, 22.0f, 10.0f };
		// 季节基础湿度
		const float seasonBaseHumidity[4] = { 60.0f, 70.0f, 65.0f, 50.0f };

	public:
		void update(int day) {
			dayCounter = day;
			currentSeason = static_cast<Season>(TW.Season); // 获取当前季节
			current = static_cast<Weather>(rand() % 3);

			// 根据季节和天气调整温度
			float weatherTempEffect = 0.0f;
			// 根据季节和天气调整湿度
			float weatherHumidityEffect = 0.0f;
			switch (current) {
				case SUNNY:
					weatherTempEffect = 5.0f;
					weatherHumidityEffect = -10.0f;
					break;
				case RAINY:
					weatherTempEffect = -3.0f;
					weatherHumidityEffect = 30.0f;
					break;
				case CLOUDY:
					weatherTempEffect = -1.0f;
					weatherHumidityEffect = 10.0f;
					break;
			}
			temp = seasonBaseTemp[currentSeason] + weatherTempEffect;

			humidity = seasonBaseHumidity[currentSeason] + weatherHumidityEffect;
			humidity = max(0.0f, min(100.0f, humidity)); // 限制湿度范围
		}

		string getWeather() const {
			const std::array<const char*, 3> weatherNames = { "晴", "雨", "阴" };
			const std::array<const char*, 4> seasonNames = { "春", "夏", "秋", "冬" };
			return string(seasonNames[currentSeason]) + "季" + " " + weatherNames[current];
		}
		Season getSeason() const {
			return currentSeason;
		}
		float getTemperature() const { // 获取气温
			return temp;
		}
		float getHumidity() const { // 获取湿度
			return humidity;
		}
};


