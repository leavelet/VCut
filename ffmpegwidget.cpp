#include "ffmpegwidget.h"

ffmpegWidget::ffmpegWidget(QWidget *parent)
    : QWidget{parent}
{
    topLayout = new QGridLayout(this);
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

}

void ffmpegWidget::loadFromFile(QString Filename){

}
void ffmpegWidget::saveToFile(QString Filename){

}
void ffmpegWidget::generate(){

}

void ffmpegWidget::Load(){

}

void ffmpegWidget::save(){

}
