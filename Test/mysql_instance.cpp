#include "mysql.h"
#include <iostream>

using namespace std;

bool executeMysql(MYSQL m_mysql, const char *sql) {
    if (mysql_query(&m_mysql, sql)) {
        cerr << "执行 sql 语句失败，错误信息为：" << mysql_error(&m_mysql) << endl;
        return false;
    } else {
        cout << "执行 sql 语句成功！" << endl;
    }
    return true;
}

int main(int argc, char *argv[]) {
    MYSQL mysql;                // 数据库结构体
    MYSQL_RES *res;             // 结果集结构体
    MYSQL_ROW row;              // char** 二维数组，存放一条条记录
    mysql_init(&mysql);         // 初始化数据库
    mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");       // 设置编码方式
    const char *host = "localhost";
    const char *user = "root";
    const char *passwd = "Dengyi@1995";
    const char *db = "db_audit";
    unsigned int port = 3306;
    //  连接数据库
    if (mysql_real_connect(&mysql, host, user, passwd, db, port, NULL, 0) == NULL) {
        cout << "连接失败！\n" << endl;
    }
    // 查询操作
    mysql_query(&mysql, "select * from station_config");
    // 获取结果集
    res = mysql_store_result(&mysql);
    // 获取每一行结果
    while (row = mysql_fetch_row(res)) {
        cout << "ID: " << row[0] << endl;
        cout << "Substation ID: " << row[1] << endl;
        cout << "Substation name: " << row[2] << endl;
        cout << "DCD name: " << row[3] << endl;
        cout << "Channel name: " << row[4] << endl;
        cout << "Channel IP: " << row[5] << endl;
        cout << "Merge cycle: " << row[7] << endl;
    }
    // 释放结果集
    mysql_free_result(res);
    // 关闭数据库
    mysql_close(&mysql);

    return 0;
}