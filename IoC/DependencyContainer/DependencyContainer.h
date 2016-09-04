#pragma once
#include <memory>
#include <functional>
#include <map>
#include <vector>
#include <typeinfo>

namespace darknessNight {
	namespace DependencyContainer {
		template<typename T> class TypeCreatorTemplate{
		public:
			std::function<std::shared_ptr<T>()> getType;
		};

		class DIContainer {
		private:
			static std::unique_ptr<DIContainer> instance;
			std::map<std::vector<std::string>, void*> typesMap;
		public:
			~DIContainer() {
				for (auto el : typesMap)
					delete el.second;
			}

			template<typename T, typename U> static void Register(std::shared_ptr<U> pointer) {
				Register<T>([=]()->std::shared_ptr<T> {return pointer; });
			}

			template <typename T> static void Register(std::function<std::shared_ptr<T>()> func) {
				TypeCreatorTemplate<T> *creator = new TypeCreatorTemplate<T>();
				creator->getType = func;
				std::vector<std::string> el = { typeid(T).name() };
				instance->typesMap[el] = (void*)creator;
			}

			template<typename T, typename U> static void Register() {
				Register<T>([]()->std::shared_ptr<T> {return std::make_shared<U>(); });
			}

			template<typename T, typename U> static void RegisterEx(std::initializer_list<std::string> types) {
				std::vector<std::string> list = { typeid(T).name() };
				getTypesList<Args...>(list)
				Register<T, U>();
			}

			template<typename T> static std::shared_ptr<T> Get() {
				std::vector<std::string> el = { typeid(T).name() };
				return ((TypeCreatorTemplate<T>*)instance->typesMap[el])->getType();
			}

			template<typename T, typename ...Args> static std::shared_ptr<T> Get(Args... args) {
				return ((TypeCreatorTemplate<T>*)instance->typesMap.begin()->second)->getType();
			}

			static void clear() {
				instance->typesMap.clear();
			}
		};
	}
}