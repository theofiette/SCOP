# pragma once

# include <ostream>
# include <cmath>
# include "core/define.hpp"
# include "math/mat.hpp"

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
		
