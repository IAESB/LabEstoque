#include "dao.h"
#include <soci/mysql/soci-mysql.h>

DaoPrt Dao::instance;

Dao::Dao(string host, string user, string password, string database)
{    
    sql.open(soci::mysql, "host="+host+" db="+database+" user="+user+" password="+password);
}

DaoPrt Dao::getInstance(const string& url, const string& user, const string& password, const string& database)
{
    if( ! instance ){
        if(!url.empty() && !user.empty())
            instance.reset(new Dao(url, user, password, database));
        else
            throw std::runtime_error("Passe a URL, Usuario e Senha na primeira vez que chamar: Dao::getInstance");
    }


    return instance;
}

Dao::~Dao()
{
}


soci::session* Dao::getConnection()
{
    return &sql;
}

ResultSet Dao::executeQuery(const string &sql)
{
    soci::session* connection = getConnection();

    ResultSet rs = connection->prepare << sql;

    return rs;
}

void Dao::executeUpdate(const string& sql)
{
    soci::session* connection = getConnection();

    *connection << sql;
    connection->commit();
}
