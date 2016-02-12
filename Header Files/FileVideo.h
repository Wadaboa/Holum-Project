//
//
//  Project : Holum
//  File Name : Game.h
//  Date : 17/12/2015
//
//

#pragma once

class FileVideo {
    private:
        float rectWidth;
        float rectHeight;
        string videoPath;
        string thumbnailPath;
        string videoTitle;
        RectangleShape thumbnail;
        Texture thumbnailTexture;

        void init();
    public:
        FileVideo();
        FileVideo(string videoPath, string videoTitle);
        void setVideoPath(string videoPath);
        string getVideoPath();
        void setThumbnailPath(string thumbnailPath);
        string getThumbnailPath();
        void setVideoTitle(string videoTitle);
        string getVideoTitle();
        RectangleShape* getThumbnail();
        Texture* getThumbnailTexture();
        void setThumbnailSize(float x, float y);
        void setThumbnailPosition(float x, float y);
        Vector2f getThumbnailSize();
        void setThumbnailScale(float x, float y);
        void moveThumbnail(float x, float y);
};