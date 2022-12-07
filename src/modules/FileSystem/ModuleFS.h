#pragma once
#include "../Module.h"

#include <src/helpers/JSON/parson.h>
#include "FSDataTypes.h"
#include <unordered_map>
#include "../ECS/ModuleECS.h"
typedef std::pair<uint64_t, WatchedData> allocpair;


class ModuleFS : public Module {
	std::vector<JSON_Value*> jsons;
public:
	ModuleFS() : Module("filesystem", true) {};
	~ModuleFS() {};

	bool Init();

	bool CleanUp();

	//bool LoadFromPath(char* draggedFileDir);

	const char* GetExecPath();
};

void TryLoad_WithParentPath(const char* path, const char* parent_path, TempIfStream& stream);
//std::vector<std::string> modelExtensionsAccepted;
std::vector<WatchedData> TryLoadFromDisk(const char* path, const char* parent_path = nullptr);
std::vector<WatchedData> TryLoadFromDiskWithParent(const char* path, Entity* parent, const char* parent_path);
bool WriteToDisk(const char* file_path, char* data, uint64_t size);
