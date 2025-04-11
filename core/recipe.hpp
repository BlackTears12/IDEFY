#ifndef RECIPE_HPP
#define RECIPE_HPP

#include <vector>
#include <QString>

using std::vector;

struct VariableAssignment
{
    enum Type { Set };

    Type type;
    QString variable;
    QString value;
};

struct Script
{
    enum Type { Bash,Python };
};

namespace core::yocto
{

class Recipe
{
public:
    QString name;
    vector<VariableAssignment> variables;
private:

};

}

#endif // RECIPE_HPP
