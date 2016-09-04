#include "DependencyContainer.h"

using namespace darknessNight::DependencyContainer;

std::unique_ptr<DIContainer> DIContainer::instance = std::unique_ptr<DIContainer>(new DIContainer());
