SQUARES_EXE = Squares
SP_INV_EXE  = SpaceInvaders
CUBE_EXE    = Cube

CXXFLAGS    = -std=c++11 -g -O2 -DGLEW_STATIC
INCLUDEDIRS = -Isrc/Engine

OS := $(shell uname)
$(info $$OS is [$(OS)])
ifeq ($(OS),Darwin)
INCLUDEDIRS := $(INCLUDEDIRS) \
	-I/usr/local/include \
	-I/usr/local/include/freetype2
LDDIRS      = -L/usr/local/lib
LIBS        = -lglfw.3 -lGLEW -lfreetype -framework OpenGL
else ifeq ($(OS),Linux)
INCLUDEDIRS := $(INCLUDEDIRS) \
	-I/usr/include/freetype2
LDDIRS      = -L/usr/local/lib
LIBS        = -lglfw -lGLEW -lGL -lfreetype
else
INCLUDEDIRS := $(INCLUDEDIRS) \
	-Ic:\usr\local\include
LDDIRS      = -Lc:\usr\local\lib
LIBS        = -lglfw3 -lgdi32 -lglew32s -lGL -lopengl32 -lfreetype
endif

SQUARES_SRCDIR = src/SquaresGame
SQUARES_OBJDIR = obj/SquaresGame
SP_INV_SRCDIR  = src/SpaceInvaders
SP_INV_OBJDIR  = obj/SpaceInvaders
CUBE_SRCDIR    = src/Cube
CUBE_OBJDIR    = obj/Cube
ENGINE_SRCDIR  = src/Engine
ENGINE_OBJDIR  = obj/Engine

