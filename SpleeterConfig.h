#ifndef SPLEETERCONFIG_H
#define SPLEETERCONFIG_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDir>
#include <QDebug>
#include <QSysInfo>

#include "fileutil.h"

class SpleeterConfig : public QObject{
public:
    static SpleeterConfig* Instance(){
        static SpleeterConfig config;
        return &config;
    }

    SpleeterConfig(QObject *parent = nullptr){
        LoadConfig();
    }

    void LoadConfig(){
        _path = QDir::currentPath();
        _path += "/spleeter.json";

        _qtVersion = qVersion();
        _osVersion = QSysInfo::productType();
        _osVersion += " ";
        _osVersion += QSysInfo::productVersion();

        if(FileUtil::Exists(_path)){
            qDebug() << "file :" << _path << " exist";
            QFile file(_path);
            if(file.open(QIODevice::ReadOnly)){
                QByteArray bytes = file.readAll();
                QJsonDocument doc = QJsonDocument::fromJson(bytes);
                QJsonObject jobj = doc.object();

                if(jobj.contains("output"))_outputPath = jobj.value("output").toString();
                if(jobj.contains("lan"))_selectLang = jobj.value("lan").toString();
                if(jobj.contains("model"))_selectModel = jobj.value("model").toInt();
                if(jobj.contains("modelPath"))_modelPath = jobj.value("modelPath").toString();
                if(jobj.contains("selectFilePath"))_selectFilePath = jobj.value("selectFilePath").toString();
                if(jobj.contains("i18n"))_i18n = jobj.value("i18n").toInt();
            }
        }else{
            qDebug() << "file :" << _path << " not exist";
            _outputPath = QDir::currentPath();
            _selectFilePath = QDir::homePath();
            _modelPath = QDir::currentPath();
            _modelPath += "/models";
        }
    }

    void SaveConfig(){
        QJsonObject jobj;
        jobj["output"] = _outputPath;
        jobj["lan"] = _selectLang;
        jobj["selectFilePath"] = _selectFilePath;
        jobj["model"] = _selectModel;
        jobj["modelPath"] = _modelPath;
        jobj["i18n"] = _i18n;

        QJsonDocument doc(jobj);
        QByteArray bytes = doc.toJson();
        FileUtil::OutputFile(_path, bytes);
    }

public:
    QString  _outputPath{""};
    QString  _selectFilePath{""};
    QString  _selectLang{"en_US"};
    int      _selectModel{2};
    QString  _modelPath{""};
    int      _i18n{0};

    QString  _aboutTile{""};
    QString  _projectUri{"https://github.com/holylong/SpleeterGUI"};
    QString  _version{"v0.1.0"};

    /// qt
    QString  _qtVersion{""};
    QString  _osVersion{""};
//    QString  _compilerVersion{""};

    QString  _path{""};
};

#endif // SPLEETERCONFIG_H
