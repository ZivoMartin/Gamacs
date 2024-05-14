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
LIBS = -L/usr/lib -lSDL2 -lSDL2_ttf -lSDL2_image -liris -L./Iris/target/release
SDL2_INCLUDE_DIR = /usr/include/SDL2
SDL2_TTF_INCLUDE_DIR = /usr/include/SDL2
BUILD_DIR = build
DIRS = $(LABLIB_DIR) $(SRC_DIR) $(SPRITES_DIR) $(GAME_DIR) $(GAME_CHARACTERS_DIR) $(MONSTERS_DIR) $(MAIN_MENU_DIR) $(BATTLE_DIR) $(POWNS_DIR) $(INTERFACES_DIR) $(ENTITY_SETTINGS_DIR)
# Source files
SOURCES = \
    $(SRC_DIR)/main.cpp \
    $(SRC_DIR)/Env.cpp \
    $(SPRITES_DIR)/Sprite.cpp \
    $(SPRITES_DIR)/Static.cpp \
    $(SPRITES_DIR)/Movable.cpp \
    $(GAME_DIR)/MainGame.cpp \
    $(GAME_CHARACTERS_DIR)/MapEntity.cpp \
    $(GAME_CHARACTERS_DIR)/GamePlayer.cpp \
    $(GAME_CHARACTERS_DIR)/Pnj.cpp \
    $(MONSTERS_DIR)/Monster.cpp \
    $(MONSTERS_DIR)/Orc.cpp \
    $(SRC_DIR)/Position.cpp \
    $(GAME_DIR)/Map.cpp \
    $(GAME_DIR)/TxtBubble.cpp \
    $(MAIN_MENU_DIR)/MainMenu.cpp \
    $(BATTLE_DIR)/MainBattle.cpp \
    $(POWNS_DIR)/Pown.cpp \
    $(POWNS_DIR)/PownMovable.cpp \
    $(POWNS_DIR)/PownMonster.cpp \
    $(POWNS_DIR)/PownPlayer.cpp \
    $(BATTLE_DIR)/BattleSquare.cpp \
    $(BATTLE_DIR)/LifeBar.cpp \
    $(INTERFACES_DIR)/Player.cpp \
    $(INTERFACES_DIR)/Renderer.cpp \
    $(INTERFACES_DIR)/MovableFighter.cpp \
    $(ENTITY_SETTINGS_DIR)/Setting.cpp \
    $(ENTITY_SETTINGS_DIR)/SettingFighter.cpp \
    $(ENTITY_SETTINGS_DIR)/SettingAttack.cpp

# Lablib sources
LABLIB_SOURCES = \
    $(LABLIB_DIR)/button.c \
    $(LABLIB_DIR)/lablib.c \
    $(LABLIB_DIR)/cursor.c \
    $(LABLIB_DIR)/scene.c \
    $(LABLIB_DIR)/input.c

# Object files
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/$(SRC_DIR)/%.o,$(SOURCES)) \
          $(patsubst $(LABLIB_DIR)/%.c,$(BUILD_DIR)/%.o,$(LABLIB_SOURCES))

INIR = mkdir -p $(BUILD_DIR) && cd $(BUILD_DIR) && mkdir -p $(DIRS) && cp -r ../res .

# Executable
EXECUTABLE = gamacs

# Build rules
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	g++ $(CXXFLAGS) -o $@ $^ $(LIBS) 

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	g++ $(CXXFLAGS) -I$(SDL2_INCLUDE_DIR) -I$(SDL2_TTF_INCLUDE_DIR) -c -o $@ $< -liris -L./Iris/target/release

$(BUILD_DIR)/%.o: $(LABLIB_DIR)/%.c | $(BUILD_DIR)
	gcc $(CXXFLAGS) -I$(SDL2_INCLUDE_DIR) -I$(SDL2_TTF_INCLUDE_DIR) -c -o $@ $<

init:
	mkdir -p $(BUILD_DIR) && cd $(BUILD_DIR) && mkdir -p $(DIRS) && cp -r ../res .

clean:
	rm -rf $(BUILD_DIR) $(EXECUTABLE)
