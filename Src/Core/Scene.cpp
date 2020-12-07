#include "Scene.h"

void Scene::CleanUp()
{
	for (int i = 0; i < loadedEntities.size(); i++)
	{
		for (int j = 0; j < loadedEntities[i].components.size(); j++)
		{
			delete loadedEntities[i].components[j];
		}
	}
}

void DirectX::to_json(json& j, const XMFLOAT3& vector)
{
	j = json{ {"x", vector.x}, {"y", vector.y}, {"z", vector.z} };
}

void DirectX::to_json(json& j, const XMFLOAT4& vector)
{
	j = json{ {"x", vector.x}, {"y", vector.y}, {"z", vector.z}, {"w", vector.w} };
}

void DirectX::from_json(const json& j, XMFLOAT3& vector)
{
	vector.x = j["x"];
	vector.y = j["y"];
	vector.z = j["z"];
}

void DirectX::from_json(const json& j, XMFLOAT4& vector)
{
	vector.x = j["x"];
	vector.y = j["y"];
	vector.z = j["z"];
	vector.w = j["w"];
}

void to_json(json& j, const std::vector<LoadedComponent*>& components)
{
	for (int i = 0; i < components.size(); i++)
	{
		switch (components[i]->type)
		{
		case MATERIAL:
			j += json{ *(LoadedMaterial*)components[i] };
			break;

		case MESH:
			j += json{ *(LoadedMesh*)components[i] };
			break;

		case RASTER_STATE:
			j += json{ *(LoadedRasterState*)components[i] };
			break;

		case ROTATOR:
			j += json{ *(LoadedRotator*)components[i] };
			break;

		case CAMERA:
			j += json{ *(LoadedCamera*)components[i] };
			break;

		case SCENE_LIGHT:
			j += json{ *(LoadedLight*)components[i] };
			break;

		default:
			j += json{ *components[i] };
			break;
		}
	}
}

void to_json(json& j, const LoadedMaterial& material)
{
	j = json{ {"shader", material.shader}, {"diffuse", material.diffuse}, {"ambient",material.ambient}, {"specular",material.specular}, {"isTransparent",material.isTransparent},
	{"diffuseMtrl",material.diffuseMtrl}, { "ambientMtrl", material.ambientMtrl }, { "specularMtrl",material.specularMtrl }, {"type", material.type} };
};

void to_json(json& j, const LoadedMesh& mesh)
{
	j = json{ {"mesh", mesh.mesh}, {"type", mesh.type} };
}

void to_json(json& j, const LoadedRasterState& rasterState)
{
	j = json{ {"startInWireframe", rasterState.startInWireframe}, {"type", rasterState.type} };
}

void to_json(json& j, const LoadedRotator& rotator)
{
	j = json{ {"tScale", rotator.tScale}, {"type", rotator.type} };
}

void to_json(json& j, const LoadedCamera& camera)
{
	j = json{ {"nearDepth", camera.nearDepth}, {"farDepth", camera.farDepth}, {"type", camera.type} };
}

void to_json(json& j, const LoadedEntity& entity)
{
	j = json{ {"transform", entity.transform}, {"parent", entity.parent}, {"components", entity.components}, {"isSelectable", entity.selectable} };
}

void to_json(json& j, const Transform& transform)
{
	j = json{ {"Position", transform.Position},{"Rotation", transform.Rotation},{"Scale", transform.Scale} };
}

void to_json(json& j, const LoadedComponent& component)
{
	j = json{ {"type", component.type} };
}

void to_json(json& j, const LoadedShader& shader)
{
	j = json{ {"path", shader.path}, {"type", shader.type} };
}

void to_json(json& j, const Scene& scene)
{
	j = json{ {"version", scene.version}, {"shaderPaths", scene.shaderPaths}, {"modelsPaths", scene.modelsPaths}, {"texturePaths", scene.texturePaths}, {"loadedEntities", scene.loadedEntities} };
}

void to_json(json& j, LoadedLight& light)
{
	j = json{ {"type", light.type}, {"Position", light.sceneLight.GetPosition() }, {"Direction", light.sceneLight.GetDirection() }, {"Diffuse", light.sceneLight.GetDiffuseColor() }, {"Ambient", light.sceneLight.GetAmbientColor() },
	{"Specular", light.sceneLight.GetSpecularColor() }, {"SpecularPower", light.sceneLight.GetSpecularPower() }, 
	{"DiffuseStrength", light.sceneLight.GetDiffuseStrength() }, {"AmbientStrength", light.sceneLight.GetAmbientStrength() }, {"SpecularStrength", light.sceneLight.GetSpecularStrength() }, };
}

