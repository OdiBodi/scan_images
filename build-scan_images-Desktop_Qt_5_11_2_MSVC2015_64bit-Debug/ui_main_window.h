/********************************************************************************
** Form generated from reading UI file 'main_window.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_WINDOW_H
#define UI_MAIN_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QPushButton *scanButton;
    QLineEdit *pathEdit;
    QPushButton *browseButton;
    QListView *imagesListView;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(693, 524);
        MainWindow->setMinimumSize(QSize(600, 500));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        scanButton = new QPushButton(centralWidget);
        scanButton->setObjectName(QStringLiteral("scanButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(scanButton->sizePolicy().hasHeightForWidth());
        scanButton->setSizePolicy(sizePolicy);
        scanButton->setMinimumSize(QSize(100, 30));
        QFont font;
        font.setPointSize(8);
        scanButton->setFont(font);

        gridLayout->addWidget(scanButton, 4, 1, 1, 1);

        pathEdit = new QLineEdit(centralWidget);
        pathEdit->setObjectName(QStringLiteral("pathEdit"));
        pathEdit->setMinimumSize(QSize(0, 26));
        pathEdit->setFont(font);
        pathEdit->setReadOnly(false);

        gridLayout->addWidget(pathEdit, 0, 0, 1, 1);

        browseButton = new QPushButton(centralWidget);
        browseButton->setObjectName(QStringLiteral("browseButton"));
        browseButton->setMinimumSize(QSize(50, 30));

        gridLayout->addWidget(browseButton, 0, 1, 1, 1);

        imagesListView = new QListView(centralWidget);
        imagesListView->setObjectName(QStringLiteral("imagesListView"));
        imagesListView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        imagesListView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        imagesListView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

        gridLayout->addWidget(imagesListView, 1, 0, 1, 2);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Scan images", nullptr));
        scanButton->setText(QApplication::translate("MainWindow", "Scan", nullptr));
        browseButton->setText(QApplication::translate("MainWindow", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_WINDOW_H
