#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <sqlite3.h>

#include "rapidjson/document.h"

class DBManager {
private:
	sqlite3* db;

public:
	DBManager();

	void addMessage(rapidjson::Value& object);

	rapidjson::Document last50(uint64_t latestID);
};

#endif // DBMANAGER_H
