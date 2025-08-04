#ifndef _IMAGE_BUF_
#define _IMAGE_BUF_

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
	std::vector<std::vector<tuple>> m_img_data{};

	ImgBuf(int width, int height);
	void writeBMP(const std::string&) const;
	void write_pixel(int width, int height, tuple color);

	tuple pixel_at(int, int);
};

ImgBuf render(Camera&, world&);

#endif