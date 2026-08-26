# pragma once

# include <ostream>
# include <cmath>
# include "define.hpp"
# include "structs.hpp"

class Camera
{

	private:

		mat4x4	_projection;

		void	_setProjectionMatrix();

	public:

		const mat4x4 &getProjectionMatrix() const;

		// Orthodox Canonical Form
					Camera(); 						
					Camera(const Camera &other);	
		Camera		&operator=(const Camera &other);
		virtual 	~Camera();						
	
};
		
