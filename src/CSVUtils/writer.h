#ifndef WRITER_H
#define WRITER_H

#include <QString>
#include <QTextCodec>
#include <QIODevice>

#include "abstractdata.h"

class abstractdata;

class Writer{

public:
    enum WriteMode
    {
        REWRITE = 0,
        APPEND
    };

    // Write data to csv-file
    static bool write(const QString& filePath,
                      const abstractdata& data,
                      const QString& separator = QString(","),
                      const QString& textDelimiter = QString("\""),
                      const WriteMode& mode = REWRITE,
                      const QStringList& header = QStringList(),
                      const QStringList& footer = QStringList(),
                      QTextCodec* codec = QTextCodec::codecForName("UTF-8"));

    // Write data to IO Device
    static bool write(QIODevice& ioDevice,
                      const AbstractData& data,
                      const QString& separator = QString(","),
                      const QString& textDelimiter = QString("\""),
                      const QStringList& header = QStringList(),
                      const QStringList& footer = QStringList(),
                      QTextCodec* codec = QTextCodec::codecForName("UTF-8"));
}

#endif // WRITER_H
