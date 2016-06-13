#ifndef _FACTORY_H_
#define _FACTORY_H_

#include <map>
#include "../../../Game/BaseData/GameData.h"

class Stage;
class Builder;
class GameStateManager;
class Factory
{

public:

	~Factory(void);

	void AddBuilder(StageType stage, Builder* pBuilder);
	void DeleteBuilder(StageType stage);
	void Clear();

	Stage* CreateStage(StageType stage, GameStateManager* GSM);

private:

	std::map<StageType, Builder*> m_builderMap;

};

#endif // FACTORY_H_