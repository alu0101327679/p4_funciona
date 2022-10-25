#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <regex>

struct data {
    int linea;
    std::string contenido;
    std::string tipo;
};

const std::regex varDeclarationPattern("(int|double)\\s+([a-zA-Z_][\\w_]*\\s*((=\\s*\\d+(\\.\\d+)?)|(\\{\\s*\\d+(\\.\\d+)?\\s*\\}))?)\\s*;\\s*$");
const std::regex loopDeclarationPattern("(while\\s*\\(.+\\)|for\\s*\\(.*?;.*?;.*?\\))\\s*(;|\\{)");
const std::regex mainDeclarationPattern("int\\s+main\\s*\\((void|int\\s+argc\\s*,\\s*char\\s*\\*\\s*argv\\s*\\[\\s*\\]\\s*)?\\)");
const std::regex lineCommentPattern("\\/\\/.*");
const std::regex firstMultilineCommentPattern("\\/\\*.*");
const std::regex lastMultilineCommentPattern(".*?\\*\\/");

class Programa
{
  private:
    bool main_bool_ = false;
    data descripcion_;
    std::vector<data> comentarios_;
    std::vector<data> bucles_;
    std::vector<data> variables_;
    std::string nombre_;

  public:
    Programa();
    ~Programa();
    void analizar(std::string);
    void mostrar(std::ostream& os);
};