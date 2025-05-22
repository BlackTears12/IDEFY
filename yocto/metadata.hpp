#ifndef METADATA_H
#define METADATA_H

#include <QFileInfo>
#include <QString>

using std::unique_ptr;
using std::shared_ptr;
using std::vector;

namespace yocto {

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
    enum Type { Export, Inherit, InheritDefer, Include, IncludeAll, Require, AddFragments };

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

class MetadataFile
{
public:
    enum Type { Recipe,RecipeAppend,Class,Configuration,KernelFragment };

    explicit MetadataFile(QString path) : filePath(path)
    {
        QFileInfo fileInfo(filePath);
        auto suffix = fileInfo.completeSuffix();
        if(suffix == "bb")
            type = Recipe;
        if(suffix == "bbappend")
            type = RecipeAppend;
        if(suffix == "class")
            type = Class;
        if(suffix == "cfg")
            type = KernelFragment;
    }

    virtual QString getPath() const { return filePath; }

    virtual QString getName() const
    {
        QFileInfo fileInfo(filePath);
        return fileInfo.fileName();
    }

    void addVariableAssignment(const VariableAssignment &assign)
    {
        varAssignments.push_back(assign);
    }

    void addScript(const Script &script) { scripts.push_back(script); }

    void addDirective(const Directive &directive) { directives.push_back(directive); }
protected:
    vector<VariableAssignment> varAssignments;
    vector<Script> scripts;
    vector<Directive> directives;
    QString filePath;
    Type type;

};

} // namespace yocto

#endif // METADATA_H
