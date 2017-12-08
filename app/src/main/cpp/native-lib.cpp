#include <jni.h>
#include "inc/fmod.hpp"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "inc/fmod_dsp_effects.h"

#include <android/log.h>

#define LOGI(FORMAT, ...) __android_log_print(ANDROID_LOG_INFO,"AAA",FORMAT,__VA_ARGS__);

#define NORMAL 0
#define DASHU 1
#define LUOLI 2
#define GAOGUAI 3
#define KONGLING 4
#define JINGSONG 5
#define MORE_DASHU 6
#define MORE_LUOLI 7
#define MORE_GAOGUAI 8
#define MORE_KONGLING 9
#define RESET 10

static float s_dashu = 1;
static float s_luoli = 1;
static float s_kuaidian = 1.0;
static float s_huisheng = 5;

void reSet();

extern "C"
JNIEXPORT void JNICALL
Java_cn_migu_hasika_fmodechange_FmodChange_playNormal(
        JNIEnv* env,
        jclass jo, jint type, jstring jstr_path) {

    const char * path = env->GetStringUTFChars(jstr_path,NULL);
    LOGI("%s", path);



    FMOD::System     *system;
    FMOD::Sound      *sound1, *sound2, *sound3;
    FMOD::Channel    *channel = 0;
    FMOD_RESULT       result;
    FMOD::DSP *dsp;
    unsigned int      version;
    void             *extradriverdata = 0;
    float frequency = 0;

    result = FMOD::System_Create(&system);
    result = system->getVersion(&version);

    result = system->init(32, FMOD_INIT_NORMAL, NULL);
    result = system->createSound(path, FMOD_DEFAULT, 0, &sound1);
    result = sound1->setMode(FMOD_LOOP_OFF);

    result = system->playSound(sound1, 0, false, &channel);

    result = system->update();

    switch (type) {
        case NORMAL:

            break;
        case DASHU:
            system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
            dsp->setParameterFloat(0, 0.5);
            channel->addDSP(0,dsp);
            break;
        case LUOLI:
            system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
            dsp->setParameterFloat(0, 3.5);
            channel->addDSP(0,dsp);
            break;

        case GAOGUAI:
            channel->getFrequency(&frequency);
            frequency = frequency*3.0;
            channel->setFrequency(frequency);
            break;

        case KONGLING:
            system->createDSPByType(FMOD_DSP_TYPE_ECHO, &dsp);
            dsp->setParameterFloat(FMOD_DSP_ECHO_DELAY, 300);
            dsp->setParameterFloat(FMOD_DSP_ECHO_FEEDBACK, 20);
            channel->addDSP(0,dsp);
            break;

        case MORE_DASHU:
            system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
            s_dashu = s_dashu - 0.2;
            dsp->setParameterFloat(0, s_dashu);
            channel->addDSP(0,dsp);
            break;

        case MORE_LUOLI:
            system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
            s_luoli += 1;
            dsp->setParameterFloat(0, s_luoli);
            channel->addDSP(0,dsp);
            break;

        case MORE_GAOGUAI:
            channel->getFrequency(&frequency);
            s_kuaidian +=1;
            frequency = frequency*s_kuaidian;
            channel->setFrequency(frequency);
            break;

        case MORE_KONGLING:
            system->createDSPByType(FMOD_DSP_TYPE_ECHO, &dsp);
            dsp->setParameterFloat(FMOD_DSP_ECHO_DELAY, 300);
            s_huisheng +=10;
            dsp->setParameterFloat(FMOD_DSP_ECHO_FEEDBACK, s_huisheng);
            channel->addDSP(0,dsp);
            break;
        case RESET:
                reSet();
            break;

        default:
            break;
    }

    result = system->update();

    bool playing = 1;

    while (playing) {
        channel->isPlaying(&playing);
        usleep(50*1000);
    }

    usleep(2*1000*1000);

    result = sound1->release();

    system->close();
    system->release();

}

void reSet(){
    s_dashu = 1;
    s_luoli = 1;
    s_kuaidian = 1.0;
    s_huisheng = 5;
}



