#include "DependencyContainer.h"

using namespace darknessNight::DependencyContainer;

std::unique_ptr<DependencyContainer> DependencyContainer::instance = std::unique_ptr<DependencyContainer>(new DependencyContainer());
