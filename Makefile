SQUARES_EXE = Squares
SP_INV_EXE = SpaceInvaders

CXXFLAGS = -std=c++11 -g -O3 -DGLEW_STATIC

LDDIRS = -L/usr/local/lib

OS := $(shell uname)
ifeq ($(OS),Darwin)
INCLUDEDIRS= -I/usr/local/include \
 -I/usr/local/include/freetype2 \
 -Isrc/Engine \
 -Isrc/SquaresGame
LIBS = -lglfw.3 -lGLEW -lSOIL -lfreetype -framework OpenGL
else
INCLUDEDIRS = -I/usr/include/freetype2 \
 -Isrc/Engine \
 -Isrc/SquaresGame
LIBS = -lglfw -lGLEW -lGL -lSOIL -lfreetype
endif

SQUARES_SRCDIR = src/SquaresGame
SQUARES_OBJDIR = obj/SquaresGame
SP_INV_SRCDIR = src/SpaceInvaders
SP_INV_OBJDIR = obj/SpaceInvaders
ENGINE_SRCDIR = src/Engine
ENGINE_OBJDIR = obj/Engine

SQUARES_SRCS = $(wildcard $(SQUARES_SRCDIR)/*.cpp)
SQUARES_OBJS = $(patsubst $(SQUARES_SRCDIR)/%.cpp, $(SQUARES_OBJDIR)/%.o, $(SQUARES_SRCS))
SP_INV_SRCS = $(wildcard $(SP_INV_SRCDIR)/*.cpp)
SP_INV_OBJS = $(patsubst $(SP_INV_SRCDIR)/%.cpp, $(SP_INV_OBJDIR)/%.o, $(SP_INV_SRCS))
ENGINE_SRCS = $(wildcard $(ENGINE_SRCDIR)/*.cpp)
ENGINE_OBJS = $(patsubst $(ENGINE_SRCDIR)/%.cpp, $(ENGINE_OBJDIR)/%.o, $(ENGINE_SRCS))

$(SQUARES_OBJDIR)/%.o: $(SQUARES_SRCDIR)/%.cpp $(SQUARES_SRCDIR)/%.h Makefile
	$(CXX) $(CXXFLAGS) $(INCLUDEDIRS) -c -o $@ $<

$(SQUARES_OBJDIR)/%.o: $(SQUARES_SRCDIR)/%.cpp Makefile
	$(CXX) $(CXXFLAGS) $(INCLUDEDIRS) -c -o $@ $<

$(SP_INV_OBJDIR)/%.o: $(SP_INV_SRCDIR)/%.cpp $(SP_INV_SRCDIR)/%.h Makefile
	$(CXX) $(CXXFLAGS) $(INCLUDEDIRS) -c -o $@ $<

$(SP_INV_OBJDIR)/%.o: $(SP_INV_SRCDIR)/%.cpp Makefile
	$(CXX) $(CXXFLAGS) $(INCLUDEDIRS) -c -o $@ $<

$(ENGINE_OBJDIR)/%.o: $(ENGINE_SRCDIR)/%.cpp $(ENGINE_SRCDIR)/%.h Makefile
	$(CXX) $(CXXFLAGS) $(INCLUDEDIRS) -c -o $@ $<

$(ENGINE_OBJDIR)/%.o: $(ENGINE_SRCDIR)/%.cpp Makefile
	$(CXX) $(CXXFLAGS) $(INCLUDEDIRS) -c -o $@ $<

$(SP_INV_EXE): $(SP_INV_OBJS) $(ENGINE_OBJS)
	$(CXX) $(LDDIRS) $(SP_INV_OBJS) $(ENGINE_OBJS) $(LIBS) -o $@

$(SQUARES_EXE): $(SQUARES_OBJS) $(ENGINE_OBJS)
	$(CXX) $(LDDIRS) $(SQUARES_OBJS) $(ENGINE_OBJS) $(LIBS) -o $@

$(SQUARES_OBJDIR)/Game.o: \
	$(ENGINE_SRCDIR)/GameBase.h \
	$(ENGINE_SRCDIR)/ResourceManager.h \
	$(ENGINE_SRCDIR)/TextRenderer.h \
	$(SQUARES_SRCDIR)/Rect.h

$(SQUARES_OBJDIR)/SquaresGame.o: \
	$(ENGINE_SRCDIR)/GameBase.h \
	$(SQUARES_SRCDIR)/Game.h

$(SQUARES_OBJDIR)/Rect.o: \
	$(ENGINE_SRCDIR)/SpriteRenderer.h \
	$(ENGINE_SRCDIR)/Texture.h \
	$(ENGINE_SRCDIR)/ResourceManager.h


$(SP_INV_OBJDIR)/Game.o: \
	$(ENGINE_SRCDIR)/GameBase.h \
	$(ENGINE_SRCDIR)/ResourceManager.h \
	$(ENGINE_SRCDIR)/TextRenderer.h \
	$(SP_INV_SRCDIR)/Ship.h \
	$(SP_INV_SRCDIR)/Bullet.h \
	$(SP_INV_SRCDIR)/Droid.h

$(SP_INV_OBJDIR)/SpaceInvaders.o: \
	$(ENGINE_SRCDIR)/GameBase.h \
	$(SP_INV_SRCDIR)/Game.h

$(SP_INV_OBJDIR)/Ship.o: \
	$(ENGINE_SRCDIR)/SpriteRenderer.h \
	$(ENGINE_SRCDIR)/Texture.h \
	$(ENGINE_SRCDIR)/ResourceManager.h

$(SP_INV_OBJDIR)/Bullet.o: \
	$(ENGINE_SRCDIR)/SpriteRenderer.h \
	$(ENGINE_SRCDIR)/Texture.h \
	$(ENGINE_SRCDIR)/ResourceManager.h

$(SP_INV_OBJDIR)/Droid.o: \
	$(ENGINE_SRCDIR)/SpriteRenderer.h \
	$(ENGINE_SRCDIR)/Texture.h \
	$(ENGINE_SRCDIR)/ResourceManager.h


$(ENGINE_OBJDIR)/GameBase.o: \
	$(ENGINE_SRCDIR)/ResourceManager.h

$(ENGINE_OBJDIR)/SpriteRenderer.o: \
	$(ENGINE_SRCDIR)/Shader.h \
	$(ENGINE_SRCDIR)/Texture.h \
	$(ENGINE_SRCDIR)/ResourceManager.h

$(ENGINE_OBJDIR)/TextRenderer.o: \
	$(ENGINE_SRCDIR)/Shader.h \
	$(ENGINE_SRCDIR)/Texture.h

clean:
	rm -rf $(SQUARES_OBJS) $(SP_INV_OBJS) $(ENGINE_OBJS) $(SQUARES_EXE) $(SP_INV_EXE)

.PHONY: clean