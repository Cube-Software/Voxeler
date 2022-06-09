#include "fr.hpp"

namespace fr {
	bool GLLogCall(const char* function, const char* file, int line) {
		while (GLenum error = glGetError()) {
			std::cout << "GL Error! :"<<  file << " Line: "<< line << std::endl;
			return false;
		}
		return true;
	}

	void GLClearError() {
		while (glGetError() != GL_NO_ERROR);
	}
}