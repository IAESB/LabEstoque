#include "node.h"

namespace calassomys {

Node::Node()
{
}


void Node::setAttrute(const string &attr, const string &text)
{
    auto it = mAttributes.find(attr);
    if(it != mAttributes.end())
        it->second.assign(text);
    else
        mAttributes.insert(make_pair(attr, text));
}

void Node::text(const string &text)
{
    this->mText = text;
}

const string &Node::text()
{
    if(isTag() && !mTagName.empty() ){
        mText = '<'+mTagName+' ';
        for(auto& par: mAttributes){
            if( ! par.first.empty() )
                mText+=par.first + "=\"" + par.second +"\" ";
        }
        mText += ">";
    }
    return mText;
}


}
