#ifndef RECIPE_HPP
#define RECIPE_HPP

#include <QString>
#include "configfile.hpp"

namespace yocto {

class Recipe
{
public:
private:
    unique_ptr<ConfigFile> content;
};

} // namespace yocto

#endif // RECIPE_HPP
