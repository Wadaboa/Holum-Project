//
//
//  Project : Holum
//  File Name : Game.h
//  Date : 17/12/2015
//
//

class FileVideo {
    private:
        string videoPath;
        string thumbnailPath;
        string videoTitle;
    
        void init();
    public:
        FileVideo(string videoPath, string videoTitle);
        string setVideoPath(string videoPath);
        void getVideoPath();
        string setThumbnailPath(string thumbnailPath);
        void getThumbnailPath();
        string setVideoTitle(string videoTitle);
        void getVideoTitle();
};
