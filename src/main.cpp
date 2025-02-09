#include <iostream>
#include "window.hpp"
#include "shader.hpp"
unsigned int shaderProgram;
unsigned int VAO;
void render()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
int main()
{
    Window window(1920, 1080, "SAGE - Engine");
    // Read in shader file
    // const char *vertex_shader = "#version 330 core\n"
    //                             "layout (location = 0) in vec3 aPos;\n"
    //                             "void main()\n"
    //                             "{\n"
    //                             "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    //                             "}\0";

    unsigned int vertexShaderID;
    vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    // 1 - ID of shader
    // 2 - Total number of strings ( only one in this case which is the whole program)
    // 3 - The source file string
    // 4 - NULL
    const char *vertex_shader = read_file("./shaders/vert.glsl").c_str();

    glShaderSource(vertexShaderID, 1, &vertex_shader, NULL);
    glCompileShader(vertexShaderID);
    // Check if shader compilation is a success..
    {
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShaderID, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                      << infoLog << std::endl;
            exit(-1);
        }
    }

    // ----------------------------------------------------------------------
    const char *fragment_shader = read_file("./shaders/frag.glsl").c_str();
    // const char *fragment_shader = "#version 330 core\n"
    //                               "out vec4 FragColor;\n"
    //                               "void main()\n"
    //                               "{\n"
    //                               "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    //                               "}";

    unsigned int fragmentShaderID;
    fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    // 1 - ID of shader
    // 2 - Total number of strings ( only one in this case which is the whole program)
    // 3 - The source file string
    // 4 - NULL
    glShaderSource(fragmentShaderID, 1, &fragment_shader, NULL);
    glCompileShader(fragmentShaderID);
    // Check if shader compilation is a success..
    {
        int success;
        char infoLog[512];
        glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShaderID, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                      << infoLog << std::endl;
            exit(-1);
        }
    }

    // a Shader program contains multiple combined shaders.
    // We can select one shader program that will be used when we issue render calls.

    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShaderID);
    glAttachShader(shaderProgram, fragmentShaderID);
    glLinkProgram(shaderProgram);
    // Check if shader program linking is a success..
    {
        int success;
        char infoLog[512];
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                      << infoLog << std::endl;
            exit(-1);
        }
    }

    // Delete shaders once we link them
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    float vertices[] = {
        0.5f, 0.5f, 0.0f,   // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f   // top left
    };
    unsigned int indices[] = {
        // note that we start from 0!
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    // Bind VAO first. then bind VBOs and attrib pointers to this VAO.
    // only need to bind the VAO to get same results.

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    unsigned int VBO;
    // we generate a general "buffer" with an id of 1.
    glGenBuffers(1, &VBO);
    // GL_ARRAY_BUFFER is the "type" of the VBO structure.
    // We can only bind/select one buffer of a particular type at a time. multiple of different types at a time is okay.
    // Once selected , any buffer calls will reference that buffer.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    /*
        We send our vertex data to this particular buffer.
        1 - Type of buffer (VBO in this case)
        2 - Total size of vertices. (3 vertices with 3 Dimensions each, 9 floats total, each float is 4 bytes so 36 bytes is the total size.)
        3 - The array reference to copy from the cpu.
        4 - Specifices how GPU should manage the data.
            - GL_STATIC_DRAW: the data is sent only once and used many times. (fastest)
            - GL_STREAM_DRAW: the data is sent only once and used by the GPU at most a few times.(faster)
            - GL_DYNAMIC_DRAW: the data is changed a lot and used many times. (slow)
    */
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int EBO;
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    unsigned int vertex_attribute_layout = 0;
    unsigned int SHOULD_NORMALIZE = GL_FALSE;
    unsigned int vertex_data_type = GL_FLOAT;
    unsigned int dimension_of_vertex = 3;
    unsigned int stride_or_vertex_size = 3 * sizeof(float);
    glVertexAttribPointer(vertex_attribute_layout, dimension_of_vertex, vertex_data_type, SHOULD_NORMALIZE, stride_or_vertex_size, (void *)0);
    glEnableVertexAttribArray(vertex_attribute_layout);

    window.run(render);
    return 0;
}

/*
Bind VAO
BindBuffer / select buffer  VBO
send BufferData vertex_data

set Vertex attrib pointer
set enable attrib array

render loop :
    use shader program
    bind VAO
    use function to draw using given vertices.
*/