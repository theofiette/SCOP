#ifndef DEFINE_HPP
# define DEFINE_HPP

# define WIDTH		1920.0f
# define HEIGHT 	1080.0f

# define FOV		90.0f
# define ZNEAR		0.1f
# define ZFAR		1000.0f

# define SENSIVITY_MIN	0.1f
# define SENSIVITY_MAX	1.0f
# define SENSIVITY_STEP	0.1f
# define SENSI_BASE	1.0f

# define CHANNELS_IN_RGB 	3
# define CHANNELS_IN_RGBA	4

# define BACKGROUND_COLOR 0.2, 0.2, 0.2, 1.0

// Shaders
# define TEXTURE_SHADER_VERT	"src/SHADERS/shader_texture.vert"
# define TEXTURE_SHADER_FRAG	"src/SHADERS/shader_texture.frag"
# define COLOR_SHADER_VERT		"src/SHADERS/shader_color.vert"
# define COLOR_SHADER_FRAG		"src/SHADERS/shader_color.frag"

// Texture
# define BASIC_TEXTURE_PATH		"resources/textures/dog.tga"

// used for better hash scattering
# define GOLDEN_RATIO	0x9e3779b9

#endif