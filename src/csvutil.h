#ifndef CSVUTIL_H
#define CSVUTIL_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QList>

#include "src/CSVUtils/abstractdata.h"
#include "src/CSVUtils/variantdata.h"
#include "xmlfunction.h"


class abstractdata;

class ContentIterator
    {
    public:
        explicit ContentIterator(const abstractdata& data,
                                 const QString& separator,
                                 const QString& textDelimiter,
                                 const QStringList& header,
                                 const QStringList& footer,
                                 int chunkSize = 1000);

        ~ContentIterator() {}

        // Check if content contains information
        bool isEmpty() const;
        // Check if content still has chunks of information to return
        bool hasNext() const;
        // Get next chunk of information
        QString getNext();

    private:
        // Compose row string from values
        QString composeRow(const QStringList& values) const;

    private:
        const abstractdata& m_data;
        const QString& m_separator;
        const QString& m_textDelimiter;
        const QStringList& m_header;
        const QStringList& m_footer;
        const int m_chunkSize;
        int m_dataRow;
        bool atEnd;
    };


class CSVUtil
{
public:
    CSVUtil(const QString& filepath);

    QList<QVariant> create_header();

    VariantData insertdata();

private:
    QString csvfile;
    bool shouldWrite;
    XmlFunction *xmlutil;

    MDC mdc;

};


class TempFileHandler
{
public:
    explicit TempFileHandler(const QString &filePath) : m_filePath(filePath) {}
    ~TempFileHandler()
    {
        QFile::remove(m_filePath);
    }

private:
    QString m_filePath;
};

class WriterPrivate
{
public:
    // Append information to the file
    static bool appendToFile(const QString& filePath,
                             ContentIterator& content,
                             QTextCodec* codec);

    // Overwrite file with new information
    static bool overwriteFile(const QString& filePath,
                              ContentIterator& content,
                              QTextCodec* codec);

    // Write to IO Device
    static bool writeToIODevice(QIODevice& ioDevice,
                                ContentIterator& content,
                                QTextCodec* codec);

    // Create unique name for the temporary file
    static QString getTempFileName();
};


#endif // CSVUTIL_H
