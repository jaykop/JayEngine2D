#include <vector>
#include <iostream>
#include "Texture.h"
#include "LodePNG\lodepng.h"

Texture::Texture(void)
{
	
}

Texture::~Texture(void)
{

}

void Texture::LoadTexture(const char* imagePath)
{

	unsigned width, height;
	std::vector<unsigned char> image;

	unsigned error = lodepng::decode(image, width, height, imagePath);
	if (error) std::cerr << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
	
	glGenTextures(1, &m_texID);
	glBindTexture(GL_TEXTURE_2D, m_texID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

}

GLuint Texture::GetTexId(void) const
{
	return m_texID;
}

void Texture::LoadBMP(const char* imagePath)
{
	bool loadTexture = true;
	unsigned char header[54], *data;
	unsigned dataPos;
	unsigned width, height;
	unsigned imageSize;

	FILE* file; 
	fopen_s(&file, imagePath, "rb");
	
	//Confirm loaded file
	if (!file) {
		//MessageBox(window, "Cannot load the image!", MB_OK);
		printf("Cannot load the image!\n");
		loadTexture = false;
	};

	//Confirm loaded file's type 
	if (fread(header, 1, 54, file) != 54 || 
		(header[0] != 'B' || header[1]!= 'M')) {
		//MessageBox(window, "This is not BMP!", MB_OK);
		printf("This is not BMP!\n");
		loadTexture = false;
	}

	//if (loadTexture)
	//{
		//Read info from byte array
		dataPos = *(int*)&(header[0x0A]);
		imageSize = *(int*)&(header[0x22]);
		width = *(int*)&(header[0x12]);
		height = *(int*)&(header[0x16]);

		if (!imageSize) imageSize = width * height * 3;	// 3 is for RGB
		if (!dataPos) dataPos = 54;

		data = new unsigned char[imageSize];	//Create a buffer
		fread(data, 1, imageSize, file);		//Read actual data from buffer
		fclose(file);

		m_texID;
		glGenTextures(1, &m_texID);				//Create an GL texture
		glBindTexture(GL_TEXTURE_2D, m_texID);	//Bind created texture

		//Give the image for GL
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

		// OpenGL has now copied the data. Free our own version
		delete[] data;

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		//return m_texID
		//m_texID;
	//}
}

