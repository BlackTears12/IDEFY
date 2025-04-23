#include "parser.hpp"
#include <QDebug>

namespace yocto {

Parser::Parser() {}

ConfigFile Parser::parseConfigFile(QString filename)
{
    tokenizer = std::make_unique<Tokenizer>(filename);
    tokenizer->printTokens();
    while (!tokenizer->end()) {
        auto tok = tokenizer->next();
        switch (tok.type) {
        case Token::VariableName:
            parseVarAssignment(tok);
            break;
        case Token::DirectiveKeyword:
            parseDirective(tok);
            break;
        case Token::EndLine:
            break;
        default:
            break;
        }
    }
}

VariableAssignment Parser::parseVarAssignment(Token token)
{
    auto varName = token.value;
    auto assign = tokenizer->next().value;
}

Directive Parser::parseDirective(Token token) {}

Script Parser::parseScript(Token token) {}

Tokenizer::Tokenizer(QString filename)
    : tokenIndex(0)
{
    QFile inputFile(filename);
    if (inputFile.open(QIODevice::ReadOnly)) {
        QTextStream in(&inputFile);
        QString logicalLine = "";
        while (!in.atEnd()) {
            logicalLine += in.readLine();
            //if not escaped newline
            if (line[line.size() - 1] != "\\") {
                tokenizeLine(logicalLine);
                logicalLine = "";
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
    return tokens[tokenIndex + skip];
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
    tokens.push_back({Token::EndOfFile, "\n"});
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
            tokens.push_back({(Token::VariableName, e});
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
    return val == "python" || val == "inherit" || val == "inlcude";
}

bool Tokenizer::isControl(QString val)
{
    return val == ":";
}

bool Tokenizer::isVariableName(QString val)
{
    /* Currently only UTF-16 variables are supported */
    return val.isValidUtf16();
}

} // namespace yocto
