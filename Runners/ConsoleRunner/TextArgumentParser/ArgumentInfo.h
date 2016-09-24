#pragma once
#include <vector>

namespace darknessNight {namespace TextParser {
	class ArgumentInfo {
	protected:
		std::string value;
		std::vector<std::string> arrayValues;
		bool used;
	public:
		ArgumentInfo();
		virtual bool isUsed() const;
		template<typename T> T getValue() const;
		template<typename T> std::vector<T> getArray() const;
		virtual void clearInfo();
	protected:
		template<typename T> T convertValue(std::string value) const;
	};

	inline ArgumentInfo::ArgumentInfo() {
		ArgumentInfo::clearInfo();
	}

	inline bool ArgumentInfo::isUsed() const {
		return used;
	}

	template<typename T> inline
		T ArgumentInfo::getValue() const {
		return convertValue<T>(value);
	}

	template<typename T> inline
	T ArgumentInfo::convertValue(std::string value) const {
		static_assert(true, "Implementation for this type not exists");
	}

	template<>
	inline bool ArgumentInfo::convertValue<bool>(std::string value) const {
		if(value == "true" || value == "1")
			return true;
		else
			return false;
	}

	template<>
	inline std::string ArgumentInfo::convertValue<std::string>(std::string value) const {
		return value;
	}

	template<>
	inline int ArgumentInfo::convertValue<int>(std::string value) const {
		return atoi(value.c_str());
	}

	template<>
	inline long long ArgumentInfo::convertValue<long long>(std::string value) const {
		return atoll(value.c_str());
	}

	template<>
	inline double ArgumentInfo::convertValue<double>(std::string value) const {
		return atof(value.c_str());
	}

	template<>
	inline float ArgumentInfo::convertValue<float>(std::string value) const {
		return static_cast<float>(atof(value.c_str()));
	}

	template<>
	inline std::vector<std::string> ArgumentInfo::getArray<std::string>() const {
		return arrayValues;
	}

	template<typename T>
	inline std::vector<T> ArgumentInfo::getArray() const {
		std::vector<T> ret;
		for(auto val:arrayValues) {
			ret.push_back(convertValue<T>(val));
		}
		return ret;
	}

	inline void ArgumentInfo::clearInfo() {
		used = false;
		value = "";
		arrayValues.clear();
	}
}}
