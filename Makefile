TARGET=meow
OBJECTS=meow.o MeowApp.o MeowWindow.o MeowConsole.o MeowSession.o MeowModule.o MeowModuleCollection.o DynamicArray.o MeowSynthModule.o MeowMidiModule.o MeowKeyboard.o MeowAudioModule.o MeowMixerModule.o KeyboardView.o
CFLAGS=-Wall -g --std=gnu99 `sdl-config --cflags`
LDLIBS=-ljack -lSDL -lX11 -lpthread -lreadline -lasound -ljack -lSDL_ttf
CC=gcc

$(TARGET) : $(OBJECTS)

clean:
	rm -rf $(OBJECTS) $(TARGET)
