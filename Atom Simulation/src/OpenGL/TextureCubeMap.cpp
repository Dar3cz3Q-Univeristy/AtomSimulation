#include "TextureCubeMap.h"

std::string TextureCubeMap::m_Faces[] = { "right", "left", "top", "bottom", "back", "front" };

TextureCubeMap::TextureCubeMap()
	: m_RendererID(0), m_FolderPath(""), m_Extension(""), m_LocalBuffer(nullptr), m_SideLength(0), m_BPP(0)
{
	GLCall(glGenTextures(1, &m_RendererID));
}

TextureCubeMap::~TextureCubeMap()
{
	GLCall(glDeleteTextures(1, &m_RendererID));
}

void TextureCubeMap::Init(const std::string& folderpath, const std::string& extension)
{
	m_FolderPath = folderpath;
	m_Extension = extension;

	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID));

	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));

	for (unsigned int i = 0; i < 6; i++) {
		int width, height;

		std::string location = m_FolderPath + "/" + m_Faces[i] + "." + m_Extension;
		m_LocalBuffer = stbi_load(location.c_str(), &width, &height, &m_BPP, 4);

		if (width != height) {
			std::cout << "Failure: image is not a square: '" << location << "'!\n";
			stbi_image_free(m_LocalBuffer);
			break;
		}

		if (i == 0) {
			m_SideLength = width;
		}

		if (m_SideLength != width) {
			std::cout << "Failure: image: '" << location << "' is not the same size as 'right." << extension << "'!\n";
			stbi_image_free(m_LocalBuffer);
			break;
		}

		if (m_LocalBuffer) {
			stbi_set_flip_vertically_on_load(0);
			GLCall(glTexImage2D(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0,
				GL_RGBA8,
				width,
				height,
				0,
				GL_RGBA,
				GL_UNSIGNED_BYTE,
				m_LocalBuffer
			));
		}
		else {
			std::cout << "Failure: could not load texture: '" << location << "'!\n";
		}

		stbi_image_free(m_LocalBuffer);
	}
}

void TextureCubeMap::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID));
}

void TextureCubeMap::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
}
