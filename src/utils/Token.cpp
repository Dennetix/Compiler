#include "Token.h"

namespace com {

    std::vector<std::string> tokensToString(const std::vector<Token>& tokens)
    {
        std::vector<std::string> res;
        for (Token t : tokens)
        {
            switch (t.first)
            {
            case TokenType::NONE:
                res.push_back("NONE");
                break;
            case TokenType::SYMBOL:
                res.push_back("SYMBOL: " + t.second);
                break;
            case TokenType::NUMBER:
                res.push_back("NUMBER: " + t.second);
                break;
            case TokenType::STRING:
                res.push_back("STRING: " + t.second);
                break;
            case TokenType::KEY_IF:
                res.push_back("KEY_IF");
                break;
            case TokenType::KEY_WHILE:
                res.push_back("KEY_WHILE");
                break;
            case TokenType::KEY_RETURN:
                res.push_back("KEY_RETURN");
                break;
            case TokenType::OP_ASSIGN:
                res.push_back("OP_ASSIGN");
                break;
            case TokenType::OP_ADD:
                res.push_back("OP_ADD");
                break;
            case TokenType::OP_SUB:
                res.push_back("OP_SUB");
                break;
            case TokenType::OP_MUL:
                res.push_back("OP_MUL");
                break;
            case TokenType::OP_DIV:
                res.push_back("OP_DIV");
                break;
            case TokenType::OP_EQUALS:
                res.push_back("OP_EQUALS");
                break;
            case TokenType::OP_LESS_THAN:
                res.push_back("OP_LESS_THAN");
                break;
            case TokenType::OP_GREATER_THAN:
                res.push_back("OP_GREATER_THAN");
                break;
            case TokenType::LOP_NOT:
                res.push_back("LOP_NOT");
                break;
            case TokenType::LOP_AND:
                res.push_back("LOP_AND");
                break;
            case TokenType::LOP_OR:
                res.push_back("LOP_OR");
                break;
            case TokenType::OPEN_BRACKET:
                res.push_back("OPEN_BRACKET");
                break;
            case TokenType::CLOSE_BRACKET:
                res.push_back("CLOSE_BRACKET");
                break;
            case TokenType::OPEN_CURLY_BRACKET:
                res.push_back("OPEN_CURLY_BRACKET");
                break;
            case TokenType::CLOSE_CURLY_BRACKET:
                res.push_back("CLOSE_CURLY_BRACKET");
                break;
            case TokenType::COMMA:
                res.push_back("COMMA");
                break;
            case TokenType::SEMICOLON:
                res.push_back("SEMICOLON");
                break;
            case TokenType::END:
                res.push_back("END");
                break;
            }
        }
        return res;
    }

}
