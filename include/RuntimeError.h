void RunTimeError(const char * message, int parameter, 
                  const char * file, int line);

#define RUNTIME_ERROR(description, parameter) RuntimeError(description, parameter, __FILE__, __LINE__)