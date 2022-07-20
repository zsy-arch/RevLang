//
// Created by zhangsiyu on 7/20/2022.
//

#include "Lexer.h"
#include "Token.h"

#include <utility>

Lexer::Lexer(std::string input) : input(std::move(input)) {
    position = 0;
    ch = read_char();
}

char Lexer::read_char() {
    if (position >= input.size()) {
        ch = 0;
    } else {
        ch = input[position++];
    }
    return ch;
}

char Lexer::next_char() {
    if (position >= input.size()) {
        return 0;
    }
    return input[position];
}

Token *Lexer::get_next_token() {
    skip_whitespace();
    Token *token = nullptr;

    switch (ch) {
        case '=':
            if (next_char() == '=') {
                read_char();
                token = Token::new_token(TokenTypes::EQ);
            } else
                token = Token::new_token(TokenTypes::ASSIGN);
            break;
        case '!':
            if (next_char() == '=') {
                read_char();
                token = Token::new_token(TokenTypes::NEQ);
            } else
                token = Token::new_token(TokenTypes::BANG);
            break;
        case '>':
            if (next_char() == '=') {
                read_char();
                token = Token::new_token(TokenTypes::GEQ);
            } else
                token = Token::new_token(TokenTypes::GT);
            break;
        case '<':
            if (next_char() == '=') {
                read_char();
                token = Token::new_token(TokenTypes::LEQ);
            } else
                token = Token::new_token(TokenTypes::LT);
            break;
        case '+':
            if (next_char() == '=') {
                read_char();
                token = Token::new_token(TokenTypes::ADD_ASSIGN);
            } else
                token = Token::new_token(TokenTypes::PLUS);
            break;
        case '-':
            if (next_char() == '=') {
                read_char();
                token = Token::new_token(TokenTypes::SUB_ASSIGN);
            } else
                token = Token::new_token(TokenTypes::MINUS);
            break;
        case '*':
            if (next_char() == '=') {
                read_char();
                token = Token::new_token(TokenTypes::MUL_ASSIGN);
            } else
                token = Token::new_token(TokenTypes::STAR);
            break;
        case '/':
            if (next_char() == '=') {
                read_char();
                token = Token::new_token(TokenTypes::DIV_ASSIGN);
            } else
                token = Token::new_token(TokenTypes::SLASH);
            break;
        case '%':
            if (next_char() == '=') {
                read_char();
                token = Token::new_token(TokenTypes::MOD_ASSIGN);
            } else
                token = Token::new_token(TokenTypes::PERCENT);
            break;
        case 0:
            token = Token::new_token(TokenTypes::END);
            break;
        default:
            if (is_digit(ch)) {
                token = get_number_token();
                return token;
            } else if (is_letter(ch)) {
                token = get_ident_or_kw();
                return token;
            } else {
                token = Token::new_token(TokenTypes::ILLEGAL);
                return token;
            }
    }
    read_char();
    return token;
}

bool Lexer::is_digit(char c) {
    return (c >= '0') && (c <= '9');
}

bool Lexer::is_letter(char c) {
    return ((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')) || (c == '_');
}

Token *Lexer::get_number_token() {
    Token *token = nullptr;
    std::string value;
    bool ok = false;
    if (ch == '0') {
        if (next_char() == 'X' || next_char() == 'x') {
            token = Token::new_token(TokenTypes::ILLEGAL);
        } else if (next_char() == 'o' || next_char() == 'O') {
            token = Token::new_token(TokenTypes::ILLEGAL);
        } else if (next_char() == 'b') {
            token = Token::new_token(TokenTypes::ILLEGAL);
        } else if (next_char() == '.') {
            value = get_number();
        } else {
            token = Token::new_token(TokenTypes::ILLEGAL);
        }
    } else {
        value = get_number();
    }

    if (value == ILLEGAL_STR) {
        token = Token::new_token(TokenTypes::ILLEGAL);
    } else if (value.find('.') == std::string::npos) {
        token = Token::new_token(TokenTypes::INTEGER);
        token->set_literal_value(value);
    } else {
        token = Token::new_token(TokenTypes::FLOAT);
        token->set_literal_value(value);
    }
    return token;
}

void Lexer::skip_whitespace() {
    while (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r')
        read_char();
}

std::string Lexer::get_number() {
    bool is_float = false, ok = false;
    std::string value;

    while (true) {
        switch (ch) {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                value += ch;
                break;
            case '.':
                if (!is_float) {
                    is_float = true;
                    value += ch;

                    if (!is_digit(next_char())) {
                        value = ILLEGAL_STR;
                        ok = true;
                    }
                } else {
                    value = ILLEGAL_STR;
                    ok = true;
                }
                break;
            default:
                ok = true;
                break;
        }
        if (ok) break;
        read_char();
    }
    return value;
}

Token *Lexer::get_ident_or_kw() {
    bool ok = false;
    std::string value;
    Token *token = nullptr;
    while (true) {
        if (is_letter(ch) || is_digit(ch)) value += ch;
        else {
            ok = true;
        }
        if (ok) break;
        read_char();
    }
    if ((token = Token::to_keyword(value)) != nullptr) {
        return token;
    }
    token = Token::new_token(TokenTypes::IDENTIFIER);
    token->set_literal_value(value);
    return token;
}
