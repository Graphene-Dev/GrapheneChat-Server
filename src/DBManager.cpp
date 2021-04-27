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

rapidjson::Document DBManager::last50(uint64_t latestID) {
  char *zErrMsg = 0;
	char sql[4096];

	sprintf(sql, "SELECT * FROM MESSAGES Order By ID ASC");

  int nC;
  int nR;

  char** result;

	int rc = sqlite3_get_table(db, sql, &result, &nR, &nC, &zErrMsg);

	if( rc != SQLITE_OK ){
    printf("SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
	}

  rapidjson::Document d;
  d.SetObject();

  rapidjson::Document::AllocatorType& allocator = d.GetAllocator();

  d.AddMember("type", "MSG_LIST", allocator);

  rapidjson::Value msgs(rapidjson::kArrayType);

  for (int i = 4; i <= nR*nC; i+=4) {
    rapidjson::Value obj(rapidjson::kObjectType);
    obj.AddMember("id", strtoul(result[i], NULL, 0), allocator);
    obj.AddMember("channel", strtoul(result[i+1], NULL, 0), allocator);
    obj.AddMember("author", strtoul(result[i+2], NULL, 0), allocator);
    obj.AddMember("msg", rapidjson::Value(result[i+3], allocator), allocator);
    msgs.PushBack(obj, allocator);
  }

  d.AddMember("list", msgs, allocator);

  sqlite3_free_table(result);
  return d;
}

void list_channels() {

}
