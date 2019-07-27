#ifndef PREVIEW_H
#define PREVIEW_H

#include <QDialog>
#include "csvutil.h"

namespace Ui {
class preview;
}

class preview : public QDialog
{
    Q_OBJECT

public:
    explicit preview(QWidget *parent = 0);
    void SetInputFileData(const QString& filepath);
    ~preview();

private:
    Ui::preview *ui;
};

#endif // PREVIEW_H
