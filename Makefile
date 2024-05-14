CFLAGS = -Wall 

# Directories
LABLIB_DIR = Lablib/lib
SRC_DIR = src
SPRITES_DIR = $(SRC_DIR)/sprites
GAME_DIR = $(SRC_DIR)/game
GAME_CHARACTERS_DIR = $(GAME_DIR)/game_characters
MONSTERS_DIR = $(GAME_CHARACTERS_DIR)/monsters
MAIN_MENU_DIR = $(SRC_DIR)/main_menu
BATTLE_DIR = $(SRC_DIR)/battle
POWNS_DIR = $(BATTLE_DIR)/powns
INTERFACES_DIR = $(SRC_DIR)/interfaces
ENTITY_SETTINGS_DIR = $(SRC_DIR)/entity_settings
LIBS = -L/usr/lib -lSDL2 -lSDL2_ttf -lSDL2_image -L/home/martin/Travail/Gamacs/Iris/target/debug/ -liris
SDL2_INCLUDE_DIR = /usr/include/SDL2
SDL2_TTF_INCLUDE_DIR = /usr/include/SDL2

# Source files
SOURCES = \
    ../$(SRC_DIR)/main.cpp \
    ../$(SRC_DIR)/Env.cpp \
    ../$(SPRITES_DIR)/Sprite.cpp \
    ../$(SPRITES_DIR)/Static.cpp \
    ../$(SPRITES_DIR)/Movable.cpp \
    ../$(GAME_DIR)/MainGame.cpp \
    ../$(GAME_CHARACTERS_DIR)/MapEntity.cpp \
    ../$(GAME_CHARACTERS_DIR)/GamePlayer.cpp \
    ../$(GAME_CHARACTERS_DIR)/Pnj.cpp \
    ../$(MONSTERS_DIR)/Monster.cpp \
    ../$(MONSTERS_DIR)/Orc.cpp \
    ../$(SRC_DIR)/Position.cpp \
    ../$(GAME_DIR)/Map.cpp \
    ../$(GAME_DIR)/TxtBubble.cpp \
    ../$(MAIN_MENU_DIR)/MainMenu.cpp \
    ../$(BATTLE_DIR)/MainBattle.cpp \
    ../$(POWNS_DIR)/Pown.cpp \
    ../$(POWNS_DIR)/PownMovable.cpp \
    ../$(POWNS_DIR)/PownMonster.cpp \
    ../$(POWNS_DIR)/PownPlayer.cpp \
    ../$(BATTLE_DIR)/BattleSquare.cpp \
    ../$(BATTLE_DIR)/LifeBar.cpp \
    ../$(INTERFACES_DIR)/Player.cpp \
    ../$(INTERFACES_DIR)/Renderer.cpp \
    ../$(INTERFACES_DIR)/MovableFighter.cpp \
    ../$(ENTITY_SETTINGS_DIR)/Setting.cpp \
    ../$(ENTITY_SETTINGS_DIR)/SettingFighter.cpp \
    ../$(ENTITY_SETTINGS_DIR)/SettingAttack.cpp

# Lablib sources
LABLIB_SOURCES = \
    ../$(LABLIB_DIR)/button.c \
    ../$(LABLIB_DIR)/lablib.c \
    ../$(LABLIB_DIR)/cursor.c \
    ../$(LABLIB_DIR)/scene.c \
    ../$(LABLIB_DIR)/input.c

# Object files
OBJECTS = $(SOURCES:.cpp=.o) $(LABLIB_SOURCES:.c=.o)

# Executable
EXECUTABLE = gamacs

# Build rules
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	g++ $(CFLAGS) -o $@ $^ $(LIBS)  

%.o: %.cpp
	g++ $(CFLAGS) -I$(SDL2_INCLUDE_DIR) -I$(SDL2_TTF_INCLUDE_DIR) -c -o $@ $<

%.o: %.c
	gcc $(CFLAGS) -I$(SDL2_INCLUDE_DIR) -I$(SDL2_TTF_INCLUDE_DIR) -c -o $@ $<

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

