// Include standard headers
#include <cstdio>   // std::FILE, std::fclose, std::fopen, std::fread, std::getchar, std::printf etc.
#include <stdint.h> // uint32_t etc.

struct read_BMP_into_world_data(const char* imagepath)
{
    std::printf("Reading image %s\n", imagepath);

    // Data read from the header of the BMP file
    unsigned char header[54];
    unsigned int dataPos;
    unsigned int imageSize;
    unsigned int width, height;
    // Actual RGB image data.
    unsigned char* image_data;

    // Open the file
    std::FILE* file = std::fopen(imagepath,"rb");
    if (!file)
    {
        std::printf("%s could not be opened.\n", imagepath);
        std::getchar();
        return 0;
    }

    // Read the header, i.e. the 54 first bytes

    // If less than 54 bytes are read, it's a problem.
    if (std::fread(header, 1, 54, file) != 54)
    {
        std::printf("Not a correct BMP file\n");
        return 0;
    }

    // A BMP files always begins with "BM"
    if ((header[0] != 'B') || (header[1] != 'M'))
    {
        std::printf("Not a correct BMP file\n");
        return 0;
    }

    // Make sure this is a 24bpp file
    if (*(int*) & (header[0x1e]) != 0)
    {
        std::printf("Not a correct BMP file\n");
        return 0;
    }

    if (*(int*) & (header[0x1c]) != 24)
    {
        std::printf("Not a correct BMP file\n");
        return 0;
    }

    // Read the information about the image
    dataPos    = *(int*) & (header[0x0a]);
    imageSize  = *(int*) & (header[0x22]);
    width      = *(int*) & (header[0x12]);
    height     = *(int*) & (header[0x16]);

    // Some BMP files are misformatted, guess missing information
    if (imageSize == 0)
    {
        imageSize = width * height * 3; // 3 : one byte for each Red, Green and Blue component
    }

    if (dataPos == 0)
    {
        dataPos = 54; // The BMP header is done that way
    }

    // Create a buffer.
    image_data = new unsigned char [imageSize];

    // Read the actual image data from the file into the buffer.
    std::fread(image_data, 1, imageSize, file);

    // Everything is in memory now, the file can be closed
    std::fclose(file);

#define COLOR_CHANNEL_RED
#define COLOR_CHANNEL_GREEN
#define COLOR_CHANNEL_BLUE
#define COLOR_CHANNEL_MEAN

    vertex_data = new int32 [4 * imageSize];

    uint8 *image_pointer = &image_data;
    int32 *vertex_pointer = &vertex_data;

    // start processing image_data.
    for (int32 x = 0; x < width; x++)
    {
        for (int32 z = height; z >= 0; z--)
        {
            pixel_data = vertex_pointer & 0xffffff; // assumes little-endian architecture.
            vertex_pointer++ = x; // x.
#elif COLOR_CHANNEL_RED
            vertex_pointer++ = (int32) *image_pointer;       // y-coordinate is the red (R) value.
#elif COLOR_CHANNEL_GREEN
            vertex_pointer++ = (int32) *(image_pointer + 1); // y-coordinate is the green (G) value.
#elif COLOR_CHANNEL_BLUE
            vertex_pointer++ = (int32) *(image_pointer + 2); // y-coordinate is the blue (B) value.
#elif COLOR_CHANNEL_MEAN
            // y-coordinate is the mean of R, G, & B.
            vertex_pointer++ = (((int32) *imgepointer) + ((int32) *(image_pointer + 1)) + ((int32) *(image_pointer + 2))) / 3;
#endif
            image_pointer += 3 * sizeof (image_data);
            vertex_pointer++ = z; // z.
            vertex_pointer++ = 0; // not in use (for alignment only).
        }
    }
