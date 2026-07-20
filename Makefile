NAME= SCOP
COMP= c++
CFLAGS= -Wall -Wextra -Werror
LDFLAGS= -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl
INCLUDES= -Iinclude
BUILD= .build/

CPPSRC =	src/main.cpp \
			src/Shader.cpp \
			src/exit.cpp
			
CSRC   = src/glad.c

OBJS = $(addprefix $(BUILD), $(CPPSRC:.cpp=.o)) \
       $(addprefix $(BUILD), $(CSRC:.c=.o))

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