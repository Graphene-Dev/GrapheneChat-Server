#include "DBManager.h"

#include <sqlite3.h>

#include <iostream>

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

DBManager::DBManager() {
	sqlite3_open("default.db", &db);
}

void DBManager::addMessage(rapidjson::Value& object) {
	char *zErrMsg = 0;
	char sql[4096];

	sprintf(sql, "INSERT INTO MESSAGES (ID, CHANNEL_ID, AUTHOR_ID, MSG) VALUES (%lu, %lu, %lu, \'%s\');", object["id"].GetUint64(), object["channel"].GetUint64(), object["author"].GetUint64(), object["msg"].GetString());

	int rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

	if( rc != SQLITE_OK ){
    printf("SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
	}
}
