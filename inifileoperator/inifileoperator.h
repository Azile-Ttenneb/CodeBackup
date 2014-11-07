#ifndef INI_FILE_OPERATOR
#define INI_FILE_OPERATOR

#include <list>
#include <string>
#include <iostream>
#include <fstream>
using std::list;
using std::string;
using std::ifstream;
using std::ofstream;
using std::cout;
using std::cerr;
using std::endl;

typedef struct {
    string key;
    string value;
} IniFileSetting;

typedef list<IniFileSetting> IniFileSettings;

typedef struct {
    string section;
    IniFileSettings settings;
} IniFileSections;

typedef list<IniFileSections> IniFileFormat;


class IniFileOperator {
public:
    /*
    构造函数
    参数: filename: ini文件路径
    */
    IniFileOperator(const string &filename);
    IniFileOperator();
    /*
    构造函数
    参数: filename: ini文件路径
    */
    IniFileOperator(const char *filename);
    ~IniFileOperator();
    /*
    取配置的值
    参数: section: section值, 取值条件
          key: key值, 取值条件
          value: value值, 返回的结果
    返回值: true 配置且取值成功
           false 未配置
    */
    bool getValue(const string &section, const string &key, string &value);
    /*
    配置值
    参数: section: section值, 配置条件
          key: key值, 配置条件
          value: value值, 欲配置的值
    返回值: true 配置成功
           false 配置失败
    */
    bool setValue(const string &section, const string &key, const string& value);
    /*
    读取文件内容
    */
    int readFile();
    /*
    更改内容写回文件
    */
    int writeFile();
    /*
    打印配置内容, 测试用函数
    */
    int printContent();
private:
    int readFile(const string &filename);
    int writeFile(const string &filename);
    /*
    分析行内容
    参数: buffer 欲分析的行内容
          section 此行所属section
          key 此行中key值
          value 此行中value值
    返回值: 0: 空行, 跳过
           1: section行
           2: 有key/value的配置行
           -1: 无意义行
    */
    int parseLine(string &buffer, string &section, string &key, string &value);
private:
    IniFileFormat m_lFileContent;
    string m_strFileName;
};

#endif
