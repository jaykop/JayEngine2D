#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//#include <vector>
#include "../Apps/GLManager.h"

class Texture{

public:
	Texture(void);
	~Texture(void);

	void LoadBMP(const char* imagePath);
	void LoadTexture(const char* imagePath);
	GLuint GetTexId(void) const;

private:
	GLuint m_texID;
	//std::vector<unsigned char> m_image;
};

#endif // _TEXTURE_H_