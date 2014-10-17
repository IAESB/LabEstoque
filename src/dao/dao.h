#ifndef DAO_H
#define DAO_H

#include <memory>
#include <vector>
#include <iostream>
#include <mysql_driver.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace std;

class Dao;
typedef shared_ptr<Dao> DaoPrt;

class Dao
{
    string url;
    string user;
    string password;
    string database;
    static DaoPrt instance;
    unique_ptr<sql::Connection> connection;
    Dao(string url, string user, string password, string database);
public:
    static DaoPrt getInstance(string url="" /*tcp://127.0.0.1:3306*/, string user="", string password="", string database="");
    ~Dao();

    bool isConnected();
    void reconnect();

    template<typename type>
    bool update(type& obj)
    {
        if( ! isConnected())
            reconnect();

        string sql = obj.getSqlUpdate();
        unique_ptr<sql::Statement> stmt( connection->createStatement() );
        if(stmt->executeUpdate(sql)>0)
            return true;
        return false;
    }

    template<typename type>
    bool remove(type& obj)
    {
        if( ! isConnected())
            reconnect();

        string sql = obj.getSqlDelete();
        unique_ptr<sql::Statement> stmt( connection->createStatement() );
        if(stmt->executeUpdate(sql)>0)
            return true;
        return false;
    }

    template<typename type>
    shared_ptr< vector< shared_ptr<type> > > select(string table, string columns="", string options="")
    {
        if( ! isConnected())
            reconnect();

        shared_ptr< vector< shared_ptr<type> > > vec(new vector< shared_ptr<type> >);
        string sql = "SELECT ";
        sql += columns.empty()?"*":columns;
        sql += " FROM "+table+" ";
        sql += options.empty()?"":options;
        unique_ptr<sql::Statement> stmt( connection->createStatement() );
        unique_ptr<sql::ResultSet> rs( stmt->executeQuery(sql) );
        while (rs->next()) {
            vec->push_back( shared_ptr<type>(new type(*rs) ) );
        }
        rs->close();
        return vec;
    }

    template<typename type>
    long long insert(type& obj)
    {
        if( ! isConnected())
            reconnect();

        long long id = -1;
        const string& sql = obj.getSqlInsert();
        unique_ptr<sql::Statement> stmt( connection->createStatement() );
        stmt->executeUpdate(sql);
        unique_ptr<sql::ResultSet> rs( stmt->executeQuery("SELECT LAST_INSERT_ID()") );

        if (rs->next())
            id = rs->getInt(1);
        rs->close();

        return id;
    }
};

#endif // DAO_H
