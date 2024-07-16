// Files management functions
// RLAPI unsigned char *LoadFileData(const char *fileName, int *dataSize); // Load file data as byte array (read)
// RLAPI void UnloadFileData(unsigned char *data);                   // Unload file data allocated by LoadFileData()
// RLAPI bool SaveFileData(const char *fileName, void *data, int dataSize); // Save data to file from byte array (write), returns true on success
// RLAPI bool ExportDataAsCode(const unsigned char *data, int dataSize, const char *fileName); // Export data to code (.h), returns true on success
// RLAPI char *LoadFileText(const char *fileName);                   // Load text data from file (read), returns a '\0' terminated string
// RLAPI void UnloadFileText(char *text);                            // Unload file text data allocated by LoadFileText()
// RLAPI bool SaveFileText(const char *fileName, char *text);        // Save text data to file (write), string must be '\0' terminated, returns true on success
//------------------------------------------------------------------

// File system functions
// RLAPI bool FileExists(const char *fileName);                      // Check if file exists
// RLAPI bool DirectoryExists(const char *dirPath);                  // Check if a directory path exists
// RLAPI bool IsFileExtension(const char *fileName, const char *ext); // Check file extension (including point: .png, .wav)
// RLAPI int GetFileLength(const char *fileName);                    // Get file length in bytes (NOTE: GetFileSize() conflicts with windows.h)
// RLAPI const char *GetFileExtension(const char *fileName);         // Get pointer to extension for a filename string (includes dot: '.png')
// RLAPI const char *GetFileName(const char *filePath);              // Get pointer to filename for a path string
// RLAPI const char *GetFileNameWithoutExt(const char *filePath);    // Get filename string without extension (uses static string)
// RLAPI const char *GetDirectoryPath(const char *filePath);         // Get full path for a given fileName with path (uses static string)
// RLAPI const char *GetPrevDirectoryPath(const char *dirPath);      // Get previous directory path for a given path (uses static string)
// RLAPI const char *GetWorkingDirectory(void);                      // Get current working directory (uses static string)
// RLAPI const char *GetApplicationDirectory(void);                  // Get the directory of the running application (uses static string)
// RLAPI bool ChangeDirectory(const char *dir);                      // Change working directory, return true on success
// RLAPI bool IsPathFile(const char *path);                          // Check if a given path is a file or a directory
// RLAPI bool IsFileNameValid(const char *fileName);                 // Check if fileName is valid for the platform/OS
// RLAPI FilePathList LoadDirectoryFiles(const char *dirPath);       // Load directory filepaths
// RLAPI FilePathList LoadDirectoryFilesEx(const char *basePath, const char *filter, bool scanSubdirs); // Load directory filepaths with extension filtering and recursive directory scan
// RLAPI void UnloadDirectoryFiles(FilePathList files);              // Unload filepaths
// RLAPI bool IsFileDropped(void);                                   // Check if a file has been dropped into window
// RLAPI FilePathList LoadDroppedFiles(void);                        // Load dropped filepaths
// RLAPI void UnloadDroppedFiles(FilePathList files);                // Unload dropped filepaths
// RLAPI long GetFileModTime(const char *fileName);                  // Get file modification time (last write time)
