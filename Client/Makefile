#
# paths
#
INCDIRS :=	./Includes ../Common/Includes ../Lib/irrKlang-64bit-1.5.0/include/
SRCDIR :=	./Sources
COMMON_SRCDIR := ../Common/Sources

#
# compilation options
#
CXX :=		g++
CXXFLAGS :=	$(addprefix -I ,$(INCDIRS)) -W -Wall -Wextra -Werror -pedantic

#
# link options
#
LINKER :=	$(CXX)
LDFLAGS :=	-L ../Lib/irrKlang-64bit-1.5.0/bin/linux-gcc-64/
LDLIBS :=	-l Irrlicht -l RakNetDLL -l pthread -l IrrKlang

#
# indie binary options
#
NAME :=		client
SRC :=		Main.cpp \
		Peer.cpp \
		Entity.cpp \
		MenuLoop.cpp \
		GameLoop.cpp \
		Input.cpp \
		Rayzal.cpp \
		Camera.cpp \
		irrKlangSceneNode.cpp
SRC :=		$(foreach var, $(SRC), \
		$(if $(wildcard $(SRCDIR)/$(var)), $(SRCDIR), $(COMMON_SRCDIR))/$(var))
OBJ :=		$(SRC:.cpp=.swag)
OBJ_DEBUG :=	$(SRC:.cpp=.debug)

#
# main build rules
#
ifeq ($(firstword $(MAKECMDGOALS)), debug)
.ONESHELL:
endif

all:		$(NAME)

%.swag:		%.cpp
		$(CXX) -c $(CXXFLAGS) -o $@ $<

$(NAME):	$(OBJ)
		$(LINKER) -o $@ $^ $(LDFLAGS) $(LDLIBS)
		@echo === $@ BUILD COMPLETE ===

%.debug:	%.cpp
		@$(CXX) -c $(CXXFLAGS) -o $@ $< &> debug.log
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
# installation rule
#
install:
		mkdir -p ~/SuckMyWheels
		cp -r ../Assets ~/SuckMyWheels
		cp ./client ~/SuckMyWheels/SuckMyWheels
		cp ../Assets/SuckMyWheels.desktop ~/.local/share/applications/

uninstall:
		rm -rfv ~/SuckMyWheels
		rm -fv ~/.local/share/applications/SuckMyWheels.desktop

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
