/********************************************************************************
** Form generated from reading UI file 'preview.ui'
**
** Created by: Qt User Interface Compiler version 5.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREVIEW_H
#define UI_PREVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_preview
{
public:
    QGridLayout *gridLayout;
    QTableWidget *tableWidget;

    void setupUi(QDialog *preview)
    {
        if (preview->objectName().isEmpty())
            preview->setObjectName(QStringLiteral("preview"));
        preview->resize(400, 300);
        gridLayout = new QGridLayout(preview);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tableWidget = new QTableWidget(preview);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        gridLayout->addWidget(tableWidget, 0, 0, 1, 1);


        retranslateUi(preview);

        QMetaObject::connectSlotsByName(preview);
    } // setupUi

    void retranslateUi(QDialog *preview)
    {
        preview->setWindowTitle(QApplication::translate("preview", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class preview: public Ui_preview {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREVIEW_H
