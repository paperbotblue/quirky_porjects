#define GLEW_STATIC

#include "../inc/glew.h"
#include "../inc/glfw3.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <csignal>
#include <string>

#define DEBUG 1
#if DEBUG
#define print(x) std::cout << x << std::endl
#else
#define print(x)
#endif

#define ASSERT(x) if(!x) raise(SIGABRT)
#define GLCall(x) GLClearError(); \
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__ ))

static void GLClearError()
{
    while(glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* function, const char* file, int line)
{
    while(GLenum  error = glGetError())
    {
        print("[OpenGL Error] : " << error << "\nFile " << file << " \nFunction: " << function << "\nLine: " << line);
        return false;
    }
    return true;
}

struct shaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

static shaderProgramSource parseShader(const std::string& filepath) {
    std::fstream stream(filepath);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while(getline(stream,line))
    {
        if(line.find("#shader") != std::string::npos)
        {
            if(line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if(line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else
        {
            ss[(int)type] << line << "\n";
        }

    }
    return {ss[0].str(),ss[1].str()};
}

static unsigned int compileShader(unsigned int type,const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id,1,&src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id,GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length* sizeof(char));
        glGetShaderInfoLog(id, length ,&length, message);
        print("Failed to compile shader" << (type == GL_VERTEX_SHADER ? "vertex" : "Fragment"));
        glDeleteShader(id);
    }
    return id;
}

static unsigned int createShader(const std::string& vertexShader,const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER,vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER,fragmentShader);
    glAttachShader(program,vs);
    glAttachShader(program,fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteProgram(vs);
    glDeleteProgram(fs);
    return program;
}

int main()
{
    GLFWwindow* window;
    /* Initialize the library */
    if (!glfwInit()) {return -1;}

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    GLCall(glfwMakeContextCurrent(window));

    if(glewInit() != GLEW_OK)
        print("Error: glew failed to initialize");

    std::cout << glGetString(GL_VERSION) << std::endl;

    float positions[12] = {
            -0.5f,-0.5f,
             0.5f,-0.5f,
             0.5f, 0.5f,
            -0.5f, 0.5f,
    };

    unsigned int indices[6] ={
        0,1,2,
        2,3,0

    };

    unsigned int glBuffer;
    GLCall(glGenBuffers(1,&glBuffer));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER,glBuffer));
    GLCall(glBufferData(GL_ARRAY_BUFFER,6* 2 *sizeof(float),positions,GL_STATIC_DRAW));

    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,sizeof(float)*2,(const void*)0));

    unsigned int ibo;
    GLCall(glGenBuffers(1,&ibo));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ibo));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER,6 * sizeof(unsigned int),indices,GL_STATIC_DRAW));

    shaderProgramSource source = parseShader("/home/guildarts/CLionProjects/GuildGauntlet/res/shaders/basic.shader");

    unsigned int shader = createShader(source.VertexSource,source.FragmentSource);
    glUseProgram(shader);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);


        GLCall(glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT, nullptr));
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}
