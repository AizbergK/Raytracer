#include "ObjParser.hpp"

Group* ObjParser::parse(const std::string file_path)
{
	if (file_path.substr(file_path.find_last_of('.')) == ".obj")
	{
		std::ifstream fin(file_path);
		std::string line{};
		while (getline(fin, line))
		{
			if (line == "" || line[0] == '#') continue;
			char c1, c2;
			std::stringstream ss{ line };
			ss.get(c1);
			ss.get(c2);
			if (c1 == 'v' && c2 == ' ')
			{
				VType vrtx;
				ss >> vrtx.x;
				ss >> vrtx.y;
				ss >> vrtx.z;
				m_vertexes.emplace_back(vrtx);
			}
			if (c1 == 'f')
			{
				ToPrint first_ver, last_ver, next_ver;
				ss >> first_ver.v;
				ss >> c2;
				ss >> first_ver.vt;
				ss >> c2;
				ss >> first_ver.vn;
				ss.get(c2);

				ss >> last_ver.v;
				ss >> c2;
				ss >> last_ver.vt;
				ss >> c2;
				ss >> last_ver.vn;
				ss.get(c2);

				ss >> next_ver.v;
				ss >> c2;
				ss >> next_ver.vt;
				ss >> c2;
				ss >> next_ver.vn;
				ss.get(c2);

				first_ver.sub_one();
				last_ver.sub_one();
				next_ver.sub_one();

				m_faces.emplace_back(first_ver);
				m_faces.emplace_back(last_ver);
				m_faces.emplace_back(next_ver);

				while (line.size() - ss.tellg() > 1 && c2 == ' ')
				{
					last_ver = next_ver;
					ss >> next_ver.v;
					ss >> c2;
					ss >> next_ver.vt;
					ss >> c2;
					ss >> next_ver.vn;
					ss.get(c2);

					next_ver.sub_one();

					m_faces.emplace_back(first_ver);
					m_faces.emplace_back(last_ver);
					m_faces.emplace_back(next_ver);
				}
			}
		}
		std::string output_file{ "./" + file_path.substr(0, file_path.find_last_of('.')) + ".txt" };
		std::ofstream fout(output_file);

		fout << "Vertex Count : " << m_faces.size() << "\n\nData :\n\n";

		Group* obj = new Group;
		for (int i = 0; i < m_faces.size(); i += 3)
		{
			Point4 pt1{ m_vertexes[m_faces[i].v].x, m_vertexes[m_faces[i].v].y, m_vertexes[m_faces[i].v].z };
			Point4 pt2{ m_vertexes[m_faces[i + 1].v].x, m_vertexes[m_faces[i + 1].v].y, m_vertexes[m_faces[i + 1].v].z };
			Point4 pt3{ m_vertexes[m_faces[i + 2].v].x, m_vertexes[m_faces[i + 2].v].y, m_vertexes[m_faces[i + 2].v].z };
			auto r = static_cast <float>(rand()) / static_cast <double>(RAND_MAX);
			auto g = static_cast <float>(rand()) / static_cast <double>(RAND_MAX);
			auto b = static_cast <float>(rand()) / static_cast <double>(RAND_MAX);
			Material rand_color{ Color4(r, g, b) };
			Triangle tr{ pt1, pt2, pt3, rand_color };

			obj->add_child(tr);
		}
		return obj;
	}
	else
	{
		std::cout << "File is not of OBJ format";
		throw;
	}
}
