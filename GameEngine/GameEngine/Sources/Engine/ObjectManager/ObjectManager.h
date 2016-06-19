#ifndef _OBJECTMANAGER_H_
#define _OBJECTMANAGER_H_

#include <hash_map>
#include <vector>

class Scene;
class World;
class Sprite;
class Application;

typedef std::hash_map<int, bool> Relation;
typedef std::hash_map<int, Sprite*> SpriteList;

class ObjectManager
{
public:
	
	// Constructor and Destructoer
	ObjectManager(void);
	~ObjectManager();

	// Functions manages objects
	void AddObject(const int SpriteID, 
		const std::string& textureDir = "Resources/Texture/rect.png");
	Sprite* GetGameObject(const int id);
	bool HasObject(const int id);
	void RemoveObject(const int id);
	
	// Manage list
	const SpriteList& GetList(void) const;
	void ClearObjectList(void);

	// Manage main system
	void BindGameSystem(Application* pApp);
	void InitGameSystem();
	void UpdateGameSystem(void);
	void ShutdownGameSystem();

	Scene* GetGameScene(void) const;
	World* GetGameWorld(void) const;

private:
	
	// Sprites info
	SpriteList m_ObjectList;	// Sprite hashmap

	// for world
	//std::vector<int, Relation> m_collision;	// Collision relation hashmap

	// The number of the sprites
	int number_of_Spt;

	Scene* scenePtr;
	World* worldPtr;

};

#endif //_OBJECTMANAGER_H_