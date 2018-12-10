add_executable(space_invaders
    Bullet.cpp
    Droid.cpp
    Game.cpp
    Ship.cpp
    SpaceInvaders.cpp)

target_link_libraries(space_invaders
    engine_lib)
