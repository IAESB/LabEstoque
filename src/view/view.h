#ifndef VIEW_H
#define VIEW_H

#include <htmlcxx/html/ParserDom.h>
#include <ostream>
#include <fstream>
#include <vector>
#include "node.h"

using namespace std;
using namespace htmlcxx;


typedef tree<calassomys::Node> treeNode;
typedef treeNode::iterator tag;
typedef vector< treeNode > vecTreeNode;
typedef vector<treeNode::iterator> vecItrNode;

namespace calassomys {

class View
{
    HTML::ParserDom html;
    map<string, treeNode::iterator> mapIdItrNode;
    map<string, vecItrNode> mapNameItrNodes;
public:
    View();
    void setContent(const ifstream& file);
    void setContent(const string& html);
    void insertContentId(string id, View& view);
    void insertContentId(string id, const ifstream& file);
	void insertContentId(string id, const string& html);
	void setContentId(string id, const string& html);
	void setContentId(string id, const ifstream& file);
    void write(std::ostream& out, const treeNode& dom);
    treeNode& getDom();
    treeNode::iterator getTagById(string id);
    vecItrNode getTagsByName(string name );
    void setText(treeNode::iterator node, const string& text);
private:
    void insertMapNameNode(treeNode::iterator& it);
    void mapeiaNameNode();
    void mapeiaIdNode();
};
}
std::ostream& operator<<(std::ostream &stream, calassomys::View &view);

#endif // VIEW_H
