#include "ffmpegwidget.h"
#include "QFile"
#include "QJsonDocument"
#include "QJsonObject"
#include "QJsonArray"
#include "QJsonParseError"
#include "QMessageBox"
#include "QListWidget"

ffmpegWidget::ffmpegWidget(ChooseFile* _fileTab, QWidget *parent)
    : QWidget{parent}, fileTab(_fileTab)
{
    topLayout = new QGridLayout(this);

    savePreset = new QPushButton("保存预设", this);
    loadPreset = new QPushButton("读取预设",this);
    generateFinalCommand = new QPushButton("应用命令到选中文件",this);

    fileToChoose = new QComboBox(this);
    presetToChoose = new QComboBox(this);

    fileComboText = new QLabel("选择应用到的文件", this);
    presetText = new QLabel("预设", this);
    finalCommandText = new QLabel("最终命令", this);
    fileNameLabel = new QLabel("输出文件名", this);

    //TODO:不使用命令的方式 直接调用相关库执行
    finalCommand = new QPlainTextEdit("ffmpeg命令", this);

    filterLine = new QLineEdit(this);
    fileName = new QLineEdit(this);

    outputFormat = new FFOptionsCombo("输出格式", ".", "如:mp4", this); options.push_back(outputFormat);
    videoQuailty = new FFOptionsCombo("视频分辨率", "-vf scale=", "如1080:1920 其中之一可填-1以实现自动计算", this);options.push_back(videoQuailty);
    videoCodec = new FFOptionsCombo("编码器", "-c:v ", "如h264, 可以在这里查看:ffmpeg.org/ffmpeg-codecs.html", this);options.push_back(videoCodec);
    frameRate = new FFOptionsCombo("帧速率", "-r ", "格式为数字，如24，或者29.97", this);options.push_back(frameRate);
    videoBitRate = new FFOptionsCombo("码率", "-b:v ", "格式为数量+单位，如10M", this);options.push_back(videoBitRate);
    audioQuality = new FFOptionsCombo("音频采样率", "-ar ", "格式为数字，如44100", this);options.push_back(audioQuality);
    audioCodec = new FFOptionsCombo("音频编码器", "-c:a ", "如libfdk_aac， 可以在这里查看:www.ffmpeg.org/ffmpeg-codecs.html#Audio-Decoders" );options.push_back(audioCodec);
    videoRotation = new FFOptionsCombo("视频旋转", "-map_metadata 0 -metadata:s:v rotate=", "如\"90\"，不推荐自定义",this );options.push_back(videoRotation);
    filter = new FFOptionsCombo("滤镜", "-filter_complex ", "请查阅www.ffmpeg.org/ffmpeg-filters.html, 如有常用的，欢迎告知作者增加!");options.push_back(filter);
    remix =  new FFOptionsCheck("仅复制","-codec copy","", 0 ,this);options.push_back(remix);
    optimizedForWeb = new FFOptionsCheck("为流传输优化","-movflags +faststart","", 0,this);options.push_back(optimizedForWeb);
    stero = new FFOptionsCheck("立体声","-ac 2","-ac 1", 1, this);options.push_back(stero);
    noVideo = new FFOptionsCheck("无视频","-vn", "", 0,this);options.push_back(noVideo);
    noAudio = new FFOptionsCheck("无音频","-an","", 0, this);options.push_back(noAudio);

    topLayout->addWidget(presetText,0,0,1,2);
    topLayout->addWidget(presetToChoose, 0, 2, 1, 6);
    topLayout->addWidget(savePreset, 0, 8, 1, 1);
    topLayout->addWidget(loadPreset, 0, 9, 1, 1);
    topLayout->addWidget(fileComboText,1,0,1,2);
    topLayout->addWidget(fileToChoose,1,2,1,6);
    //topLayout->addWidget(commandsWidget, 2, 0, 5, 1);

    topLayout->addWidget(fileNameLabel, 2, 0, 1, 2);
    topLayout->addWidget(fileName, 2, 2, 1, 2);
    topLayout->addWidget(outputFormat,2, 4, 1, 2);
    topLayout->addWidget(remix,2, 6, 1, 1);
    topLayout->addWidget(optimizedForWeb,2, 7 ,1,1);

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
    topLayout->addWidget(finalCommand, 8, 0, 2, 10);
    topLayout->addWidget(generateFinalCommand, 10, 3, 1, 4);

    fileToChoose->addItem("所有文件");
    fileToChoose->addItem("当前文件");

    connect(noVideo->box,&QCheckBox::stateChanged,this,[this]()
    {
        if(noVideo->box->isChecked())
        {
            videoQuailty->setEnabled(false);
            videoCodec->setEnabled(false);
            frameRate->setEnabled(false);
            videoBitRate->setEnabled(false);
        }
        else
        {
            videoQuailty->setEnabled(true);
            videoCodec->setEnabled(true);
            frameRate->setEnabled(true);
            videoBitRate->setEnabled(true);
        }
        generate();
    });
    connect(noAudio->box,&QCheckBox::stateChanged,this,[this]()
    {
        if(noAudio->box->isChecked())
        {
            stero->setEnabled(false);
            audioQuality->setEnabled(false);
            audioCodec->setEnabled(false);
        }
        else
        {
            stero->setEnabled(true);
            audioQuality->setEnabled(true);
            audioCodec->setEnabled(true);
        }
        generate();
    });
    connect(savePreset,&QPushButton::clicked,this,&ffmpegWidget::save);
    num=1;
    currentnum=1;
    connect(loadPreset,&QPushButton::clicked,this,&ffmpegWidget::Load);

    QDir dir;
    if(!dir.exists("./preset"))
    {
        dir.mkdir("./preset");
    }
    dir.setPath("./preset");
    QString path=dir.path()+"/default.json";
    dir.cdUp();
    dir.cdUp();
    QFile file(dir.absolutePath()+"/VCut/default.json");
    file.copy(path);
    presetToChoose->addItem("default.json");
    loadFromFile("./preset/default.json");
    generate();

    connect(presetToChoose,&QComboBox::currentTextChanged,this,[this]()
    {
       loadFromFile("./preset/"+presetToChoose->currentText());
    });

    connect(fileTab->fileToChoose, &Filelist::contentChanged, this, [&](){
        //merge
        if(fileTab->fileToChoose->mergeOrSingle->isChecked()){
            return;
        }
        for(int i = 2; i < fileToChoose->count(); i++){
            fileToChoose->removeItem(i);
        }
        auto iter = fileTab->fileToChoose->filelist.begin();
        for(; iter != fileTab->fileToChoose->filelist.end(); iter++){
            fileToChoose->addItem(iter->filename);
        }
    });
    connect(fileTab->fileToChoose->Qlist, &QListWidget::currentRowChanged, this, [&](){
        //merge
        if(fileTab->fileToChoose->mergeOrSingle->isChecked()){
            return;
        }
        fileToChoose->removeItem(1);
        if(fileTab->fileToChoose->Qlist->currentRow()>=0)
        {
            fileToChoose->insertItem(1, "当前文件: "+ fileTab->fileToChoose->Qlist->currentItem()->text());
        }
        else
        {
            fileToChoose->insertItem(1, "当前文件");
        }

        fileToChoose->setCurrentIndex(1);
    });

    connect(fileTab->fileToChoose->mergeOrSingle, &QCheckBox::stateChanged, this, [&](){
        if(fileTab->fileToChoose->mergeOrSingle->isChecked()){
            fileToChoose->clear();
            fileToChoose->addItem("全部文件");
        }
        else{
            fileToChoose->addItem("当前文件：空");
            for(auto &x: fileTab->fileToChoose->filelist){
                fileToChoose->addItem(x.filename);
            }
        }
    });
    connect(generateFinalCommand, &QPushButton::clicked, this, &ffmpegWidget::apply);
     for(auto t: options){
         connect(t, &AbstructOption::stateChanged, this, &ffmpegWidget::generate);
     }
}

