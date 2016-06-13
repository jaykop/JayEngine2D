#include "Factory.h"
#include "../Builder.h"
#include "../../Utilities/Debug/Debug.h"

Factory::~Factory(void)
{
	Clear();
}

void Factory::AddBuilder(StageType stage, Builder* pBuilder)
{
	//Find if there is existing stage 
	auto found = m_builderMap.find(stage);
	
	//If there is, assert
	DEBUG_ASSERT(found == m_builderMap.end(), "Error: Stage Duplication!");

	//Unless, make new builder
	m_builderMap.insert(std::make_pair(stage, pBuilder));
}

void Factory::DeleteBuilder(StageType stage)
{
	//I do not understand why we need this

	//Find if there is existing stage 
	auto found = m_builderMap.find(stage);
	
	//If there is not, assert
	DEBUG_ASSERT(found != m_builderMap.end(), "Error: Not Existing Stage!");
	
	//if there is, erase
	m_builderMap.erase(stage);
}

void Factory::Clear()
{
	for (auto it = m_builderMap.begin(); it != m_builderMap.end(); ++it)
		delete it->second;

	m_builderMap.clear();
}

Stage* Factory::CreateStage(StageType stage, GameStateManager* GSM)
{
	//Find if there is existing stage 
	auto found = m_builderMap.find(stage);

	//If there is not, assert
	DEBUG_ASSERT(found != m_builderMap.end(), "Error: Not Existing Stage!");

	//if there is, erase
	return found->second->BuildeStage(GSM);
}