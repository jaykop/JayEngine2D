/******************************************************************************/
/*!
\file   Scene.cpp
\author Jeong Juyong
\par    email: jeykop14\@gmail.com
\date   2016/06/19(yy/mm/dd)

\description
Contains Scene's class functions
All content (C) 2016 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include <algorithm>
#include "Scene.h"
#include "../Graphic//Sprite.h"
#include "../Graphic/Text.h"
#include "../ObjectManager/ObjectManager.h"
#include "../Apps/Application.h"

/******************************************************************************/
/*!
\brief - Scene Constructor

\param pApp - pointer to Application

*/
/******************************************************************************/
Scene::Scene(Application* pApp)
: m_width(0), m_height(0), m_zNear(0),
m_zFar(0), m_fovy(0), aspectRatio(0), m_radius(0),
m_camera(vec4()), m_bgColor(vec4(0,0,0,0))
{
	m_pApp = pApp;
	m_DrawList.clear();
}

/******************************************************************************/
/*!
\brief - Scene Destructor
*/
/******************************************************************************/
Scene::~Scene(void)
{}

/******************************************************************************/
/*!
\brief - Initiaiize Scene
*/
/******************************************************************************/
void Scene::Init(void)
{
	freetype::m_font.SetFont("Resource/Font/Default.ttf", 36);

	//Get projection information
	ProjectionInfo temp = m_pApp->GetGLManager()->GetProjectionInfo();

	m_width = static_cast<int>(temp.m_width);
	m_height = static_cast<int>(temp.m_height);
	m_zNear = static_cast<float>(temp.m_zNear);
	m_zFar = static_cast<float>(temp.m_zFar);
	m_fovy = static_cast<float>(temp.m_fovy);
	aspectRatio = static_cast<float>(m_width) / static_cast<float>(m_height);

	m_camera = vec4(0, 0, 80, 0);

	//glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertex_buffer_data), m_vertex_buffer_data, GL_STATIC_DRAW);

	m_texId = glGetUniformLocation(m_pApp->GetGLManager()->GetShader(0).m_programID, "Texture");

	// Sort Sprites by projection type and z Order
	ReorderSprites();
}

