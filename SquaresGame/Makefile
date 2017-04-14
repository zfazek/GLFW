CXXFLAGS = -std=c++11 -g -O3

LIBS=-lglfw -lGLEW -lGL -lSOIL

objects = \
	SquaresGame.o \
	Game.o \
	Rect.o \
	ResourceManager.o \
	Shader.o \
	SpriteRenderer.o \
	Texture.o

SquaresGame: $(objects)
	$(CXX) $(CXXFLAGS) $(objects) $(LIBS) -o $@

SquaresGame.o: Game.h \
	ResourceManager.h

Game.o: Rect.h \
	ResourceManager.h \
	SpriteRenderer.h

Rect.o: SpriteRenderer.h \
	ResourceManager.h

clean:
	rm -rf $(objects) SquaresGame

.PHONY: clean

