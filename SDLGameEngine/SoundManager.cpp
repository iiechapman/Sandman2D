//
//  SoundManager.cpp
//  LudumDare29
//
//  Created by Evan Chapman on 4/27/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//


#include "SoundManager.h"
#include "Event.h"


SoundManager* SoundManager::s_pInstance = 0;

SoundManager* SoundManager::Instance(){
    if (!s_pInstance){
        s_pInstance = new SoundManager();
    }
    return s_pInstance;
    
}

SoundManager::SoundManager(){
    cout << "Initializing sound Manager\n";
    

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, (4096 / 2))==-1) {
        printf("Mix_OpenAudio: %s\n", Mix_GetError());
        exit(2);
    } else {
        cout << "opened audio" << endl;
    }
    
    
    int flags=MIX_INIT_OGG;
    int initted = Mix_Init(flags);
    if((initted & flags) != flags) {
        printf("Mix_Init: Failed to init required ogg and mod support!\n");
        printf("Mix_Init: %s\n", Mix_GetError());
        // handle error
    } else {
        cout << "mix init success\n";
    }
    
    //Mix_VolumeMusic(100);
    Mix_Volume(0, 50);
    Mix_Volume(1, 50);
    Mix_Volume(2, 50);
    
    m_eventHandler.registerHandler();
    m_eventHandler.registerEvent("play_sound");
    m_eventHandler.registerEvent("play_song");
    m_eventHandler.registerEvent("song_volume");
}

SoundManager::~SoundManager(){
    cout << "Deleting sound manager\n";
    m_eventHandler.deregisterHandler();
}


bool SoundManager::loadSong(string fileName, string soundID){
    cout << "Loading song\n";
    if (fileName != ""){
        Mix_Music* pTempSong = Mix_LoadMUS(fileName.c_str());
    
    if (pTempSong){
        m_songMap[soundID] = pTempSong;
        cout << "Loaded song succesfully\n";
        pTempSong = 0;
        return true;
    } else {
        cout << "failed to load song\n";
    }
    
    }
    return false;
}

bool SoundManager::loadSound(string fileName, string soundID){
    
    Mix_Chunk* pTempSound = Mix_LoadWAV(fileName.c_str());
    
    if (pTempSound){
        m_soundMap[soundID] = pTempSound;
        cout << "Loaded sound succesfully\n";
        return true;
    } else {
        cout << "failed to load sound\n";
    }
    
    return false;
}


void SoundManager::playSong(string ID){
    if (m_songMap[ID]){
        Mix_PlayMusic(m_songMap[ID], -1);
    }
}

void SoundManager::playSound(string ID){
    m_currentChannel++;
    if (m_currentChannel >= m_totalChannels){
        m_currentChannel = -1;
    }
    
    if (m_soundMap[ID]){
        Mix_PlayChannel(m_currentChannel, m_soundMap[ID], 0);
    } else {
        cout << "Sound does not exist!\n";
    }
}

void SoundManager::stopSong(){
    Mix_HaltMusic();
}

void SoundManager::stopSound(int channel){
    Mix_HaltChannel(channel);
}

void SoundManager::setSongVolume(int volume){
    Mix_VolumeMusic(volume);
}

void SoundManager::clearSoundMap(){
    m_soundMap.clear();
}

void SoundManager::clean(){
    cout << "Cleaning texture manager\n";
}

void SoundManager::update(){
    while (m_eventHandler.hasEvents()) {
        //cout << "Handling event from SM!\n";
        Event* currentEvent = m_eventHandler.getTopEvent();
        
        if (currentEvent->getEventName() == string("play_sound")){
            string argument = (*currentEvent->getArguments())[0];
            playSound(argument);
        }
        
        if (currentEvent->getEventName() == string("play_song")){
            string argument = (*currentEvent->getArguments())[0];
            playSong(argument);
        }
        
        if (currentEvent->getEventName() == string("song_volume")){
            string argument = (*currentEvent->getArguments())[0];
            setSongVolume(atoi(argument.c_str()));
        }
        
        
    }
}








