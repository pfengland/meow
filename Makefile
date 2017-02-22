TARGET=meow
OBJECTS=meow.o MeowApp.o MeowWindow.o MeowConsole.o MeowSession.o MeowModule.o MeowModuleCollection.o DynamicArray.o MeowSynthModule.o MeowMidiModule.o MeowKeyboard.o MeowAudioModule.o MeowMixerModule.o
CFLAGS=-Wall -g --std=gnu99
LDLIBS=-ljack -lSDL -lX11 -lpthread -lreadline -lasound -ljack
CC=gcc

$(TARGET) : $(OBJECTS)

clean:
	rm -rf $(OBJECTS) $(TARGET)
