#include "my_listview_customization.h"

#include <QListView>
#include <QPainter>
#include <QDebug>
#include <QMutex>
#include <QPixmapCache>
#include <QThreadPool>


LoadPixmapTask::LoadPixmapTask(const QString& fileName, QMutex& mutex, QSet<QString>& imagesInLoad)
    : QRunnable()
    , _mutex(mutex)
    , _imagesInLoad(imagesInLoad)
    , _fileName(fileName)
{}

void LoadPixmapTask::run()
{
    QPixmap pixmap;
    if (pixmap.load(_fileName))
    {
        qDebug() << "create new pixmap \"" << _fileName << "\"";
    }
    else
    {
        qDebug() << "can't create new pixmap \"" << _fileName << "\"";
    }

    _mutex.lock();
    QPixmapCache::insert(_fileName, pixmap);
    _imagesInLoad.remove(_fileName);
    _mutex.unlock();
}


MyListModel::MyListModel(QObject* parent)
    : QAbstractListModel(parent)
{ }

int MyListModel::rowCount(const QModelIndex& parent) const
{
   (void) parent;
   return _fileNames.size();
}

QVariant MyListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || (index.row() >= _fileNames.size()))
    {
       return QVariant();
    }

    if (role == Qt::DecorationRole)
    {
        const auto idx = index.row();
        const auto fileName = _fileNames[idx];

        QPixmap pm;

        _mutex.lock();
        const auto isFound = QPixmapCache::find(fileName, &pm);
        _mutex.unlock();

        if (!isFound && !_imagesInLoad.contains(fileName) && _imagesInLoad.size() < MaxLoadPixmapTasks)
        {
            _mutex.lock();
            _imagesInLoad.insert(fileName);
            _mutex.unlock();

            QThreadPool::globalInstance()->start(new LoadPixmapTask(fileName, _mutex, _imagesInLoad));
        }

        return pm.isNull() ? QVariant() : pm;
    }
    else
    {
        return QVariant();
    }
}

void MyListModel::setFileNames(const QStringList& fileNames)
{
    beginResetModel();
    _fileNames = fileNames;
    endResetModel();
}


MyListViewItemDelegate::MyListViewItemDelegate(QListView* parent)
    : QStyledItemDelegate(parent)
{
    _parentListView = parent;
}

void MyListViewItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    if (!index.isValid())
    {
        return;
    }

    QPixmap pixmap = index.data(Qt::DecorationRole).value<QPixmap>();
    if (!pixmap.isNull())
    {
        const auto lvSize = _parentListView->size();

        pixmap = pixmap.scaled(lvSize.width(), option.rect.height(), Qt::KeepAspectRatio, Qt::FastTransformation);

        const auto pmWidth = pixmap.rect().width();
        const auto pmHeight = pixmap.rect().height();

        const int x = lvSize.width() / 2 - pmWidth / 2;
        const int y = option.rect.center().y() - pmHeight / 2;

        if (option.state & QStyle::State_Selected)
        {
            painter->fillRect(option.rect, option.palette.highlight());
        }

        painter->drawPixmap(QRect(x, y, pmWidth, pmHeight), pixmap);
    }
}
