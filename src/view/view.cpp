#include "view.h"
#include <fstream>
#include <sstream>

namespace calassomys
{

View::View()
{
}

void View::setContent(const ifstream& file)
{
    stringstream ss;
    ss << file.rdbuf();
    setContent(ss.str());
}

void View::setContent(const string &htmlText)
{
    html.parse(htmlText);
}

void View::setContentId(string id, string fileNameContent)
{
    ifstream file(fileNameContent);
    stringstream ss;
    ss << file.rdbuf();
    HTML::ParserDom dom;
    dom.parse(ss.str());
    const treeNode& newTree = (treeNode&)dom.getTree();

    treeNode::iterator it = getTagById(id);
    if(getDom().is_valid(it)){
        treeNode& tree = const_cast<treeNode&>(getDom());
        tree.erase_children(it);
        tree.append_child(it, newTree.begin());
    }

    mapeiaIdNode();
    mapeiaNameNode();
}

void View::insertContentId(string id, View &view)
{
    treeNode::iterator it = getTagById(id);
    if(getDom().is_valid(it)){
        treeNode& tree = const_cast<treeNode&>(getDom());
        tree.append_children(it, view.getDom().begin(), view.getDom().end());
    }

    mapeiaIdNode();
    mapeiaNameNode();
}

void View::insertContentId(string id, const ifstream& file)
{
    View view;
    view.setContent(file);
    insertContentId(id, view);
}

void View::insertContentId(string id, const string &html)
{
    View view;
    view.setContent(html);
    insertContentId(id, view);
}

treeNode& View::getDom()
{
    return const_cast<treeNode&>((const treeNode&)html.getTree());
}

treeNode::iterator View::getTagById(string id)
{
    if(mapIdItrNode.empty())
        mapeiaIdNode();
    auto it = mapIdItrNode.find(id);
    if(it!=mapIdItrNode.end())
        return it->second;

    return getDom().end();
}

void View::write(std::ostream& out, const treeNode& dom)
{
    treeNode::iterator it = dom.begin();
    it->parseAttributes();

    const string& text = it->text();
    out << text;

    for ( unsigned i=0; i<dom.number_of_children(it); i++ )
    {
        write(out, dom.child(it,i) );
    }

    const string &closinText = it->closingText();
    out << closinText;
}

void View::insertMapNameNode(treeNode::iterator& it)
{
    it->parseAttributes();
    auto attr = it->attribute("name");
    if(attr.first)
        mapNameItrNodes[attr.second].push_back(it);
}

void View::mapeiaNameNode()
{
    mapNameItrNodes.clear();
    for(auto it=getDom().begin(); it!=getDom().end(); it++)
    {
        insertMapNameNode(it);
    }
}

void View::mapeiaIdNode()
{
    mapIdItrNode.clear();
    for(auto it=getDom().begin(); it!=getDom().end(); it++)
    {
        if(it->attributes().empty())
            it->parseAttributes();
        auto attr = it->attribute("id");
        if(attr.first)
            mapIdItrNode[attr.second] = it;
    }
}

vecItrNode View::getTagsByName(string id)
{
    if(mapNameItrNodes.empty()){
        mapeiaNameNode();
    }

    auto it = mapNameItrNodes.find(id);
    if(it != mapNameItrNodes.end())
        return it->second;

    return vecItrNode();
}

void View::setText(treeNode::iterator node, const string &text)
{
    if(getDom().is_valid(node))
        for ( unsigned i=0; i<getDom().number_of_children(node); i++ )
        {
            treeNode::iterator it = getDom().child(node, i);
            if ( !it->isTag() && !it->isComment() )
            {
                it->text( text );
            }
        }
}

} // end namespace

std::ostream& operator<<(std::ostream &stream, calassomys::View &view)
{
    view.write(stream, view.getDom());
}
