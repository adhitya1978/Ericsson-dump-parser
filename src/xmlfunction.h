#ifndef XMLFUNCTION_H
#define XMLFUNCTION_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QList>

#include <QDomDocument>
#include <QStringList>

#include "global_main.h"
#include "memory.h"

/*context mfh*/
struct MFH_STRUCT
{
    QString ffv;
    QString sn;
    QString st;
    QString vn;
    QString cbt;

};

/*context MD*/
struct MD_STRUCT
{
    NEID    _neid;
    MI      _mi;
};

struct NEID_STRUCT
{
    QString neun;
    QString nedn;
    QString nesw;
};

struct MI_STRUCT
{
    QString       mts;
    QString       gp;
    QStringList   mt;
    QList<MV>     *_mv;
};

struct MV_STRUCT
{
    QString moid;
    QStringList r;
};

struct MDC_STRUCT{
    MFH     _mfh;
    QList<MD>      *_md;
};

class XmlFunction
{
public:
    XmlFunction(const QString& input_name);

    int SetupDocument();

    MDC CreateMDCStruct();

    MDC *getCurrentMDC() const;

private:

    MFH_STRUCT mfh_create(void);

    NODE_TYPE Setup_node_type(const QString& nodetype);

    MFH CreateMFHStruct(const QDomElement &node);

    NEID CreateNEIDStruct(const QDomElement &node);

    MI CreateMIStruct(const QDomElement& node);

    MV CreateMVStruct(const QDomElement& node);

    MD CreateMDStruct(NEID_STRUCT NEID, MV_STRUCT MV);

private:
    const QString filename;
    QDomDocument xmldocument;
    MDC *currentMDC;
};

#endif // XMLFUNCTION_H
