#include "Token.h"

namespace com {

    std::string tokenTypeToString(TokenType type)
    {
        switch (type)
        {
        case TokenType::SYMBOL:
            return "Symbol";
        case TokenType::NUMBER:
            return "Number";
        case TokenType::KEY_IF:
            return "'if'";
        case TokenType::KEY_WHILE:
            return "'while'";
        case TokenType::KEY_OUT:
            return "'out'";
        case TokenType::OP_ADD:
            return "'+'";
        case TokenType::OP_SUB:
            return "'-'";
        case TokenType::OP_MUL:
            return "'*'";
        case TokenType::OP_DIV:
            return "'/'";
        case TokenType::OP_EQUALS:
            return "'=='";
        case TokenType::OP_LESS_THAN:
            return "'<'";
        case TokenType::OP_GREATER_THAN:
            return "'>'";
        case TokenType::OP_ASSIGN:
            return "'='";
        case TokenType::LOP_NOT:
            return "'!'";
        case TokenType::LOP_AND:
            return "'&'";
        case TokenType::LOP_OR:
            return "'|'";
        case TokenType::OPEN_BRACKET:
            return "'('";
        case TokenType::CLOSE_BRACKET:
            return "')'";
        case TokenType::OPEN_CURLY_BRACKET:
            return "'{'";
        case TokenType::CLOSE_CURLY_BRACKET:
            return "'}'";
        case TokenType::SEMICOLON:
            return "';'";
        case TokenType::EOI:
            return "End of input";
        default:
            return "None";
        }
    }

    std::string tokenToString(const Token& token)
    {
        if (token.second == "")
            return tokenTypeToString(token.first);
        return tokenTypeToString(token.first) + ": " + token.second;
    }

}
