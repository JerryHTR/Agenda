Agenda:Storage.o Meeting.o Date.o User.o AgendaService.o AgendaUI.o Agenda.o Log.o
	g++ -std=c++0x Storage.o Meeting.o Date.o User.o AgendaService.o AgendaUI.o Agenda.o Log.o -o Agenda
Log.o:Log.h Log.cpp AgendaUI.h AgendaService.h Storage.h Meeting.h Date.h User.h
	g++ -std=c++0x Log.cpp -c
Agenda.o:Agenda.cpp AgendaUI.h AgendaService.h Storage.h Meeting.h Date.h User.h
	g++ -std=c++0x Agenda.cpp -c
AgendaUI.o:AgendaUI.cpp AgendaUI.h AgendaService.h Storage.h Meeting.h Date.h User.h
	g++ -std=c++0x AgendaUI.cpp -c
AgendaService.o:AgendaService.cpp AgendaService.h Storage.h Meeting.h Date.h User.h
	g++ -std=c++0x AgendaService.cpp -c
Storage.o:Storage.h Storage.cpp Meeting.h Date.h User.h
	g++ -std=c++0x Storage.cpp -c
Meeting.o:Meeting.h Meeting.cpp Date.h
	g++ -std=c++0x Meeting.cpp -c
Date.o:Date.h Date.cpp
	g++ -std=c++0x Date.cpp -c
User.o:User.h User.cpp
	g++ -std=c++0x User.cpp -c

clean:
	rm *.o Agenda
