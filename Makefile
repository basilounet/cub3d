##========== SOURCES ==========##

SRC =	utils/utils.c \
		parser/parser.c \
		parser/color.c \
		parser/checker_map.c \
		parser/checker_color.c \
		parser/checker_param.c \
		parser/player.c \
		parser/param.c \
		parser/map.c \
		execution/raycaster.c \
		execution/movment.c \
		execution/ft_hooks.c \
		utils/vector_utils.c \
		drawing/draw_shapes.c \
		unleak.c \
		error.c \
		main.c

SRC_B =	utils/utils_bonus.c \
		parser/parser_bonus.c \
		parser/color_bonus.c \
		parser/checker_map_bonus.c \
		parser/checker_color_bonus.c \
		parser/checker_param_bonus.c \
		parser/player_bonus.c \
		parser/param_bonus.c \
		parser/map_bonus.c \
		pause/pause.c \
		pause/buttons_utils.c \
		pause/buttons_callback.c \
		execution/raycaster_bonus.c \
		execution/movment_bonus.c \
		execution/ft_hooks_bonus.c \
		utils/vector_utils_bonus.c \
		drawing/minimap_bonus.c \
		drawing/draw_lines_bonus.c \
		drawing/draw_shapes_bonus.c \
		unleak_bonus.c \
		error_bonus.c \
		main_bonus.c

##========== NAMES ==========##

NAME = cub3D
BONUS = cub3D_bonus
SRCS_DIR = src/
OBJS_DIR = obj/
SRCS_B_DIR = src_bonus/
OBJS_B_DIR = obj_bonus/
LIBFT_DIR = libft/
LIBFT = libft.a
INCLUDE_DIR = includes
INCLUDE_B_DIR = includes_bonus

##========== OBJECTS ==========##

OBJS = $(addprefix $(OBJS_DIR),$(SRC:.c=.o))
OBJS_B = $(addprefix $(OBJS_B_DIR),$(SRC_B:.c=.o))

##========== COLORS ==========##

