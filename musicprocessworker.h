#ifndef MUSICPROCESSWORKER_H
#define MUSICPROCESSWORKER_H

#include <QThread>
#include <QStringList>

class MusicProcessWorker : public QThread
{
    Q_OBJECT
public:
    explicit MusicProcessWorker(QObject *parent = nullptr);


protected:
    void run();


    int Append(const QString &item){
        _items.append(item);
        return _items.size();
    }

    void ForcedInterruption(){
        _bSuspend = true;
    }

private:
    QStringList  _items;
    bool         _bSuspend{false};

signals:
    void ProcessSignal(const QString& msg);
};

#endif // MUSICPROCESSWORKER_H
