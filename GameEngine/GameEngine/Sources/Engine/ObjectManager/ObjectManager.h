#ifndef _OBJECTMANAGER_H_
#define _OBJECTMANAGER_H_

#include <hash_map>

class Sprite;
class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

	void AddObject(const int SpriteID, const std::string& textureDir = "");
	void RemoveObject(const int id);
	Sprite* GetGameObject(const int id);
	bool HasObject(const int id);
	const std::hash_map<int, Sprite*>& GetList(void) const;

	void ClearObjectList(void);

private:
	//Todo: Make a sprite list somewhere for Obj Manager
	std::hash_map<int, Sprite*> m_ObjectList;
	int number_of_Spt;

};

#endif //_OBJECTMANAGER_H_