CXX := g++
CXXFLAGS := -std=c++11 -Wall

# Add the source files of your project
SOURCES := game.cpp sourcefiles/ball.cpp  sourcefiles/paddle.cpp sockets/client.cpp sockets/server.cpp

# Specify the name of the output executable
EXECUTABLE := sfml_program

# Specify the libraries to link (e.g., SFML)
LIBRARIES := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network -lsfml-system

.PHONY: all clean run

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBRARIES)

clean:
	rm -f $(EXECUTABLE)

run: clean $(EXECUTABLE)
	./$(EXECUTABLE)
