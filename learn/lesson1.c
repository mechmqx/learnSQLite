#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

#define _DEBUG_

int main( void )
{
 sqlite3 *db=NULL;
 char *zErrMsg = 0;
 int rc;
 
 //打开指定的数据库文件,如果不存在将创建一个同名的数据库文件
 rc = sqlite3_open("zieckey.db", &db); 
 if( rc )
 {
  fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
  sqlite3_close(db);
  //exit(1);
  return 0;
 }
 else printf("You have opened a sqlite3 database named zieckey.db successfully!\nCongratulations! Have fun !  ^-^ ...\n");
 
 //create a table, if exist not create and notice, storing in zErrMsg
 char *sql = "CREATE TABLE SensorData( \
		 ID INTEGER PRIMARY KEY, \
		 SensorID INTEGER, \
		 SiteNum INTEGER, \
		 Time VARCHAR(12), \
		 SensorParameter REAL \
		 );";
 sqlite3_exec(db,sql,0,0,&zErrMsg);

#ifdef _DEBUG_
 printf("%s\n",&zErrMsg);
#endif

 //insert data
 sql = "INSERT INTO \"SensorData\" VALUES(NULL, 1, 1, '20060511206',18.9);";
 sqlite3_exec(db,sql,0,0,&zErrMsg);
#ifdef _DEBUG_
 printf("%s\n",&zErrMsg);
#endif

 sql = "INSERT INTO \"SensorData\" VALUES(NULL, 2, 1, '20060511306',16.4);";
 sqlite3_exec(db,sql,0,0,&zErrMsg);
#ifdef _DEBUG_
 printf("%s\n",&zErrMsg);
#endif

 int nrow = 0, ncolumn = 0;
 char **azResult;

// querying the db
  sql = "SELECT * FROM SensorData";
  sqlite3_get_table(db,sql,&azResult,&nrow,&ncolumn,&zErrMsg);
  
  int i = 0;
  printf("row:%d column:%d \n",nrow,ncolumn);
  printf("\nThe reslut of quering is:\n");
  for(i=0;i<(nrow+1)*ncolumn;i++)
  {
	  printf("azResult[%d]=%s\n",i,azResult[i]);
  }
  sqlite3_free_table(azResult);

#ifdef _DEBUG_
  printf("zErrMsg = %s\n",&zErrMsg);
#endif

  //delete item
  sql = "DELETE FROM SensorData WHERE SensorID=1;";
  sqlite3_exec(db,sql,0,0,&zErrMsg);
#ifdef _DEBUG_
  printf("zErrMsg=%s\n",&zErrMsg);
#endif

// querying the db after delete item
  sql = "SELECT * FROM SensorData";
  sqlite3_get_table(db,sql,&azResult,&nrow,&ncolumn,&zErrMsg);
  
  printf("\n\n\nrow:%d column:%d \n",nrow,ncolumn);
  printf("\nThe reslut of quering is:\n");
  for(i=0;i<(nrow+1)*ncolumn;i++)
  {
	  printf("azResult[%d]=%s\n",i,azResult[i]);
  }
  sqlite3_free_table(azResult);



 sqlite3_close(db); //关闭数据库
 return 0;
}
