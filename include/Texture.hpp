# pragma once

# include <scop.hpp>

# include <iostream>

class Texture
{
	private:

		unsigned int	_ID;
		unsigned int	_unit;

		static uint32_t	_bitUnit; //bit pattern to specify which unit are set

		void			_loadTexture(const char* path) const;

	public:

		unsigned int	getID() const;

		// Orthodox Canonical Form
					Texture(); 						//Default constructor
					Texture(const Texture &other);	//Copy constructor
		virtual 	~Texture();						//Destructor
		Texture	&operator=(const Texture &other); //Assignement operator
};
		
