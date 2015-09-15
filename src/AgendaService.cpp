#include "AgendaService.h"
#include <iostream>

AgendaService::AgendaService() {
  startAgenda();
}

AgendaService::~AgendaService() {
  quitAgenda();
}

bool AgendaService::userLogIn(std::string userName, std::string password) {
  std::list<User> result = \
    storage_->queryUser([=](const User& u){return u.getName() == userName &&
					   u.getPassword() == password;});
  if (result.size() != 0) {
    return true;
  } else {
    return false;
  }
}

bool AgendaService::userRegister(std::string userName, std::string password,
		  std::string email, std::string phone) {
  User newUser(userName, password, email, phone);
  std::list<User> result = \
    storage_->queryUser([=](const User& u){return u.getName() == userName;});
  if (result.size() != 0) {
    return false;
  } else {
    storage_->createUser(newUser);
    return true;
  }
}

bool AgendaService::deleteUser(std::string userName, std::string password) {
  int sum = \
    storage_->deleteUser([=](const User& u){return u.getName() == userName &&
					    u.getPassword() == password;});
  if (sum) {
    storage_->deleteMeeting([=](const Meeting& m)\
			    {return m.getSponsor() == userName\
				|| m.getParticipator() == userName;});
    return true;
  } else {
    return false;
  }
}

std::list<User> AgendaService::listAllUsers(void) {
  std::list<User> result = \
    storage_->queryUser([=](const User& u){return true;});
  return result;
}

bool AgendaService::createMeeting(std::string userName, std::string title,
                     std::string participator,
		   std::string startDate, std::string endDate) {
  std::list<User> result1 = \
    storage_->queryUser([=](const User& u){return u.getName() == userName;});
  std::list<User> result2 = \
    storage_->queryUser([=](const User& u){return u.getName() == participator;});
  std::list<Meeting> result3 = \
    storage_->queryMeeting([=](const Meeting& m){return m.getTitle() == title;});
  std::list<Meeting> result4 = \
    storage_->queryMeeting([=](const Meeting& m)->bool{
	if (Date::stringToDate(startDate) >= Date::stringToDate(endDate) \
	    || (!(Date::isValid(Date::stringToDate(startDate)))		\
		|| !(Date::isValid(Date::stringToDate(endDate))))) {
	  return true;
	} else {
	  if (userName == m.getSponsor() || participator == m.getParticipator() || userName == m.getParticipator()
	      || participator == m.getSponsor()) {
	    if ((m.getStartDate() <= Date::stringToDate(startDate)	\
	         && Date::stringToDate(startDate) < m.getEndDate()	\
	         &&  m.getEndDate() < Date::stringToDate(endDate))	\
	        || (Date::stringToDate(startDate) < m.getStartDate()	\
		    && Date::stringToDate(endDate) > m.getStartDate()	\
		    && Date::stringToDate(endDate) <= m.getEndDate())	\
	        || (Date::stringToDate(startDate) >= m.getStartDate()	\
		    && Date::stringToDate(endDate) <= m.getEndDate())	\
	        || (Date::stringToDate(startDate) < m.getStartDate()	\
		    && Date::stringToDate(endDate) > m.getEndDate())) {
	    return true;
	    } else {
	      return false;
	    }
	  } else {
	  return false;
	  }
	}
      });
  if (result1.size() != 0 && result2.size() != 0 && result3.size() == 0 \
      && result4.size() == 0 && userName != participator) {
    Meeting newMeet(userName, participator, Date::stringToDate(startDate), Date::stringToDate(endDate), title);
    storage_->createMeeting(newMeet);
    return true;
  } else {
    return false;
  }
}

std::list<Meeting> AgendaService::meetingQuery(std::string userName,
					       std::string title) {
  std::list<Meeting> result = \
  storage_->queryMeeting([=](const Meeting& m){return m.getTitle() == title \
					       && (m.getSponsor() == userName \
						   || m.getParticipator() == \
						   userName);});
  return result;
}

std::list<Meeting> AgendaService::meetingQuery(std::string userName, std::string startDate,
                                std::string endDate) {
  std::list<Meeting> result = \
  storage_->queryMeeting([=](const Meeting& m)->bool{
      if (Date::isValid(Date::stringToDate(startDate)) && Date::isValid(Date::stringToDate(endDate)) \
	  && Date::stringToDate(startDate) <= Date::stringToDate(endDate)) {
      if ((m.getStartDate() <= Date::stringToDate(startDate)	\
	         && Date::stringToDate(startDate) <= m.getEndDate()	\
	         &&  m.getEndDate() < Date::stringToDate(endDate))	\
	        || (Date::stringToDate(startDate) < m.getStartDate()	\
		    && Date::stringToDate(endDate) >= m.getStartDate()	\
		    && Date::stringToDate(endDate) <= m.getEndDate())	\
	        || (Date::stringToDate(startDate) >= m.getStartDate()	\
		    && Date::stringToDate(endDate) <= m.getEndDate())	\
	        || (Date::stringToDate(startDate) < m.getStartDate()	\
		    && Date::stringToDate(endDate) > m.getEndDate())) {
	if (m.getSponsor() == userName || m.getParticipator() == userName) {
	  return true;
	} else {
	  return false;
	}
      } else {
	return false;
      }
      } else {
	return false;
      }
    });
  return result;
}

std::list<Meeting> AgendaService::listAllMeetings(std::string userName) {
  std::list<Meeting> result = \
    storage_->queryMeeting([=](const Meeting& m){return m.getSponsor() == \
						 userName || \
						 m.getParticipator() \
						 == userName;});
  return result;
}

std::list<Meeting> AgendaService::listAllSponsorMeetings(std::string userName) {
  std::list<Meeting> result = \
    storage_->queryMeeting([=](const Meeting& m){return m.getSponsor() == \
						 userName;});
 return result;
}

std::list<Meeting> AgendaService::listAllParticipateMeetings(std::string userName) {
  std::list<Meeting> result = \
    storage_->queryMeeting([=](const Meeting& m){return m.getParticipator() == \
						 userName;});
 return result;
}

bool AgendaService::deleteMeeting(std::string userName, std::string title) {
  int sum = \
  storage_->deleteMeeting([=](const Meeting& m){return m.getSponsor() == \
						 userName && \
						  m.getTitle() == title;});
  if (sum) {
    return true;
  } else {
    return false;
  }
}

bool AgendaService::deleteAllMeetings(std::string userName) {
   int sum = \
  storage_->deleteMeeting([=](const Meeting& m){return m.getSponsor() == \
						 userName;});
  if (sum) {
    return true;
  } else {
    return false;
  }
}

void AgendaService::startAgenda(void) {
   storage_ = Storage::getInstance();
}

void AgendaService::quitAgenda(void) {
   storage_->sync();
}
