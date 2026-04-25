#include "platform_movie_player.h"

const char* getMoviePath(MovieID id)
{
    switch (id)
    {
        case MOVIE_INTRO:
            return "intro.mp4";
        
        case MOVIE_BUMPER_1_2:
            return "bumper12.mp4";
        
        case MOVIE_BUMPER_2_3:
            return "bumper23.mp4";
        
        case MOVIE_BUMPER_3_4:
            return "bumper34.mp4";
        
        case MOVIE_EXTRO:
            return "extro.mp4";
        
        case MOVIE_GAME_OVER:
            return "gameover.mp4";
        
        default:
            return nullptr;
    }
}

MoviePlayer::MoviePlayer()
{
    playing = false;
    streamEnded = false;
    movieDurationSec = 0.0;
    movieStartTicksMs = 0;
    lastPresentedPtsSec = -1.0;
}

MoviePlayer::~MoviePlayer()
{
    clearState();
}

void MoviePlayer::clearState()
{
}

bool MoviePlayer::playFile(char *filePath, MovieDoneCallback callback, void *userData)
{
    return false;
}

void MoviePlayer::invokeDoneCallback(bool naturalEnd)
{
}

void MoviePlayer::stop(bool naturalEnd)
{
}

bool MoviePlayer::isPlaying()
{
    return false;
}

bool MoviePlayer::decodeNextFrame()
{
    return false;
}

void MoviePlayer::presentCurrentFrame(uint8_t *pixels, int width, int height, int pitch)
{
}

void MoviePlayer::update(uint8_t *pixels, int width, int height, int pitch)
{
}
