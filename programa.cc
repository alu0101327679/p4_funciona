#include "programa.h"

Programa::Programa()
{
}

Programa::~Programa()
{
}

void
Programa::analizar(std::string nombre){
  std::ifstream file(nombre);
  nombre_ = nombre;
    std::string linea;
    int n_linea = 1;
    
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
            descripcion_.linea = n_linea;
            descripcion_.contenido = contenido;
            descripcion_.tipo = tipo;
            // comentarios.push_back({n_linea, contenido, tipo});
            // std::cout << contenido << std::endl;


        }else if (std::regex_search(linea, cm, varDeclarationPattern))
        {
            tipo = cm[1];
            variables_.push_back({n_linea, cm[2].str(), tipo});
            // std::cout << "detectado int: " << cm[1] << std::endl; //<< cm[1] << std::endl
            // std::cout << "int en cuestion" << cm[2] << std::endl; //cm[2] << std::endl
            
            // std::cout << "la linea es: " << n_linea << std::endl;
        } else if (std::regex_search(linea, cm, loopDeclarationPattern))
        {
            tipo = "bucle";
            // std::cout << "loop detectado" << std::endl;
            // std::cout << ((cm[0].str().find("while") != std::string::npos) ? "while" : "for") << std::endl;
            // std::cout << "la linea es: " << n_linea << std::endl;
            bucles_.push_back({n_linea, ((cm[0].str().find("while") != std::string::npos) ? "while" : "for"), tipo});


        } else if (std::regex_search(linea, cm, mainDeclarationPattern))
        {
            // tipo = "main";
            // std::cout << "Main encontrado" << std::endl;
            // std::cout << cm[0] << std::endl;
            // std::cout << "la linea es: " << n_linea << std::endl;
            // datos.push_back({"main", tipo});
            main_bool_ = true;

        }else if (std::regex_search(linea, cm, lineCommentPattern))
        {
            tipo = "comentario";
            // std::cout << "Comentario encontrado" << std::endl;
            // std::cout << cm[0] << std::endl << std::endl;
            // std::cout << "la linea es: " << n_linea << std::endl;
            comentarios_.push_back({n_linea, cm[0].str(), tipo});
        }
        
    n_linea++;   
    }
    file.close();
}


void 
Programa::mostrar(std::ostream& os){
  os << "PROGRAM: " << nombre_ << std::endl;

    os << "DESCRIPTION: " << std::endl;
    os << descripcion_.contenido << std::endl;

    os << "VARIABLES: " << std::endl;
    for (auto i : variables_)
    {

        os << "[Linea " <<i.linea << " ]: " << i.tipo << ": " << i.contenido << std::endl;

    }
    os << std::endl;

    os << "LOOPS: " << std::endl;
    for (auto i : bucles_)
    {

        os << "[Linea " <<i.linea << " ]: " << i.contenido << std::endl;
    }
    os << std::endl;

    os << "MAIN: ";
    if (main_bool_)
    {
        os << "\nTRUE" << std::endl;
    }else{
        os << "\nFALSE" << std::endl;
    }
    os << std::endl;

    os << "COMMENTS: " << std::endl;
    for (auto i : comentarios_)
    {
        os << "[Linea " << "1 - " << descripcion_.linea << "] " << "DESCRIPCION" << std::endl;
        os << "[Linea " <<i.linea << " ]: "<<  i.contenido << std::endl;
        
    }
    os << std::endl;

}