void ffmpegWidget::loadFromFile(QString Filename){
    const QString properties[]={"输出格式","视频分辨率","编码器","帧速率","码率","音频采样率",
                                  "音频编码器","视频旋转","滤镜","仅复制","为流传输优化","立体声",
                                  "无视频","无音频"};
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
            int opsize=options.size();
            for(int i=0;i<opsize;i++)
            {
                if(jsonObj.contains(properties[i]))
                {
                    options[i]->read(jsonObj.value(properties[i]).toObject());
                }
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
    QJsonObject jsonObj;
    int opsize=options.size();
    const QString properties[15]={"输出格式","视频分辨率","编码器","帧速率","码率","音频采样率",
                                  "音频编码器","视频旋转","滤镜","仅复制","为流传输优化","立体声",
                                  "无视频","无音频"};
    for(int i=0;i<opsize;i++)
    {
        options[i]->write(options[i]->obj);
        jsonObj[properties[i]]=options[i]->obj;
    }
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
    if(fileName->text().length() == 0 ){
        if(fileToChoose->currentIndex() == 0 && fileTab->fileToChoose->filelist.size() != 0){
            QString out_file = fileTab->fileToChoose->filelist.begin()->filename;
            int lst = out_file.lastIndexOf(".");
            out_file.erase(out_file.constBegin()+lst, out_file.constBegin()+out_file.length());
            srand(time(0));
            out_file += "_out";
            fileName->setText(out_file);
        }
    }
    QString command = "ffmpeg -hide_banner ";
    for(int i = 1; i < options.size(); i++){
        auto x = options[i];
        if(x->isEnabled() && x->getCommand() != ""){
            command = command + x->getCommand();
            command = command + QString(" ");
        }
    }
    finalCommand->clear();
    finalCommand->document()->setPlainText(command);
}

void ffmpegWidget::apply(){
    if(finalCommand->document()->toPlainText().contains("ffmpeg命令") )generate();
    int cnt = fileToChoose->currentIndex();
    if( cnt == 0 || (cnt == 1 && fileTab->fileToChoose->Qlist->currentRow() < 0)){
        for(auto iter = fileTab->fileToChoose->filelist.begin(); iter != fileTab->fileToChoose->filelist.end(); iter++){
            iter->command = finalCommand->document()->toPlainText() + " " + fileName->text() + outputFormat->getCommand();
        }
    }
    if(cnt == 1){
        //current dat have valid value
        int x = fileTab->fileToChoose->Qlist->currentRow();
        auto file = fileTab->fileToChoose->filelist.begin();
        for(int i = 1; i <= x; i++) file++;
        auto cmd = file->filename;
        cmd.erase(cmd.constBegin() + cmd.lastIndexOf("."), cmd.constEnd());
        cmd+="_out" + outputFormat->getCommand();
        file->command = finalCommand->document()->toPlainText() + " \"" + cmd + "\"";
    }
    else{
        //change cnt-2
        auto file = fileTab->fileToChoose->filelist.begin();
        for(int i = 1; i <= cnt-2; i++) file++;
        auto cmd = file->filename;
        cmd.erase(cmd.constBegin() + cmd.lastIndexOf("."), cmd.constEnd());
        cmd+="_out" + outputFormat->getCommand();
        file->command = finalCommand->document()->toPlainText() + " \"" + cmd + "\"";
    }
}

void ffmpegWidget::Load(){
    QString filename=QFileDialog::getOpenFileName(this,tr("打开json文件"),"");
    this->loadFromFile(filename);
}

void ffmpegWidget::save(){
    QString savename="./preset/mypreset";
    savename+=QString::number(num);
    savename+=".json";
    this->saveToFile(savename);
    QString filename="mypreset";
    filename+=QString::number(num);
    filename+=".json";
    presetToChoose->addItem(filename);
    presetToChoose->setCurrentIndex(num);
    num++;
}

ffmpegWidget::~ffmpegWidget()
{
    delete topLayout;
}
