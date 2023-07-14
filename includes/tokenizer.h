
#include "token.h"
#include <algorithm>
#include <cctype>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#ifndef TOKENIZER_H
#define TOKENIZER_H

// enum KEYWORD_TYPE {
//     CLASS,
//     METHOD,
//     FUNCTION,
//     CONSTRUCTOR,
//     INT,
//     BOOLEAN,
//     CHAR,
//     VOID,
//     VAR,
//     STATIC,
//     FIELD,
//     LET,
//     DO,
//     IF,
//     ELSE,
//     WHILE,
//     RETURN,
//     TRUE,
//     FALSE,
//     null,
//     THIS
// };

class Tokenizer {
  private:
    std::string currentToken = "";
    size_t currPosition = 0;
    std::string line;
    std::ifstream file;
    std::vector<std::string> tokens{"keyword", "symbol",
                                    "identifier"
                                    "integerConstant",
                                    "stringConstant"};
    std::string symbols = "{}()[].,;+-*/&|<>=~";
    std::vector<std::string> keywords{
        "class", "method", "function", "constructor", "int",    "boolean",
        "char",  "void",   "var",      "static",      "field",  "let",
        "do",    "if",     "else",     "while",       "return", "true",
        "false", "null",   "this"};

  public:
    int total = 0;
    Tokenizer(const std::string infile);
    bool hasMoreTokens();
    void advance();
    Token construct_token();
    TOKEN_TYPE tokenType();
    std::string keyWord();
    char sympol();
    std::string identifier();
    int intVal();
    std::string stringVal();
    void close();
};

#endif