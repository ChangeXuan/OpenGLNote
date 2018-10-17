#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;
class Shader {
	public:
		unsigned int ID;

		Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath=nullptr) {
			// shader代码字符串变量
			string vertexCode;
			string fragmentCode;
			string geometryCode;
			// 顶点shader和片段shader的文件流
			ifstream vShaderFile;
			ifstream fShaderFile;
			ifstream gShaderFile;
			// 确保ifstream能抛出错误
			vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        	fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        	gShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
		
        	try {
        		// 打开文件
        		vShaderFile.open(vertexPath);
        		fShaderFile.open(fragmentPath);

        		// 创建文件流并读取文件信息
        		stringstream vShaderStream, fShaderStream;
        		vShaderStream << vShaderFile.rdbuf();
        		fShaderStream << fShaderFile.rdbuf();

        		// 关闭文件
        		vShaderFile.close()
        		fShaderFile.close();

        		// 把文件流信息转换为代码字符串
        		vertexCode = vShaderStream.str();
        		fragmentCode = fShaderStream.str();

        		// ???
        		if (geometryPath != nullptr) {
        			gShaderFile.open(geometryPath);
        			stringstream gShaderStream;
        			gShaderStream << gShaderFile.rdbuf();
        			gShaderFile.close();
        			geometryCode = gShaderStream.str();
        		}
        	} catch (ifstream::failure e) {
        		cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl; 
        	}   

        	// 把cpp的字符串转为c语言的字符串
        	const char* vShaderCode = vertexCode.c_str();
        	const char* fShaderCode = fragmentCode.c_str();    	

        	unsigned int vertex, fragment;
        	// 顶点着色器
        	vertex = glCreateShader(GL_VERTEX_SHADER);
        	glShaderSource(vertex, 1, &vShaderCode, NULL);
        	glCompileShader(vertex);
        	checkCompileErrors(vertex, "VERTEX");
        	// 片段着色器
        	fragment = glCreateShader(GL_FRAGMENT_SHADER);
        	glShaderSource(fragment, 1, &fShaderCode, NULL);
        	glCompileShader(fragment);
        	checkCompileErrors(fragment, "FRAGMENT");

        	// 几何形状
        	unsigned int geometry;
        	if(geometryPath != nullptr) {
            	const char * gShaderCode = geometryCode.c_str();
	            geometry = glCreateShader(GL_GEOMETRY_SHADER);
	            glShaderSource(geometry, 1, &gShaderCode, NULL);
	            glCompileShader(geometry);
	            checkCompileErrors(geometry, "GEOMETRY");
        	}

        	// 创建着色器程序
        	ID = glCreateProgram();
        	glAttachShader(ID,vertex);
        	glAttachShader(ID,fragment);
        	if (geometryPath != nullptr) {
        		glAttachShader(ID,geometry);
        	}
        	glLinkPrograme(ID);
        	checkCompileErrors(ID, "PROGRAM");

        	// 删除
        	glDeleteShader(vertex);
	        glDeleteShader(fragment);
	        if(geometryPath != nullptr) {
	        	glDeleteShader(geometry);
	        }
		}

		// 使用着色器程序
		void use() {
			glUseProgram(ID);
		}

		// 动态设置uniform变量
		// 外部设置一个bool值
		void setBool(const string &name, bool value) const {
			glUniformli(glGetUniformLocation(ID, name.c_str), (int)value);
		}
		// 外部设置一个int值
		void setInt(const std::string &name, int value) const { 
	        glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
	    }
	    // 外部设置一个float值
	    void setFloat(const std::string &name, float value) const { 
	        glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
	    }
	    // 外部设置2维向量（传入一组数据）
	    void setVec2(const std::string &name, const glm::vec2 &value) const { 
	        glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
	    }
	    // 外部设置2维向量（每个数字都要传入）
	    void setVec2(const std::string &name, float x, float y) const { 
	        glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y); 
	    }
	    // 外部设置3维向量（传入一组数据）
	    void setVec3(const std::string &name, const glm::vec3 &value) const { 
	        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
	    }
	    // 外部设置3维向量（每个数字都要传入）
	    void setVec3(const std::string &name, float x, float y, float z) const { 
	        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z); 
	    }
	    // 外部设置4维向量（传入一组数据）
	    void setVec4(const std::string &name, const glm::vec4 &value) const { 
	        glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
	    }
	    // 外部设置4维向量（每个数字都要传入）
	    void setVec4(const std::string &name, float x, float y, float z, float w) { 
	        glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w); 
	    }
	    // 外部设置二维数组
	    void setMat2(const std::string &name, const glm::mat2 &mat) const {
	        glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	    }
	    // 外部设置三维数组
	    void setMat3(const std::string &name, const glm::mat3 &mat) const {
	        glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	    }
	    // 外部设置4维数组
	    void setMat4(const std::string &name, const glm::mat4 &mat) const {
	        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	    }


	private:
		void checkCompileErrors(GLuint shader, string type) {
			GLint success;
			GLchar infoLog[512];
			if (type != "PROGRAM") {
				glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
				if (!success) {
					 glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                     cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << endl;
				}
			} else {
            	glGetProgramiv(shader, GL_LINK_STATUS, &success);
            	if(!success) {
                	glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                	std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            	}
        	}
		}
};
#endif