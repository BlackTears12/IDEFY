#ifndef PARSER_HPP
#define PARSER_HPP

#include <QFile>
#include "configfile.hpp"
#include <memory>

namespace yocto {

struct Token
{
    enum Type {
        AssignOperator,
        QuotedString,
        DirectiveKeyword,
        FunctionDefinition,
        VariableName,
        EndLine,
        EndOfFile
    };

    Token(Type t, QString v)
        : type(t)
        , value(v)
    {}

    Type type;
    QString value;
};

class Tokenizer
{
public:
    Tokenizer(QString filename);

    Token next();
    Token peek(unsigned int skip = 0);
    void skipUntilNewline();
    bool end() const { return tokenIndex >= tokens.size(); }

    void printTokens() const;
private:
    void tokenizeLine(QString line);

    void tokenizeUnquoted(QString val);

    bool isAssignOperator(QString val);
    bool isDirectiveKeyword(QString val);
    bool isFunctionDefinition(QString val);
    bool isVariableName(QString val);

    vector<Token> tokens;
    unsigned int tokenIndex;
};

class Parser
{
public:
    Parser();

    unique_ptr<ConfigFile> parseConfigFile(QString filename);

private:
    VariableAssignment parseVarAssignment(Token token);
    Directive parseDirective(Token token);
    Script parseScript(Token token);

    VariableAssignment::Type matchVarAssignmentType(const QString &assign) const;
    VariableAssignment finalizeAssignment(const VariableAssignment &assign) const;

    Directive::Type matchDirectiveType(const QString dir) const;
    std::unique_ptr<Tokenizer> tokenizer;
};

} // namespace yocto

#endif // PARSER_HPP
