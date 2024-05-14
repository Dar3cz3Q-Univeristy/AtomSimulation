#pragma once
#include <iostream>

#include "stb_image/stb_image.h"

#include "Renderer.h"

class Texture
{
public:
	Texture() {};
	virtual ~Texture() {};

	virtual void Bind(unsigned int slot = 0) const = 0;
	virtual void Unbind() const = 0;
	virtual inline int GetWidth() const = 0;
	virtual inline int GetHeight() const = 0;
};

