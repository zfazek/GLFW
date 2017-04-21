EXE = SquaresGame

CXXFLAGS = -std=c++11 -g -O3 -DGLEW_STATIC

INCLUDEDIRS = -I/usr/include/freetype2 \
 -Isrc/Engine \
 -Isrc/SquaresGame


LDDIRS = -L/usr/local/lib

LIBS = -lglfw -lGLEW -lGL -lSOIL -lfreetype

OBJDIR = obj/SquaresGame
SRCDIR = src/SquaresGame
ENGINE_OBJDIR = obj/Engine
ENGINE_SRCDIR = src/Engine

SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))
ENGINE_SRCS = $(wildcard $(ENGINE_SRCDIR)/*.cpp)
ENGINE_OBJS = $(patsubst $(ENGINE_SRCDIR)/%.cpp, $(ENGINE_OBJDIR)/%.o, $(ENGINE_SRCS))

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(SRCDIR)/%.h Makefile
	$(CXX) $(CXXFLAGS) $(INCLUDEDIRS) -c -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp Makefile
	$(CXX) $(CXXFLAGS) $(INCLUDEDIRS) -c -o $@ $<

$(ENGINE_OBJDIR)/%.o: $(ENGINE_SRCDIR)/%.cpp $(ENGINE_SRCDIR)/%.h Makefile
	$(CXX) $(CXXFLAGS) $(INCLUDEDIRS) -c -o $@ $<

$(ENGINE_OBJDIR)/%.o: $(ENGINE_SRCDIR)/%.cpp Makefile
	$(CXX) $(CXXFLAGS) $(INCLUDEDIRS) -c -o $@ $<

$(EXE): $(OBJS) $(ENGINE_OBJS)
	$(CXX) $(LDDIRS) $(OBJS) $(ENGINE_OBJS) $(LIBS) -o $@

$(ENGINE_OBJDIR)/GameBase.o: \
	$(ENGINE_SRCDIR)/ResourceManager.h

$(OBJDIR)/Game.o: \
	$(ENGINE_SRCDIR)/GameBase.h \
	$(SRCDIR)/Rect.h \
	$(ENGINE_SRCDIR)/ResourceManager.h \
	$(ENGINE_SRCDIR)/TextRenderer.h

$(OBJDIR)/SquaresGame.o: \
	$(ENGINE_SRCDIR)/GameBase.h \
	$(SRCDIR)/Game.h

$(OBJDIR)/Rect.o: \
	$(ENGINE_SRCDIR)/SpriteRenderer.h \
	$(ENGINE_SRCDIR)/Texture.h \
	$(ENGINE_SRCDIR)/ResourceManager.h

$(ENGINE_OBJDIR)/SpriteRenderer.o: \
	$(ENGINE_SRCDIR)/Shader.h \
	$(ENGINE_SRCDIR)/Texture.h \
	$(ENGINE_SRCDIR)/ResourceManager.h

$(ENGINE_OBJDIR)/TextRenderer.o: \
	$(ENGINE_SRCDIR)/Shader.h \
	$(ENGINE_SRCDIR)/Texture.h

clean:
	rm -rf $(OBJS) $(ENGINE_OBJS) $(EXE)

.PHONY: clean
