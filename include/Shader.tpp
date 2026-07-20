# include <Shader.hpp>

template <typename T>
void Shader::setUniform(const std::string &name, T value) const
{
	GLint loc = glGetUniformLocation(_ID, name.c_str());

	if constexpr (std::is_same_v<T, bool>)
		glUniform1i(loc, static_cast<int>(value));
	else if constexpr (std::is_same_v<T, int>)
		glUniform1i(loc, value);
	else if constexpr (std::is_same_v<T, float>)
		glUniform1f(loc, value);
	else
		std::cerr << "Shader::setUniform: unsupported type" << std::endl;
}