#include "Storage.h"
#include <fstream>
#include <iostream>
#include <cstring>
using std::string;
using std::ifstream;
using std::ofstream;

Storage* Storage::instance_ = NULL;

Storage::Storage() {
  readFromFile("./");
}

Storage *Storage::getInstance(void) {
  if (instance_ == NULL) {
    instance_ = new Storage();
  }
  return instance_;
}

Storage::~Storage() {
  instance_ = NULL;
  sync();
}

bool Storage::readFromFile(const char *fpath) {
  char path1[100], path2[100];
  strcpy(path1, fpath);
  strcpy(path2, fpath);
  strcat(path1, "User.csv");
  strcat(path2, "Meeting.csv");
  /* for (int i = 0; i < strlen(path1); i++) {
    std::cout << path1[i];
  }
  std::cout << std::endl; */
  ifstream in(path1, ifstream::ate);
  if (!in) {
    return false;
  }
  ifstream::pos_type end_mark1 = in.tellg();
  in.seekg(0, ifstream::beg);
  string info;
  while (in && in.tellg() != end_mark1
	 && getline(in, info)) {
    // std::cout << info << std::endl;
    string n, p, e, ph;
    if (info.find("name") != string::npos) {
      continue;
    }
    int comma[10] = {0};
    for (int i = 1, t = 0; i < info.size(); i++) {
      if (info[i] == '"' && info[i + 1] == '"') {
	i = i + 1; //hehe
	continue;
      }
      if (info[i] == '"' && info[i + 1] == ',') {
	comma[t++] = i + 1;
	i = i + 2; //hehe
	continue;
      }
    }
    for (int i = 1; i < comma[0] - 1; i++) {
      if (info[i] == '"' && info[i + 1] == '"') {
	n.push_back(info[i]);
	i++;
      } else {
        n.push_back(info[i]);
      }
    }
    for (int i = comma[0] + 2; i < comma[1] - 1; i++) {
      if (info[i] == '"' && info[i + 1] == '"') {
	p.push_back(info[i]);
	i++;
      } else {
        p.push_back(info[i]);
      }
    }
    for (int i = comma[1] + 2; i < comma[2] - 1; i++) {
      if (info[i] == '"' && info[i + 1] == '"') {
	e.push_back(info[i]);
	i++;
      } else {
        e.push_back(info[i]);
      }
    }
    for (int i = comma[2] + 2; i < info.length() - 1; i++) {
      if (info[i] == '"' && info[i + 1] == '"') {
	ph.push_back(info[i]);
	i++;
      } else {
        ph.push_back(info[i]);
      }
    }
    User u(n, p, e, ph);
    userList_.push_back(u);
  }
  
  in.close();
  in.open(path2, ifstream::ate);
  if (!in) {
    return false;
  }
  ifstream::pos_type end_mark2 = in.tellg();
  in.seekg(0, ifstream::beg);
  string minfo;
  while (in && in.tellg() != end_mark2
	 && getline(in, minfo)) {
    string s, p, t;
    Date st, et;
    if (minfo.find("sponsor") != string::npos) {
      continue;
    }
    int mcomma[10] = {0};
    for (int i = 1, t = 0; i < minfo.size(); i++) {
      if (minfo[i] == '"' && minfo[i + 1] == '"') {
	i = i + 1;
	continue;
      }
      if (minfo[i] == '"' && minfo[i + 1] == ',') {
	mcomma[t++] = i + 1;
	i = i + 2;
	continue;
      }
    }
    for (int i = 1; i < mcomma[0] - 1; i++) {
      if (minfo[i] == '"' && minfo[i + 1] == '"') {
	s.push_back(minfo[i]);
	i++;
      } else {
        s.push_back(minfo[i]);
      }
    }
    for (int i = mcomma[0] + 2; i < mcomma[1] - 1; i++) {
      if (minfo[i] == '"' && minfo[i + 1] == '"') {
	p.push_back(minfo[i]);
	i++;
      } else {
        p.push_back(minfo[i]);
      }
    }
    string sd, ed;
    for (int i = mcomma[1] + 2; i < mcomma[2] - 1; i++) {
      if (minfo[i] == '"' && minfo[i + 1] == '"') {
	sd.push_back(minfo[i]);
	i++;
      } else {
        sd.push_back(minfo[i]);
      }
    }
    st = Date::stringToDate(sd);
    for (int i = mcomma[2] + 2; i < mcomma[3] - 1; i++) {
      if (minfo[i] == '"' && minfo[i + 1] == '"') {
	ed.push_back(minfo[i]);
	i++;
      } else {
        ed.push_back(minfo[i]);
      }
    }
    et = Date::stringToDate(ed);
    for (int i = mcomma[3] + 2; i < minfo.length() - 1; i++) {
      if (minfo[i] == '"' && minfo[i + 1] == '"') {
	t.push_back(minfo[i]);
	i++;
      } else {
        t.push_back(minfo[i]);
      }
    }
    Meeting m(s, p, st, et, t);
    meetingList_.push_back(m);
  }
  return true;
}

