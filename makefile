CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

# Cible principale (nom de l'exécutable souhaité)
main: clockCalendarCOPY.o
	$(CXX) $(CXXFLAGS) -o main clockCalendarCOPY.o

# Compilation de l'objet (.o) dépendant du .cpp et du .h
clockCalendarCOPY.o: clockCalendarCOPY.cpp calendarDisplay.h
	$(CXX) $(CXXFLAGS) -c clockCalendarCOPY.cpp

# Nettoyage des fichiers générés
clean:
	rm -f *.o main