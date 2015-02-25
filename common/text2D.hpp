#ifndef TEXT2D_HPP
#define TEXT2D_HPP

void initText2D(const char *texturePath, const char *char_font_texture_file_format);
void printText2D(const char *text, uint32_t x, uint32_t y, uint32_t size, const char *char_font_texture_file_format);
void cleanupText2D();

#endif
