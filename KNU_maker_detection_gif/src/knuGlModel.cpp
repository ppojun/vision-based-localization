#include "knuGlModel.h"

#include "yeAssimp.h"

void KOglBase::setVAO() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(SYE::Vertex), &vertices[0], GL_STATIC_DRAW);

		//Vertex struct 순서데로...
		// vertex positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SYE::Vertex), (void*)0);
		// vertex colors
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(SYE::Vertex), (void*)offsetof(SYE::Vertex, Color));

		/*
		// vertex texture coords
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

		// vertex tangent
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
		// vertex bitangent
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
		*/
	glBindVertexArray(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

KOglGrid::KOglGrid( SYE::Shader *pShader, unsigned int rows, unsigned int cols, float unit, glm::mat4 mv, glm::vec3 color) {
	this->pShader = pShader;
	this->mMatModel = mv;

	glm::vec3	stPos;
	stPos.x = (-float(cols)/2)*unit;
	stPos.y = (-float(rows)/2)*unit;
	stPos.z = 0;

	SYE::Vertex vertex;
	for(int i=0; i <= cols; i++) {
		vertex.Position.x = stPos.x + (i*unit);
		vertex.Position.y = stPos.y;
		vertex.Position.z = 0;
		vertex.Color = color;
		vertices.push_back(vertex);

		vertex.Position.x = stPos.x + (i*unit);
		vertex.Position.y = -stPos.y;
		vertex.Position.z = 0;
		vertex.Color = color;
		vertices.push_back(vertex);
	}

	for(int i=0; i <= rows; i++) {

		vertex.Position.x = stPos.x;
		vertex.Position.y = stPos.y + (i*unit);
		vertex.Position.z = 0;
		vertex.Color = color;
		vertices.push_back(vertex);

		vertex.Position.x = -stPos.x;
		vertex.Position.y = stPos.y + (i*unit);
		vertex.Position.z = 0;
		vertex.Color = color;
		vertices.push_back(vertex);
	}

	// std의 forEach 구문 테스트 용.
	std::for_each(vertices.begin(), vertices.end(), [](SYE::Vertex &vertex) {
			//std::cout<<glm::to_string(vertex.Position)<<std::endl;
			//std::cout<<glm::to_string(vertex.Color)<<std::endl;
			});

	setVAO();
}

KOglGrid::~KOglGrid() {
}

void KOglGrid::render(glm::mat4 view, glm::mat4 proj) {
	//printf("Render...\n");
	if(pShader!=nullptr) {
		pShader->use();
		pShader->setMat4("view", view);
		pShader->setMat4("projection", proj);
		pShader->setMat4("model", mMatModel);

		glBindVertexArray(VAO);
		glDrawArrays(GL_LINES, 0, vertices.size());
		//printf("-----------[%lu]\n", vertices.size());
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

KOglObject::KOglObject() {
}

KOglObject::~KOglObject() {
}

void KOglObject::initialize(SYE::Shader *pShader, eKOglObjectType type, glm::vec3 ptRD) {
}