SQUARES_SRCS   = $(wildcard $(SQUARES_SRCDIR)/*.cpp)
SQUARES_OBJS   = $(patsubst $(SQUARES_SRCDIR)/%.cpp, $(SQUARES_OBJDIR)/%.o, $(SQUARES_SRCS))
SP_INV_SRCS    = $(wildcard $(SP_INV_SRCDIR)/*.cpp)
SP_INV_OBJS    = $(patsubst $(SP_INV_SRCDIR)/%.cpp, $(SP_INV_OBJDIR)/%.o, $(SP_INV_SRCS))
CUBE_SRCS      = $(wildcard $(CUBE_SRCDIR)/*.cpp)
CUBE_OBJS      = $(patsubst $(CUBE_SRCDIR)/%.cpp, $(CUBE_OBJDIR)/%.o, $(CUBE_SRCS))
ENGINE_SRCS    = $(wildcard $(ENGINE_SRCDIR)/*.cpp)
ENGINE_OBJS    = $(patsubst $(ENGINE_SRCDIR)/%.cpp, $(ENGINE_OBJDIR)/%.o, $(ENGINE_SRCS))

all: $(CUBE_EXE)

$(CUBE_EXE): $(CUBE_OBJS) $(ENGINE_OBJS)
	$(CXX) $(LDDIRS) $(CUBE_OBJS) $(ENGINE_OBJS) $(LIBS) -o $@

$(SP_INV_EXE): $(SP_INV_OBJS) $(ENGINE_OBJS)
	$(CXX) $(LDDIRS) $(SP_INV_OBJS) $(ENGINE_OBJS) $(LIBS) -o $@

$(SQUARES_EXE): $(SQUARES_OBJS) $(ENGINE_OBJS)
	$(CXX) $(LDDIRS) $(SQUARES_OBJS) $(ENGINE_OBJS) $(LIBS) -o $@

$(SQUARES_OBJDIR)/%.o: $(SQUARES_SRCDIR)/%.cpp Makefile
	$(CXX) $(CXXFLAGS) $(INCLUDEDIRS) -c -o $@ $<

$(SP_INV_OBJDIR)/%.o: $(SP_INV_SRCDIR)/%.cpp Makefile
	$(CXX) $(CXXFLAGS) $(INCLUDEDIRS) -c -o $@ $<

$(CUBE_OBJDIR)/%.o: $(CUBE_SRCDIR)/%.cpp Makefile
	$(CXX) $(CXXFLAGS) $(INCLUDEDIRS) -c -o $@ $<

$(ENGINE_OBJDIR)/%.o: $(ENGINE_SRCDIR)/%.cpp Makefile
	$(CXX) $(CXXFLAGS) $(INCLUDEDIRS) -c -o $@ $<

$(SQUARES_OBJDIR)/SquaresGame.o: \
	$(ENGINE_SRCDIR)/GameBase.h \
	$(SQUARES_SRCDIR)/Game.h

$(SQUARES_OBJDIR)/Game.o: \
	$(SQUARES_SRCDIR)/Game.h \
	$(ENGINE_SRCDIR)/GameBase.h \
	$(ENGINE_SRCDIR)/ResourceManager.h \
	$(ENGINE_SRCDIR)/TextRenderer.h \
	$(SQUARES_SRCDIR)/Rect.h

$(SQUARES_OBJDIR)/Rect.o: \
	$(SQUARES_SRCDIR)/Rect.h \
	$(ENGINE_SRCDIR)/SpriteRenderer.h \
	$(ENGINE_SRCDIR)/Texture.h \
	$(ENGINE_SRCDIR)/ResourceManager.h


$(SP_INV_OBJDIR)/SpaceInvaders.o: \
	$(ENGINE_SRCDIR)/GameBase.h \
	$(SP_INV_SRCDIR)/Game.h

$(SP_INV_OBJDIR)/Game.o: \
	$(SP_INV_SRCDIR)/Game.h \
	$(ENGINE_SRCDIR)/GameBase.h \
	$(ENGINE_SRCDIR)/ResourceManager.h \
	$(ENGINE_SRCDIR)/TextRenderer.h \
	$(SP_INV_SRCDIR)/Ship.h \
	$(SP_INV_SRCDIR)/Bullet.h \
	$(SP_INV_SRCDIR)/Droid.h

$(SP_INV_OBJDIR)/Ship.o: \
	$(SP_INV_SRCDIR)/Ship.h \
	$(ENGINE_SRCDIR)/SpriteRenderer.h \
	$(ENGINE_SRCDIR)/Texture.h \
	$(ENGINE_SRCDIR)/ResourceManager.h

$(SP_INV_OBJDIR)/Bullet.o: \
	$(SP_INV_SRCDIR)/Bullet.h \
	$(ENGINE_SRCDIR)/SpriteRenderer.h \
	$(ENGINE_SRCDIR)/Texture.h \
	$(ENGINE_SRCDIR)/ResourceManager.h

$(SP_INV_OBJDIR)/Droid.o: \
	$(SP_INV_SRCDIR)/Droid.h \
	$(ENGINE_SRCDIR)/SpriteRenderer.h \
	$(ENGINE_SRCDIR)/Texture.h \
	$(ENGINE_SRCDIR)/ResourceManager.h


$(CUBE_OBJDIR)/CubeGame.o: \
	$(ENGINE_SRCDIR)/GameBase.h \
	$(CUBE_SRCDIR)/Game.h

$(CUBE_OBJDIR)/Game.o: \
	$(CUBE_SRCDIR)/Game.h \
	$(ENGINE_SRCDIR)/GameBase.h \
	$(ENGINE_SRCDIR)/ResourceManager.h \
	$(ENGINE_SRCDIR)/TextRenderer.h

$(CUBE_OBJDIR)/Cube.o: \
	$(CUBE_SRCDIR)/Cube.h \
	$(ENGINE_SRCDIR)/Renderer.h \
	$(ENGINE_SRCDIR)/Texture.h \
	$(ENGINE_SRCDIR)/ResourceManager.h


$(ENGINE_OBJDIR)/GameBase.o: \
	$(ENGINE_SRCDIR)/GameBase.h \
	$(ENGINE_SRCDIR)/ResourceManager.h \
	$(ENGINE_SRCDIR)/Camera.h

$(ENGINE_OBJDIR)/SpriteRenderer.o: \
	$(ENGINE_SRCDIR)/SpriteRenderer.h \
	$(ENGINE_SRCDIR)/Shader.h \
	$(ENGINE_SRCDIR)/Texture.h \
	$(ENGINE_SRCDIR)/ResourceManager.h

$(ENGINE_OBJDIR)/Renderer.o: \
	$(ENGINE_SRCDIR)/Renderer.h \
	$(ENGINE_SRCDIR)/Shader.h \
	$(ENGINE_SRCDIR)/Texture.h \
	$(ENGINE_SRCDIR)/ResourceManager.h

$(ENGINE_OBJDIR)/Camera.o: \
	$(ENGINE_SRCDIR)/Camera.h

$(ENGINE_OBJDIR)/TextRenderer.o: \
	$(ENGINE_SRCDIR)/TextRenderer.h \
	$(ENGINE_SRCDIR)/Shader.h \
	$(ENGINE_SRCDIR)/Texture.h

clean:
	rm -rf $(SQUARES_OBJS) $(SP_INV_OBJS) $(CUBE_OBJS) $(ENGINE_OBJS) $(SQUARES_EXE) $(SP_INV_EXE) $(CUBE_EXE)

.PHONY: clean all
