#pragma once
#include "Structures.h"
#include <vector>
#include "json.hpp"
#include "Light.h"
using json = nlohmann::json;

enum ComponentType
{
	MATERIAL, MESH, RENDERER, RASTER_STATE, ROTATOR, RENDERING_BUFFER, SELECTION_HIDE, CAMERA, CAMERA_CONTROLLER, SCENE_LIGHT, NO_TYPE
};

struct LoadedComponent
{
	int type;

	LoadedComponent(ComponentType type) :
		type(type)
	{}

	LoadedComponent() :
		type(NO_TYPE)
	{}
};

struct LoadedMaterial :LoadedComponent
{
	int shader;
	int diffuse;
	int ambient;
	int specular;
	bool isTransparent;
	XMFLOAT4 diffuseMtrl;
	XMFLOAT4 ambientMtrl;
	XMFLOAT4 specularMtrl;

	LoadedMaterial(int shader, int diffuse, int ambient, int specular, bool isTransparent, XMFLOAT4 diffuseMtrl, XMFLOAT4 ambientMtrl, XMFLOAT4 specularMtrl) :
		LoadedComponent(MATERIAL), shader(shader), diffuse(diffuse), ambient(ambient), specular(specular), isTransparent(isTransparent), diffuseMtrl(diffuseMtrl), ambientMtrl(ambientMtrl), specularMtrl(specularMtrl)
	{}

	LoadedMaterial() :
		LoadedComponent(MATERIAL)
	{}
};

struct LoadedMesh : LoadedComponent
{
	int mesh;

	LoadedMesh(int mesh) :
		LoadedComponent(MESH), mesh(mesh)
	{}

	LoadedMesh() :
		LoadedComponent(MESH)
	{}
};

struct LoadedRasterState :LoadedComponent
{
	bool startInWireframe;

	LoadedRasterState(bool startInWireframe) :
		LoadedComponent(RASTER_STATE), startInWireframe(startInWireframe)
	{}

	LoadedRasterState() :
		LoadedComponent(RASTER_STATE)
	{}
};

struct LoadedRotator :LoadedComponent
{
	XMFLOAT3 tScale;

	LoadedRotator(XMFLOAT3 tScale) :
		LoadedComponent(ROTATOR), tScale(tScale)
	{}

	LoadedRotator() :
		LoadedComponent(ROTATOR)
	{}
};

struct LoadedCamera :LoadedComponent
{
	float nearDepth;
	float farDepth;

	LoadedCamera(float nearDepth, float farDepth) :
		LoadedComponent(CAMERA), nearDepth(nearDepth), farDepth(farDepth)
	{}

	LoadedCamera() :LoadedComponent(CAMERA)
	{}
};

struct LoadedLight :LoadedComponent
{
	Light sceneLight;

	LoadedLight() :
		LoadedComponent(SCENE_LIGHT)
	{}
};


struct LoadedEntity
{
	Transform transform;
	int parent;
	std::vector<LoadedComponent*> components;

	LoadedEntity(Transform transform, int parent, std::vector<LoadedComponent*> components) :
		transform(transform), parent(parent), components(components)
	{
	}

	LoadedEntity() :
		transform(XMFLOAT3(0, 0, 0), XMFLOAT3(0, 0, 0), XMFLOAT3(0, 0, 0)), parent(-1)
	{}
};

enum ShaderType { LIGHT, COLOR };

struct LoadedShader {
	std::string path;
	ShaderType type;

	LoadedShader()
	{};

	LoadedShader(const std::string& path, ShaderType type) :
		path(path), type(type)
	{};
};

struct Scene
{
	float version;
	std::vector<LoadedEntity> loadedEntities;
	std::vector<LoadedShader> shaderPaths;
	std::vector<std::string> modelsPaths;
	std::vector<std::string> texturePaths;

	void CleanUp();
};

namespace DirectX
{
	void to_json(json& j, const XMFLOAT3& vector);
	void to_json(json& j, const XMFLOAT4& vector);

	void from_json(const json& j, XMFLOAT3& vector);
	void from_json(const json& j, XMFLOAT4& vector);
}

void to_json(json& j, const std::vector<LoadedComponent*>& components);
void to_json(json& j, const LoadedMaterial& material);
void to_json(json& j, const LoadedMesh& mesh);
void to_json(json& j, const LoadedRasterState& rasterState);
void to_json(json& j, const LoadedRotator& rotator);
void to_json(json& j, const LoadedCamera& camera);
void to_json(json& j, const LoadedEntity& entity);
void to_json(json& j, const Transform& transform);
void to_json(json& j, const LoadedComponent& component);
void to_json(json& j, const LoadedShader& shader);
void to_json(json& j, const Scene& scene);
void to_json(json& j, LoadedLight& light);

void from_json(const json& j, std::vector<LoadedComponent*>& components);
void from_json(const json& j, LoadedMaterial& material);
void from_json(const json& j, LoadedMesh& mesh);
void from_json(const json& j, LoadedRasterState& rasterState);
void from_json(const json& j, LoadedRotator& rotator);
void from_json(const json& j, LoadedCamera& camera);
void from_json(const json& j, LoadedEntity& entity);
void from_json(const json& j, Transform& transform);
void from_json(const json& j, LoadedComponent& component);
void from_json(const json& j, LoadedShader& shader);
void from_json(const json& j, Scene& scene);
void from_json(const json& j, LoadedLight& light);