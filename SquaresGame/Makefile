EXE = SquaresGame

CXXFLAGS = -std=c++11 -g -O3

LIBS=-lglfw -lGLEW -lGL -lSOIL

OBJDIR=obj
SRCDIR=src

SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(SRCDIR)/%.h Makefile
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp Makefile
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(EXE): $(OBJS)
	$(CXX) $(OBJS) $(LIBS) -o $@

$(OBJDIR)/Game.o: \
	$(SRCDIR)/Rect.h \
	$(SRCDIR)/ResourceManager.h \
	$(SRCDIR)/SpriteRenderer.h

$(OBJDIR)/SquaresGame.o: \
	$(SRCDIR)/Game.h \
	$(SRCDIR)/ResourceManager.h

$(OBJDIR)/Rect.o: \
	$(SRCDIR)/SpriteRenderer.h \
	$(SRCDIR)/ResourceManager.h

clean:
	rm -rf $(OBJS) $(EXE)

.PHONY: clean
