#ifndef _IMAGE_BUF_
#define _IMAGE_BUF_

#include <windows.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <execution>  

#include "Tuples.hpp"
#include "Camera.hpp"
#include "World.hpp"

class ImgBuf {
public:
	int m_width = 0, m_height = 0;
	std::vector<std::vector<Color4>> m_img_data{};

	ImgBuf(int width, int height);
	void writeBMP(const std::string&) const;
	void write_pixel(int width, int height, Color4 color);

	Color4 pixel_at(int, int);
};

ImgBuf render(Camera&, World&, int max_depth);
ImgBuf test_render(Camera&, World&, int max_depth);

#endif