void from_json(const json& j, std::vector<LoadedComponent*>& components)
{
	for (int i = 0; i < j.size(); i++)
	{
		LoadedComponent component = j[i][0];
		LoadedComponent* pComponent;

		LoadedMaterial material;
		LoadedMesh mesh;
		LoadedRasterState rasterState;
		LoadedRotator rotator;
		LoadedCamera camera;
		LoadedLight light;

		switch (component.type)
		{
		case MATERIAL:
			material = j[i][0];
			pComponent = new LoadedMaterial(material);
			break;

		case MESH:
			mesh = j[i][0];
			pComponent = new LoadedMesh(mesh);
			break;

		case RASTER_STATE:
			rasterState = j[i][0];
			pComponent = new LoadedRasterState(rasterState);
			break;

		case ROTATOR:
			rotator = j[i][0];
			pComponent = new LoadedRotator(rotator);
			break;

		case CAMERA:
			camera = j[i][0];
			pComponent = new LoadedCamera(camera);
			break;
		
		case SCENE_LIGHT:
			light = j[i][0];
			pComponent = new LoadedLight(light);
			break;

		default:
			pComponent = new LoadedComponent(component);
			break;
		}

		components.push_back(pComponent);
	}
}

void from_json(const json& j, LoadedMaterial& material)
{
	material.shader = j["shader"];
	material.diffuse = j["diffuse"];
	material.ambient = j["ambient"];
	material.specular = j["specular"];
	material.isTransparent = j["isTransparent"];
	material.diffuseMtrl = j["diffuseMtrl"];
	material.ambientMtrl = j["ambientMtrl"];
	material.specularMtrl = j["specularMtrl"];
	material.type = j["type"];
}

void from_json(const json& j, LoadedMesh& mesh)
{
	mesh.mesh = j["mesh"];
	mesh.type = j["type"];
}

void from_json(const json& j, LoadedRasterState& rasterState)
{
	rasterState.startInWireframe = j["startInWireframe"];
	rasterState.type = j["type"];
}

void from_json(const json& j, LoadedRotator& rotator)
{
	rotator.tScale = j["tScale"];
	rotator.type = j["type"];
}

void from_json(const json& j, LoadedCamera& camera)
{
	camera.farDepth = j["farDepth"];
	camera.nearDepth = j["nearDepth"];
	camera.type = j["type"];
}

void from_json(const json& j, LoadedEntity& entity)
{
	entity.transform = j["transform"];
	entity.parent = j["parent"];
	entity.components = j["components"];
	entity.selectable = j["isSelectable"];
}

void from_json(const json& j, Transform& transform)
{
	transform.Position = j["Position"];
	transform.Scale = j["Scale"];
	transform.Rotation = j["Rotation"];
}

void from_json(const json& j, LoadedComponent& component)
{
	component.type = j["type"];
}

void from_json(const json& j, LoadedShader& shader)
{
	shader.path = j["path"];
	shader.type = j["type"];
}

void from_json(const json& j, Scene& scene)
{
	scene.version = j["version"];
	scene.shaderPaths = j["shaderPaths"].get<std::vector<LoadedShader>>();
	scene.modelsPaths = j["modelsPaths"].get<std::vector<std::string>>();
	scene.texturePaths = j["texturePaths"].get<std::vector<std::string>>();
	scene.loadedEntities = j["loadedEntities"].get<std::vector<LoadedEntity>>();
}

void from_json(const json& j, LoadedLight& light)
{
	light.sceneLight.SetPosition(j["Position"]);
	light.sceneLight.SetDirection(j["Direction"]);
	light.sceneLight.SetDiffuse(j["Diffuse"]);
	light.sceneLight.SetAmbient(j["Ambient"]);
	light.sceneLight.SetSpecular(j["Specular"]);
	light.sceneLight.SetSpecularPower(j["SpecularPower"]);
	light.sceneLight.SetDiffuseStrength(j["DiffuseStrength"]);
	light.sceneLight.SetAmbientStrength(j["AmbientStrength"]);
	light.sceneLight.SetSpecularStrength(j["SpecularStrength"]);
}
