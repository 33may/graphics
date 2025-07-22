#include"shaderClass.h"

std::string loadFileSrc(const char* path){
    std::ifstream in(path, std::ios::binary);

    if (!in) {
        std::perror(path);
        return {};
    }

    return std::string((std::istreambuf_iterator<char>(in)),
                        std::istreambuf_iterator<char>());
}


Shader::Shader(const char* vertextFilePath, const char* fragmentFilePath){

    // read source files
    std::string vertexSrc = loadFileSrc(vertextFilePath);
    std::string fragmentSrc = loadFileSrc(fragmentFilePath);

    // cast to c strings
    const GLchar* srcVertexPtr = vertexSrc.c_str();
    const GLchar* srcFragmentPtr = fragmentSrc.c_str();

    
    // initialize vertexShader ptr
    GLuint vertexShader;

    // create vertex shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // insert source into shader
    glShaderSource(vertexShader, 1, &srcVertexPtr, nullptr);

    // compile vertex shader
    glCompileShader(vertexShader);

    compileErrors(vertexShader, "VERTEX");
        
    // initialize fragmentShader ptr
    GLuint fragmentShader;

    // create fragment shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // insert source into shader
    glShaderSource(fragmentShader, 1, &srcFragmentPtr, nullptr);

    // compile vertex shader
    glCompileShader(fragmentShader);

    compileErrors(fragmentShader, "FRAGMENT");

    // create program
    ID = glCreateProgram();

    // attach vertex to the program
    glAttachShader(ID, vertexShader);

    // attach fragment to the program
    glAttachShader(ID, fragmentShader);

    // link components inside program
    glLinkProgram(ID);

    compileErrors(ID, "PROGRAM");

    // delete components, they are included in program
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Activate(){
    glUseProgram(ID);
}

void Shader::Delete(){
    glDeleteProgram(ID);
}

void Shader::compileErrors(unsigned int shader, const char* type){
    GLint has_compiled;
    char infolog[1024];

    if (type != "PROGRAM"){
        glGetShaderiv(shader, GL_COMPILE_STATUS, &has_compiled);
        if (has_compiled == GL_FALSE){
            glGetShaderInfoLog(shader, 1024, NULL, infolog);
            std::cout << "SHADER_COMPILATION_FAILED for: " << type << "\n" << infolog << std::endl; 
        }
    }
    else{
        glGetShaderiv(shader, GL_COMPILE_STATUS, &has_compiled);
        if (has_compiled == GL_FALSE){
            glGetProgramInfoLog(shader, 1024, NULL, infolog);
            std::cout << "SHADER_LINKING_FAILED for: " << type << "\n" << infolog << std::endl; 
        }
    }
}