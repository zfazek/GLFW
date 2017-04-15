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

Game.o: Game.h \
	Rect.h \
	ResourceManager.h \
	SpriteRenderer.h

Rect.o: Rect.h \
	SpriteRenderer.h \
	ResourceManager.h

ResourceManager.o: ResourceManager.h

Shader.o: Shader.h

SpriteRenderer.o: SpriteRenderer.h

Texture.o: Texture.h

clean:
	rm -rf $(objects) SquaresGame

.PHONY: clean

