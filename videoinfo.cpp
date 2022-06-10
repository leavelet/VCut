#include "videoinfo.h"

videoInfo::videoInfo(VideoPlayer* vplayer, QWidget *parent)
    : QWidget{parent}
{
    player = vplayer;
    info = new QLabel(this);
}

void videoInfo::changeInfo(){

}
