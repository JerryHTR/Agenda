#include "AgendaUI.h"
#include <iostream>
#include <iomanip>
#include "Log.h"
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::setw;

AgendaUI::AgendaUI() {}

void AgendaUI::OperationLoop(void) {
  std::string operation;
  startAgenda();
  while (1) {
    operation = getOperation();
    executeOperation(operation);
  }
  quitAgenda();
}

void AgendaUI::startAgenda(void) {
  std::cout << "----------------------------------------------------------------- Agenda -----------------------------------------------------------------\n\n";
  std::cout << "Action :\n" << "l   - log in Agenda by user name and password\n"
	    << "r   - register an Agenda account\n"
	    << "q   - quit Agenda\n"
	    << "\n------------------------------------------------------------------------------------------------------------------------------------------\n\n";
}

std::string AgendaUI::getOperation() {
  std::string operation;
  if (agendaService_.userLogIn(userName_, userPassword_) == 0) {
    std::cout << "Agenda : ~$ ";
  } else {
    std::cout << "Agenda@" << userName_ << " : #";
  }
  std::cin >> operation;
  return operation;
}

bool AgendaUI::executeOperation(std::string op) {
  Log log;
  if (agendaService_.userLogIn(userName_, userPassword_) == 0) {
    if (op == "l") {
      userLogIn();
      return true;
    }
    else if (op == "r") {
      userRegister();
      return true;
    }
    else if (op == "q") {
      quitAgenda();
      return true;
    } else {
      std::cout << "[error] Wrong command! "
                << "Please input \"l\", \"r\" or \"q\"\n";
      log.writeToFile("[error] Wrong command! Please input \"l\", \"r\" or \"q\"\n");
      startAgenda();
      return false;
    }
  } else {
    if (op == "o") {
      userLogOut();
      return true;
    }
    else if (op == "dc") {
      deleteUser();
      return true;
    }
    else if (op == "lu") {
      listAllUsers();
      return true;
    }
    else if (op == "cm") {
      createMeeting();
      return true;
    }
    else if (op == "la") {
      listAllMeetings();
      return true;
    }
    else if (op == "las") {
      listAllSponsorMeetings();
      return true;
    }
    else if (op == "lap") {
      listAllParticipateMeetings();
      return true;
    }
    else if (op == "qm") {
      queryMeetingByTitle();
      return true;
    }
    else if (op == "qt") {
      queryMeetingByTimeInterval();
      return true;
    }
    else if (op == "dm") {
      deleteMeetingByTitle();
      return true;
    }
    else if (op == "da") {
      deleteAllMeetings();
      return true;
    } else {
      std::cout << "[error] Wrong command! "
		<< "Please input proper command as the list shows\n";
      log.writeToFile("[error] Wrong command! Please input proper command as the list shows\n");
      return false;
    }
  }
}

void AgendaUI::userLogIn(void) {
  std::cout << "[log in] [user name] [password]\n"
	    << "[log in] ";
  std::cin >> userName_ >> userPassword_;
  Log log;
  if (agendaService_.userLogIn(userName_, userPassword_)) {
    log.writeToFile(userName_ + " log in succeed\n");
    std::cout << "[log in] succeed!\n\n"
	      << "----------------------------------------------------------------- Agenda -----------------------------------------------------------------\n\n"
	      << "Action :\n"
	      << "o   - log out Agenda\n"
	      << "dc  - delete Agenda account\n"
	      << "lu  - list all Agenda user\n"
	      << "cm  - create a meeting\n"
	      << "la  - list all meetings\n"
	      << "las - list all sponsor meetings\n"
	      << "lap - list all participate meetings\n"
	      << "qm  - query meeting by title\n"
	      << "qt  - query meeting by time interval\n"
	      << "dm  - delete meeting by title\n"
	      << "da  - delete all meetings\n"
	      << "\n------------------------------------------------------------------------------------------------------------------------------------------\n\n";
  } else {
    log.writeToFile(userName_ + " log in fail\n");
    std::cout << "[error] log in fail!\n";
    userName_ = userPassword_ = "";
    std::cout << "Wrong user name or password.Please check out\n";
    startAgenda();
  }
}