/******************************************************************************/
/*!
\brief - Draw Scene
*/
/******************************************************************************/
void Scene::Draw(TextList textList)
{
	//Refresh the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(m_bgColor.x, m_bgColor.y, m_bgColor.z, m_bgColor.w);

	//Todo: Lambda loop expression
	//std::for_each(m_DrawList.begin(), m_DrawList.end(),
	//	[&](DrawList::iterator it)
	//{

	/*glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertex_buffer_data), m_vertex_buffer_data, GL_STATIC_DRAW);
	glUseProgram(m_pApp->GetGLManager()->GetShader(0).m_programID);*/
	//for (auto it = m_DrawList.begin(); it != m_DrawList.end(); ++it)
	//{
	//	//Update pipeline
	//	Pipeline((*it));

	//	//Initialize matrix
	//	m_matrixID = glGetUniformLocation(m_pApp->GetGLManager()->GetShader(0).m_programID, "MVP");

	//	//Implement Matrix
	//	glUniformMatrix4fv(m_matrixID, 1, GL_FALSE, &m_mvp.m_member[0][0]);

	//	//Coloring
	//	vec4 sptColor = ((*it)->GetColor());
	//	GLuint color = glGetUniformLocation(m_pApp->GetGLManager()->GetShader(0).m_programID, "Color");
	//	glUniform4f(color, sptColor.x, sptColor.y, sptColor.z, sptColor.w);

	//	GLuint shape = glGetUniformLocation(m_pApp->GetGLManager()->GetShader(0).m_programID, "Shape");
	//	glUniform1d(shape, (*it)->GetSpriteShape());

	//	//More high quality?
	//	//glUniformMatrix4fv();

	//	// Bind our texture in Texture Unit 0
	//	glActiveTexture(GL_TEXTURE0);
	//	glBindTexture(GL_TEXTURE_2D, (*it)->GetTexture()->GetTexId());

	//	// Set our "myTextureSampler" sampler to user Texture Unit 0
	//	glUniform1i(m_texId, 0);

	//	//first attribute buffer : vertices
	//	glEnableVertexAttribArray(0);
	//	glBindBuffer(GL_ARRAY_BUFFER, m_pApp->GetGLManager()->GetVertexBuffer());
	//	glVertexAttribPointer(
	//		0,						// must be match the layout in the shader
	//		3,						// size : X+Y+Z => 3
	//		GL_FLOAT,				// type
	//		GL_FALSE,				// normalized
	//		5 * sizeof(GLfloat),	// stride
	//		(GLvoid*)0				// array buffer offset
	//		);

	//	// 2nd attribute buffer : UVs
	//	glEnableVertexAttribArray(1);
	//	glBindBuffer(GL_ARRAY_BUFFER, m_pApp->GetGLManager()->GetVertexBuffer());
	//	glVertexAttribPointer(
	//		1,								// attribute. No particular reason for 1, but must match the layout in the shader.
	//		2,								// size : U+V => 2
	//		GL_FLOAT,						// type
	//		GL_TRUE,						// normalized?
	//		5 * sizeof(GLfloat),			// stride
	//		(GLvoid*)(3 * sizeof(GLfloat))	// array buffer offset
	//		);

	//	// Draw the triangle
	//	glDrawArrays(GL_QUADS, 0, 4);
	//	glDisableVertexAttribArray(0);
	//	glDisableVertexAttribArray(1);
	//}

	for (auto it = textList.begin(); it != textList.end(); ++it)
	{
		//Update pipeline
		Pipeline(it->second);

		//Initialize matrix
		m_matrixID = glGetUniformLocation(m_pApp->GetGLManager()->GetShader(0).m_programID, "MVP");

		//Implement Matrix
		glUniformMatrix4fv(m_matrixID, 1, GL_FALSE, &m_mvp.m_member[0][0]);

		//Coloring
		vec4 sptColor = (it->second->GetColor());
		GLuint color = glGetUniformLocation(m_pApp->GetGLManager()->GetShader(0).m_programID, "Color");
		glUniform4f(color, sptColor.x, sptColor.y, sptColor.z, sptColor.w);

		wchar_t* fmt = it->second->GetText();

		// We want a coordinate system where things coresponding to window pixels.
		// freetype::pushScreenCoordinateMatrix();

		GLuint font = freetype::m_font.list_base;
		float h = freetype::m_font.height / .63f;						//We make the height about 1.5* that of

		wchar_t	text[256];								// Holds Our String
		va_list		ap;										// Pointer To List Of Arguments

		if (fmt == NULL)									// If There's No Text
			*text = 0;											// Do Nothing

		else {
			va_start(ap, fmt);									// Parses The String For Variables
			vswprintf_s(text, fmt, ap);						// And Converts Symbols To Actual Numbers
			va_end(ap);											// Results Are Stored In Text
		}

		//Here is some code to split the text that we have been
		//given into a set of lines.  
		//This could be made much neater by using
		//a regular expression library such as the one avliable from
		//boost.org (I've only done it out by hand to avoid complicating
		//this tutorial with unnecessary library dependencies).
		const wchar_t *start_line = text;
		using std::wstring;
		std::vector<wstring> lines;
		const wchar_t *c;

		// temporary code for figuring out the maximum unicode id used in the incomming text
		// wchar_t m=0;
		// for(c=text;*c;c++) {
		//	if(*c>m) m=*c;
		// }

		for (c = text; *c; c++) {
			if (*c == '\n') {
				wstring line;
				for (const wchar_t *n = start_line; n < c; n++) line.append(1, *n);
				lines.push_back(line);
				start_line = c + 1;
			}
		}
		if (start_line) {
			wstring line;
			for (const wchar_t *n = start_line; n < c; n++) line.append(1, *n);
			lines.push_back(line);
		}

		glListBase(font);

		//This is where the text display actually happens.
		//For each line of text we reset the modelview matrix
		//so that the line's text will start in the correct position.
		//Notice that we need to reset the matrix, rather than just translating
		//down by h. This is because when each character is
		//draw it modifies the current matrix so that the next character
		//will be drawn immediatly after it.  
		for (unsigned i = 0; i < lines.size(); i++) {

			glTranslatef(it->second->GetPosition().x, it->second->GetPosition().y - h*i, 0);

			//  The commented out raster position stuff can be useful if you need to
			//  know the length of the text that you are creating.
			//  If you decide to use it make sure to also uncomment the glBitmap command
			//  in make_dlist().
			//	glRasterPos2f(0,0);
			//glCallLists(lines[i].length(), GL_UNSIGNED_BYTE, lines[i].c_str());
			glCallLists(lines[i].length(), GL_UNSIGNED_SHORT, lines[i].c_str());
			//	float rpos[4];
			//	glGetFloatv(GL_CURRENT_RASTER_POSITION ,rpos);
			//	float len=x-rpos[0];
		}
		// freetype::pop_projection_matrix();

		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);

		// Set our "myTextureSampler" sampler to user Texture Unit 0
		glUniform1i(m_texId, 0);

		//first attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, m_pApp->GetGLManager()->GetVertexBuffer());
		glVertexAttribPointer(
			0,						// must be match the layout in the shader
			3,						// size : X+Y+Z => 3
			GL_FLOAT,				// type
			GL_FALSE,				// normalized
			5 * sizeof(GLfloat),	// stride
			(GLvoid*)0				// array buffer offset
			);

		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, m_pApp->GetGLManager()->GetVertexBuffer());
		glVertexAttribPointer(
			1,								// attribute. No particular reason for 1, but must match the layout in the shader.
			2,								// size : U+V => 2
			GL_FLOAT,						// type
			GL_TRUE,						// normalized?
			5 * sizeof(GLfloat),			// stride
			(GLvoid*)(3 * sizeof(GLfloat))	// array buffer offset
			);

		// Draw the triangle
		glDrawArrays(GL_QUADS, 0, 4);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	}

	//Use shader
	//glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_STATIC_DRAW);
	//glUseProgram(m_pApp->GetGLManager()->GetShader(1).m_programID);

	//for (auto it = textList.begin(); it != textList.end(); ++it)
	//{
	//	//Update pipeline
	//	Pipeline((*it).second);

	//	//Initialize matrix
	//	m_matrixID = glGetUniformLocation(m_pApp->GetGLManager()->GetShader(1).m_programID, "projection");

	//	//Implement Matrix
	//	glUniformMatrix4fv(m_matrixID, 1, GL_FALSE, &m_mvp.m_member[0][0]);

	//	//Coloring
	//	vec4 sptColor = ((*it).second->GetColor());
	//	GLuint color = glGetUniformLocation(m_pApp->GetGLManager()->GetShader(1).m_programID, "textColor");
	//	glUniform4f(color, sptColor.x, sptColor.y, sptColor.z, sptColor.w);

	//	// GLuint shape = glGetUniformLocation(m_pApp->GetGLManager()->GetShader(1).m_programID, "Shape");
	//	// glUniform1d(shape, (*it).second->GetSpriteShape());

	//	GLfloat new_x = static_cast<GLfloat>((*it).second->GetPosition().x);

	//	// Iterate all character
	//	std::wstring::const_iterator c;
	//	for (c = (*it).second->GetText().begin(); c != (*it).second->GetText().end(); ++c)
	//	{
	//		Character ch = (*it).second->GetCharacter()[*c];
	//		GLfloat xpos = new_x + ch.Beering.x * (*it).second->GetScale().x;
	//		GLfloat ypos = (*it).second->GetPosition().y - (ch.Size.y - ch.Beering.y) * (*it).second->GetScale().y;

	//		GLfloat w = ch.Size.x * (*it).second->GetScale().x;
	//		GLfloat h = ch.Size.y * (*it).second->GetScale().y;

	//		//Update vbo
	//		GLfloat vertices[6][4] = {
	//			{ xpos, ypos + h, 0.0, 0.0 },
	//			{ xpos, ypos, 0.0, 1.0 },
	//			{ xpos + w, ypos, 1.0, 1.0 },

	//			{ xpos, ypos + h, 0.0, 0.0 },
	//			{ xpos + w, ypos, 1.0, 1.0 },
	//			{ xpos + w, ypos + h, 1.0, 0.0 }
	//		};

	//		glActiveTexture(GL_TEXTURE0);
	//		glBindTexture(GL_TEXTURE_2D, ch.textureID);

	//		glUniform1i(m_texId, 0);

	//		glEnableVertexAttribArray(0);
	//		glBindBuffer(GL_ARRAY_BUFFER, m_pApp->GetGLManager()->GetVertexBuffer());
	//		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	//		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

	//		//Render quad
	//		glDrawArrays(GL_TRIANGLES, 0, 6);
	//		// advance cursor for next glyph
	//		new_x += (ch.Advance >> 6) * (*it).second->GetScale().x;
	//		//Bit shift	
	//	}
	//	glDisableVertexAttribArray(0);
	//}

	//std::cout <<  "\n";
	//}); //Lambda loop expression
}

