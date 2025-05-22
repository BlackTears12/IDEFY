#include "parser.hpp"
#include <QDebug>

namespace yocto {

Parser::Parser() {}

unique_ptr<MetadataFile> Parser::parseConfigFile(QString filePath)
{
    tokenizer = std::make_unique<Tokenizer>(filePath);
    auto config = std::make_unique<MetadataFile>(filePath);
    while (!tokenizer->end()) {
        auto tok = tokenizer->next();
        switch (tok.type) {
        case Token::VariableName:
            config->addVariableAssignment(parseVarAssignment(tok));
            break;
        case Token::DirectiveKeyword:
            config->addDirective(parseDirective(tok));
            break;
        case Token::EndLine:
            break;
        default:
            break;
        }
    }
    return config;
}

VariableAssignment Parser::parseVarAssignment(Token token)
{
    auto varName = token.value;
    auto assign = tokenizer->next().value;

    //TODO verify token mathing
    tokenizer->skipUntilNewline();
    return finalizeAssignment({matchVarAssignmentType(assign), varName, tokenizer->next().value});
}

Directive Parser::parseDirective(Token token)
{
    Directive dir{matchDirectiveType(token.value)};
    while (!tokenizer->end() && tokenizer->peek().type != Token::EndLine) {
        dir.parameters.push_back(tokenizer->next().value);
    }
    if (!tokenizer->end())
        tokenizer->next();
    return dir;
}

Script Parser::parseScript(Token token) {}

VariableAssignment::Type Parser::matchVarAssignmentType(const QString &assign) const
{
    if (assign == "=") {
        return VariableAssignment::Hard;
    } else if (assign == "?=") {
        return VariableAssignment::Default;
    } else if (assign == "??=") {
        return VariableAssignment::WeakDefault;
    } else if (assign == ":=") {
        return VariableAssignment::ImmendiateExpand;
    } else if (assign == ".=") {
        return VariableAssignment::Append;
    } else if (assign == "=.") {
        return VariableAssignment::Prepend;
    } else if (assign == "+=") {
        return VariableAssignment::AppendWithSpace;
    } else if (assign == "=+") {
        return VariableAssignment::PrependWithSpace;
    } else {
        return VariableAssignment::Hard;
    }
}

VariableAssignment Parser::finalizeAssignment(const VariableAssignment &assign) const
{
    /*
     * TODO 
     * verify override syntax
     * recognize flags
     * recognize var expansions
     */

    return assign;
}

Directive::Type Parser::matchDirectiveType(const QString dir) const
{
    return Directive::Include;
}

Tokenizer::Tokenizer(QString filePath)
    : tokenIndex(0)
{
    QFile inputFile(filePath);
    if (inputFile.open(QIODevice::ReadOnly)) {
        QTextStream in(&inputFile);
        QString logicalLine = "";
        while (!in.atEnd()) {
            auto line = in.readLine();
            if (line.size() < 1 || line[0] == '#')
                continue;
            logicalLine += line;

            //if not escaped newline
            if (logicalLine[logicalLine.size() - 1] != "\\") {
                tokenizeLine(logicalLine);
                logicalLine = "";
            } else {
                logicalLine.chop(1);
            }
        }
        inputFile.close();
    }
}

Token Tokenizer::next()
{
    auto t = peek();
    tokenIndex++;
    return t;
}

Token Tokenizer::peek(unsigned int skip)
{
    if (tokenIndex + skip >= tokens.size())
        return {Token::EndOfFile, "/n"};
    return tokens[tokenIndex + skip];
}

void Tokenizer::skipUntilNewline()
{
    auto n = next();
    while (n.type != Token::EndLine && n.type != Token::EndOfFile) {
        n = next();
    }
}

void Tokenizer::printTokens() const
{
    for (auto &e : tokens) {
        qDebug() << e.type << " - " << e.value;
    }
}

void Tokenizer::tokenizeLine(QString line)
{
    auto parts = line.split("\"", Qt::KeepEmptyParts);
    bool inOpenStr = false;
    foreach (const auto &part, parts) {
        if (inOpenStr) {
            tokens.push_back({Token::QuotedString, part});
        } else {
            tokenizeUnquoted(part);
        }
        inOpenStr = !inOpenStr;
    }
}

void Tokenizer::tokenizeUnquoted(QString val)
{
    if (val.isEmpty())
        return;
    /* TODO actual tokenization */
    for (auto &e : val.split(" ", Qt::SkipEmptyParts)) {
        if (isAssignOperator(e))
            tokens.push_back({Token::AssignOperator, e});
        else if (isDirectiveKeyword(e))
            tokens.push_back({Token::DirectiveKeyword, e});
        else if (isVariableName(e))
            tokens.push_back({Token::VariableName, e});
        else
            qDebug() << "Could not tokenize " << e;
    }
}

bool Tokenizer::isAssignOperator(QString val)
{
    return val == "=" || val == "?=" || val == "??=" || val == ":=" || val == "+=" || val == "=+"
           || val == ".=" || val == "=.";
}

bool Tokenizer::isDirectiveKeyword(QString val)
{
    return val == "python" || val == "inherit" || val == "include";
}

bool Tokenizer::isVariableName(QString val)
{
    /* Currently only UTF-16 variables are supported */
    return val.isValidUtf16();
}

} // namespace yocto
