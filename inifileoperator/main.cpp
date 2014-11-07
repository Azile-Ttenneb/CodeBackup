#include "inifileoperator.h"

int main()
{
    string section = "cfg";
    string key = "url";
    string value = "/EBClient/html/index.html";
    IniFileOperator file("./a.ini");
    file.readFile();
    file.printContent();
    file.setValue(section, key, value);
    file.writeFile();
    section = "maindialog";
    key = "hrefincurrent";
    file.getValue(section, key, value);
    cout << value << endl;
    return 0;
}
