# pragma once

// # include "scop.hpp"

# include <string>
# include <iostream>
# include <ostream>
# include "core/opengl.hpp"
# include "loader/fileLoader.hpp"

class Shader
{
	private:

		unsigned int 	_ID;

		unsigned int	_compilShaderFile(const char* path, GLenum type) const;
		void 			_checkShaderCompil(unsigned int shaderID) const;
		void 			_checkProgramLink(unsigned int programID) const;

		Shader() = delete; 										//Default constructor is not allowed
		Shader(const Shader &other) = delete;					//Copy constructor is not allowed
		Shader		&operator=(const Shader &other) = delete; 	//Assignement operator is not allowed

	public:

		unsigned int		getID() const;
		void				use() const;

		template <typename T>
		void	setUniform(const std::string &name, T value) const;

		// Orthodox Canonical Form
					Shader(const char* vertexPath, const char* fragmentPath);
		virtual 	~Shader();						//Destructor
};
# include <render/Shader.tpp>
