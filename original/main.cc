#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <regex>

bool main_bool = false;

struct data {
    int linea;
    std::string contenido;
    std::string tipo;
};

data descripcion;

int main(int argc, char *argv[])
{
    // std::string expresion = "^https?:\/\/([a-zA-Z0-9-]+)\.(es|com|net)$";

    std::regex varDeclarationPattern("(int|double)\\s+([a-zA-Z_][\\w_]*\\s*((=\\s*\\d+(\\.\\d+)?)|(\\{\\s*\\d+(\\.\\d+)?\\s*\\}))?)\\s*;\\s*$");
    std::regex loopDeclarationPattern("(while\\s*\\(.+\\)|for\\s*\\(.*?;.*?;.*?\\))\\s*(;|\\{)");
    std::regex mainDeclarationPattern("int\\s+main\\s*\\((void|int\\s+argc\\s*,\\s*char\\s*\\*\\s*argv\\s*\\[\\s*\\]\\s*)?\\)");
    std::regex lineCommentPattern("\\/\\/.*");
    std::regex firstMultilineCommentPattern("\\/\\*.*");
    std::regex lastMultilineCommentPattern(".*?\\*\\/");

    std::regex for_while_regex("(\\s{2}*)?(for|while)\\s\\(.*\\)\\s\\{");

    std::ifstream file(argv[1]);
    std::string linea;
    int n_linea = 1;

    std::vector<data> comentarios;
    std::vector<data> bucles;
    std::vector<data> variables;
    
    while (std::getline(file, linea))
    {
        std::smatch cm;
        std::string tipo="";
        std::regex_search(linea, cm, lineCommentPattern);

        if (std::regex_search(linea, cm, firstMultilineCommentPattern))
        {
            std::string contenido("");
            // std::cout << "Detectado principio de bloque de comando" << std::endl;
            contenido += cm[0].str();
            while (std::getline(file, linea))
            {
                
                std::regex_search(linea, cm, lastMultilineCommentPattern);
                if (cm.size() > 0)
                {
                    contenido += cm[0].str() + "\n";
                    // std::cout << "Detectado final de bloque de comando" << std::endl;
                    n_linea++;
                    break;
                }
                contenido += linea + "\n";
                n_linea++;
            }
            tipo = "comentario";
            descripcion.linea = n_linea;
            descripcion.contenido = contenido;
            descripcion.tipo = tipo;
            // comentarios.push_back({n_linea, contenido, tipo});
            // std::cout << contenido << std::endl;


        }else if (std::regex_search(linea, cm, varDeclarationPattern))
        {
            tipo = cm[1];
            variables.push_back({n_linea, cm[2].str(), tipo});
            // std::cout << "detectado int: " << cm[1] << std::endl; //<< cm[1] << std::endl
            // std::cout << "int en cuestion" << cm[2] << std::endl; //cm[2] << std::endl
            
            // std::cout << "la linea es: " << n_linea << std::endl;
        } else if (std::regex_search(linea, cm, loopDeclarationPattern))
        {
            tipo = "bucle";
            // std::cout << "loop detectado" << std::endl;
            // std::cout << ((cm[0].str().find("while") != std::string::npos) ? "while" : "for") << std::endl;
            // std::cout << "la linea es: " << n_linea << std::endl;
            bucles.push_back({n_linea, ((cm[0].str().find("while") != std::string::npos) ? "while" : "for"), tipo});


        } else if (std::regex_search(linea, cm, mainDeclarationPattern))
        {
            // tipo = "main";
            // std::cout << "Main encontrado" << std::endl;
            // std::cout << cm[0] << std::endl;
            // std::cout << "la linea es: " << n_linea << std::endl;
            // datos.push_back({"main", tipo});
            main_bool = true;

        }else if (std::regex_search(linea, cm, lineCommentPattern))
        {
            tipo = "comentario";
            // std::cout << "Comentario encontrado" << std::endl;
            // std::cout << cm[0] << std::endl << std::endl;
            // std::cout << "la linea es: " << n_linea << std::endl;
            comentarios.push_back({n_linea, cm[0].str(), tipo});
        }
        
    n_linea++;   
    }

    std::cout << "PROGRAM: " << argv[1] << std::endl;

    std::cout << "DESCRIPTION: " << std::endl;
    std::cout << descripcion.contenido << std::endl;

    std::cout << "VARIABLES: " << std::endl;
    for (auto i : variables)
    {

        std::cout << "[Linea " <<i.linea << " ]: " << i.tipo << ": " << i.contenido << std::endl;

    }
    std::cout << std::endl;

    std::cout << "LOOPS: " << std::endl;
    for (auto i : bucles)
    {

        std::cout << "[Linea " <<i.linea << " ]: " << i.contenido << std::endl;
    }
    std::cout << std::endl;

    std::cout << "MAIN: ";
    if (main_bool)
    {
        std::cout << "\nTRUE" << std::endl;
    }else{
        std::cout << "\nFALSE" << std::endl;
    }
    std::cout << std::endl;

    std::cout << "COMMENTS: " << std::endl;
    for (auto i : comentarios)
    {
        std::cout << "[Linea " << "1 - " << descripcion.linea << "] " << "DESCRIPCION" << std::endl;
        std::cout << "[Linea " <<i.linea << " ]: "<<  i.contenido << std::endl;
        
    }
    std::cout << std::endl;





}