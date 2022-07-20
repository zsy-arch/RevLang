//
// Created by zhangsiyu on 7/20/2022.
//

#ifndef REVLANG_TOKEN_H
#define REVLANG_TOKEN_H

#define ILLEGAL_STR "ILLEGAL"

#include <string>
#include <map>
#include <utility>
#include <vector>
#include <algorithm>

enum TokenTypes {
    // END OF FILE
    ILLEGAL,
    END,
    LET,
    CONST,
    FUNC,
    RETURN,
    IDENTIFIER,
    ASSIGN,
    ADD_ASSIGN,
    SUB_ASSIGN,
    MUL_ASSIGN,
    DIV_ASSIGN,
    MOD_ASSIGN,
    PLUS,
    MINUS,
    STAR,
    SLASH,
    BANG,
    PERCENT,
    IF,
    ELSE,
    TRUE,
    FALSE,
    EQ,
    NEQ,
    LT,
    GT,
    LEQ,
    GEQ,
    INTEGER,
    FLOAT,
};

class Token {
private:
    static std::vector<std::string> KEYWORDS;
    static std::map<std::string, TokenTypes> DEF_TOKENS;
    static std::map<TokenTypes, std::string> *INV_DEF_TOKENS;

    std::string token_string;
    TokenTypes token_type;
    std::string literal_value;

    Token(std::string tokenString, const TokenTypes &token_type);

    static void maybe_init_token();

public:

    static Token *new_token(const std::string &token_string);

    static Token *new_token(const TokenTypes &token_type);

    static Token* to_keyword(const std::string& s);

    bool operator==(const std::string &rhs) const;

    bool operator==(const int &rhs) const;

    bool operator==(const Token &rhs) const;

    bool operator!=(const Token &rhs) const;

    const std::string &get_literal_value() const;

    void set_literal_value(const std::string &_literal_value);

    const std::string &get_token_string() const;
};

#endif //REVLANG_TOKEN_H
