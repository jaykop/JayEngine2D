/******************************************************************************/
/*!
\file   RigidBody.h
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains RigidBody's class and members

All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef _RIGIDBODY_H_
#define _RIGIDBODY_H_

#include "../Utilities/Math/MathUtils.h"

//! For Rectangle sprites
class Vertices{

public:

	//! Vertices constructor, destructor, operator
	Vertices(){ vertice[0] = vertice[1] = vertice[2] = vertice[3] = vec3(); }
	~Vertices(){};
	vec3& operator[](const int index){ return vertice[index]; }

private:
	// Four vectices (RECT)
	vec3 vertice[4];
};

//! For Rectangle sprites
class Edges{

public:

	//! Vertices constructor, destructor, operator
	Edges(){ edges[0] = edges[1] = edges[2] = edges[3] = vec3(); }
	~Edges(){};
	vec3& operator[](const int index){ return edges[index]; }

private:
	// Four vectices (RECT)
	vec3 edges[4];
};

class Sprite;

//! Rigidbody' shape
enum Shape { BALL, BOX };

//! class RigidBody
class RigidBody{

public:
	RigidBody(Sprite* owner);
	~RigidBody();

	Sprite* GetOwnerSprite(void) const;

	//Manage Body' scale 
	void SetScale(const vec3& scale);
	vec3 GetScale(void) const;

	//Manage Body's direction to move
	void SetDirectionAngle(float m_direction);
	float GetDirectionAngle(void) const;

	//Manager body's physics info
	void SetSpeed(const vec3& speed);
	vec3 GetSpeed(void) const;

	void SetVelocity(const vec3& velocity);
	vec3 GetVelocity(void) const;
	void ClearVelocity(void);

	void SetForce(const vec3& force);

	//Todo: What would I do???
	void SetAcceleration(float acceleration);
	float GetAcceleration(void) const;

	// Body's shape type
	void SetShape(Shape type);
	Shape GetShape(void) const;

	void SetMass(float mass);
	float GetMass(void) const;

	//Manage Body's status
	void ActivateMove(bool move);
	bool GetMoveToggle(void) const;

	void ActivateCollider(bool active);
	bool GetColliderToggle(void) const;

	void  SetFriction(float friction);
	float GetFriction(void) const;

	// Manage Collision partner
	void CheckCollided(bool collided);
	void SetCollisionWith(Sprite* partner);

	bool IsCollided(void) const;
	bool IsCollisionWith(Sprite* partner);
	Sprite* GetCollisionWith(void) const;
	
	// Get vertices and edges
	Vertices GetVertices(void);
	Edges GetEdges(void);

private:

	//! Motion float info
	float m_mass;
	float m_direction;
	float m_acceleration;
	float m_friction;

	//! Motion vector Info
	vec3 m_lastPos;
	vec3 m_scale;
	vec3 m_speed;
	vec3 m_velocity;

	//! Collision info
	bool m_collider;
	bool m_move;
	bool m_isCollided;
	Sprite* m_with;
	Edges m_edges;
	Vertices m_verts;

	//! Sprite owner
	Sprite* m_owner;

	//! Body's shape(Ball or box)
	Shape m_shape;
};

#endif // _RIGIDBODY_H_