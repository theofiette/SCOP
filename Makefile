NAME= SCOP
COMP= c++
CFLAGS= -Wall -Wextra -Werror -g
LDFLAGS= -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl
INCLUDES= -Iinclude -Ithird-party
BUILD= .build/

EXTSRC =	third-party/glad/glad.c

CPPSRC =	src/core/exit.cpp \
			src/core/init.cpp \
			src/core/main.cpp \
			src/input/inputs.cpp \
			src/loader/fileLoader.cpp \
			src/math/vectorMath.cpp \
			src/mesh/Mesh.cpp \
			src/render/render.cpp \
			src/render/Camera.cpp \
			src/render/Material.cpp \
			src/render/Shader.cpp \
			src/render/Texture.cpp 
			
OBJS = $(addprefix $(BUILD), $(CPPSRC:.cpp=.o)) \
       $(addprefix $(BUILD), $(EXTSRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(COMP) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

$(BUILD)%.o: %.cpp
	@mkdir -p $(dir $@)
	$(COMP) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD)%.o: %.c
	@mkdir -p $(dir $@)
	$(COMP) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) -r $(BUILD)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re