#ifndef NODE_H
#define NODE_H

#include <htmlcxx/html/Node.h>

namespace calassomys {
using namespace std;

class Node : public htmlcxx::HTML::Node
{
public:
    Node();
    void setAttrute(const string& attr, const string& text);
    void text(const std::string& text);
    const std::string& text();
};

}
#endif // NODE_H
