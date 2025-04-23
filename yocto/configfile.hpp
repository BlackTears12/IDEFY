#ifndef CONFIGFILE_HPP
#define CONFIGFILE_HPP

#include <QString>

namespace yocto {

using std::unique_ptr;
using std::vector;

/* Represents a single assignment to a bitbake variable */
struct VariableAssignment
{
    enum Type {
        Hard,             // =
        Default,          // ?=
        WeakDefault,      // ??=
        ImmendiateExpand, // :=
        Append,           // .=
        Prepend,          // =.
        AppendWithSpace,  // +=
        PrependWithSpace, // =+
        AppendOverride,   // :append
        PrependOverride,  // :preprend
        RemoveOverride    // :remove
    };

    VariableAssignment(Type t, QString var, QString val, QString fl = QString())
        : type(t)
        , variable(var)
        , value(val)
        , flag(fl)
    {}

    constexpr bool isOverrideSyntax() const
    {
        return type == AppendOverride || type == PrependOverride || type == RemoveOverride;
    }

    bool isSettingAFlag() const { return !flag.isEmpty(); }

    Type type;
    QString variable;
    QString value;
    QString flag;
};

struct Directive
{
    enum Type { Export, Inherit, InheridDefer, Include, IncludeAll, Require, AddFragments };

    Type type;
    vector<QString> parameters;

    Directive(Type t, const vector<QString> params = {})
        : type(t)
        , parameters(params)
    {}
};

struct Script
{
    enum Type { Bash, Python, BitbakeStylePython, AnonymousPython };
};

struct ConfigFile
{
    vector<VariableAssignment> varAssignments;
    vector<Script> scripts;
    vector<Directive> directives;

    void addVariableAssignment(const VariableAssignment &assign)
    {
        varAssignments.push_back(assign);
    }

    void addScript(const Script &script) { scripts.push_back(script); }

    void addDirective(const Directive &directive) { directives.push_back(directive); }
};

} // namespace yocto

#endif // CONFIGFILE_HPP
