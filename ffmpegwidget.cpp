#include "ffmpegwidget.h"
#include "QFile"
#include "QJsonDocument"
#include "QJsonObject"
#include "QJsonArray"
#include "QJsonParseError"
#include "QMessageBox"

ffmpegWidget::ffmpegWidget(QWidget *parent)
    : QWidget{parent}
{
    topLayout = new QGridLayout(this);
    /*
    presetLayout = new QGridLayout;
    filterLayout = new QGridLayout;
    finalCommandLayout = new QGridLayout;
    fileChooseLayout = new QHBoxLayout;
    outputLayout = new QHBoxLayout;
    viedoLayout = new QHBoxLayout;
    audioLayout = new QHBoxLayout;
    miscLayout = new QHBoxLayout;

    commandsWidget = new QWidget(this);
    commandLayout = new QGridLayout(commandsWidget);
    */

    savePreset = new QPushButton("保存预设", this);
    loadPreset = new QPushButton("读取预设",this);
    generateFinalCommand = new QPushButton("应用命令",this);

    fileToChoose = new QComboBox(this);
    presetToChoose = new QComboBox(this);

    fileComboText = new QLabel("选择应用到的文件", this);
    presetText = new QLabel("预设", this);
    finalCommandText = new QLabel("最终命令", this);
    //TODO:不使用命令的方式 直接调用相关库执行
    finalCommand = new QPlainTextEdit("ffmpeg命令", this);

    filterLine = new QLineEdit(this);

    outputFormat = new FFOptionsCombo("输出格式", ".", "如:mp4", this); options.push_back(outputFormat);
    videoQuailty = new FFOptionsCombo("视频分辨率", "-vf scale=", "如1080:1920 其中之一可填-1以实现自动计算", this);options.push_back(videoQuailty);
    videoCodec = new FFOptionsCombo("编码器", "-c:v ", "如h264, 可以在这里查看:ffmpeg.org/ffmpeg-codecs.html", this);options.push_back(videoCodec);
    frameRate = new FFOptionsCombo("帧速率", "-r ", "格式为数字，如24，或者29.97", this);options.push_back(frameRate);
    videoBitRate = new FFOptionsCombo("帧速率", "-b:v ", "格式为数量+单位，如10M", this);options.push_back(videoBitRate);
    audioQuality = new FFOptionsCombo("音频采样率", "-ar ", "格式为数字，如44100", this);options.push_back(audioQuality);
    audioCodec = new FFOptionsCombo("音频编码器", "-c:a ", "如libfdk_aac， 可以在这里查看:www.ffmpeg.org/ffmpeg-codecs.html#Audio-Decoders" );options.push_back(audioCodec);
    videoRotation = new FFOptionsCombo("视频旋转", "-map_metadata 0 -metadata:s:v rotate=", "如\"90\"，不推荐自定义",this );options.push_back(videoRotation);
    filter = new FFOptionsCombo("滤镜", "-filter_complex ", "请查阅www.ffmpeg.org/ffmpeg-filters.html, 如有常用的，欢迎告知作者增加!");options.push_back(filter);
    remix =  new FFOptionsCheck("仅复制","-codec copy","", 0 ,this);options.push_back(remix);
    optimizedForWeb = new FFOptionsCheck("为流传输优化","-movflags +faststart","", 0,this);options.push_back(optimizedForWeb);
    stero = new FFOptionsCheck("立体声","-ac 2","-ac 1", 1, this);options.push_back(stero);
    noVideo = new FFOptionsCheck("无视频","-vn", "", 0,this);options.push_back(noVideo);
    noAudio = new FFOptionsCheck("无音频","-an","", 0, this);options.push_back(noAudio);

    /*
    fileChooseLayout->addWidget(fileComboText);
    fileChooseLayout->addWidget(fileToChoose);

    presetLayout->addWidget(presetText, 0, 0, 1, 1);
    presetLayout->addWidget(presetToChoose, 0, 1, 1, 3);
    presetLayout->addWidget(savePreset, 0, 5, 1, 1);
    presetLayout->addWidget(loadPreset, 0, 6, 1, 1);

    outputLayout->addWidget(outputFormat);
    outputLayout->addWidget(remix);
    outputLayout->addWidget(optimizedForWeb);

    viedoLayout->addWidget(noVideo);
    viedoLayout->addWidget(videoQuailty);
    viedoLayout->addWidget(videoCodec);
    viedoLayout->addWidget(frameRate);
    viedoLayout->addWidget(videoBitRate);

    audioLayout->addWidget(noAudio);
    audioLayout->addWidget(stero);
    audioLayout->addWidget(audioQuality);
    audioLayout->addWidget(audioCodec);

    miscLayout->addWidget(videoRotation);

    filterLayout->addWidget(filter, 0, 0, 1, 1);
    filterLayout->addWidget(filterLine, 0, 1, 1, 3);
    finalCommandLayout->addWidget(finalCommandText, 0, 0, 1, 1);
    finalCommandLayout->addWidget(finalCommand, 1, 0, 3, 4);

    commandLayout->addLayout(outputLayout, 0, 0, 1, 1);
    commandLayout->addLayout(viedoLayout, 1, 0, 1, 1);
    commandLayout->addLayout(audioLayout, 2, 0, 1, 1);
    commandLayout->addLayout(miscLayout, 3, 0, 1, 1);
    commandLayout->addLayout(filterLayout, 4, 0, 1, 1);

//    commandsWidget->setStyleSheet("border: 1px solid red");

    topLayout->addLayout(presetLayout, 0, 0, 1, 1);
    topLayout->addLayout(fileChooseLayout, 1, 0, 1, 1);
    topLayout->addWidget(commandsWidget, 2, 0, 5, 1);
    topLayout->addLayout(finalCommandLayout, 7, 0, 2, 1);
    topLayout->addWidget(generateFinalCommand, 9, 0, 1, 1);
    */

    topLayout->addWidget(presetText,0,0,1,2);
    topLayout->addWidget(presetToChoose, 0, 2, 1, 6);
    topLayout->addWidget(savePreset, 0, 8, 1, 1);
    topLayout->addWidget(loadPreset, 0, 9, 1, 1);
    topLayout->addWidget(fileComboText,1,0,1,2);
    topLayout->addWidget(fileToChoose,1,2,1,6);
    //topLayout->addWidget(commandsWidget, 2, 0, 5, 1);

    topLayout->addWidget(outputFormat,2,0,1,2);
    topLayout->addWidget(remix,2,2,1,2);
    topLayout->addWidget(optimizedForWeb,2,4,1,2);

    topLayout->addWidget(noVideo,3,0,1,2);
    topLayout->addWidget(videoQuailty,3,2,1,2);
    topLayout->addWidget(videoCodec,3,4,1,2);
    topLayout->addWidget(frameRate,3,6,1,2);
    topLayout->addWidget(videoBitRate,3,8,1,2);

    topLayout->addWidget(noAudio,4,0,1,2);
    topLayout->addWidget(stero,4,2,1,2);
    topLayout->addWidget(audioQuality,4,4,1,2);
    topLayout->addWidget(audioCodec,4,6,1,2);

    topLayout->addWidget(videoRotation,5,0,1,2);

    topLayout->addWidget(filter, 6, 0, 1, 6);
    topLayout->addWidget(filterLine, 6, 6, 1, 4);

    topLayout->addWidget(finalCommandText, 7, 0, 1, 2);
    topLayout->addWidget(finalCommand, 8, 0, 3, 10);
    topLayout->addWidget(generateFinalCommand, 9, 0, 1, 1);

    connect(noVideo->box,&QCheckBox::stateChanged,this,[this]()
    {
        if(noVideo->box->isChecked())
        {
            videoQuailty->setEnabled(false);
            videoCodec->setEnabled(false);
            frameRate->setEnabled(false);
            videoBitRate->setEnabled(false);
            videoQuailty->setVisible(false);
            videoCodec->setVisible(false);
            frameRate->setVisible(false);
            videoBitRate->setVisible(false);
        }
        else
        {
            videoQuailty->setEnabled(true);
            videoCodec->setEnabled(true);
            frameRate->setEnabled(true);
            videoBitRate->setEnabled(true);
            videoQuailty->setVisible(true);
            videoCodec->setVisible(true);
            frameRate->setVisible(true);
            videoBitRate->setVisible(true);
        }
    });
    connect(noAudio->box,&QCheckBox::stateChanged,this,[this]()
    {
        if(noAudio->box->isChecked())
        {
            stero->setEnabled(false);
            audioQuality->setEnabled(false);
            audioCodec->setEnabled(false);
            stero->setVisible(false);
            audioQuality->setVisible(false);
            audioCodec->setVisible(false);
        }
        else
        {
            stero->setEnabled(true);
            audioQuality->setEnabled(true);
            audioCodec->setEnabled(true);
            stero->setVisible(true);
            audioQuality->setVisible(true);
            audioCodec->setVisible(true);
        }
    });
    connect(savePreset,&QPushButton::clicked,this,&ffmpegWidget::save);
    num=1;
    currentnum=1;
    connect(loadPreset,&QPushButton::clicked,this,&ffmpegWidget::Load);
}

