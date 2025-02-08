#define __MT_BSP_MAP_CPP__

#include <fstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "common.h"
#include "engine/math/Math.h"
#include "graphic/Graphic.h"
#include "BspMap.h"

#include "graphic/buffer/VertexArrayObject.h"
#include "graphic/texture/Texture.h"

#include "graphic/bsp/bsp5/bsp.hpp"

using namespace std;
using namespace mt;
using namespace mt::graphic;

ShaderProgram BspMap::shader;


class BspMap::BspMapImpl {
public:
	VertexArrayObject VAO;

	Bsp* map_;
};

BspMap::BspMap() {
	// Component
	// impl->map = new bsp("./res/bsp/de_dust2.bsp");
	// impl->map = new bsp("./res/bsp/css_cs_deadhouse_1.0/cs_deadhouse.bsp");
	// impl->map = new bsp("./res/bsp/source/CS_Sklad_Top-X/maps/cs_sklad_top-x.bsp");

	// Implement
	impl = new BspMapImpl();
}

BspMap::~BspMap() {
	// Component
	// delete impl->map;

	// Implement
	delete impl;
}

void BspMap::init(string name) {
	impl->map_ = new Bsp("./res/EngineQuakeIII/maps/test1.bsp");// #TODO tao nhung chua xoa
}

void BspMap::update() {
}

void BspMap::render() {

	this->shader.use();

	// Model Mat
	mat4 modelMat;
	// modelMat.rotate(quat(Math::toRadian(-90.0), vec3 (1,0,0)));
	// modelMat.scale(1.0f);
	// Tham khao: glUniform1f(ShaderManager::GetInstance()->UseShaderProgram(ShaderManager::BasicShader).uniforms[WorldScaleFactor], );
	this->shader.setMat4(2, modelMat);

	// // Graphic::ins.wireframe(true);
	// Graphic::ins.cullFaceToogle(false);

	// // impl->texture.bind();

	vec3 camPos = Graphic::ins.camera.position;
	const glm::vec4 _camPos(camPos.x, camPos.y, camPos.z, 1.0f);
	std::vector<bsp_face *> renderables_ = impl->map_->ComputeVisibleFaces(_camPos);

  glBindBuffer(GL_ARRAY_BUFFER, impl->map_->vboId);


  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, impl->map_->iboId);
  glEnableVertexAttribArray(2);
  for (unsigned int i = 0; i < renderables_.size(); ++i) {
		bsp_face *face = renderables_[i];
		const bsp_face &current_face = *face;

		// Shader *shader = shaderLoader::GetShader(current_face.texture); // #TODO

		// if (shader->q3_shader_.stages_.size() ==
		// 		0) // skip no shader / no draw. should be sorted out before.
		// {
		// 	return;
		// }

		// does everything in here need to be done every time? move into the
		// conditional below?
		// SetupShader(shader, current_face.lm_index); // #TODO

		// if (current_shader_ != shader) {
		// 	glUseProgram(shader->shader_);
		// 	current_shader_ = shader;
		// }

		// if (shader->time_idx_ != -1) { // #TODO
		// 	glUniform1f(shader->time_idx_, time_);
		// }

		// glUniformMatrix4fv(shader->projection_idx_, 1, false, // #TODO
		// 									glm::value_ptr(projectionmatrix_));
		// glUniformMatrix4fv(shader->model_idx_, 1, false,
		// 									glm::value_ptr(modelmatrix_));

		if (current_face.type == POLYGON || current_face.type == MESH) {
			const bsp_face &current_face = *face;
			const int offset = current_face.vertex;

			if (offset >= impl->map_->num_vertexes_)
				return;

			// Shader &shader = *current_shader_; // #TODO

			// shader.position_idx_
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
														sizeof(bsp_vertex),
														reinterpret_cast<void *>(offset * sizeof(bsp_vertex)));

			// shader.tex_coord_idx_
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
														sizeof(bsp_vertex),
														reinterpret_cast<void *>(offset * sizeof(bsp_vertex) +
																										sizeof(glm::vec3)));

			// shader.lm_coord_idx_
			glVertexAttribPointer(
					2, 2, GL_FLOAT, GL_FALSE, sizeof(bsp_vertex),
					reinterpret_cast<void *>(offset * sizeof(bsp_vertex) + sizeof(glm::vec3) +
																	sizeof(glm::vec2)));

			// shader.color_idx_
			glVertexAttribPointer(
					3, 4, GL_BYTE, GL_FALSE, sizeof(bsp_vertex),
					reinterpret_cast<void *>(offset * sizeof(bsp_vertex) + sizeof(glm::vec3) +
																	sizeof(glm::vec2) + sizeof(glm::vec2) +
																	sizeof(glm::vec3)));

			glDrawElements(
					GL_TRIANGLES, current_face.num_meshverts, GL_UNSIGNED_INT,
					reinterpret_cast<void *>(current_face.meshvert * sizeof(bsp_meshvert)));
		}
		else if (current_face.type == PATCH) {
			// Shader &shader = *current_shader_; // #TODO
			auto offset = face->vertex;

			// glUniform1ui(shader.patchWidth_, face->size[0]); // #TODO
			// glUniform1ui(shader.patchHeight_, face->size[1]);

			if ((face->size[0] == 15 || face->size[1] == 15) ||
					(face->size[0] == 9 && face->size[1] == 5)) {
				// logger::Debug("patch size: %d %d %d", face->size[0], face->size[1],
				// 							face->num_vertices);
				return;
			}

			if (face->size[0] * face->size[1] != face->num_vertices) {
				// logger::Debug("VERY BAD VERY BAD");
				return;
			}

			// shader.position_idx_
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(bsp_vertex),
					reinterpret_cast<void *>(offset * sizeof(bsp_vertex)));

			// shader.tex_coord_idx_
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(bsp_vertex),
					reinterpret_cast<void *>(offset * sizeof(bsp_vertex) + sizeof(glm::vec3)));

			// shader.lm_coord_idx_
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(bsp_vertex),
					reinterpret_cast<void *>(offset * sizeof(bsp_vertex) + sizeof(glm::vec3) + sizeof(glm::vec2)));

			// shader.color_idx_
			glVertexAttribPointer(3, 4, GL_BYTE, GL_FALSE, sizeof(bsp_vertex),
					reinterpret_cast<void *>(offset * sizeof(bsp_vertex)
					+ sizeof(glm::vec3) + sizeof(glm::vec2) + sizeof(glm::vec2) + sizeof(glm::vec3)));

			float subdivisions[] = {10.0f, 10.0f, 10.0f, 10.0f};
			glPatchParameterfv(GL_PATCH_DEFAULT_OUTER_LEVEL, subdivisions);
			glPatchParameterfv(GL_PATCH_DEFAULT_INNER_LEVEL, subdivisions);
			glPatchParameteri(GL_PATCH_VERTICES, face->num_vertices);
			glDrawArrays(GL_PATCHES, 0, face->num_vertices);
		}
		else if (current_face.type == BILLBOARD) {
			// RenderBillboard();
		}
  }

	// impl->VAO.bind();
	// impl->VAO.drawElementTriangle();
	// impl->VAO.unbind();

	// // Graphic::ins.wireframe(false);
	// Graphic::ins.cullFaceToogle(true);
}
