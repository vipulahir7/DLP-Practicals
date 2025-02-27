// #include <iostream>
// #include <fstream>
// #include <string>
// #include <regex>
// #include <unordered_set>
// #include <vector>

// using namespace std;

// struct Token {
//     string type;
//     string value;
// };

// const unordered_set<string> keywords = {
//     "int", "char", "float", "double", "return", "if", "else", "for", "while", "do", "switch", "case", "break", "continue", "void", "static", "struct", "typedef", "const"
// };


// const unordered_set<char> punctuation = {'(', ')', '{', '}', '[', ']', ',', ';'};
// const unordered_set<string> operators = {"=", "+", "-", "*", "/", "%", "==", "!=", "<", "<=", ">", ">=", "&&", "||", "!", "&", "|", "^", "~", "<<", ">>"};

// void removeCommentsInFile(const string &filename, string &processedSource) {
//     ifstream inputFile(filename);
//     if (!inputFile.is_open()) {
//         cerr << "Error: Could not open file " << filename << endl;
//         return;
//     }

//     string line;
//     bool multiLineComment = false;

//     while (getline(inputFile, line)) {
//         if (multiLineComment) {
//             size_t endPos = line.find("*/");
//             if (endPos != string::npos) {
//                 multiLineComment = false;
//                 line = line.substr(endPos + 2);
//             } else {
//                 continue;
//             }
//         }

//         size_t singleLinePos = line.find("//");
//         if (singleLinePos != string::npos) {
//             line = line.substr(0, singleLinePos);
//         }

//         size_t multiLineStart = line.find("/*");
//         if (multiLineStart != string::npos) {
//             multiLineComment = true;
//             line = line.substr(0, multiLineStart);
//         }

//         if (!line.empty()) {
//             processedSource += line + "\n";
//         }
//     }

//     inputFile.close();
// }

// vector<Token> tokenize(const string &sourceCode, unordered_set<string> &symbolTable, vector<string> &lexicalErrors) {
//     vector<Token> tokens;
//     regex tokenRegex(R"((\d+[a-zA-Z_][a-zA-Z0-9_]*|[a-zA-Z_][a-zA-Z0-9_]*|\d+|'[^']*'|"[^"]*"|==|!=|<=|>=|&&|\|\||[{}()\[\],;]|[-+*/%=&|^!<>~]))");
//     smatch match;
//     string::const_iterator searchStart(sourceCode.cbegin());

//     while (regex_search(searchStart, sourceCode.cend(), match, tokenRegex)) {
//         string token = match[0];

//         // Check for keywords
//         if (keywords.count(token)) {
//             tokens.push_back({"Keyword", token});
//         }
//         else if (punctuation.count(token[0])) {
//             tokens.push_back({"Punctuation", token});
//         }
//         else if (operators.count(token)) {
//             tokens.push_back({"Operator", token});
//         }
//         else if (regex_match(token, regex(R"(\d+)"))) {
//             tokens.push_back({"Constant", token});
//         }
//         else if (regex_match(token, regex(R"('[^']*')"))) {
//             tokens.push_back({"String", token});
//         }
//         else if (regex_match(token, regex(R"([a-zA-Z_][a-zA-Z0-9_]*)"))) {
//             tokens.push_back({"Identifier", token});
//             if (token != "main") {
//                 symbolTable.insert(token);
//             }
//         }
//         else if (regex_match(token, regex(R"(\d+[a-zA-Z_][a-zA-Z0-9_]*)"))) {
//             lexicalErrors.push_back(token);
//         }
//         else {
//             lexicalErrors.push_back(token);
//         }

//         searchStart = match.suffix().first;
//     }

//     return tokens;
// }


// void writeOutput(const string &filename, const vector<Token> &tokens, const unordered_set<string> &symbolTable, const vector<string> &lexicalErrors, const string &processedSource) {
//     ofstream outputFile(filename);
//     if (!outputFile.is_open()) {
//         cerr << "Error: Could not open file for writing: " << filename << endl;
//         return;
//     }

//     outputFile << "TOKENS:\n";
//     for (const auto &token : tokens) {
//         outputFile << token.type << ": " << token.value << "\n";
//     }

//     outputFile << "\nSYMBOL TABLE ENTRIES:\n";
//     for (const auto &symbol : symbolTable) {
//         outputFile << symbol << "\n";
//     }

//     outputFile << "\nLEXICAL ERRORS:\n";
//     for (const auto &error : lexicalErrors) {
//         outputFile << error << "\n";
//     }

//     outputFile << "\nMODIFIED SOURCE CODE:\n" << processedSource;
//     outputFile.close();
// }

// int main() {
//     string filename = "sample.txt";
//     string processedSource = "";

//     removeCommentsInFile(filename, processedSource);

//     unordered_set<string> symbolTable;
//     vector<string> lexicalErrors;
//     vector<Token> tokens = tokenize(processedSource, symbolTable, lexicalErrors);

//     string outputFilename = "output.txt";
//     writeOutput(outputFilename, tokens, symbolTable, lexicalErrors, processedSource);

//     cout << "Lexical analysis complete. Results saved to " << outputFilename << endl;

//     return 0;
// }

#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <regex>

using namespace std;

enum TokenType {
    KEYWORD, IDENTIFIER, CONSTANT, STRING, PUNCTUATION, OPERATOR, LEXICAL_ERROR
};

unordered_set<string> keywords = {"int", "return", "void", "char", "long", "float", "struct"};
unordered_set<char> operators = {'+', '-', '*', '/', '=', '%', '&', '|', '!', '<', '>'};
unordered_set<char> punctuation = {';', ',', '(', ')', '{', '}', '[', ']'};

