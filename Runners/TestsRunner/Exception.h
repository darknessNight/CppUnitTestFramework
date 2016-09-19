#pragma once
#include <string>

namespace darknessNight {
	namespace Exceptions {
		class Exception :public std::exception {
		protected:
			std::string message;
		public:
			explicit Exception(std::string mess) {
				message = mess;
			}

			const char* what() const override {
				return message.c_str();
			}

			virtual std::string getMessage() const {
				return message;
			}
		};
	}
}