bool Storage::writeToFile(const char *fpath) {
  char path1[100], path2[100];
  strcpy(path1, fpath);
  strcpy(path2, fpath);
  strcat(path1, "User.csv");
  strcat(path2, "Meeting.csv");
  ofstream out(path1);
  ifstream in(path1);
  if (!out || !in) {
    return false;
  }
  string str;
  in >> str;
  if (str.length() == 0) {
    out << "\"name\",\"password\",\"email\",\"phone\"\n";
  }
  std::list<User>::iterator it = userList_.begin();
  while (it != userList_.end()) {
    out << '"';
    int ln = it->getName().length();
    string n = it->getName();
    for (int i = 0; i < ln; i++) {
      if (n[i] == '"') {
	out << n[i];
      }
      out << n[i];
    }
    out << '"' << ',' << '"';
    string p = it->getPassword();
    for (int i = 0; i < p.length(); i++) {
      if (p[i] == '"') {
	out << p[i];
      }
      out << p[i];
    }
    out << '"' << ',' << '"';
    string e = it->getEmail();
    for (int i = 0; i < e.length(); i++) {
      if (e[i] == '"') {
	out << e[i];
      }
      out << e[i];
    }
    out << '"' << ',' << '"';
    string ph = it->getPhone();
    for (int i = 0; i < ph.length(); i++) {
      if (ph[i] == '"') {
	out << ph[i];
      }
      out << ph[i];
    }
    out << '"' << "\n";
    it++;
  }

  out.close();
  in.close();
  out.open(path2);
  in.open(path2);
  if (!out || !in) {
    return false;
  }
  string str2;
  in >> str2;
  if (str2.length() == 0) {
    out << "\"sponsor\",\"participator\",\"sdate\",\"edate\",\"title\"\n";
  }
  std::list<Meeting>::iterator it2 = meetingList_.begin();
  while (it2 != meetingList_.end()) {
    string sd, ed;
    sd = Date::dateToString(it2->getStartDate());
    ed = Date::dateToString(it2->getEndDate());
    out << '"';
    string spo = it2->getSponsor();
    for (int i = 0; i < spo.length(); i++) {
      if (spo[i] == '"') {
	out << spo[i];
      }
      out << spo[i];
    }
    out << '"' << ',' << '"';
    string par = it2->getParticipator();
    for (int i = 0; i < par.length(); i++) {
      if (par[i] == '"') {
	out << par[i];
      }
      out << par[i];
    }
    out << '"' << ',' << '"' << sd << '"'
	<< ',' << '"'<< ed << '"' << ',' << '"';
    string ti = it2->getTitle();
    for (int i = 0; i < ti.length(); i++) {
      if (ti[i] == '"') {
	out << ti[i];
      }
      out << ti[i];
    }
    out << '"' << "\n";
    it2++;
  }
  return true;
}

void Storage::createUser(const User& u) {
  userList_.push_back(u);
}

std::list<User> Storage::queryUser(std::function<bool(const User&)> filter) {
  std::list<User> nl;
  std::list<User>::iterator it = userList_.begin();
  while (it != userList_.end()) {
    if (filter(*it)) {
      nl.push_back(*it);
    }
    it++;
  }
  return nl;
}

int Storage::updateUser(std::function<bool(const User&)> filter,
	       std::function<void(User&)> switcher) {
  int sum = 0;
  std::list<User>::iterator it = userList_.begin();
  while (it != userList_.end()) {
    if (filter(*it)) {
      switcher(*it);
      sum++;
    }
    it++;
  }
  return sum;
}

int Storage::deleteUser(std::function<bool(const User&)> filter) {
  int sum = 0;
  std::list<User>::iterator it = userList_.begin();
  while (it != userList_.end()) {
    if (filter(*it)) {
      it = userList_.erase(it);
      sum++;
      continue;
    }
    it++;
  }
  return sum;
}

void Storage::createMeeting(const Meeting& m) {
  meetingList_.push_back(m);
}

std::list<Meeting> Storage::queryMeeting(
		   std::function<bool(const Meeting&)> filter) {
  std::list<Meeting> nl;
  std::list<Meeting>::iterator it = meetingList_.begin();
  while (it != meetingList_.end()) {
    if (filter(*it)) {
      nl.push_back(*it);
    }
    it++;
  }
  return nl;
}
  
int Storage::updateMeeting(std::function<bool(const Meeting&)> filter,
		  std::function<void(Meeting&)> switcher) {
  int sum = 0;
  std::list<Meeting>::iterator it = meetingList_.begin();
  while (it != meetingList_.end()) {
    if (filter(*it)) {
      switcher(*it);
      sum++;
    }
    it++;
  }
  return sum;
}

int Storage::deleteMeeting(std::function<bool(const Meeting&)> filter) {
  int sum = 0;
  std::list<Meeting>::iterator it = meetingList_.begin();
  while (it != meetingList_.end()) {
    if (filter(*it)) {
      it = meetingList_.erase(it);
      sum++;
      continue;
    }
    it++;
  }
  return sum;
}

bool Storage::sync(void) {
  if (writeToFile("./")) {
    return true;
  }
  return false;
}