BASE_COLOR 	=		\033[0;39m
BLACK		=		\033[30m
GRAY 		=		\033[0;90m
DARK_GRAY	=		\033[37m
RED 		=		\033[0;91m
DARK_GREEN	=		\033[32m
DARK_RED	=		\033[31m
GREEN 		=		\033[0;92m
ORANGE 		=		\033[0;93m
DARK_YELLOW	=		\033[33m
BLUE 		=		\033[0;94m
DARK_BLUE	=		\033[34m
MAGENTA		=		\033[0;95m
DARK_MAGENTA=		\033[35m
CYAN 		=		\033[0;96m
WHITE		=		\033[0;97m

##========== COMPILATOR ==========##

CC = clang

##========== FLAGS ==========##

CFLAGS = -Wall -Wextra -Werror
LDFLAGS = $(LIBS)
LIBS = -I$(INCLUDE_DIR) -I$(INCLUDE_B_DIR) -I$(LIBMLX)/include -I$(LIBFT_INCLUDE)
LIBFT_INCLUDE = $(LIBFT_DIR)includes/
MLX_INCLUDE_FLAGS = -I/usr/include -Imlx_linux -O3 -c
MLXFLAGS = -L$(LIBMLX)/build -lmlx42 -ldl -lglfw -pthread -lm
LIBMLX	:= ./MLX42

##========== MODES ==========##

TIMER = 0.0
IS_PRINT = 1

ifdef DEBUG
    CFLAGS += -g
	LDFLAGS += -D DEBUG=42
	DEBUG_MODE = 1
endif

ifdef FAST
	J4 = -j$(nproc)
endif

ifdef FSANITIZE
	LDFLAGS += -fsanitize=address
	FSANITIZE_MODE = 1
endif

##========== ANIMATIONS ==========##

NUM_SRC = $(words $(SRC))
INDEX = 0
NUMBER_OF_ANIMATION = 1
ifndef
	ANIMATION_RATE = 100
endif

##========== COMPILATION ==========##

all : libmlx libft $(NAME)

bonus : libmlx libft $(BONUS)

libft :
	@DEBUG=$(DEBUG_MODE) TIMER=$(TIMER) IS_PRINT=$(IS_PRINT) FSANITIZE=$(FSANITIZE_MODE) make -C $(LIBFT_DIR) --no-print-directory $(J4)

libmlx:
	@if [ ! -d "$(LIBMLX)" ]; then \
		echo "$(DARK_GRAY)Directory $(LIBMLX) does not exist. Cloning the repository...$(BASE_COLOR)"; \
		git clone https://github.com/codam-coding-college/MLX42.git; \
	fi
	@cmake $(LIBMLX) -B $(LIBMLX)/build
	@make -C $(LIBMLX)/build --no-print-directory -j$(nproc)

$(NAME) : $(OBJS)
	@$(CC) -o $(NAME) $(CFLAGS) $(OBJS) $(LDFLAGS) $(MLXFLAGS) $(LIBFT_DIR)$(LIBFT)
	@echo "$(GREEN)-= cub3D compiled =-$(BASE_COLOR)"

$(BONUS) : $(OBJS_B)
	@$(CC) -o $(BONUS) $(CFLAGS) $(OBJS_B) $(LDFLAGS) $(MLXFLAGS) $(LIBFT_DIR)$(LIBFT)
	@echo "$(GREEN)-= cub3D compiled =-$(BASE_COLOR)"

clean :
	@rm -rf $(OBJS_DIR)
	@rm -rf $(LIBMLX)/build
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory

fclean : clean
	@rm -rf $(NAME)
	@rm -rf $(BONUS)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "$(CYAN)Files cleaned$(BASE_COLOR)"

re : fclean all

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
ifeq ($(IS_PRINT),1)
	@sleep $(TIMER)
	@clear
	@echo "$(GREEN)-= Compiling cub3D =-$(BASE_COLOR)"
	$(animations)
	$(loading)
	$(file_size_graph)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(LDFLAGS) $(MLX_INCLUDE_FLAGS) -c $< -o $@
else
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(LDFLAGS) $(MLX_INCLUDE_FLAGS) -c $< -o $@
endif

$(OBJS_B_DIR)%.o : $(SRCS_B_DIR)%.c
ifeq ($(IS_PRINT),1)
	@sleep $(TIMER)
	@clear
	@echo "$(GREEN)-= Compiling cub3D =-$(BASE_COLOR)"
	$(animations)
	$(loading)
	$(file_size_graph)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(LDFLAGS) $(MLX_INCLUDE_FLAGS) -c $< -o $@
else
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(LDFLAGS) $(MLX_INCLUDE_FLAGS) -c $< -o $@
endif

define animations
	$(animation_$(shell expr $(INDEX) / $(ANIMATION_RATE) % $(NUMBER_OF_ANIMATION)))
endef

define loading
	@$(eval INDEX=$(shell expr $(INDEX) + 1))
	@echo "╔═══════════════════════════════════════════════════╗"
	@echo -n "║"
	$(loading_color)
	@echo -n "▓"
	@for i in $$(seq 1 $$(expr $(INDEX) \* 50 / $(NUM_SRC))); do \
		echo -n "▓"; \
	done
	@for i in $$(seq 1 $$(expr 50 - $(INDEX) \* 50 / $(NUM_SRC))); do \
		echo -n " "; \
	done
	@echo "$(BASE_COLOR)║" $(shell expr $(INDEX) \* 100 / $(NUM_SRC))%
	@echo "╚═══════════════════════════════════════════════════╝"
endef

define loading_color
	@if [ $$(expr $(INDEX) - 1) -lt $$(expr $(NUM_SRC) \* 1 / 4) ]; then \
		echo -n "$(DARK_RED)" ; \
	elif [ $$(expr $(INDEX) - 1) -lt $$(expr $(NUM_SRC) \* 2 / 4) ]; then \
		echo -n "$(RED)" ; \
	elif [ $$(expr $(INDEX) - 1) -lt $$(expr $(NUM_SRC) \* 3 / 4) ]; then \
		echo -n "$(ORANGE)" ; \
	else \
		echo -n "$(GREEN)" ; \
	fi
endef

define file_size_graph
	@awk -v size=$(shell stat -c %s $<) 'BEGIN { printf "[ "; for (i=0; i<int(size/1000); i++) printf "#"; printf " ] (%d KB)\n", size/1000 }'
endef

define animation_0
	@echo -n "$(WHITE)"
	@echo " .----------------.  .----------------.  .----------------.  .----------------.  .----------------. " 
	@echo "| .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |"
	@echo "| |     ______   | || | _____  _____ | || |   ______     | || |    ______    | || |  ________    | |"
	@echo "| |   .' ___  |  | || ||_   _||_   _|| || |  |_   _ \    | || |   / ____ \`.  | || | |_   ___ \`.  | |"
	@echo "| |  / .'   \_|  | || |  | |    | |  | || |    | |_) |   | || |   \`'  __) |  | || |   | |   \`. \ | |"
	@echo "| |  | |         | || |  | '    ' |  | || |    |  __'.   | || |   _  |__ '.  | || |   | |    | | | |"
	@echo "| |  \ \`.___.'\  | || |   \ \`--' /   | || |   _| |__) |  | || |  | \____) |  | || |  _| |___.' / | |"
	@echo "| |   \`._____.'  | || |    \`.__.'    | || |  |_______/   | || |   \______.'  | || | |________.'  | |"
	@echo "| |              | || |              | || |              | || |              | || |              | |"
	@echo "| '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |"
	@echo " '----------------'  '----------------'  '----------------'  '----------------'  '----------------' "
	@echo -n "$(BASE_COLOR)"
endef

.PHONY : all libmlx clean fclean re libft