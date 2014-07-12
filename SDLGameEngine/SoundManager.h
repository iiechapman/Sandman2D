//
//  SoundManager.h
//  LudumDare29
//
//  Created by Evan Chapman on 4/26/14.
//  Copyright (c) 2014 Evan Chapman. All rights reserved.
//

#include <iostream>
#include <string>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2_mixer/SDL_mixer.h>

using namespace std;

class SoundManager{
public:
    ~SoundManager();
    
    static SoundManager* Instance();
    
    bool loadSound(string fileName, string soundID);
    bool loadSong(string fileName, string soundID);
    
    void playSong(string ID);
    void playSound(string ID);
    
    void stopSong();
    void stopSound(int channel);
    
    void clearSoundMap();
    void clean();
    
    
private:
    SoundManager();
    static SoundManager* s_pInstance;
    
    map<string, Mix_Music*> m_songMap;
    map<string, Mix_Chunk*> m_soundMap;
    int m_totalChannels = 2;
    int m_currentChannel = 0;
};



