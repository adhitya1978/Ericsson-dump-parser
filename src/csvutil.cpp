#include "csvutil.h"
#include "global_main.h"
#include "xmlfunction.h"

const char  *  DOUBLE_QUOTE = "\"";
const char  *  CR   =  "\r";
const char  *  LF   =  "\n";


ContentIterator::ContentIterator(const abstractdata &data,
                                 const QString &separator,
                                 const QString &textDelimiter,
                                 const QStringList &header,
                                 const QStringList &footer,
                                 int chunkSize):
    m_data(data), m_separator(separator), m_textDelimiter(textDelimiter),
    m_header(header), m_footer(footer), m_chunkSize(chunkSize), m_dataRow(-1),
    atEnd(false)
{

}

bool ContentIterator::isEmpty() const
{
    return m_data.isEmpty() && m_header.isEmpty() && m_footer.isEmpty();
}

bool ContentIterator::hasNext() const
{
    return !atEnd;
}

QString ContentIterator::getNext()
{
    // Check if we have already get to the end of the content
    if ( atEnd )
    {
        return QString();
    }

    QString content;
    int rowsNumber = 0;

    // Initially m_dataRow have negative value. Negative value indicates that
    // client have called this function first time. In this case at the
    // beginning of the chunk we should place header information. And then
    // set m_dataRow to the index of the first row in main data container.
    if ( m_dataRow < 0 )
    {
        if ( false == m_header.isEmpty() )
        {
            content.append(composeRow(m_header));
            ++rowsNumber;
        }

        m_dataRow = 0;
    }

    // Check if m_dataRow is less than number of rows in m_data. If this is
    // true, add information from the m_data to the chunk. Otherwise, this means
    // that we already have passed all information from the m_data.
    if ( m_dataRow < m_data.rowCount() )
    {
        int endRow = qMin(m_dataRow + m_chunkSize - rowsNumber,
                          m_data.rowCount());
        for ( int i = m_dataRow; i < endRow; ++i, ++m_dataRow, ++rowsNumber )
        {
            content.append(composeRow(m_data.rowValues(i)));
        }
    }

    // If we still have place in chunk, try to add footer information to it.
    if ( rowsNumber < m_chunkSize )
    {
        if ( false == m_footer.isEmpty() )
        {
            content.append(composeRow(m_footer));
            ++rowsNumber;
        }

        // At this point chunk contains the last row - footer. That
        // means that we get to the end of content.
        atEnd = true;
    }

    return content;
}

QString ContentIterator::composeRow(const QStringList &values) const
{
    QStringList rowValues = values;
    const QString twoDelimiters = m_textDelimiter + m_textDelimiter;
    for (int i = 0; i < rowValues.size(); ++i)
    {
        rowValues[i].replace(m_textDelimiter, twoDelimiters);

        QString delimiter = m_textDelimiter;
        if (delimiter.isEmpty() &&
                (rowValues.at(i).contains(m_separator)
                 || rowValues.at(i).contains(CR)
                 || rowValues.at(i).contains(LF)))
        {
            delimiter = DOUBLE_QUOTE;
        }

        rowValues[i].prepend(delimiter);
        rowValues[i].append(delimiter);
    }

    QString result = rowValues.join(m_separator);
    result.append(LF);

    return result;
}


CSVUtil::CSVUtil(const QString &filepath):
    csvfile(filepath)
{
    xmlutil = new XmlFunction(filepath);
    xmlutil->SetupDocument();
}


QList<QVariant> CSVUtil::create_header()
{
    QList<QVariant> header;
    header << QVariant("NEID") << QVariant("MOID") << QVariant("Counter");

    mdc = xmlutil->CreateMDCStruct();

    QList<MD> *_lmd = mdc->_md;

    QList<MD>::const_iterator i;

    for(i = _lmd->constBegin(); i != _lmd->constEnd(); ++i){
        header << QVariant((*i)->_mi->mts);
    }

    return header;

}

VariantData CSVUtil::insertdata()
{
    QList<QVariant> row;
    VariantData listrow;

    if(mdc){
        QList<MD> *listMD = mdc->_md;
        QList<MD>::const_iterator i;
        for(i = listMD->constBegin() ; i != listMD->constEnd(); ++i)
        {
            QList<MV> *lmv = (*i)->_mi->_mv;
            int currentPosition = 0;


            for(QList<MV>::const_iterator itermv = lmv->constBegin();
                itermv != lmv->constEnd(); ++itermv){

                int totalvalue = (*i)->_mi->mt.count();

                while(true){

                    if(currentPosition == totalvalue){
                        currentPosition = 0; break;
                    }
                    /*insert neid*/
                    row << QVariant((*i)->_neid->nedn);

                    /*insert MOID*/
                    row << QVariant((*itermv)->moid);

                    /*insert counter*/
                    QStringList mt = (*i)->_mi->mt;
                    row << QVariant(mt[currentPosition]);

                    /*insert r*/
                    QStringList r = (*itermv)->r;
                    row << QVariant(r[currentPosition]);

                    listrow.addRow(row);

                    row.clear();

                    ++currentPosition;
                }
            }
        }
    }
    return listrow;
}
