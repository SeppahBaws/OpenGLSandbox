#pragma once

class Renderer
{
public:
	struct ViewportData
	{
		int x;
		int y;
		int width;
		int height;
	};
	
public:
	static void Init(const ViewportData& vp);
	
	static void Clear(float r, float g, float b, float a);

	static void Render(unsigned int VAO, unsigned int EBO, int count);

public:
	static unsigned int s_DemoShader;
};
