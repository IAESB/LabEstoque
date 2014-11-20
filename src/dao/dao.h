#ifndef DAO_H
#define DAO_H

#include <memory>
#include <vector>
#include <iostream>
#include <soci/soci.h>

using namespace std;

class Dao;
typedef shared_ptr<Dao> DaoPrt;
typedef soci::rowset<soci::row> ResultSet;

class Dao
{
    soci::session sql;
    static DaoPrt instance;
    Dao(string host, string user, string password, string database);
public:
    static DaoPrt getInstance(const string& url="" /*tcp://127.0.0.1:3306*/, const string& user="", const string& password="", const string& database="");
    ~Dao();

    bool isConnected();
    soci::session* getConnection();

    void executeUpdate(const string& sql);
    ResultSet executeQuery(const string& sql);

    template<typename type>
    bool update(type& obj)
    {
        soci::session* connection = getConnection();

        string sql = obj.getSqlUpdate();
        *connection << sql;

        return true;
    }

    template<typename type>
    bool remove(type& obj)
    {
        soci::session* connection = getConnection();

        string sql = obj.getSqlDelete();
        *connection << sql;
        return false;
    }

    template<typename type>
    shared_ptr< vector< shared_ptr<type> > > select(string table, string columns="", string options="")
    {
        soci::session* connection = getConnection();

        shared_ptr< vector< shared_ptr<type> > > vec(new vector< shared_ptr<type> >);
        string sql = "SELECT ";
        sql += columns.empty()?"*":columns;
        sql += " FROM "+table+" ";
        sql += options.empty()?"":options;

        soci::rowset<soci::row> linhas = connection->prepare << sql;
        for(soci::row& linha: linhas) {
            vec->push_back( shared_ptr<type>(new type(linha) ) );
        }

        return vec;
    }

    template<typename type>
    long long insert(type& obj)
    {
        soci::session* connection = getConnection();

        long long id = -1;
        string sql = obj.getSqlInsert();

        *connection << sql;
        *connection << "SELECT LAST_INSERT_ID()", soci::into(id);

        return id;
    }
};

#endif // DAO_H
