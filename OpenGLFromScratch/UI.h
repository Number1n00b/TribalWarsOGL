#pragma once

#include <iostream>
#include <ft2build.h>
#include <freetype/freetype.h>
#include <GL/glew.h>

class UI
{
    public:
        UI() {
            //Initialise FreeType
            if (FT_Init_FreeType(&m_ftLib)) {
                std::cout << "Constructing UI..." << std::endl;
                std::cout << "Could not init freetype library!" << std::endl;
            }

            if (FT_New_Face(m_ftLib, "FreeSans.ttf", 0, &m_fontFaces[FREESANS])) {
                std::cout << "Could not open font: " << "FreeSans.ttf" << std::endl;
            }

            //Create the texture. @Refactor: Use my texture class instead;
            glActiveTexture(GL_TEXTURE0);
            glGenTextures(1, &m_texture);
            glBindTexture(GL_TEXTURE_2D, m_texture);

            //Enable blending for text drawing.
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            //Not sure what this does, and doesnt work. @Cleanup
            //glUniform1i(uniform_tex, 0);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

            GLuint vbo;
            glGenBuffers(1, &vbo);
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);


            glDisable(GL_BLEND);
            glPixelStorei(GL_UNPACK_ALIGNMENT, 0);
        }

        void render_text(const char *text, float x, float y, float sx, float sy) {
            const char *p;

            FT_GlyphSlot g = m_fontFaces[FREESANS]->glyph;

            for (p = text; *p; p++) {
                if (FT_Load_Char(m_fontFaces[FREESANS], *p, FT_LOAD_RENDER))
                    continue;

                glTexImage2D(
                    GL_TEXTURE_2D,
                    0,
                    GL_RED,
                    g->bitmap.width,
                    g->bitmap.rows,
                    0,
                    GL_RED,
                    GL_UNSIGNED_BYTE,
                    g->bitmap.buffer
                );

                float x2 = x + g->bitmap_left * sx;
                float y2 = -y - g->bitmap_top * sy;
                float w = g->bitmap.width * sx;
                float h = g->bitmap.rows * sy;

                GLfloat box[4][4] = {
                    { x2,     -y2    , 0, 0 },
                    { x2 + w, -y2    , 1, 0 },
                    { x2,     -y2 - h, 0, 1 },
                    { x2 + w, -y2 - h, 1, 1 },
                };

                glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
                glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

                x += (g->advance.x / 64) * sx;
                y += (g->advance.y / 64) * sy;
            }
        }

    private:
        enum m_fontFaceNames {
            FREESANS,

            NUMBER_FONTS
        };

        GLuint m_texture;

        FT_Library m_ftLib;
        FT_Face m_fontFaces[NUMBER_FONTS];
};

