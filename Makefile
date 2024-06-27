##========== SOURCES ==========##

SRC =	mandatory/utils/utils.c \
		mandatory/parser/parser.c \
		mandatory/parser/color.c \
		mandatory/parser/checker_map.c \
		mandatory/parser/checker_color.c \
		mandatory/parser/checker_param.c \
		mandatory/parser/player.c \
		mandatory/parser/param.c \
		mandatory/parser/map.c \
		mandatory/execution/raycaster.c \
		mandatory/execution/movment.c \
		mandatory/execution/ft_hooks.c \
		mandatory/utils/vector_utils.c \
		mandatory/drawing/draw_shapes.c \
		mandatory/unleak.c \
		mandatory/error.c \
		mandatory/main.c

BONUS_SRC =	bonus/utils/utils_bonus.c \
			bonus/parser/parser_bonus.c \
			bonus/parser/color_bonus.c \
			bonus/parser/checker_map_bonus.c \
			bonus/parser/checker_color_bonus.c \
			bonus/parser/checker_param_bonus.c \
			bonus/parser/player_bonus.c \
			bonus/parser/param_bonus.c \
			bonus/parser/map_bonus.c \
			bonus/execution/raycaster_bonus.c \
			bonus/execution/movment_bonus.c \
			bonus/execution/ft_hooks_bonus.c \
			bonus/utils/vector_utils_bonus.c \
			bonus/drawing/minimap_bonus.c \
			bonus/drawing/draw_lines_bonus.c \
			bonus/drawing/draw_shapes_bonus.c \
			bonus/unleak_bonus.c \
			bonus/error_bonus.c \
			bonus/main_bonus.c

##========== NAMES ==========##

NAME = cub3D
BONUS = cub3D_bonus
SRCS_DIR = src/
OBJS_DIR = obj/
LIBFT_DIR = libft
INCLUDE_DIR = includes

##========== OBJECTS ==========##

OBJS = $(addprefix $(OBJS_DIR),$(SRC:.c=.o))
BONUS_OBJS = $(addprefix $(OBJS_DIR),$(BONUS_SRC:.c=.o))

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
LIBS = -I$(INCLUDE_DIR) -I$(LIBMLX)/include
LIBFT = $(LIBFT_DIR)/libft.a
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

all : libmlx $(NAME)

bonus : libmlx $(BONUS)



libmlx:
	@if [ ! -d "$(LIBMLX)" ]; then \
		echo "$(DARK_GRAY)Directory $(LIBMLX) does not exist. Cloning the repository...$(BASE_COLOR)"; \
		git clone https://github.com/codam-coding-college/MLX42.git; \
	fi
	@cmake $(LIBMLX) -B $(LIBMLX)/build
	@make -C $(LIBMLX)/build --no-print-directory -j$(nproc)

$(NAME) : $(LIBFT) $(OBJS)
	@$(CC) -o $(NAME) $(CFLAGS) $(OBJS) $(LDFLAGS) $(MLXFLAGS) libft/libft.a
	@echo "$(GREEN)-= cub3D compiled =-$(BASE_COLOR)"

$(BONUS) : $(LIBFT) $(BONUS_OBJS)
	@$(CC) -o $(BONUS) $(CFLAGS) $(BONUS_OBJS) $(LDFLAGS) $(MLXFLAGS) libft/libft.a
	@echo "$(GREEN)-= cub3D compiled =-$(BASE_COLOR)"

$(LIBFT) :
	@DEBUG=$(DEBUG_MODE) TIMER=$(TIMER) IS_PRINT=$(IS_PRINT) FSANITIZE=$(FSANITIZE_MODE) make -C $(LIBFT_DIR) --no-print-directory $(J4)

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

.PHONY : all libmlx clean fclean re