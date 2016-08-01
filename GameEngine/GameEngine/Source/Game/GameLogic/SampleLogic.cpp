#include "SampleLogic.h"

void SampleLogic::Load(const Json::Value& data)
{
	std::cout << "SanpleLogic Load\n";
	
	if (data["Object"].isArray())
	{
		for (auto it = data["Object"].begin();
			it != data["Object"].end();
			++it)
		{
			if ((*it).isMember("SanpleLogic") &&
				data["SanpleLogic"].isArray() &&
				(*it).isMember("ID") &&
				(*it)["ID"].isInt())
			{
				int id = (*it)["ID"].asInt();
				/*m_OBM->GetGameObject<Object*>*/

				for (auto it2 = data["SanpleLogic"].begin();
					it2 != data["SanpleLogic"].end();
					++it2)
				{
					if ((*it2).isMember("NewColor") &&
						(*it2)["NewColor"].isArray() &&
						(*it2)["NewColor"].size() == 4 &&
						(*it2)["NewColor"][0].isNumeric())
						color = vec4(
							(*it2)["NewColor"][0].asFloat(),
							(*it2)["NewColor"][1].asFloat(),
							(*it2)["NewColor"][2].asFloat(),
							(*it2)["NewColor"][3].asFloat());

					if ((*it2).isMember("NewSize") &&
						(*it2)["NewSize"].isArray() &&
						(*it2)["NewSize"].size() == 3 &&
						(*it2)["NewSize"][0].isNumeric())
						size = vec3(
							(*it2)["NewSize"][0].asFloat(),
							(*it2)["NewSize"][1].asFloat(),
							(*it2)["NewSize"][2].asFloat());
				}
			}
		}
	}
}

void SampleLogic::Init(void)
{
	std::cout << "SanpleLogic Inited\n";
	test = new int;
	Sprite* newOwner = static_cast<Sprite*>(m_pOwner);
	newOwner->SetColor(color);
	newOwner->SetScale(size);
}

void SampleLogic::Update(void)
{
	std::cout << "SanpleLogic Update\n";
}

void SampleLogic::Shutdown(void)
{
	delete test;
	test = 0;
	std::cout << "SanpleLogic Shutdown\n";
}

void SampleLogic::Unload(void)
{
	std::cout << "SanpleLogic Unload\n";
	
}