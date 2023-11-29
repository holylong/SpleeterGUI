#ifndef FILEUTIL_H
#define FILEUTIL_H

#include <QObject>
#include <QFile>

class FileUtil : public QObject
{
    Q_OBJECT
public:
    explicit FileUtil(QObject *parent = nullptr);

    static bool Exists(const QString& path){
        QFile file(path);
        return file.exists();
    }

    static void OutputFile(const QString& path, const QByteArray& json){
        QFile file(path);
        if(file.open(QIODevice::WriteOnly) == true)
        {
            file.write(json);
        }
    }


    static QString GetFilePath(const QString& filePath){
        int temp = filePath.lastIndexOf("/");
        QString execName = filePath.right(filePath.length() - temp - 1);
        return filePath.left(temp + 1);
    }

    static QString GetName(const QString& filePath){
        int temp = filePath.lastIndexOf("/");
        return filePath.right(filePath.length() - temp - 1);
    }

signals:

};

#endif // FILEUTIL_H
