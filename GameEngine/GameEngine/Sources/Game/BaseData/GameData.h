#ifndef _GAMEDATA_H_
#define _GAMEDATA_H_

/*! Enum of all stage types in the game */
enum  StageType { 

	ST_MENU, 
	ST_LV1, 
	ST_LV2, 
	ST_LV3, 
	ST_GAMEOVER, 
	ST_PAUSE 
};

struct GameData
{
	float dt;
};

namespace Resolution{

	//Resolution Setup
	struct ScreenSize
	{
		int width;
		int height;
	};

	const ScreenSize SCR_640X480{ 640, 480 };
	const ScreenSize SCR_800X600{ 800, 600 };
	const ScreenSize SCR_1024X768{ 1024, 768 };
	const ScreenSize SCR_1280X1024{ 1280, 1024 };
	const ScreenSize SCR_1920X1080{ 1920, 1080 };

};

#endif // _GAMEDATA_H_