void AgendaUI::userRegister(void) {
  std:cout << "[register] [user name] [password] [email] [phone]\n"
	  << "[register] ";
  string name_, password_, email_, phone_;
  std::cin >> name_ >> password_ >> email_ >> phone_;
  Log log;
  if (agendaService_.userRegister(name_, password_, email_, phone_)) {
    log.writeToFile(name_ + " register succeed\n");
    std::cout << "[register] succeed!\n\n";
    startAgenda();
  } else {
    log.writeToFile(name_ + " register fail\n");
    std::cout << "[error] register fail!\n";
    std::cout << "This user name has already existed, please change\n";
    startAgenda();
  }
}

void AgendaUI::quitAgenda(void) {
  Log log;
  log.writeToFile("quit Agenda\n");
  exit(0);
}

void AgendaUI::userLogOut(void) {
  Log log;
  log.writeToFile(userName_ + " log out succeed\n");
  userName_ = userPassword_ = "";
  std::cout << "Log out successfully!\n";
  startAgenda();
}

void AgendaUI::deleteUser(void) {
  Log log;
  if (agendaService_.deleteUser(userName_, userPassword_)) {
    log.writeToFile(userName_ + " is deleted\n");
    std::cout << "[delete agenda account] succeed!\n";
  }
  startAgenda();
}

void AgendaUI::listAllUsers(void) {
  Log log;
  log.writeToFile("listAllUsers is called by " + userName_ + "\n");
  std::list<User> result = agendaService_.listAllUsers();
  std::list<User>::iterator it = result.begin();
  std::cout << "\n----------------------------------------------------------------- Agenda -----------------------------------------------------------------\n\n";
  std::cout << "[list all users]\n\n"
	    << std::left << setw(26) << "name"
	    << std::left << setw(26) << "email"
	    << std::left << setw(26) << "phone"
	    << std::endl << std::endl;
  while (it != result.end()) {
    std::cout << std::left << setw(26) << it->getName()
              << std::left << setw(26) << it->getEmail() //xiugaile!!
              << std::left << setw(26) << it->getPhone()
              << std::endl << std::endl;
    it++;
  }
  std::cout << "------------------------------------------------------------------------------------------------------------------------------------------\n\n";
}

void AgendaUI::createMeeting(void) {
  Log log;
  std::cout << "\n----------------------------------------------------------------- Agenda -----------------------------------------------------------------\n\n";
  std::cout << "[create meeting] "
	    << "[title] "
	    << "[participator] "
	    << "[start time(yyyy-mm-dd/hh:mm)] "
	    << "[end time(yyyy-mm-dd/hh:mm)]"
	    << std::endl;
  string t, p, st, et;
  std::cout << "[create meeting] ";
  std::cin >> t >> p >> st >> et;
  if (agendaService_.createMeeting(userName_, t, p, st, et)) {
    log.writeToFile(userName_ + " create meeting " + t + "succeed\n");
    std::cout << "\n[create meeting] succeed!\n";
    std::cout << "\n------------------------------------------------------------------------------------------------------------------------------------------\n\n";
  } else {
    log.writeToFile(userName_ + " create meeting " + t + " failed\n");
    std::cout << "\n[error] create meeting fail!\n";
    std::cout << "\n------------------------------------------------------------------------------------------------------------------------------------------\n\n";
  }
}

void AgendaUI::listAllMeetings(void) {
  Log log;
  log.writeToFile(userName_ + " list all meetings\n");
  std::cout << "[list all meetings]\n\n";
  std::list<Meeting> result = agendaService_.listAllMeetings(userName_);
  printMeetings(result);
}

void AgendaUI::listAllSponsorMeetings(void) {
  Log log;
  log.writeToFile(userName_ + " list all sponsor meetings\n");
  std::cout << "[list all sponsor meetings]\n\n";
  std::list<Meeting> result = agendaService_.listAllSponsorMeetings(userName_);
  printMeetings(result);
}

void AgendaUI::listAllParticipateMeetings(void) {
  Log log;
  log.writeToFile(userName_ + " list all participate meetings\n");
  std::cout << "[list all participate meetings]\n\n";
  std::list<Meeting> result = agendaService_.listAllParticipateMeetings(userName_);
  printMeetings(result);
}

