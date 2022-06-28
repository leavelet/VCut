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

class ffmpegWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ffmpegWidget(QWidget *parent = nullptr);
    QGridLayout *topLayout;
    QGridLayout *presetLayout, *filterLayout, *finalCommandLayout, *commandLayout;
    QHBoxLayout *outputLayout, *viedoLayout, *audioLayout, *miscLayout, *fileChooseLayout;
    vector<AbstructOption*> options;

    QPushButton *savePreset, *loadPreset, *generateFinalCommand;
    QComboBox *fileToChoose, *presetToChoose;
    FFOptionsCombo *outputFormat, *videoQuailty, *videoCodec, *frameRate, *videoBitRate,
        *audioQuality, *audioCodec, *videoRotation, *filter;
    FFOptionsCheck *remix, *hardwareAcceleration, *optimizedForWeb, *stero, *noVideo, *noAudio;
    QLabel *presetText, *finalCommandText, *fileComboText;
    QPlainTextEdit* finalCommand;
    QLineEdit* filterLine;

    QWidget* commandsWidget;

    void loadFromFile(QString Filename = "./defalut.json");
    void saveToFile(QString Filename = "./userSaved.json");
    void generate();

    int num;
    int currentnum;

public slots:
    void Load();
    void save();
};

#endif // FFMPEGWIDGET_H
