CXX := g++.exe
CXXFLAGS := -s -O3 -mwindows -std=c++17 -Wall -pedantic -IW:\SFML\include -MMD -MP -DSFML_STATIC
LDFLAGS := -LW:\SFML\lib -static-libgcc -static-libstdc++ -static -lpthread -lsfml-graphics-s -lsfml-audio-s -lsfml-network-s -lsfml-window-s -lsfml-system-s -lopengl32 -lws2_32 -lopenal -lflac -lvorbisenc -lvorbisfile -lvorbis -logg -lfreetype -lwinmm -lgdi32 -lsfml-main -mwindows

TARGET := main

all: compile link start

compile:
	$(CXX) $(CXXFLAGS) -c -o $(TARGET).o $(TARGET).cpp

link:
	$(CXX) -o $(TARGET) $(TARGET).o $(LDFLAGS)

start:
	erase -f $(TARGET) *.o
	erase -f $(TARGET) *.d
	./$(TARGET)


ifeq "$(MAKECMDGOALS)" ""
-include $(DEP)
endif