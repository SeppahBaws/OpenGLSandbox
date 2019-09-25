#include "pch.h"
#include "Texture.h"

#include "../dependencies/stb_image/stb_image.h"
#include <glad/glad.h>

Texture::Texture(const std::string& path)
	: m_Path(path)
{
	// Create OpenGL Texture
	glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureId);
	glBindTexture(GL_TEXTURE_2D, m_TextureId);

	// Texture Options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Load data
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	stbi_uc* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

	ASSERT(data, "Failed to load texture at '{0}'", path);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}

void Texture::Bind(uint32_t slot)
{
	glBindTextureUnit(slot, m_TextureId);
}
