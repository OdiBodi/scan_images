#include "main_window.h"
#include "ui_main_window.h"
#include "my_listview_customization.h"

#include <QDir>
#include <QDirIterator>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>


MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    _ui->pathEdit->setText(QDir::currentPath());

    _ui->imagesListView->setItemDelegate(new MyListViewItemDelegate(_ui->imagesListView));
    _ui->imagesListView->setBatchSize(10);
    _ui->imagesListView->setLayoutMode(QListView::Batched);
    _ui->imagesListView->setModel(new MyListModel());
}

MainWindow::~MainWindow()
{
    delete _ui;
}

void MainWindow::on_browseButton_clicked()
{
    auto path = _ui->pathEdit->text();
    if (path.isEmpty())
    {
        path = QDir::currentPath();
    }

    auto dir = QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this, tr("Select folder..."), path));
    if (!dir.isEmpty())
    {
        _ui->pathEdit->setText(dir);
    }
}

void MainWindow::on_scanButton_clicked()
{
    const auto path = QDir::cleanPath(_ui->pathEdit->text());
    const QStringList filter = { "*.bmp", "*.jpeg", "*.jpg", "*.png" };

    QDirIterator it(path, filter, (QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot), QDirIterator::Subdirectories);
    QStringList fileNames;

    while (it.hasNext())
    {
        auto fileName = it.next();
        fileNames << fileName;

        qDebug() << fileName;
    }

    if (fileNames.isEmpty())
    {
        QMessageBox::critical(this, "Error", "Files not found!");
    }
    else
    {
        dynamic_cast<MyListModel*>(_ui->imagesListView->model())->setFileNames(fileNames);
    }
}
