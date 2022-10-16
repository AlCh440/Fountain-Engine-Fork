#pragma once
#include <stdint.h>
#include <libs/glew/include/GL/glew.h>
#include <gl/GL.h>
#include <src/helpers/MathGeoLib/MathGeoLib.h>
#include <src/modules/FileSystem/FSDataTypes.h>

struct OpenGLState {
	bool lighting = false;
	bool cull_faces = true;
	bool depth_test = true;
	bool color_material = true;
	bool texture2D = true;

	uint32_t src_blend = GL_SRC_ALPHA, dst_blend = GL_ONE_MINUS_SRC_ALPHA;
	uint32_t poly_mode = GL_FRONT_AND_BACK, poly_fill = GL_FILL;
};


struct VTX_arr {
	std::vector<float3> vertices;
	GLenum draw_mode = GL_STATIC_DRAW;
};

// Non-Interleaved Mesh - Data Blocks
struct NIMesh {
	std::vector<float3> vertices;
	std::vector<float3> normals;
	std::vector<float2> uvs;

	std::vector<uint32_t> indices;
	std::vector<uint16_t> h_indices; // in case it has halfsized indices

	GLenum draw_mode;
	GLenum polytype;

	KeyPosPair material;
};

struct GPUMesh {
	uint32_t vtx_id = 0;
	uint32_t norm_id = 0;
	uint32_t uvs_id = 0;
	uint32_t num_vtx = 0;

	uint32_t idx_id = 0;
	uint64_t num_idx = 0;

	KeyPosPair material;
};

struct Texture {
	char* bytes;
	uint32_t size;
	uint32_t w, h;
	uint32_t format;
	uint32_t unit_size;
	uint32_t unit_type;
};

struct GPUTex {
	uint32_t img_id;
	uint32_t w, h;
};

struct MaterialState {
	bool cull_faces = true;
	bool texture2D = true;
	uint32_t shading_model = GL_SMOOTH;
	uint32_t src_blend = GL_SRC_ALPHA, dst_blend = GL_ONE_MINUS_SRC_ALPHA;
};

struct TexRelation {
	uint64_t tex_uid;
	uint32_t type; // Be it Normal Map, Albedo,...
};

struct Material {
	std::string name;
	float3 diffuse;
	float3 specular;
	float shininess;
	float shine_strength;

	float3 ambient;
	float3 emissive;
	
	float3 transparent;
	float opacity;

	float3 reflective;
	float reflectivity;

	float refractiveness;

	std::vector<TexRelation> textures;

};

struct GPUMat {
	const Material* mat;
	KeyPosPair disk_id;
	std::vector<TexRelation> gpu_textures;
};

struct GPUFBO {
	GLuint framebuffer_id;
	GLuint renderbuffer_id;
	GPUTex attachment;
};