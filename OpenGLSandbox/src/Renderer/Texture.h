#pragma once

#include <string>

class Texture
{
public:
	Texture(const std::string& path);

	void Bind(uint32_t slot = 0);

	inline uint32_t GetWidth() const { return m_Width; }
	inline uint32_t GetHeight() const { return m_Height; }

private:
	uint32_t m_TextureId;
	uint32_t m_Width, m_Height;
	std::string m_Path;
};
