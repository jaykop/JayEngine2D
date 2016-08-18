#ifndef _DemoLogic_GameOver_H_
#define _DemoLogic_GameOver_H_

#include "../../Engine/Logic/GameLogic/GameLogic.h"
#include "../../Engine/Logic/LogicBuilder.h"

class DemoLogic_GameOverBuilder : public LogicBuilder
{

public:
	DemoLogic_GameOverBuilder() {};
	virtual ~DemoLogic_GameOverBuilder() {};
	virtual GameLogic* BuildLogic(Object* Owner) const;

};

class DemoLogic_GameOver : public GameLogic
{
public:

	DemoLogic_GameOver(Object* owner);
	virtual ~DemoLogic_GameOver(void) {};

	virtual void Load(const Json::Value& data);
	virtual void Init(GameData& gd);
	virtual void Update(GameData& gd);
	virtual void Shutdown(GameData& gd);
	virtual void Unload(void);

	void BasicControl(void);

private:

	Object* m_Owner;
	ObjectManager* m_OBM;
	GameStateManager* m_GSM;

};

#endif // _DemoLogic_GameOver_H_