#ifndef FFMPEGWIDGET_H
#define FFMPEGWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QPlainTextEdit>
#include <QLineEdit>

#include "ffoptions.h"
#include "filelist.h"
#include "choosefile.h"

class ffmpegWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ffmpegWidget(ChooseFile* fileTab, QWidget *parent = nullptr);
    QGridLayout *topLayout;
    QGridLayout *presetLayout, *filterLayout, *finalCommandLayout, *commandLayout;
    QHBoxLayout *outputLayout, *viedoLayout, *audioLayout, *miscLayout, *fileChooseLayout;
    vector<AbstructOption*> options;

    QPushButton *savePreset, *loadPreset, *generateFinalCommand, *applyToChosen;
    QComboBox *fileToChoose, *presetToChoose;
    FFOptionsCombo *outputFormat, *videoQuailty, *videoCodec, *frameRate, *videoBitRate,
        *audioQuality, *audioCodec, *videoRotation, *filter;
    FFOptionsCheck *remix, *hardwareAcceleration, *optimizedForWeb, *stero, *noVideo, *noAudio;
    QLabel *presetText, *finalCommandText, *fileComboText, *fileNameLabel;
    QPlainTextEdit *finalCommand;
    QLineEdit *filterLine, *fileName;

    QWidget* commandsWidget;
    ChooseFile* fileTab;

    void loadFromFile(QString Filename = "./defalut.json");
    void saveToFile(QString Filename = "./userSaved.json");

    int num;
    int currentnum;

    ~ffmpegWidget();

public slots:
    void Load();
    void save();
    void generate();
    void apply();
};

#endif // FFMPEGWIDGET_H
