TARGET = chirkser

CXX = g++
CXX_FLAGS = -Wall -pedantic -Wextra -std=c++14

BUILD_DIR = build
DOC_DIR = doc
SRC_DIR = src
HEADERS := $(wildcard src/*.h src/*/*.hpp)
.PHONY: all
all: compile doc

.PHONY: compile
compile: $(TARGET)

.PHONY: run
run: $(TARGET)
		./$(TARGET)

.PHONY: clean
clean:
								rm -rf $(TARGET) $(DOC_DIR)  $(BUILD_DIR)/ 2>/dev/null

.PHONY: doc
doc: Doxyfile $(HEADERS)
	doxygen Doxyfile




# Requirements / Dependencies
$(BUILD_DIR)/%.o:               src/%.cpp
							    mkdir -p $(BUILD_DIR)
							    $(CXX) $(CXX_FLAGS) $< -c -o $@


$(BUILD_DIR)/%.o:               src/*/%.cpp
								mkdir -p $(BUILD_DIR)
								$(CXX) $(CXX_FLAGS) $< -c -o $@

$(TARGET):                      $(BUILD_DIR)/main.o $(BUILD_DIR)/CUserInterface.o $(BUILD_DIR)/CPlayer.o $(BUILD_DIR)/CPiece.o \
							    $(BUILD_DIR)/CMoves.o $(BUILD_DIR)/CMove.o $(BUILD_DIR)/CLogic.o \
							    $(BUILD_DIR)/CGame.o $(BUILD_DIR)/CConsts.o $(BUILD_DIR)/CBoard.o \
							    $(BUILD_DIR)/CPlayerReal.o $(BUILD_DIR)/CPlayerComputer.o $(BUILD_DIR)/CBishop.o \
							    $(BUILD_DIR)/CKing.o $(BUILD_DIR)/CKnight.o $(BUILD_DIR)/COffboard.o \
							    $(BUILD_DIR)/CPawn.o $(BUILD_DIR)/CQueen.o $(BUILD_DIR)/CRook.o \
							    $(BUILD_DIR)/CSpace.o
								mkdir -p $(BUILD_DIR)
								$(CXX) $(CXX_FLAGS) $^ -o $@


$(BUILD_DIR)/main.o:			src/main.cpp src/CUserInterface.h src/CPlayer.h src/CPiece.h  \
								src/CMoves.h src/CMove.h src/CLogic.h src/CGame.h src/CConsts.h  \
								src/CBoard.h src/CPlayers/CPlayerComputer.h src/CPlayers/CPlayerReal.h  \
								src/CPieces/CBishop.h src/CPieces/CKing.h src/CPieces/COffboard.h src/CPieces/CPawn.h  \
								src/CPieces/CQueen.h src/CPieces/CRook.h src/CPieces/CSpace.h

$(BUILD_DIR)/CMoves.o:			src/CMoves.cpp src/CMoves.h src/CConsts.h

$(BUILD_DIR)/CMove.o:			src/CMove.cpp src/CMoves.h src/CConsts.h

$(BUILD_DIR)/CLogic.o:			src/CLogic.cpp src/CLogic.h src/CBoard.h src/CPlayers/CPlayerReal.h src/CPlayers/CPlayerComputer.h  \
								src/CPieces/CPawn.h  src/CMoves.h src/CMove.h src/CConsts.h \
								src/CPieces/CBishop.h src/CPieces/CKing.h src/CPieces/CKnight.h src/CPieces/COffboard.h  \
								src/CPieces/CSpace.h src/CPieces/CQueen.h src/CPieces/CRook.h  src/CPiece.h  \
								src/CPlayer.h

$(BUILD_DIR)/CGame.o:			src/CGame.cpp src/CGame.h src/CUserInterface.h src/CLogic.h  \
								src/CBoard.h src/CPlayers/CPlayerReal.h src/CPlayers/CPlayerComputer.h  \
								src/CPieces/CPawn.h  src/CMoves.h src/CMove.h src/CConsts.h \
								src/CPieces/CBishop.h src/CPieces/CKing.h src/CPieces/CKnight.h src/CPieces/COffboard.h  \
								src/CPieces/CSpace.h src/CPieces/CQueen.h src/CPieces/CRook.h  src/CPiece.h  \
								src/CPlayer.h


$(BUILD_DIR)/CUserInterface.o: src/CUserInterface.cpp src/CUserInterface.h

$(BUILD_DIR)/CPiece.o:			src/CPiece.cpp src/CPiece.h src/CMove.h src/CConsts.h

$(BUILD_DIR)/CConsts.o:			src/CConsts.cpp src/CConsts.h

$(BUILD_DIR)/CPiece.o:			src/CPiece.cpp src/CPiece.h src/CMove.h src/CConsts.h

$(BUILD_DIR)/CBoard.o:			src/CBoard.cpp src/CBoard.h src/CPieces/CPawn.h  src/CMoves.h  \
								src/CPieces/CBishop.h src/CPieces/CKing.h src/CPieces/CKnight.h src/CPieces/COffboard.h  \
								src/CPieces/CSpace.h src/CPieces/CQueen.h src/CPieces/CRook.h  src/CPiece.h  \
								src/CConsts.h  src/CMove.h

$(BUILD_DIR)/CSpace.o:          src/CPieces/CSpace.cpp src/CPieces/CSpace.h src/CPieces/../CPiece.h  \
                                src/CPieces/../CConsts.h src/CPieces/../CMove.h

$(BUILD_DIR)/CRook.o:           src/CPieces/CRook.cpp src/CPieces/CRook.h   src/CPieces/../CBoard.h\
								src/CPieces/../CConsts.h src/CPieces/../CMove.h \
								src/CPieces/CPawn.h  src/CPieces/../CMoves.h \
								src/CPieces/CBishop.h src/CPieces/CKing.h src/CPieces/CKnight.h src/CPieces/COffboard.h  \
								src/CPieces/CSpace.h src/CPieces/CQueen.h  src/CPieces/../CPiece.h  \
								src/CPieces/../CConsts.h  src/CPieces/../CMove.h


$(BUILD_DIR)/CQueen.o:          src/CPieces/CQueen.cpp src/CPieces/CQueen.h  src/CPieces/../CBoard.h  \
								src/CPieces/../CConsts.h src/CPieces/../CMove.h  \
                                src/CPieces/CPawn.h  src/CPieces/../CMoves.h  \
                                src/CPieces/CBishop.h src/CPieces/CKing.h src/CPieces/CKnight.h src/CPieces/COffboard.h  \
                                src/CPieces/CSpace.h src/CPieces/CRook.h  src/CPieces/../CPiece.h  \
                                src/CPieces/../CConsts.h  src/CPieces/../CMove.h

$(BUILD_DIR)/CPawn.o:           src/CPieces/CPawn.cpp src/CPieces/CPawn.cpp  src/CPieces/../CBoard.h  \
								src/CPieces/../CConsts.h src/CPieces/../CMove.h  \
                                src/CPieces/../CMoves.h  \
                                src/CPieces/CBishop.h src/CPieces/CKing.h src/CPieces/CKnight.h src/CPieces/COffboard.h  \
                                src/CPieces/CSpace.h src/CPieces/CQueen.h src/CPieces/CRook.h  src/CPieces/../CPiece.h  \
                                src/CPieces/../CConsts.h  src/CPieces/../CMove.h

$(BUILD_DIR)/CKnight.o:         src/CPieces/CKnight.cpp src/CPieces/CKnight.h  src/CPieces/../CBoard.h  \
								src/CPieces/../CConsts.h src/CPieces/../CMove.h  \
                                src/CPieces/CPawn.h  src/CPieces/../CMoves.h  \
                                src/CPieces/CBishop.h src/CPieces/CKing.h src/CPieces/COffboard.h  \
                                src/CPieces/CSpace.h src/CPieces/CQueen.h src/CPieces/CRook.h  src/CPieces/../CPiece.h  \
                                src/CPieces/../CConsts.h  src/CPieces/../CMove.h

$(BUILD_DIR)/CKing.o:           src/CPieces/CKing.cpp src/CPieces/CKing.h  src/CPieces/../CBoard.h  \
								src/CPieces/../CConsts.h src/CPieces/../CMove.h  \
                                src/CPieces/CPawn.h  src/CPieces/../CMoves.h  \
                                src/CPieces/CBishop.h src/CPieces/CKing.h src/CPieces/COffboard.h  \
                                src/CPieces/CSpace.h src/CPieces/CQueen.h src/CPieces/CRook.h  src/CPieces/../CPiece.h  \
                                src/CPieces/../CConsts.h  src/CPieces/../CMove.h

$(BUILD_DIR)/CBishop.o:         src/CPieces/CBishop.cpp src/CPieces/CBishop.h src/CPieces/../CBoard.h  \
								src/CPieces/../CConsts.h src/CPieces/../CMove.h  \
                                src/CPieces/CPawn.h  src/CPieces/../CMoves.h  \
                                src/CPieces/CKing.h src/CPieces/CKnight.h src/CPieces/COffboard.h  \
                                src/CPieces/CSpace.h src/CPieces/CQueen.h src/CPieces/CRook.h  src/CPieces/../CPiece.h  \
                                src/CPieces/../CConsts.h  src/CPieces/../CMove.h

$(BUILD_DIR)/COffboard.o:       src/CPieces/COffboard.cpp src/CPieces/COffboard.h src/CPieces/../CPiece.h  \
                                src/CPieces/../CConsts.h src/CPieces/../CMove.h

S(BUILD_DIR)/CPlayer.o:			src/CPlayer.cpp src/CPlayer.h src/CBoard.h  \
								src/CPieces/CPawn.h  src/CMoves.h  \
								src/CPieces/CBishop.h src/CPieces/CKing.h src/CPieces/CKnight.h src/CPieces/COffboard.h  \
								src/CPieces/CSpace.h src/CPieces/CQueen.h src/CPieces/CRook.h  src/CPieces/../CPiece.h  \
								src/CPieces/../CConsts.h  src/CPieces/../CMove.h

S(BUILD_DIR)/CPlayerReal.o:		src/CPlayers/CPlayerReal.cpp src/CPlayers/CPlayerReal.h src/CPlayers/../CPlayer.h  \
								src/CPlayers/../CBoard.h src/CPlayers/../CConsts.h src/CPlayers/../CMove.h  \
								src/CPlayers/../CPieces/CPawn.h  src/CPlayers/../CMoves.h  \
								src/CPlayers/../CPieces/CKing.h src/CPlayers/../CPieces/CKnight.h src/CPlayers/../CPieces/COffboard.h  \
								src/CPlayers/../CPieces/CSpace.h src/CPlayers/../CPieces/CQueen.h src/CPlayers/../CPieces/CRook.h  src/CPlayers/../CPiece.h  \
							 	src/CPlayers/../CConsts.h  src/CPlayers/../CMove.h
S(BUILD_DIR)/CPlayerComputer.o:	src/CPlayers/CPlayerComputer.cpp src/CPlayers/CPlayerComputer.h src/CPlayers/../CPlayer.h  \
								src/CPlayers/../CBoard.h src/CPlayers/../CConsts.h src/CPlayers/../CMove.h  \
								src/CPlayers/../CPieces/CPawn.h  src/CPlayers/../CMoves.h  \
								src/CPlayers/../CPieces/CKing.h src/CPlayers/../CPieces/CKnight.h src/CPlayers/../CPieces/COffboard.h  \
								src/CPlayers/../CPieces/CSpace.h src/CPlayers/../CPieces/CQueen.h src/CPlayers/../CPieces/CRook.h  src/CPlayers/../CPiece.h  \
							 	src/CPlayers/../CConsts.h  src/CPlayers/../CMove.h


