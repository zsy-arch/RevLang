//
// Created by zhangsiyu on 7/20/2022.
//

#include "Token.h"

std::vector<std::string> Token::KEYWORDS = {
        "let",
        "const",
        "func",
        "if",
        "else",
        "true",
        "false",
};

std::map<std::string, TokenTypes> Token::DEF_TOKENS = {
        {"ILLEGAL",    TokenTypes::ILLEGAL},
        {"END",        TokenTypes::END},
        {"LET",        TokenTypes::LET},
        {"CONST",      TokenTypes::CONST},
        {"IDENTIFIER", TokenTypes::IDENTIFIER},
        {"FUNC",       TokenTypes::FUNC},
        {"RETURN",     TokenTypes::RETURN},
        {"ASSIGN",     TokenTypes::ASSIGN},
        {"ADD_ASSIGN", TokenTypes::ADD_ASSIGN},
        {"SUB_ASSIGN", TokenTypes::SUB_ASSIGN},
        {"MUL_ASSIGN", TokenTypes::MUL_ASSIGN},
        {"DIV_ASSIGN", TokenTypes::DIV_ASSIGN},
        {"MOD_ASSIGN", TokenTypes::MOD_ASSIGN},
        {"PLUS",       TokenTypes::PLUS},
        {"MINUS",      TokenTypes::MINUS},
        {"STAR",       TokenTypes::STAR},
        {"SLASH",      TokenTypes::SLASH},
        {"BANG",       TokenTypes::BANG},
        {"PERCENT",    TokenTypes::PERCENT},
        {"IF",         TokenTypes::IF},
        {"ELSE",       TokenTypes::ELSE},
        {"TRUE",       TokenTypes::TRUE},
        {"FALSE",      TokenTypes::FALSE},
        {"EQ",         TokenTypes::EQ},
        {"NEQ",        TokenTypes::NEQ},
        {"LT",         TokenTypes::LT},
        {"GT",         TokenTypes::GT},
        {"LEQ",        TokenTypes::LEQ},
        {"GEQ",        TokenTypes::GEQ},
        {"INTEGER",    TokenTypes::INTEGER},
        {"FLOAT",      TokenTypes::FLOAT},
};

std::map<TokenTypes, std::string> *Token::INV_DEF_TOKENS = nullptr;

Token::Token(std::string tokenString, const TokenTypes &token_type) : token_string(std::move(tokenString)),
                                                                      token_type(token_type) {
    maybe_init_token();
}

Token *Token::new_token(const std::string &token_string) {
    if (Token::DEF_TOKENS.find(token_string) != Token::DEF_TOKENS.end()) {
        auto *token = new Token(token_string, Token::DEF_TOKENS[token_string]);
        return token;
    }
    return nullptr;
}

Token *Token::new_token(const TokenTypes &token_type) {
    maybe_init_token();
    if (Token::INV_DEF_TOKENS->find(token_type) != Token::INV_DEF_TOKENS->end()) {
        auto *token = new Token(INV_DEF_TOKENS->at(token_type), token_type);
        return token;
    }
    return nullptr;
}

bool Token::operator==(const Token &rhs) const {
    return token_string == rhs.token_string &&
           token_type == rhs.token_type;
}

bool Token::operator!=(const Token &rhs) const {
    return !(rhs == *this);
}

bool Token::operator==(const std::string &rhs) const {
    return rhs == this->token_string;
}

bool Token::operator==(const int &rhs) const {
    return rhs == this->token_type;
}

void Token::maybe_init_token() {
    if (Token::INV_DEF_TOKENS == nullptr) {
        INV_DEF_TOKENS = new std::map<TokenTypes, std::string>;
        for (const auto &item: DEF_TOKENS) {
            INV_DEF_TOKENS->insert(INV_DEF_TOKENS->begin(),
                                   std::pair<TokenTypes, std::string>(item.second, item.first));
        }
    }
}

const std::string &Token::get_literal_value() const {
    return literal_value;
}

void Token::set_literal_value(const std::string &_literal_value) {
    literal_value = _literal_value;
}


Token *Token::to_keyword(const std::string &s) {
    if (std::find(KEYWORDS.begin(), KEYWORDS.end(), s) != KEYWORDS.end()) {
        std::string token_string = s;
        std::transform(token_string.begin(), token_string.end(), token_string.begin(), ::toupper);
        return new Token(token_string, DEF_TOKENS[token_string]);
    }
    return nullptr;
}

const std::string &Token::get_token_string() const {
    return token_string;
}
