#include "preview.h"
#include "ui_preview.h"

preview::preview(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::preview)
{
    ui->setupUi(this);
    this->setWindowTitle("bT@ymail.com");

}

void preview::SetInputFileData(const QString &filepath)
{
    CSVUtil *csv = new CSVUtil(filepath);

    QStringList header;
    foreach (const QVariant& var, csv->create_header()) {
        header.append(var.toString());
    }

    ui->tableWidget->setColumnCount(header.count());
    ui->tableWidget->setHorizontalHeaderLabels(header);

    VariantData data = csv->insertdata();


    ui->tableWidget->setRowCount(data.rowCount());

    for (auto r=0; r<data.rowCount(); r++){
        for (auto c=0; c<header.count(); c++){
            QStringList list = data.rowValues(r);
            QString item = QString("%1").arg(list.count() > c ? list.at(c) : tr("NA"));
            ui->tableWidget->setItem(r, c, new QTableWidgetItem(item));

        }
    }
}

preview::~preview()
{
    delete ui;
}
