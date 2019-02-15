#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

class Resource {
	protected:
		unsigned int resourceId;
		string resourcePath;
	public:
		virtual ~Resource() {};

		virtual int load() = 0;
		virtual void unload() = 0;

		void setId(unsigned int id);
		unsigned int getId();

		void setPath(string path);
		string getPath();
};

class ResourceManager {
	private:
		static ResourceManager* _instance;
		unordered_map<std::string, Resource*> resources;

		ResourceManager();
	public:
		static ResourceManager* instance();
		void loadResource(Resource* res, string name, string path);

		template<typename T>
		T* getResource(string name) {
			unordered_map<std::string, Resource*>::iterator it = resources.find(name);
			return (it == resources.end()) ? nullptr : dynamic_cast<T*>(it->second);
		}
};

#endif