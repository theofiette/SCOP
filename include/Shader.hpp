# pragma once

# include <scop.hpp>

# include <string>
# include <fstream>
# include <sstream>
# include <iostream>

class Shader
{
	private:

		unsigned int 	_ID;

		unsigned int	_compilShaderFile(const char* path, GLenum type) const;
		void 			_checkShaderCompil(unsigned int shaderID) const;
		void 			_checkProgramLink(unsigned int programID) const;

		Shader(); 						//Default constructor is not allowed

	public:

		unsigned int		getID() const;

		void				use() const;

		template <typename T>
		void	setUniform(const std::string &name, T value) const;

		// Orthodox Canonical Form
					Shader(const char* vertexPath, const char* fragmentPath);
					Shader(const Shader &other);	//Copy constructor
		virtual 	~Shader();						//Destructor
		Shader		&operator=(const Shader &other); //Assignement operator
};
		
# include <Shader.tpp>
