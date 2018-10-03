#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QStandardItemModel>
#include <QDebug>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QPixmapCache>
#include <QListView>
#include <QThreadPool>
#include <QMutex>


namespace Ui
{
    class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void on_browseButton_clicked();
    void on_scanButton_clicked();

private:
    Ui::MainWindow* _ui;
};


#endif // MAIN_WINDOW_H
