#ifndef MY_LISTVIEW_CUSTOMIZATION_H
#define MY_LISTVIEW_CUSTOMIZATION_H


#include <QStyledItemDelegate>
#include <QAbstractListModel>
#include <QRunnable>
#include <QMutex>
#include <QSet>


class QListView;


class LoadPixmapTask : public QRunnable
{
public:
    LoadPixmapTask(const QString& fileName, QMutex& mutex, QSet<QString>& imagesInLoad);

private:
    void run() override;

private:
    QMutex& _mutex;
    QSet<QString>& _imagesInLoad;
    QString _fileName;
};


class MyListModel : public QAbstractListModel
 {
     Q_OBJECT

public:
    static const int MaxLoadPixmapTasks = 10;

public:
    MyListModel(QObject* parent = nullptr);

    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex& index, int role) const override;

public:
    void setFileNames(const QStringList& fileNames);

private:
    QStringList _fileNames;

    mutable QMutex _mutex;
    mutable QSet<QString> _imagesInLoad;
};


class MyListViewItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit MyListViewItemDelegate(QListView* parent);

    virtual void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;

private:
    QListView* _parentListView = nullptr;
};


#endif // MY_LISTVIEW_CUSTOMIZATION_H
