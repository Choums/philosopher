NAME		=	philo

SRCDIR		=	./src
INCDIR		=	./includes
OBJDIR		=	obj

SRCS		=	philo.c\
				checker.c\
				funct.c\
				lst_manager.c\
				th_manager.c\

OBJ			=	${addprefix ${OBJDIR}/,${SRCS:.c=.o}}

CC			=	clang

CFLAGS		=	-g3 -Wall -Wextra -fsanitize=thread

all:			obj ${FT_LIB} ${NAME}

${NAME}:		${OBJ}
				${CC} ${CFLAGS} ${OBJ} -o ${NAME} -lpthread

${OBJDIR}/%.o:	${SRCDIR}/%.c includes/philo.h
				${CC} ${CFLAGS} ${FT_INC} -I ${INCDIR} -o $@ -c $<

obj:
				mkdir -p ${OBJDIR}

clean:
				rm -rf ${OBJDIR}

fclean:			clean
				rm -rf ${NAME}

re:				fclean all

.PHONY:			all clean fclean re