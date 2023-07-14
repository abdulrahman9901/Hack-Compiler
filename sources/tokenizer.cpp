#include "../includes/tokenizer.h"

bool isComment(std::string& line) {
    // Check if the line is a comment
    size_t pos = line.find("//");
    if (pos != std::string::npos) {
        line.erase(pos); // Remove the comment portion
    }

    return line.empty();
}

Tokenizer::Tokenizer(const std::string infile) {
    std::cout << "at constructor " << infile << std::endl;
    file.open(infile);
}

void Tokenizer::advance() {
    currentToken = "";
    if (file.is_open()) {
        if (currPosition >= line.length()) {
            std::getline(file, line);
            currPosition = 0;
        }
        if (!isComment(line)) {
            std::string breaks = "{}()[].,;+-*/&|<>=~ ";

            if (currPosition < line.length()) {
                if (breaks.find(line[currPosition]) != std::string::npos &&
                    !std::isspace(line[currPosition])) {
                    currentToken = +!std::isspace(currentToken[0])
                                       ? line[currPosition]
                                       : ' ';

                    currPosition++;
                } else if (breaks.find(line[currPosition]) ==
                               std::string::npos &&
                           !std::isspace(line[currPosition])) {
                    currentToken.clear();

                    if (line[currPosition] == '"') {
                        // Extract the string within double quotation marks
                        currentToken += line[currPosition++]; // Add the
                                                              // opening
                                                              // quotationmark
                        while (currPosition < line.length() &&
                               line[currPosition] != '"') {
                            currentToken += line[currPosition++];
                        }
                        if (currPosition < line.length() &&
                            line[currPosition] == '"') {
                            currentToken +=
                                line[currPosition++]; // Add the closing
                                                      // quotation mark
                        }
                    } else {
                        while (currPosition < line.length() &&
                               breaks.find(line[currPosition]) ==
                                   std::string::npos &&
                               !std::isspace(line[currPosition])) {
                            currentToken += line[currPosition];
                            currPosition++;
                        }
                    }

                } else {
                    currPosition++; // Skip the space character
                }

                // Trim the currentToken to remove leading and trailing
                // spaces
                currentToken.erase(0, currentToken.find_first_not_of(' '));
                currentToken.erase(currentToken.find_last_not_of(' ') + 1);

                // Skip empty tokens or tokens consisting only of
                // spaces
                if (!currentToken.empty() && currentToken != " ") {
                    total++;
                    std::cout << "Token: " << total << std::endl;
                }
            }
        }
    } else {
        std::cout << "Failed to open the file." << std::endl;
    }
}

bool Tokenizer::hasMoreTokens() { return !file.eof(); }

Token Tokenizer::construct_token() {
    Token token;
    token.value = currentToken;

    bool isNumber = true;
    try {
        double number = std::stod(currentToken);
    } catch (const std::invalid_argument&) {
        isNumber = false;
    } catch (const std::out_of_range&) {
        isNumber = false;
    }
    if (currentToken.length() == 1 &&
        symbols.find(currentToken) != std::string::npos &&
        !std::isspace(currentToken[0])) {
        token.type = TOKEN_TYPE::SYMBOL;
    } else if (std::find(keywords.begin(), keywords.end(), currentToken) !=
               keywords.end()) {
        token.type = TOKEN_TYPE::KEYWORD;
    } else if (isNumber) {
        token.type = TOKEN_TYPE::INT_CONST;
    } else if (currentToken.length() >= 2 && currentToken.front() == '"' &&
               currentToken.back() == '"') {
        token.type = TOKEN_TYPE::STRING_CONST;
    } else if (currentToken != "" && !std::isspace(currentToken[0])) {
        token.type = TOKEN_TYPE::IDENTIFIER;
    } else {
        token.type = TOKEN_TYPE::OTHERS;
    }

    return token;
}
void Tokenizer::close() { file.close(); }
// TOKEN_TYPE Tokenizer::tokenType() {}
// KEYWORD_TYPE Tokenizer::keyWord() {}
// char Tokenizer::sympol() {}
// std::string Tokenizer::identifier() {}
// int Tokenizer::intVal() {}
// std::string Tokenizer::stringVal() {}
