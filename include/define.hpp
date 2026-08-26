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

# define TEXTURE_STEP 0.02f

// Shaders

# define SHADER_VERT "src/SHADERS/shader.vert"
# define SHADER_FRAG "src/SHADERS/shader.frag"

// Texture
# define BASIC_TEXTURE_PATH		"resources/textures/dog.tga"

// used for better hash scattering
# define GOLDEN_RATIO	0x9e3779b9

// error codes
# define ERR_CODE_DEFAULT "Program terminated after encountering an undocumented error"
# define ERR_CODE_0 "Invalid arguments"
# define ERR_CODE_1 "Failed initialisation of glfw"
# define ERR_CODE_2 "Could not create a glfw window"
# define ERR_CODE_3 "Could not load glad functions"
# define ERR_CODE_4 "Shader compilation error"
# define ERR_CODE_5 "Shader linkage error"
# define ERR_CODE_6 "Invalid texture format"
# define ERR_CODE_7 "Invalid texture channels"
# define ERR_CODE_8 "Invalid object format"
# define ERR_CODE_9 "fileLoader could not open or read file"

#endif