#pragma once

#include "GLView.h"
#include <gl3w/gl3w.h>

class GLState
{
public:
	GLState();
	~GLState();

private:
	GLView view;
};