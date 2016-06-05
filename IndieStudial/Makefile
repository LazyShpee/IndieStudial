#
# paths
#
INCDIR :=	./includes
IRR_INCDIR :=	$(dir $(shell find /usr/include/ /mingw64/include/ -type f -name "irrlicht.h" -print -quit))
SRCDIR :=	./sources

#
# compilation options
#
CXX :=		g++
CXXFLAGS :=	-I $(INCDIR) -W -Wall -Wextra -Werror -pedantic

#
# link options
#
LINKER :=	$(CXX)
LDFLAGS :=
LDLIBS :=	-l Irrlicht

#
# indie binary options
#
NAME :=		indie
SRC :=		main.cpp \
		MenuLoop.cpp \
		GameLoop.cpp \
		Player.cpp \
		Camera.cpp \
		Entity.cpp \
		Input.cpp \
		Vehicle.cpp \
		Vector.cpp \
		Missile.cpp
SRC :=		$(addprefix $(SRCDIR)/, $(SRC))
OBJ :=		$(SRC:.cpp=.swag)
OBJ_DEBUG :=	$(SRC:.cpp=.debug)

#
# main build rules
#
ifeq ($(firstword $(MAKECMDGOALS)), debug)
.ONESHELL:
else ifeq ($(firstword $(MAKECMDGOALS)), msys)
LDFLAGS +=	-D MSYS
endif

all:		$(NAME)

%.swag:		%.cpp
		CPLUS_INCLUDE_PATH=$(IRR_INCDIR) $(CXX) -c $(CXXFLAGS) -o $@ $<

$(NAME):	$(OBJ)
		$(LINKER) -o $@ $^ $(LDFLAGS) $(LDLIBS)
		@echo === $@ BUILD COMPLETE ===

%.debug:	%.cpp
		@export CPLUS_INCLUDE_PATH=$(IRR_INCDIR)
		$(CXX) -c $(CXXFLAGS) -o $@ $< &> debug.log
		[ $$? -ne 0 ] && less debug.log && exit -1 || exit 0

debug:		$(OBJ_DEBUG)
		@$(LINKER) -o $@ $^ $(LDFLAGS) $(LDLIBS) &> debug.log
		[ $$? -ne 0 ] && less debug.log && exit -1
		$(RM) debug.log $^
		echo === $@ BUILD COMPLETE ===
		echo
		./$@
		echo
		$(RM) $@
		echo === $@ EXECUTION COMPLETE ===

#
# clean rules
#
RM :=		rm -fv

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

#
# special rules
#
.PHONY:		all debug clean fclean re

.SILENT:	clean fclean

.DEFAULT:
		@echo nik ta mèr tu peu pa fèr sa
