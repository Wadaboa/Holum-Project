//
//
//  Project : Holum
//  File Name : Game.h
//  Date : 17/12/2015
//
//

#pragma once

class File {
    private:
        float rectWidth;
        float rectHeight;
        string path;
        string thumbnailPath;
        string title;
        RectangleShape thumbnail;
        Texture thumbnailTexture;

        void init();
    public:
        File();
        File(string path, string title);
        void setPath(string path);
        string getPath();
        void setThumbnailPath(string thumbnailPath);
        string getThumbnailPath();
        void setTitle(string title);
        string getTitle();
        RectangleShape* getThumbnail();
        Texture* getThumbnailTexture();
        void setThumbnailSize(float x, float y);
        void setThumbnailPosition(float x, float y);
        Vector2f getThumbnailSize();
        void setThumbnailScale(float x, float y);
        void moveThumbnail(float x, float y);
};