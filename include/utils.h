#pragma once

/**
 * @brief This function clears all Fifo type files in specified directory
 * 
 * @param targetDirectory Path to directory from where to delete fifo files
 */
void utils_clearFifoFiles(const char *targetDirectory);

/**
 * @brief Executes the program located in filePath argument and returs it's output
 * 
 * @param filepath path to the target program
 * @return char* program output
 */
char *utils_execProgram(const char *filepath);

/**
 * @brief Replaces all occurences of [whatChar] to [toChar] in given null terminated input string
 * 
 * @param input null terminated input string
 * @param whatChar what char to replace
 * @param toChar charachter that will replace the old ones
 */
void utils_replaceChar(char *input, const char whatChar, const char toChar);

/**
 * @brief Type of function that is acceptable as child main function
 * 
 */
typedef void (*childMain_t)(void);

/**
 * @brief Clones current process into another process and executes fiven function in a child
 * 
 * @param mainF Main function that will be executed in child process
 */
void utils_cloneProcess(childMain_t mainF);

/**
 * @brief Checks if the given directory exists
 * 
 * @param path payj to a directory
 * @return int 0 if not exists and 1 if exists
 */
int utils_dirExists(const char *path);