void ffmpegWidget::loadFromFile(QString Filename){
    QFile file(Filename);
    bool flag=file.open(QIODevice::ReadOnly);
    if(flag)
    {
        QByteArray data=file.readAll();
        file.close();
        QJsonParseError parseError;
        QJsonDocument doc=QJsonDocument::fromJson(data,&parseError);
        if(parseError.error==QJsonParseError::NoError)
        {
            QJsonObject jsonObj=doc.object();
            if(jsonObj.contains("输出格式"))
            {
                outputFormat->read(jsonObj.value("输出格式").toObject());
            }
            if(jsonObj.contains("视频分辨率"))
            {
                videoQuailty->read(jsonObj.value("视频分辨率").toObject());
            }
            if(jsonObj.contains("编码器"))
            {
                videoCodec->read(jsonObj.value("编码器").toObject());
            }
            if(jsonObj.contains("帧速率(格式为数字)"))
            {
                frameRate->read(jsonObj.value("帧速率(格式为数字)").toObject());
            }
            if(jsonObj.contains("帧速率(格式为数量+单位)"))
            {
                videoBitRate->read(jsonObj.value("帧速率(格式为数量+单位)").toObject());
            }
            if(jsonObj.contains("音频采样率"))
            {
                audioQuality->read(jsonObj.value("音频采样率").toObject());
            }
            if(jsonObj.contains("音频编码器"))
            {
                audioCodec->read(jsonObj.value("音频编码器").toObject());
            }
            if(jsonObj.contains("视频旋转"))
            {
                videoRotation->read(jsonObj.value("视频旋转").toObject());
            }
            if(jsonObj.contains("滤镜"))
            {
                filter->read(jsonObj.value("滤镜").toObject());
            }
            if(jsonObj.contains("仅复制"))
            {
                remix->read(jsonObj.value("仅复制").toObject());
            }
            if(jsonObj.contains("为流传输优化"))
            {
                optimizedForWeb->read(jsonObj.value("为流传输优化").toObject());
            }
            if(jsonObj.contains("立体声"))
            {
                stero->read(jsonObj.value("立体声").toObject());
            }
            if(jsonObj.contains("无视频"))
            {
                noVideo->read(jsonObj.value("无视频").toObject());
            }
            if(jsonObj.contains("无音频"))
            {
                noAudio->read(jsonObj.value("无音频").toObject());
            }
        }
        else
        {
            QMessageBox::warning(this,"Error","Json Error");
        }
    }
    else
    {
        QMessageBox::warning(this,"Error","Counld not open the file");
    }
}
void ffmpegWidget::saveToFile(QString Filename){
    outputFormat->write(outputFormat->obj);
    videoQuailty->write(videoQuailty->obj);
    videoCodec->write(videoCodec->obj);
    frameRate->write(frameRate->obj);
    videoBitRate->write(videoBitRate->obj);
    audioQuality->write(audioQuality->obj);
    audioCodec->write(audioCodec->obj);
    videoRotation->write(videoRotation->obj);
    filter->write(filter->obj);
    remix->write(remix->obj);
    optimizedForWeb->write(optimizedForWeb->obj);
    stero->write(stero->obj);
    noVideo->write(noVideo->obj);
    noAudio->write(noAudio->obj);
    QJsonObject jsonObj;
    jsonObj["输出格式"]=outputFormat->obj;
    jsonObj["视频分辨率"]=videoQuailty->obj;
    jsonObj["编码器"]=videoCodec->obj;
    jsonObj["帧速率(格式为数字)"]=frameRate->obj;
    jsonObj["帧速率(格式为数量+单位)"]=videoBitRate->obj;
    jsonObj["音频采样率"]=audioQuality->obj;
    jsonObj["音频编码器"]=audioCodec->obj;
    jsonObj["视频旋转"]=videoRotation->obj;
    jsonObj["滤镜"]=filter->obj;
    jsonObj["仅复制"]=remix->obj;
    jsonObj["为流传输优化"]=optimizedForWeb->obj;
    jsonObj["立体声"]=stero->obj;
    jsonObj["无视频"]=noVideo->obj;
    jsonObj["无音频"]=noAudio->obj;
    QJsonDocument doc(jsonObj);
    QByteArray data=doc.toJson();
    QFile file(Filename);
    bool flag=file.open(QIODevice::WriteOnly);
    if(flag)
    {
        file.write(data);
        file.close();
    }
    else
    {
        QMessageBox::warning(this,"Error","Could not open the file");
    }
}
void ffmpegWidget::generate(){

}

void ffmpegWidget::Load(){
    QString filename=presetToChoose->currentText();
    this->loadFromFile(filename);
}

void ffmpegWidget::save(){
    QString savename="./preset";
    savename+=QString::number(num);
    savename+=".json";
    this->saveToFile(savename);
    presetToChoose->addItem(savename);
    presetToChoose->setCurrentIndex(num-1);
    num++;
}
