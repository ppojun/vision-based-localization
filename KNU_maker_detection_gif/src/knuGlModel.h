#ifndef KNUGLMODEL_H
#define KNUGLMODEL_H

#include <GL/gl3w.h>
#include <glm/glm.hpp>

#include <vector>

namespace SYE {
	class Shader;
	struct Vertex;
}

// 다양한 Opengl class가 늘어나는 것에 대비하여 공통 변수, 함수 등을 모아둠.
class KOglBase {
	private:
	protected:
		GLuint VAO, VBO;
		glm::mat4 mMatModel = glm::mat4(1.0f);	//초기 위치(Model viewer matrix)
		SYE::Shader *pShader;
		std::vector<SYE::Vertex> vertices;
		void setVAO();
	public:
		KOglBase() {};
		virtual ~KOglBase() {};

		virtual void render(glm::mat4 view, glm::mat4 proj) {};
};

class KOglGrid: public KOglBase {
	private:
	protected:
	public:
		KOglGrid(
				SYE::Shader *pShader
				, unsigned int rows = 100
				, unsigned int cols = 100
				, float unit = 1.0f
				, glm::mat4 mv = glm::mat4(1.0f)
				, glm::vec3 color = glm::vec3(0.7f, 0.7f, 0.7f)
				);
		virtual ~KOglGrid();
		void render(glm::mat4 view, glm::mat4 proj);
};

// 기본 도형은 미리 만들어서 쓰기 편하게...

enum eKOglObjectType {
	KObjTriangle = 0,
	KObjRectangle,
	KObjCircle,
};

class KOglObject: public KOglBase {
	private:
	protected:
	public:
		KOglObject();
		virtual ~KOglObject();

		void initialize(
				SYE::Shader *pShader
				, eKOglObjectType type
				, glm::vec3 ptRD = glm::vec3(0, 10, 0)	// Size, 원점은 고정, Right-Down 값만 지정함.
				);

};

#endif
