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

#endif // _GAMEDATA_H_