#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "spleeterconfig.h"
#include "aboutwidget.h"

#include <QAction>
#include <QTextEdit>
#include <QDebug>
#include <QFileDialog>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAcceptDrops(true);
    InitConfig();
    InitView();
    InitSigSlot();
}

void MainWindow::InitConfig()
{
//    SpleeterConfig::Instance()->LoadConfig();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug() << "closeEvent";
}

void MainWindow::dragEnterEvent(QDragEnterEvent* event)
{
   if(!event->mimeData()->urls()[0].fileName().right(3).compare("aac")
           || !event->mimeData()->urls()[0].fileName().right(3).compare("mp3"))
       event->acceptProposedAction();
    else
       event->ignore();
}

void MainWindow::dropEvent(QDropEvent* event)
{
    const QMimeData*qm = event->mimeData();
    _items.append(qm->urls()[0].toLocalFile());
    for(auto item:_items){
        ui->textEdit_console->append(item);
    }
}

void MainWindow::InitView()
{
    this->setAcceptDrops(true);
    setWindowTitle(tr("MainWindow") + " " + SpleeterConfig::Instance()->_version);

    /// fixed size
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
    setFixedSize(this->width(), this->height());

    ui->lineEdit->setText(SpleeterConfig::Instance()->_outputPath);
    ui->textEdit_console->setAttribute(Qt::WA_InputMethodEnabled, false);
    ui->textEdit_console->setAcceptDrops(false);

    /// about
    QAction *aboutAction = new QAction();
    aboutAction->setText(tr("About"));
    ui->menuHelp->addAction(aboutAction);
    QObject::connect(aboutAction, &QAction::triggered, [=](){
        _aboutWidget->show();
    });

    /// lang chinese
    QAction *chnAction = new QAction();
    chnAction->setText(tr("LangChinese"));
    ui->menuLanguage->addAction(chnAction);
    QObject::connect(chnAction, &QAction::triggered, [=](){
        qDebug() << "is chinese";
        SpleeterConfig::Instance()->_i18n = 1;
        SpleeterConfig::Instance()->_selectLang = "zh_CN";
    });

    /// lang english
    QAction *engAction = new QAction();
    engAction->setText(tr("LangEnglish"));
    ui->menuLanguage->addAction(engAction);
    QObject::connect(engAction, &QAction::triggered, [=](){
        qDebug() << "is english";
        SpleeterConfig::Instance()->_i18n = 1;
        SpleeterConfig::Instance()->_selectLang = "en_US";
    });

    /// exit
    QAction *exitAction = new QAction();
    exitAction->setText(tr("Exit"));
    ui->menuFile->addAction(exitAction);
    QObject::connect(exitAction, &QAction::triggered, [=](){
        qApp->exit(0);
//        close();
    });

    ui->label_console->adjustSize();
    ui->label_parts_output->setFixedWidth(250);

    switch(SpleeterConfig::Instance()->_selectModel){
        case 2:
            ui->ckbox_2_parts->setChecked(true);
            ui->label_parts_output->setText(tr("TextLabel_2_parts"));
            break;
        case 4:
            ui->ckbox_4_parts->setChecked(true);
            ui->label_parts_output->setText(tr("TextLabel_4_parts"));
            break;
        case 5:
            ui->ckbox_5_parts->setChecked(true);
            ui->label_parts_output->setText(tr("TextLabel_5_parts"));
            break;
        default:
            ui->ckbox_2_parts->setChecked(true);
            ui->label_parts_output->setText(tr("TextLabel_2_parts"));
            break;
    }

    /// checkbox 2
    QObject::connect(ui->ckbox_2_parts, &QCheckBox::clicked, [=]{
        ui->ckbox_4_parts->setChecked(false);
        ui->ckbox_5_parts->setChecked(false);
        SpleeterConfig::Instance()->_selectModel = 2;
        ui->label_parts_output->setText(tr("TextLabel_2_parts"));
    });

    /// checkbox 4
    QObject::connect(ui->ckbox_4_parts, &QCheckBox::clicked, [=]{
        ui->ckbox_2_parts->setChecked(false);
        ui->ckbox_5_parts->setChecked(false);
        SpleeterConfig::Instance()->_selectModel = 4;
        ui->label_parts_output->setText(tr("TextLabel_4_parts"));
    });

    /// checkbox 5
    QObject::connect(ui->ckbox_5_parts, &QCheckBox::clicked, [=]{
        ui->ckbox_2_parts->setChecked(false);
        ui->ckbox_4_parts->setChecked(false);
        SpleeterConfig::Instance()->_selectModel = 5;
        ui->label_parts_output->setText(tr("TextLabel_5_parts"));
    });

    QObject::connect(ui->textEdit_console, &QTextEdit::textChanged, [=]{
//        qDebug() << "text:" << ui->textEdit_console->toPlainText();
    });


    QObject::connect(ui->btn_select, &QPushButton::clicked, [=]{
        QString fpath = QFileDialog::getOpenFileName(this, tr("Select File"),
                                                    SpleeterConfig::Instance()->_selectFilePath,
                                                    tr("Music Files (*.aac *.mp3)"));
        if(!fpath.isEmpty()){
            SpleeterConfig::Instance()->_selectFilePath = FileUtil::GetFilePath(fpath);
            qDebug() << fpath << " " << SpleeterConfig::Instance()->_selectFilePath;
            _items.append(fpath);
        }
    });

    QObject::connect(ui->btn_output, &QPushButton::clicked, [=]{
        QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                        SpleeterConfig::Instance()->_outputPath,
                                                        QFileDialog::ShowDirsOnly
                                                        | QFileDialog::DontResolveSymlinks);
        if(!dir.isEmpty()){
            qDebug() << dir;
            SpleeterConfig::Instance()->_outputPath = dir;
            ui->lineEdit->setText(SpleeterConfig::Instance()->_outputPath);
        }
    });

    _aboutWidget = new AboutWidget();
}

void MainWindow::InitSigSlot()
{

}

MainWindow::~MainWindow()
{
    qDebug() << "~MainWindow";
    SpleeterConfig::Instance()->SaveConfig();
    delete ui;
}

