# pragma once

# include <scop.hpp>
# include <vector>

class Mesh
{
	private:

		unsigned int _VAO;
		unsigned int _VBO;
		unsigned int _EBO;

		Mesh() = delete;								//Default constructor
		Mesh	&operator=(const Mesh &other) = delete;	//Assignement operator
		Mesh(const Mesh &other) = delete;				//Copy constructor

	public:

		unsigned int	get_VAO() const;
		unsigned int	get_VBO() const;
		unsigned int	get_EBO() const;

		void			draw() const;

		Mesh(const char* objFile);
		virtual 	~Mesh();						//Destructor
};
		