struct Token {
    TokenType type;
    string value;
};

vector<string> symbolTable;

bool isKeyword(const string& word) {
    return keywords.find(word) != keywords.end();
}

bool isOperator(char ch) {
    return operators.find(ch) != operators.end();
}

bool isPunctuation(char ch) {
    return punctuation.find(ch) != punctuation.end();
}

bool isIdentifier(const string& word) {
    return regex_match(word, regex("[a-zA-Z_][a-zA-Z0-9_]*"));
}

bool isConstant(const string& word) {
    return regex_match(word, regex("[0-9]+"));
}

void addToSymbolTable(const string& identifier) {
    if (find(symbolTable.begin(), symbolTable.end(), identifier) == symbolTable.end()) {
        symbolTable.push_back(identifier);
    }
}

void tokenize(const string& sourceCode, vector<Token>& tokens, vector<string>& errors) {
    string current;
    bool inString = false;
    bool inChar = false;
    bool inComment = false;

    for (size_t i = 0; i < sourceCode.length(); ++i) {
        char ch = sourceCode[i];

        if (inComment) {
            if (ch == '*' && i + 1 < sourceCode.length() && sourceCode[i + 1] == '/') {
                inComment = false;
                ++i;
            }
            continue;
        } else if (ch == '/' && i + 1 < sourceCode.length() && sourceCode[i + 1] == '*') {
            inComment = true;
            ++i;
            continue;
        }

        if (inString) {
            current += ch;
            if (ch == '"') {
                tokens.push_back({STRING, current});
                current.clear();
                inString = false;
            }
            continue;
        } else if (ch == '"') {
            inString = true;
            current += ch;
            continue;
        }

        if (inChar) {
            current += ch;
            if (ch == '\'' && current.length() > 2) {
                tokens.push_back({STRING, current});
                current.clear();
                inChar = false;
            }
            continue;
        } else if (ch == '\'') {
            inChar = true;
            current += ch;
            continue;
        }

        if (isspace(ch)) {
            if (!current.empty()) {
                if (isKeyword(current)) {
                    tokens.push_back({KEYWORD, current});
                } else if (isIdentifier(current)) {
                    tokens.push_back({IDENTIFIER, current});
                    addToSymbolTable(current);
                } else if (isConstant(current)) {
                    tokens.push_back({CONSTANT, current});
                } else {
                    errors.push_back(current);
                    tokens.push_back({LEXICAL_ERROR, current});
                }
                current.clear();
            }
            continue;
        }

        if (isOperator(ch)) {
            if (!current.empty()) {
                if (isKeyword(current)) {
                    tokens.push_back({KEYWORD, current});
                } else if (isIdentifier(current)) {
                    tokens.push_back({IDENTIFIER, current});
                    addToSymbolTable(current);
                } else if (isConstant(current)) {
                    tokens.push_back({CONSTANT, current});
                } else {
                    errors.push_back(current);
                    tokens.push_back({LEXICAL_ERROR, current});
                }
                current.clear();
            }
            tokens.push_back({OPERATOR, string(1, ch)});
            continue;
        } else if (isPunctuation(ch)) {
            if (!current.empty()) {
                if (isKeyword(current)) {
                    tokens.push_back({KEYWORD, current});
                } else if (isIdentifier(current)) {
                    tokens.push_back({IDENTIFIER, current});
                    addToSymbolTable(current);
                } else if (isConstant(current)) {
                    tokens.push_back({CONSTANT, current});
                } else {
                    errors.push_back(current);
                    tokens.push_back({LEXICAL_ERROR, current});
                }
                current.clear();
            }
            tokens.push_back({PUNCTUATION, string(1, ch)});
            continue;
        }

        current += ch;
    }

    if (!current.empty()) {
        if (isKeyword(current)) {
            tokens.push_back({KEYWORD, current});
        } else if (isIdentifier(current)) {
            tokens.push_back({IDENTIFIER, current});
            addToSymbolTable(current);
        } else if (isConstant(current)) {
            tokens.push_back({CONSTANT, current});
        } else {
            errors.push_back(current);
            tokens.push_back({LEXICAL_ERROR, current});
        }
    }
}

void printTokens(const vector<Token>& tokens) {
    cout << "TOKENS:\n";
    for (const auto& token : tokens) {
        string type;
        switch (token.type) {
            case KEYWORD: type = "Keyword"; break;
            case IDENTIFIER: type = "Identifier"; break;
            case CONSTANT: type = "Constant"; break;
            case STRING: type = "String"; break;
            case PUNCTUATION: type = "Punctuation"; break;
            case OPERATOR: type = "Operator"; break;
            case LEXICAL_ERROR: type = "Lexical Error"; break;
        }
        cout << type << ": " << token.value << endl;
    }
}

void printSymbolTable() {
    cout << "\nSYMBOL TABLE:\n";
    for (size_t i = 0; i < symbolTable.size(); ++i) {
        cout << i + 1 << ") " << symbolTable[i] << endl;
    }
}

void printErrors(const vector<string>& errors) {
    if (!errors.empty()) {
        cout << "\nLEXICAL ERRORS:\n";
        for (const auto& error : errors) {
            cout << error << "\n";
        }
    }
}

int main() {
    ifstream inputFile("pract1.c");
    if (!inputFile.is_open()) {
        cerr << "Error: Unable to open source file." << endl;
        return 1;
    }

    string sourceCode((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
    inputFile.close();

    vector<Token> tokens;
    vector<string> errors;

    tokenize(sourceCode, tokens, errors);
    printTokens(tokens);
    printSymbolTable();
    printErrors(errors);

    return 0;
}
