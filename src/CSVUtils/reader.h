#ifndef READER_H
#define READER_H

#include <QString>
#include <QTextCodec>
#include <QIODevice>

class Reader
{
public:
    class AbstractProcessor{
    public:
        explicit AbstractProcessor() {}
        virtual ~AbstractProcessor() {}

        // Preprocess one raw line from a file
        // @input:
        // line - raw line from a file
        virtual void preProcessRawLine(QString& line)
        {
            // Here you can edit line
            Q_UNUSED(line);
        }

        // Process one row worth of elements
        // @input:
        // - elements - list of row elements
        // @output:
        // bool - True if elements was processed successfully, False in case
        // of error. If process() return False, the csv-file will be stopped
        // reading
        virtual bool processRowElements(const QStringList& elements) = 0;
    };

    // Read csv-file and save it's data as strings to QList<QStringList>
    static QList<QStringList> readToList(const QString& filePath,
                                         const QString& separator = QString(","),
                                         const QString& textDelimiter = QString("\""),
                                         QTextCodec* codec = QTextCodec::codecForName("UTF-8"));

    // Read csv-formatted data from IO Device and save it
    // as strings to QList<QStringList>
    static QList<QStringList> readToList(QIODevice& ioDevice,
                                         const QString& separator = QString(","),
                                         const QString& textDelimiter = QString("\""),
                                         QTextCodec* codec = QTextCodec::codecForName("UTF-8"));

    // Read csv-file and save it's data to AbstractData-based container
    // class
    static bool readToData(const QString& filePath,
                           AbstractData& data,
                           const QString& separator = QString(","),
                           const QString& textDelimiter = QString("\""),
                           QTextCodec* codec = QTextCodec::codecForName("UTF-8"));

    // Read csv-formatted data from IO Device and save it
    // to AbstractData-based container class
    static bool readToData(QIODevice& ioDevice,
                           AbstractData& data,
                           const QString& separator = QString(","),
                           const QString& textDelimiter = QString("\""),
                           QTextCodec* codec = QTextCodec::codecForName("UTF-8"));

    // Read csv-file and process it line-by-line
    static bool readToProcessor(const QString& filePath,
                                AbstractProcessor& processor,
                                const QString& separator = QString(","),
                                const QString& textDelimiter = QString("\""),
                                QTextCodec* codec = QTextCodec::codecForName("UTF-8"));

    // Read csv-formatted data from IO Device and process it line-by-line
    static bool readToProcessor(QIODevice& ioDevice,
                                AbstractProcessor& processor,
                                const QString& separator = QString(","),
                                const QString& textDelimiter = QString("\""),
                                QTextCodec* codec = QTextCodec::codecForName("UTF-8"));
};

#endif // READER_H