/******************************************************************************/
/*!
\brief - Shutdown Scene
*/
/******************************************************************************/
void Scene::Shutdown()
{
	// Clear all sprites from the list to draw
	m_DrawList.clear();
	freetype::m_font.Clean();
}

/******************************************************************************/
/*!
\brief - Scene's graphic pipeline

\param sprite - sprite to be drawed
*/
/******************************************************************************/
void Scene::Pipeline(const Sprite* sprite)
{
	//Init model matrix
	mat44 model;
	model.SetIdentity();

	//Setting Perspection
	mat44 projection;
	if (sprite->GetProjectionType() == PERSPECTIVE)
		projection = mat44::Perspective(m_fovy, aspectRatio, m_zNear, m_zFar);
	else
		projection = mat44::Ortho(-m_width / 2.f, m_width / 2.f, -m_height / 2.f, m_height / 2.f, m_zNear, m_zFar);

	//Setting Camera
	mat44 camera = mat44::LookAt(
		vec3(m_camera),
		vec3(m_camera.x, m_camera.y, 0),
		vec3(cosf(Math::DegToRad((m_camera.w + 90.f))),
			sinf(Math::DegToRad((m_camera.w + 90.f))),
			0));

	//Transform model mat
	model = model * mat44::Scale(sprite->GetScale());
	model = model * mat44::Rotate(Math::DegToRad(sprite->GetRotation()), vec3(.0f, .0f, 1.f));
	model = model * mat44::Translate(sprite->GetPosition());

	//calculate fined final matrix
	m_mvp = projection.Transpose() * camera.Transpose() * model.Transpose();
	m_mvp = m_mvp.Transpose();
}

