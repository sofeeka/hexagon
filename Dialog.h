//
// Created by Sonia on 02.06.2023.
//

#ifndef HEXAGON_DIALOG_H
#define HEXAGON_DIALOG_H


#include <string>

class Dialog {
public:
    static std::string getUserInputString(const std::string& title, const std::string& defaultText = "");
};


#endif //HEXAGON_DIALOG_H
