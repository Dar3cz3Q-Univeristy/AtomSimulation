#pragma once
#include "Texture.h"

class TextureCubeMap : public Texture
{
public:
	TextureCubeMap();
	~TextureCubeMap();

	void Init(const std::string& folderpath, const std::string& extension);
	void Bind(unsigned int slot = 0) const override;
	void Unbind() const override;

	inline int GetWidth() const override { return m_SideLength; };
	inline int GetHeight() const override { return m_SideLength; };
private:
	unsigned int m_RendererID;
	std::string m_FolderPath;
	std::string m_Extension;
	static std::string m_Faces[6];
	unsigned char* m_LocalBuffer;
	int m_SideLength, m_BPP;
};

