#include "Vector3.h"
#include <string>

namespace phoenix
{
	const Vector3 one;
	const Vector3 zero;
	const Vector3 up;
	const Vector3 down;
	const Vector3 left;
	const Vector3 right;

	std::istream& operator >> (std::istream& stream, Vector3& v)
	{
		std::string line;
		std::getline(stream, line);

		std::string xs = line.substr(line.find("{") + 1, line.find(",") - (line.find("{") - 1));
		v.x = std::stof(xs);

		std::string ys = line.substr(line.find(",") + 1, line.find("}") - (line.find(",") + 1));
		v.y = std::stof(ys);

		return stream;
	}

	/*std::ostream& operator << (std::ostream& stream, const Vector3& v, const Vector3& z)
	{
		stream << v.x << " " << v.y << " " << v.z << " ";

		return stream;
	}*/
}