/******************************************************************************/
/*!
\brief - Camera settor

\param camera
*/
/******************************************************************************/
void Scene::SetCamera(const vec4& camera)
{
	m_camera = camera;
}

/******************************************************************************/
/*!
\brief - Camera gettor

\return m_camera
*/
/******************************************************************************/
vec4 Scene::GetCamera(void) const
{
	return m_camera;
}

/******************************************************************************/
/*!
\brief - Background Color settor

\param background
*/
/******************************************************************************/
void Scene::SetBackgroundColor(const vec4& background)
{
	m_bgColor = background;
}

/******************************************************************************/
/*!
\brief - Background Color gettor

\return m_bgColor
*/
/******************************************************************************/
vec4 Scene::GetBackgroundColor(void) const
{
	return m_bgColor;
}

namespace
{
	/******************************************************************************/
	/*!
	\brief - Order algorithm

	\param a - 1st compared
	\param b - 2nd compared

	*/
	/******************************************************************************/
	bool reorder_sprites(const Sprite* a, const Sprite* b)
	{
		// Distinguish ortho type and pers type 
		if (a->GetProjectionType() == ORTHOGONAL && b->GetProjectionType() == PERSPECTIVE)
			return false;
		
		else if (a->GetProjectionType() == PERSPECTIVE && b->GetProjectionType() == ORTHOGONAL)
			return true;
		
		// Return higher z order on
		else
			return a->GetPosition().z < b->GetPosition().z;
	}
}

/******************************************************************************/
/*!
\brief - Order algorithm

*/
/******************************************************************************/
void Scene::ReorderSprites(void)
{
	// Order algorithm
	std::sort(m_DrawList.begin(), m_DrawList.end(), reorder_sprites);
}

/******************************************************************************/
/*!
\brief - Add Sprite to the list

\param newSpt - sprite to put into the list
*/
/******************************************************************************/
void Scene::AddSprite(Sprite* sprite)
{
	// Add sprite by Zorder and Projection type
	auto it = m_DrawList.begin();

	for (; it != m_DrawList.end(); ++it)
	{
		// If new sprite's z order is lower than next sprite
		// Stop here
		if ((*it)->GetPosition().z > sprite->GetPosition().z)
			break;
	}

	// Add sprite to the place where stopped
	m_DrawList.insert(it, sprite);

	// Sort Sprites by projection type and z Order
	ReorderSprites();

}

/******************************************************************************/
/*!
\brief - Add Text to the list

\param text - sprite to put into the list
*/
/******************************************************************************/
void Scene::AddSprite(Text* text)
{
	// Add sprite by Zorder and Projection type
	m_TextList.insert(std::hash_map<int, Text*>::value_type(
		text->GetID(), text));

	text->SetProjectionType(ORTHOGONAL);
}

/******************************************************************************/
/*!
\brief - Delete Sprite from the list

\param id - sprite's id to delete
*/
/******************************************************************************/
void Scene::DeleteSprite(const int id)
{
	//Find the sprite from the vector
	for (auto it = m_DrawList.begin(); it != m_DrawList.end(); ++it)
	{
		// If found same id that client want to get
		if ((*it)->GetID() == id)
		{
			// Delete it
			m_DrawList.erase(it);
			// m_OrderList.erase(it++); 
			break;
		}
	}

	// Sort Sprites by projection type and z Order
	ReorderSprites();
}