EXE = SquaresGame

CXXFLAGS = -std=c++11 -g -O3 -DGLEW_STATIC

INCLUDEDIRS = -I/usr/include/freetype2

LIBS = -lglfw -lGLEW -lGL -lSOIL -lfreetype

OBJDIR = obj
SRCDIR = src

SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(SRCDIR)/%.h Makefile
	$(CXX) $(CXXFLAGS) $(INCLUDEDIRS) -c -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp Makefile
	$(CXX) $(CXXFLAGS) $(INCLUDEDIRS) -c -o $@ $<

$(EXE): $(OBJS)
	$(CXX) $(OBJS) $(LIBS) -o $@

$(OBJDIR)/Game.o: \
	$(SRCDIR)/Rect.h \
	$(SRCDIR)/ResourceManager.h \
	$(SRCDIR)/TextRenderer.h

$(OBJDIR)/SquaresGame.o: \
	$(SRCDIR)/Game.h \
	$(SRCDIR)/ResourceManager.h

$(OBJDIR)/Rect.o: \
	$(SRCDIR)/SpriteRenderer.h \
	$(SRCDIR)/ResourceManager.h

$(OBJDIR)/TextRenderer.o: \
	$(SRCDIR)/Shader.h \
	$(SRCDIR)/Texture.h \
	$(SRCDIR)/ResourceManager.h

clean:
	rm -rf $(OBJS) $(EXE)

.PHONY: clean
