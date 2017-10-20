//
// Created by Steven on 10/7/2017.
//

#include <afxres.h>
#include "file_utils.h"


BOOL InitWorldMap(FILE *world_map_file, short world_map[MAX_DIMENSION][MAX_DIMENSION]) {
    char temp_string[NUMBER_MAX_LENGTH] = { '\0' };
    char c;
    USHORT i;
    BOOL completed;
    int x = 0, y = 0;
    while ((c = (char) fgetc(world_map_file)) != EOF) {
        switch (c) {
            case ',':
                world_map[x][y] = (short) atoi(temp_string);
                x++;
                ZeroMemory(temp_string, sizeof(temp_string));
                break;
            case '\n':
                world_map[x][y] = (short) atoi(temp_string);
                y++;
                x = 0;
                ZeroMemory(temp_string, sizeof(temp_string));
            case '\r':
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                completed = FALSE;
                for (i = 0; i < (sizeof(temp_string) - 1) && !completed; ++i) {
                    if (temp_string[i] == '\0') {
                        temp_string[i] = c;
                        completed = TRUE;
                    }
                }

                if (!completed) {
                    printf("Got too long string");
                    return FALSE;
                }
                break;
            default:
                printf("Read illegal character from world map file. (%c)", c);
                return FALSE;
        }
    }
    world_map[x][y] = (short) atoi(temp_string);
    return TRUE;
}

BOOL GetWorldMapFileName(int argc, char **argv, const char *file_name) {
    if (argc < 2) {
        if (!OpenFileDialog((char *) file_name)) {
            return FALSE;
        }
    } else {
        strcpy_s((char *) file_name, MAX_PATH, argv[1]);
    }
    return TRUE;
}

/***********************************************************************************************************************
BOOL OpenFileDialog(char *fileName)

 Input:
    char *fileName - pointer to file name string

 Return:
    BOOL -
        TRUE if succeeded
        FALSE if failed
***********************************************************************************************************************/
BOOL OpenFileDialog(char *fileName) {
    OPENFILENAME ofn;       // common dialog box structure
    HWND hwnd = NULL;       // owner window
    char title[MAX_PATH];
    sprintf(title, "Open world map %d by %d", MAX_DIMENSION, MAX_DIMENSION);

    // Initialize OPENFILENAME
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = fileName;
    ofn.lpstrTitle = title;
    // Set lpstrFile[0] to '\0' so that GetOpenFileName does not
    // use the contents of szFile to initialize itself.
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter = "*.csv\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = MAX_PATH;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    // Display the Open dialog box.
    return GetOpenFileName(&ofn);
}