void AgendaUI::queryMeetingByTitle(void) {
  Log log;
  log.writeToFile(userName_ + " query meetings by title\n");
  std::cout << "\n----------------------------------------------------------------- Agenda -----------------------------------------------------------------\n\n";
  std::cout << "[query meeting] [title]:\n"
	    << "[query meeting] ";
  string t;
  std::cin >> t;
  std::list<Meeting> result;
  result = agendaService_.meetingQuery(userName_, t);
  std::list<Meeting>::iterator it = result.begin();
  std::cout << std::endl
	    << std::left << setw(30) << "sponsor"
            << std::left << setw(30) << "participator"
            << std::left << setw(30) << "start time"
            << std::left << setw(30) << "end time"
	    << std::endl << std::endl;
  while (it != result.end()) {
    std::cout << std::left << setw(30) << it->getSponsor()
              << std::left << setw(30) << it->getParticipator()
              << std::left << setw(30) << Date::dateToString(it->getStartDate())
              << std::left << setw(30) << Date::dateToString(it->getEndDate())
	      << std::endl << std::endl;
    it++;
  }
  if (result.size() == 0) {
    std::cout << "There is no meeting record now\n";
  }
  std::cout << "------------------------------------------------------------------------------------------------------------------------------------------\n\n";
}

void AgendaUI::queryMeetingByTimeInterval(void) {
  Log log;
  log.writeToFile(userName_ + " query meetings by time interval\n");
  std::cout << "[query meetings] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]\n"
            << "[query meetings] ";
  string st, et;
  std::cin >> st >> et;
  std::cout << std::endl;
  std::list<Meeting> result;
  result = agendaService_.meetingQuery(userName_, st, et);
  printMeetings(result);
}

void AgendaUI::deleteMeetingByTitle(void) {
  std::cout << "\n----------------------------------------------------------------- Agenda -----------------------------------------------------------------\n\n";
  std::cout << "[delete meeting] [title]\n"
	    << "[delete meeting] ";
  string t;
  std::cin >> t;
  std::cout << std::endl;
  Log log;
  if (agendaService_.deleteMeeting(userName_, t)) {
    log.writeToFile(userName_ + " delete meeting by title succeed\n");
    std::cout << "[delete meeting by title] succeed!\n";
    std::cout << "\n------------------------------------------------------------------------------------------------------------------------------------------\n\n";
  } else {
    log.writeToFile(userName_ + " delete meeting by title fail\n");
    std::cout << "[error] delete meeting fail!\n";
    std::cout << "\n------------------------------------------------------------------------------------------------------------------------------------------\n\n";
  }
}

void AgendaUI::deleteAllMeetings(void) {
  Log log;
  std::cout << "\n----------------------------------------------------------------- Agenda -----------------------------------------------------------------\n\n";
  if (agendaService_.deleteAllMeetings(userName_)) {
    log.writeToFile(userName_ + " delete all meetings succeed\n");
    std::cout << "[delete all meeting] succeed!\n";
    std::cout << "\n------------------------------------------------------------------------------------------------------------------------------------------\n\n";
  } else {
    log.writeToFile(userName_ + " delete all meetings fail\n");
    std::cout << "[error] delete all meetings fail!\n";
    std::cout << "\n------------------------------------------------------------------------------------------------------------------------------------------\n\n";
  }
}

void AgendaUI::printMeetings(std::list<Meeting> meetings) {
  std::cout << "\n----------------------------------------------------------------- Agenda -----------------------------------------------------------------\n\n";
  std::cout << std::left << setw(30) << "title"
	    << std::left << setw(30) << "sponsor"
            << std::left << setw(30) << "participator"
            << std::left << setw(30) << "start time"
            << std::left << setw(30) << "end time"
	    << std::endl;
  std::list<Meeting>::iterator it = meetings.begin();
  while (it != meetings.end()) {
    std::cout << std::left << setw(30) << it->getTitle()
	      << std::left << setw(30) << it->getSponsor()
              << std::left << setw(30) << it->getParticipator()
              << std::left << setw(30) << Date::dateToString(it->getStartDate())
              << std::left << setw(30) << Date::dateToString(it->getEndDate())
	      << std::endl;
    it++;
  }
  std::cout << "------------------------------------------------------------------------------------------------------------------------------------------\n\n";
}
