# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpeeters <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/05 20:49:34 by lpeeters          #+#    #+#              #
#    Updated: 2023/08/21 19:01:54 by lpeeters         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#program name
NAME = philo

#compiler
CC = cc -pthread

#remove
RM = rm -rf

#flags
CFLAGS = -g -Wall -Wextra -Werror

#redirect output to /dev/null to silence it
OUT = > /dev/null

#find sources
SRCS = ${shell find . -name "*.c" -not -path "*lib*"}

#header file
HEADERS = ${shell find . -name "*.h" -not -path "*lib*"}

#find other makefiles
MKFL = ${shell find . -mindepth 2 \( -name "Makefile" -o -name "makefile" \)}

#find library files
LIBS = ${shell find . -name "*.a"}

#fetch object files
OBJS = ${SRCS:%.c=${OBJ_DIR}%.o}

#fetch makefile directory
MKFL_DIRS = ${dir ${MKFL}}

#fetch library directory
LIB_DIRS = ${dir ${LIBS}}

#object directory
OBJ_DIR = OBJS/

#make directories for object files
MK_DIR = mkdir -p ${@D}

#fetch library filename
LIB_PNAMES = ${notdir ${LIBS}} #cut off the path
LIB_LNAMES = ${LIB_PNAMES:lib%.a=%} #cut off the library files' "lib" prefix
LIB_NAMES = ${LIB_LNAMES:.a=} #cut off the library files' ".a" suffix

#all libraries with their directories, compilation flags and names
LIB_ALL = ${foreach libdir,${LIB_DIRS},-L ${libdir}} \
	  ${foreach libname,${LIB_NAMES},-l ${libname}}

#all headers with their compilation flag
HDR_ALL = ${foreach header,${HEADERS},-I ${header}}

#make other projects that were found
MKFL_ALL = ${foreach mkfldir,${MKFL_DIRS}, make -C ${mkfldir} ${OUT} ;}

#make object files
${OBJ_DIR}%.o: %.c
	@${MK_DIR}
	@${CC} ${CFLAGS} -c $< -o $@

#make
all: MK ${NAME}
	@${OUT}

#make project into program
${NAME}: ${OBJS} ${HEADERS}
	@${CC} ${OBJS} ${HDR_ALL} ${LIB_ALL} ${MLXFLAGS} -o ${NAME}
	@chmod +x ${NAME}

#make library
MK:
	@${MKFL_ALL}

#clean object files and directories
clean:
	@${RM} ${OBJ_DIR}
	@${foreach mkfldir,${MKFL_DIRS}, make -C ${mkfldir} fclean ${OUT} ;}

#clean everything that was made
fclean: clean
	@${RM} ${NAME}

#remake
re: fclean all

#targets
.PHONY: all clean fclean re MK
