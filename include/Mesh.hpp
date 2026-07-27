# pragma once

# include <scop.hpp>
# include <vector>
# include <map>

typedef struct meshData {

	std::vector<vec3>	vertices;
	std::vector<vec3>	indexes;

} t_meshData;

class Mesh
{
	private:

		unsigned int _VAO;
		unsigned int _VBO;
		unsigned int _EBO;

		// Parsing methods called at instanciation
		void	_parseFile(const char* objFile, meshData &data) const;
		void	_parseVertex(const std::string &line, meshData &data) const;
		void	_parseIndex(const std::string &line, meshData &data) const;

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
		
