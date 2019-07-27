#ifndef ABSTRACTDATA_H
#define ABSTRACTDATA_H

#include <QStringList>



class abstractdata
{
public:
    explicit abstractdata(){}
    virtual ~abstractdata() {}

    // Add new empty row
    virtual void addEmptyRow() = 0;
    // Add new row with specified values (as strings)
    virtual void addRow(const QStringList& values) = 0;
    // Clear all data
    virtual void clear() = 0;
    // Check if there are any rows
    virtual bool isEmpty() const = 0;
    // Get number of rows
    virtual int rowCount() const = 0;
    // Get values of specified row as list of strings
    virtual QStringList rowValues(const int& row) const = 0;
};

#endif // ABSTRACTDATA_H
