#ifndef _OBJPARSER_H_
#define _OBJPARSER_H_

#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>

#include "Shapes.hpp"

class ObjParser
{
private:
	struct VType
	{
		float x, y, z;

	};
	struct TType
	{
		float tu, tv;
	};
	struct NType
	{
		float nx, ny, nz;
	};
	struct ToPrint
	{
		uint32_t v, vt, vn;
		void sub_one() { v -= 1; vt -= 1; vn -= 1; }
	};

	std::vector<VType> m_vertexes;
	std::vector<TType> m_textures;
	std::vector<NType> m_normals;
	std::vector<ToPrint> m_faces;


public:
	Group* parse(const std::string);
};

#endif