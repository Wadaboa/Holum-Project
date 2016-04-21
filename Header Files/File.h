//
//
//  Project : Holum
//  File Name : File.h
//  Date : 13/02/2016
//
//

#pragma once

/*!
 * \class File
 * \brief The File class describes resources relative to the Video and ThreeD sections.
 */
class File {
    private:
        /*! 
         * The thumbnail's rectangle width, measured in pixels.
         *
         * Default = 480px.
         */
        float rectWidth;
    
        /*! The thumbnail's rectangle height, measured in pixels.
         *
         * Default = 720px.
         */
        float rectHeight;
    
        /*! This path is relative to the file which is being processed, like an OBJ or an MP4. */
        string path;
    
        /*! The thumbnail's absolute path. */
        string thumbnailPath;
    
        /*! The name of the image file used to identify a particular resource. */
        string title;
    
        /*! The actual thumbnail's rectangle, whose perimeter is rectWidth * rectHeight, drawn using SFML functions. */
        RectangleShape thumbnail;
    
        /*! The actual thumbnail's texture, which contains the image specified in the title variable. */
        Texture thumbnailTexture;
    
        /*! Called by the constructor, it is used to load a specific thumbnail, using the constructor's parameters. */
        void init();
    
    public:
        /*! Constructs a File object, without setting any parameter. */
        File();
    
        /*! Constructs a File object, by setting the path and title variables to the given values. */
        File(string path, string title);
    
        /*! Sets the file path. */
        void setPath(string path);
    
        /*! Returns the file path. */
        string getPath();
    
        /*! Sets the thumbnail's path. */
        void setThumbnailPath(string thumbnailPath);
    
        /*! Returns the thumbnail's path. */
        string getThumbnailPath();
    
        /*! Sets the image's name. */
        void setTitle(string title);
    
        /*! Returns the image's name. */
        string getTitle();
    
        /*! Returns the thumbnail object. */
        RectangleShape* getThumbnail();
    
        /*! Returns the thumbnail's texture object. */
        Texture* getThumbnailTexture();
    
        /*! Sets the thumbnail's size. */
        void setThumbnailSize(float x, float y);
    
        /*! Sets the thumbnail's position. */
        void setThumbnailPosition(float x, float y);
    
        /*! Returns the thumbnail's current position. */
		Vector2f getThumbnailPosition();
    
        /*! Returns the thumbnail's size. */
        Vector2f getThumbnailSize();
    
        /*! Sets the thumbnail's scale factor. */
        void setThumbnailScale(float x, float y);
    
        /*! Sets the thumbnail's position, by adding the given offset to the current position. */
        void moveThumbnail(float x, float y);
};