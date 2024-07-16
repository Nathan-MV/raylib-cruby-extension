// Text drawing functions
// RLAPI void DrawFPS(int posX, int posY);                                                     // Draw current FPS
// RLAPI void DrawText(const char *text, int posX, int posY, int fontSize, Color color);       // Draw text (using default font)
// RLAPI void DrawTextEx(Font font, const char *text, Vector2 position, float fontSize, float spacing, Color tint); // Draw text using font and additional parameters
// RLAPI void DrawTextPro(Font font, const char *text, Vector2 position, Vector2 origin, float rotation, float fontSize, float spacing, Color tint); // Draw text using Font and pro parameters (rotation)
// RLAPI void DrawTextCodepoint(Font font, int codepoint, Vector2 position, float fontSize, Color tint); // Draw one character (codepoint)
// RLAPI void DrawTextCodepoints(Font font, const int *codepoints, int codepointCount, Vector2 position, float fontSize, float spacing, Color tint); // Draw multiple character (codepoint)

// Text font info functions
// RLAPI void SetTextLineSpacing(int spacing);                                                 // Set vertical line spacing when drawing with line-breaks
// RLAPI int MeasureText(const char *text, int fontSize);                                      // Measure string width for default font
// RLAPI Vector2 MeasureTextEx(Font font, const char *text, float fontSize, float spacing);    // Measure string size for Font
// RLAPI int GetGlyphIndex(Font font, int codepoint);                                          // Get glyph index position in font for a codepoint (unicode character), fallback to '?' if not found
// RLAPI GlyphInfo GetGlyphInfo(Font font, int codepoint);                                     // Get glyph font info data for a codepoint (unicode character), fallback to '?' if not found
// RLAPI Rectangle GetGlyphAtlasRec(Font font, int codepoint);                                 // Get glyph rectangle in font atlas for a codepoint (unicode character), fallback to '?' if not found

// Text codepoints management functions (unicode characters)
// RLAPI char *LoadUTF8(const int *codepoints, int length);                // Load UTF-8 text encoded from codepoints array
// RLAPI void UnloadUTF8(char *text);                                      // Unload UTF-8 text encoded from codepoints array
// RLAPI int *LoadCodepoints(const char *text, int *count);                // Load all codepoints from a UTF-8 text string, codepoints count returned by parameter
// RLAPI void UnloadCodepoints(int *codepoints);                           // Unload codepoints data from memory
// RLAPI int GetCodepointCount(const char *text);                          // Get total number of codepoints in a UTF-8 encoded string
// RLAPI int GetCodepoint(const char *text, int *codepointSize);           // Get next codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure
// RLAPI int GetCodepointNext(const char *text, int *codepointSize);       // Get next codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure
// RLAPI int GetCodepointPrevious(const char *text, int *codepointSize);   // Get previous codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure
// RLAPI const char *CodepointToUTF8(int codepoint, int *utf8Size);        // Encode one codepoint into UTF-8 byte array (array length returned as parameter)

// Text strings management functions (no UTF-8 strings, only byte chars)
// NOTE: Some strings allocate memory internally for returned strings, just be careful!
// RLAPI int TextCopy(char *dst, const char *src);                                             // Copy one string to another, returns bytes copied
// RLAPI bool TextIsEqual(const char *text1, const char *text2);                               // Check if two text string are equal
// RLAPI unsigned int TextLength(const char *text);                                            // Get text length, checks for '\0' ending
// RLAPI const char *TextFormat(const char *text, ...);                                        // Text formatting with variables (sprintf() style)
// RLAPI const char *TextSubtext(const char *text, int position, int length);                  // Get a piece of a text string
// RLAPI char *TextReplace(const char *text, const char *replace, const char *by);             // Replace text string (WARNING: memory must be freed!)
// RLAPI char *TextInsert(const char *text, const char *insert, int position);                 // Insert text in a position (WARNING: memory must be freed!)
// RLAPI const char *TextJoin(const char **textList, int count, const char *delimiter);        // Join text strings with delimiter
// RLAPI const char **TextSplit(const char *text, char delimiter, int *count);                 // Split text into multiple strings
// RLAPI void TextAppend(char *text, const char *append, int *position);                       // Append text at specific position and move cursor!
// RLAPI int TextFindIndex(const char *text, const char *find);                                // Find first text occurrence within a string
// RLAPI const char *TextToUpper(const char *text);                      // Get upper case version of provided string
// RLAPI const char *TextToLower(const char *text);                      // Get lower case version of provided string
// RLAPI const char *TextToPascal(const char *text);                     // Get Pascal case notation version of provided string
// RLAPI const char *TextToSnake(const char *text);                      // Get Snake case notation version of provided string
// RLAPI const char *TextToCamel(const char *text);                      // Get Camel case notation version of provided string

// RLAPI int TextToInteger(const char *text);                            // Get integer value from text (negative values not supported)
// RLAPI float TextToFloat(const char *text);                            // Get float value from text (negative values not supported)
