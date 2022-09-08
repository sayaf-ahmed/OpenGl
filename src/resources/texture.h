#pragma once
#include <glad/glad.h>
enum class textureWrapping
{
	none = -1,
	repeat= 0x2901,
	mirroredRepeat = 0X8370, 
	edgeClamp = 0X812F, 
	boarderClamp= 0X812D
};

enum class textureInternalFormat
{

};

enum class textureMagFiltering
{
	none = -1,
	linear = 0x2601, 
	nearest = 0x2600, 
};

enum class textureDimensions
{
	none = -1,
	texture_1D = 0x0DE0,
	texture_2D = 0x0DE1, 
	texture_3D = 0x806F

};
enum class textureMinFiltering
{
	none = -1,
	linear = 0x2601,
	nearest = 0x2600,
	nearMipMapLinear = 0x2702,
	nearMipMapNearest = 0x2700,
	linearMipMapLinear = 0x2703,
	linearMipMapNearest = 0X2701
};

struct textureProperties
{
	textureDimensions type = textureDimensions::texture_2D;
	textureWrapping wrapS = textureWrapping::edgeClamp, 
		            wrapT = textureWrapping::edgeClamp, 
		            wrapR = textureWrapping::none;

	textureMinFiltering minFilter = textureMinFiltering::linearMipMapLinear;
	textureMagFiltering magFilter = textureMagFiltering::linear;

	bool useMipMap = true;

	bool useBoarder = false;
	float boarderCol[4] = {0, 0, 0, 0};

};

class texture
{
private:
	unsigned int m_id;
	textureProperties m_properties;
	int width, height, channels;
	char* m_filePath;

public:
	texture();
	texture(const char* filePath, const textureProperties& props = textureProperties());

	void load(const char* filePath, const textureProperties& props = textureProperties());

	void setProperties(const textureProperties& props);

	void create(int width, int height, const textureProperties& props = textureProperties());

	void createDepthTexture(int width, int height, const textureProperties& props = textureProperties());
	void createStencilTexture(int width, int height, const textureProperties& props = textureProperties());
	void createCombineDepthStencil(int width, int height, const textureProperties& props = textureProperties());
	void use(int slot);
	void destroy();

	unsigned int getId() const;

	~texture();

};

