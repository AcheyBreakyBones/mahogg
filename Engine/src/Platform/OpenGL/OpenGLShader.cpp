#include "enpch.h"
#include "OpenGLShader.h"
#include <filesystem>
#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Engine
{
	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")
		{
			return GL_VERTEX_SHADER;
		}
		if (type == "fragment" || type == "pixel")
		{
			return GL_FRAGMENT_SHADER;
		}
		EN_CORE_ASSERT(false, "Unknown shader type!");
		return 0;
	}
		
	OpenGLShader::OpenGLShader(const std::string& path)
	{
		std::string source = ReadFile(path);
		auto shaderSources = PreProcess(source);
		Compile(shaderSources);

		// Extract name from filepath
		std::filesystem::path FP = path;
		// Returns the file's name stripped of the extension
		m_Name = FP.stem().string();
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& 
		vertexSrc, const std::string& fragmentSrc)
		: m_Name(name)
	{
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSrc;
		sources[GL_FRAGMENT_SHADER] = fragmentSrc;
		Compile(sources);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	std::string OpenGLShader::ReadFile(const std::string& path)
	{
		std::string result;
		std::ifstream in(path, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else
		{
			EN_CORE_ERROR("Could not open file '{0}'", path);
		}
		return result;
	}

	// Deduces the shader type (vertex or fragment) 
	// by reading the shader file for "#type"
	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(
		const std::string& source)
	{
		std::unordered_map<GLenum, std::string> shaderSources;
		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		// Start of shader type declaration line
		size_t typePos = source.find(typeToken, 0);
		while (typePos != std::string::npos)
		{
			// End of shader type declaration line
			size_t EOL = source.find_first_of("\r\n", typePos);	
			EN_CORE_ASSERT(EOL != std::string::npos, "Syntax Error");

			// Move to the character after typeToken
			// Start of shader type name (after "#type " keyword)
			size_t begin = typePos + typeTokenLength + 1;
			std::string type = source.substr(begin, EOL - begin);
			EN_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");

			// Start of shader code after shader type declaration line
			size_t codePos = source.find_first_not_of("\r\n", EOL);
			EN_CORE_ASSERT(codePos != std::string::npos, "Syntax Error");
			// Start of next shader type declaration line
			typePos = source.find(typeToken, codePos);

			// If there are no more shader types to read, then read the current
			// shader code into its designated type index
			if (typePos == std::string::npos)
			{
				shaderSources[ShaderTypeFromString(type)] = source.substr(codePos);
			}
			// If there is another shader type following the current one, then only
			// read the shader code that goes up to that line
			else
			{
				shaderSources[ShaderTypeFromString(type)] = source.substr(codePos,
					typePos - codePos);
			}
			/*
			shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos, pos - 
				(nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
			*/
		}

		return shaderSources;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		GLuint program = glCreateProgram();
		EN_CORE_ASSERT(shaderSources.size() <= 2, "No more than 2 shaders are allowed!")
		std::array<GLuint, 2> glShaderIDs;
		uint32_t glShaderIDIndex = 0;
		for (auto& keyValue : shaderSources)
		{
			GLuint type = keyValue.first;
			const std::string& source = keyValue.second;

			// Create an empty shader handle
			GLuint shader = glCreateShader(type);

			// Send the shader source code to GL
			// Note that std::string's .c_str is NULL character terminated.
			const GLchar* sourceCStr = source.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);
			
			// Compile the shader
			glCompileShader(shader);
			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				// We don't need the shader anymore.
				glDeleteShader(shader);
				EN_CORE_ERROR("{0}", infoLog.data());
				EN_CORE_ASSERT(false, "Shader compilation failure!");
				break;
			}
			glAttachShader(program, shader);
			glShaderIDs[glShaderIDIndex++] = shader;
		}
		m_RendererID = program;

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = GL_FALSE;
		// NOTE: Why does &isLinked need to be cast as an int*?
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			for (auto id : glShaderIDs)
			{
				glDeleteShader(id);
			}

			EN_CORE_ERROR("{0}", infoLog.data());
			EN_CORE_ASSERT(false, "Shader link failure!");
			return;
		}

		// Always detach and delete shaders after a successful link.
		for (auto id : glShaderIDs)
		{
			glDetachShader(program, id);
			glDeleteShader(id);
		}
  }

  void OpenGLShader::Bind() const
  {
		glUseProgram(m_RendererID);
  }

  void OpenGLShader::Unbind() const
  {
		glUseProgram(0);
  }

  void OpenGLShader::UploadUniformInt(const std::string& name, int value)
  {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
  }

  void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
  {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, value);
  }

  void OpenGLShader::UploadUniformFloat2(const std::string& name, glm::vec2& value)
  {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, value.x, value.y);
  }

  void OpenGLShader::UploadUniformFloat3(const std::string& name, glm::vec3& value)
  {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
  }

  void OpenGLShader::UploadUniformFloat4(const std::string& name, glm::vec4& value)
  {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
  }

  void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
  {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
  }

  void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
  {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
  }
}