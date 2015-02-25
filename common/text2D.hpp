#ifndef TEXT2D_HPP
#define TEXT2D_HPP

void initText2D(GLuint screen_width, GLuint screen_height, const char *texturePath, const char *char_font_texture_file_format);
void printText2D(GLuint screen_width, GLuint screen_height, GLuint x, GLuint y, GLuint size, const char *text, const char *char_font_texture_file_format);
void cleanupText2D();

#endif
