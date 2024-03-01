
#ifndef FREETYPESTUFF_H
#define FREETYPESTUFF_H

#include <ft2build.h>
#include FT_FREETYPE_H

namespace rendering {

extern FT_Library freeTypeLib;
extern FT_Face fontFaceMain;
extern FT_Face fontFaceBackUp1;
extern FT_Face fontFaceBackUp2;

} // namespace rendering

#endif // FREETYPESTUFF_H
