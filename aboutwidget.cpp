#include "aboutwidget.h"
#include "spleeterconfig.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>

AboutWidget::AboutWidget(QWidget *parent) : QWidget(parent)
{
    setFixedSize(538, 272);
    QHBoxLayout *layout = new QHBoxLayout();

    QLabel *icon = new QLabel();
    icon->setPixmap(QPixmap(":/res/icon.svg"));

    QVBoxLayout *vlayout = new QVBoxLayout();
    vlayout->setSpacing(2);
    QLabel *title = new QLabel();
    title->setText(tr("MainWindow"));
    vlayout->addWidget(title, 0, Qt::AlignTop);
    vlayout->addStretch(5);

    QLabel *version = new QLabel();
    version->setText(tr("Version") + ": " + SpleeterConfig::Instance()->_version);
    vlayout->addWidget(version, 0, Qt::AlignVCenter);

//    QLabel *cppVersion = new QLabel();
//    cppVersion->setText(tr("CppVersion") + ": " + SpleeterConfig::Instance()->_version);
//    vlayout->addWidget(cppVersion, 0, Qt::AlignVCenter);

    QLabel *qtVersion = new QLabel();
    qtVersion->setText(tr("QtVersion") + ": " + SpleeterConfig::Instance()->_qtVersion);
    vlayout->addWidget(qtVersion, 0, Qt::AlignVCenter);

    QLabel *osVersion = new QLabel();
    osVersion->setText(tr("OsVersion") + ": " + SpleeterConfig::Instance()->_osVersion);
    vlayout->addWidget(osVersion, 0, Qt::AlignVCenter);
    vlayout->addStretch(25);

    layout->addWidget(icon, 0, Qt::AlignLeft);
    layout->addLayout(vlayout);
    setLayout(layout);
}
