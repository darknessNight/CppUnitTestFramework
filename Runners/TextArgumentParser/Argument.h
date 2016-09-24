#pragma once
#include "ArgumentInfo.h"
#include "ArgumentRegister.h"

namespace darknessNight { namespace TextParser {
	class Argument :public ArgumentRegister, public ArgumentInfo {
	protected:
		bool correctArg = true;
	protected:
		friend class ArgumentParser;
	public:
		Argument() = default;

		explicit Argument(bool isEmpty) {
			this->correctArg = isEmpty;
		}

	protected:
		bool isCorrect() const {
			return correctArg;
		}

		void setDefaultValueIfNeeded() {
			if(!used)
				value = defaultValue;
		}

		void clear() {
			clearInfo();
		}
	};
}}