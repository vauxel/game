#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

class Resource {
	protected:
		unsigned int resourceId;
		const char* resourcePath;
	public:
		virtual ~Resource() {};

		virtual int load() = 0;
		virtual void unload() = 0;

		void setId(unsigned int id);
		unsigned int getId();

		void setPath(const char* path);
		const char* getPath();
};

class ResourceManager {
	private:
		static ResourceManager* _instance;
		std::unordered_map<std::string, Resource*> resources;

		ResourceManager();
	public:
		static ResourceManager* instance();
		void loadResource(Resource* res, std::string name, std::string path);

		template<typename T>
		T* getResource(std::string name) {
			std::unordered_map<std::string, Resource*>::iterator it = resources.find(name);
			return (it == resources.end()) ? nullptr : dynamic_cast<T*>(it->second);
		}
};

#endif