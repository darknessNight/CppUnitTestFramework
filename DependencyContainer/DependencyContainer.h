#pragma once
#include <memory>
#include <functional>
#include <map>

namespace darknessNight {
	namespace DependencyContainer {
		class TypeCreator {};
		template<typename T> class TypeCreatorTemplate {
		public:
			std::function<std::shared_ptr<T>()> getType;
		};

		class DependencyContainer {
		private:
			static std::unique_ptr<DependencyContainer> instance;
			std::map<std::string, void*> typesMap;
		public:
			~DependencyContainer() {
				for (auto el : typesMap)
					delete el.second;
			}

			template<typename T, typename U> static void Register(std::shared_ptr<U> pointer) {
				Register<T>([=]()->std::shared_ptr<T> {return pointer; });
			}

			template <typename T> static void Register(std::function<std::shared_ptr<T>()> func) {
				TypeCreatorTemplate<T> *creator = new TypeCreatorTemplate<T>();
				creator->getType = func;
				instance->typesMap[typeid(T).name()] = (void*)creator;
			}

			template<typename T, typename U> static void Register() {
				Register<T>([]()->std::shared_ptr<T> {return std::make_shared<U>(); });
			}

			template<typename T> static std::shared_ptr<T> Get() {
				return ((TypeCreatorTemplate<T>*)instance->typesMap[typeid(T).name()])->getType();
			}

			static void clear() {
				instance->typesMap.clear();
			}
		};
	}
}