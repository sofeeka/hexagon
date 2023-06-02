#ifndef HEXAGON_DIALOG_H
#define HEXAGON_DIALOG_H

#include <string>

class Dialog {
public:
/**
 * @brief Allows the user to enter a string through a dialog window.
 * This function displays a dialog window with the specified title and text ("" by default).
 * The user can enter a string by typing on the keyboard. The function returns the
 * entered string when the user presses the Enter key. If the user closes the dialog
 * window or presses the Escape key, an empty string is returned.
 *
 * @param title The title of the dialog window.
 * @param defaultText The default text to display in the input field (optional and can be deleted by the user).
 *
 * @return std::string The string entered by the user, or an empty string if canceled.
*/
static std::string getUserInputString(const std::string& title, const std::string& defaultText = "");

/**
 * @brief Displays a message dialog with the specified message.
 *
 * This function shows a message dialog  with the specified message. The dialog
 * box is a rectangular shape with a white background and displays the message in
 * a readable font. The function will block the program execution until the dialog
 * box is closed by the user.
 *
 * @param msg The message to display in the dialog box.
 *
 * @return bool Returns true if the dialog box was successfully closed, false otherwise.
*/
static bool showMessageDialog(const std::string &msg);
};

#endif //HEXAGON_DIALOG_H