#include "dao.h"
#include "exception/exception.h"

DaoPrt Dao::instance;

Dao::Dao(string url, string user, string password, string database)
{    
    this->url = url;
    this->user = user;
    this->password = password;
    this->database = database;
}

DaoPrt Dao::getInstance(string url, string user, string password, string database)
{
    if( ! instance ){
        if(!url.empty() && !user.empty())
            instance.reset(new Dao(url, user, password, database));
        else
            throw Exception("Passe a URL, Usuario e Senha na primeira vez que chamar: Dao::getInstance");
    }


    return instance;
}

Dao::~Dao()
{
}


Dao::Connection Dao::getConnection()
{
    if(!url.empty() && !user.empty()){
        sql::Driver *driver = get_driver_instance();
        sql::Connection* con = driver->connect(url, user, password);
		Connection connection(con);
        connection->setSchema(database);
		return connection;
    }
    else
        throw Exception("Passe a URL, Usuario e Senha na primeira vez que chamar: Dao::getInstance");
}

