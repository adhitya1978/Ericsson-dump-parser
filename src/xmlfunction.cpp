#include "xmlfunction.h"

XmlFunction::XmlFunction(const QString &input_name):
    filename(input_name)
{
}


NODE_TYPE XmlFunction::Setup_node_type(const QString &nodetype)
{
    if(nodetype == "mfh")   return NODE_TYPE_MFH;
    if(nodetype == "md")    return NODE_TYPE_MD;
    if(nodetype == "neid")  return NODE_TYPE_NEID;
    if(nodetype == "mv")    return NODE_TYPE_MV;
    if(nodetype == "mi")    return NODE_TYPE_MI;
    return NODE_TYPE_UKNOWN;
}

//[0]
int XmlFunction::SetupDocument()
{
    QString errmsg;
    int errorLine, errorColumn;

    if(filename.size() < 0)  return -1;

    QFile file(filename);

    if(!xmldocument.setContent(&file,
                              &errmsg,
                              &errorLine,
                              &errorColumn))
    {
        file.close();
        return -1;
    };

    file.close();

    return 0;

}

//[1]
MDC XmlFunction::CreateMDCStruct()
{
    /*create mdc*/
    struct MDC_STRUCT *_mdc = (struct MDC_STRUCT*) nodeparse_malloc_zero(sizeof(struct MDC_STRUCT));

    QDomElement element = xmldocument.documentElement();

    QDomNode firstnode = element.firstChild();

    QList<MD> *l = new QList<MD>();

    while (!firstnode.isNull()) {
        QDomElement current = firstnode.toElement();
        if(current.nodeName() == "mfh"){
            _mdc->_mfh = CreateMFHStruct(current);
        }
        if(current.nodeName() == "md"){
            struct MD_STRUCT *_md = new  MD_STRUCT;

            QDomElement next = current.toElement();

            QDomNode child = next.firstChild();

            while(!child.isNull()){

                QDomElement currentchild = child.toElement();

                if(currentchild.nodeName() == "neid") _md->_neid =  CreateNEIDStruct(currentchild);
                if(currentchild.nodeName() == "mi")   _md->_mi   =  CreateMIStruct(currentchild);
                child = currentchild.nextSibling();

            }
            l->append(_md);

        }
        firstnode = current.nextSibling();
    }
    _mdc->_md = l;
    return _mdc;
}

// node [mfh]
MFH XmlFunction::CreateMFHStruct(const QDomElement& node)
{
    struct MFH_STRUCT *_mfh = new MFH_STRUCT;

    QDomNode node_mfh = node.firstChild();

    while(!node_mfh.isNull()){
        QDomElement current = node_mfh.toElement();
        if(current.nodeName() == "ffv")    _mfh->ffv = current.text();
        if(current.nodeName() == "sn")     _mfh->sn = current.text();
        if(current.nodeName() == "st")     _mfh->st = current.text();
        if(current.nodeName() == "vn")     _mfh->vn = current.text();
        if(current.nodeName() == "cbt")    _mfh->cbt = current.text();
        node_mfh = current.nextSibling();
    }

    return _mfh;
}

// node[NEID]
NEID XmlFunction::CreateNEIDStruct(const QDomElement &node)
{
    /*prepare struct NEID*/
    struct NEID_STRUCT *_neid =new NEID_STRUCT;

    QDomNode node_neid = node.firstChild();

    while(!node_neid.isNull()){
        QDomElement current = node_neid.toElement();
        if(current.nodeName() == "neun") _neid->neun = current.text();
        if(current.nodeName() == "nedn") _neid->nedn = current.text();
        if(current.nodeName() == "nesw") _neid->nesw = current.text();
        node_neid = current.nextSibling();
    }
    return _neid;
}

// node[MI]
MI XmlFunction::CreateMIStruct(const QDomElement &node)
{
    /*prepare struct NEID*/
    struct MI_STRUCT *_mi =new MI_STRUCT;

    /*node mt have more 2 need to be list*/
    QStringList mtlist;

    QList<MV> *mv = new QList<MV>();

    QDomNode node_mi = node.firstChild();

    while (!node_mi.isNull()) {
        QDomElement current = node_mi.toElement();
        if(current.nodeName() == "mts") _mi->mts = current.text();
        if(current.nodeName() == "gp") _mi->gp = current.text();
        if(current.nodeName() == "mt") mtlist << current.text();
        if(current.nodeName() == "mv") mv->append(CreateMVStruct(current));
        node_mi = current.nextSibling();
    }
    // add mt list to struct
    _mi->mt = mtlist;
    _mi->_mv = mv;

    return _mi;

}

// node[MV]
MV XmlFunction::CreateMVStruct(const QDomElement &node)
{
    QStringList r;
    struct MV_STRUCT *_mv =new MV_STRUCT;

    QDomNode node_mv = node.firstChild();

    while (!node_mv.isNull()) {
        QDomElement current = node_mv.toElement();
        if(current.nodeName() == "moid") _mv->moid = current.text();
        if(current.nodeName() == "r") r << current.text();
        node_mv = current.nextSibling();
    }
    _mv->r = r;

    return _mv;
}

MDC *XmlFunction::getCurrentMDC() const
{
    return currentMDC;
}

