#include "inifileoperator.h"

IniFileOperator::IniFileOperator(const string &filename) : m_strFileName (filename)
{
}

IniFileOperator::IniFileOperator()
{
}

IniFileOperator::IniFileOperator(const char *filename) : m_strFileName (filename)
{
}

IniFileOperator::~IniFileOperator()
{
}

bool IniFileOperator::getValue(const string &section, const string &key, string& value)
{
    IniFileFormat::iterator itSection = m_lFileContent.begin();
    while (itSection != m_lFileContent.end())
    {
        if (itSection->section == section)
        {
            IniFileSettings::iterator itKey = itSection->settings.begin();
            while (itKey != itSection->settings.end())
            {
                if (itKey->key == key)
                {
                    value = itKey->value;
                    return true;
                }
                itKey++;
            }
        }
        itSection++;
    }
    return false;
}

bool IniFileOperator::setValue(const string &section, const string &key, const string& value)
{
    IniFileFormat::iterator itSection = m_lFileContent.begin();
    while (itSection != m_lFileContent.end())
    {
        if (itSection->section == section)
        {
            IniFileSettings::iterator itKey = itSection->settings.begin();
            while (itKey != itSection->settings.end())
            {
                if (itKey->key == key)
                {
                    itKey->value = value;
                    return true;
                }
                itKey++;
            }
            IniFileSetting stTmp;
            stTmp.key = key;
            stTmp.value = value;
            itSection->settings.push_back(stTmp);
            return true;
        }
        itSection++;
    }
    IniFileSections stTmpSection;
    stTmpSection.section = section;
    if (key.length() != 0)
    {
	IniFileSetting stTmp;
	stTmp.key = key;
	stTmp.value = value;
	stTmpSection.settings.push_back(stTmp);
    }
    m_lFileContent.push_back(stTmpSection);
    return true;
}

int IniFileOperator::readFile(const string &filename)
{
    ifstream fsReadFile(filename.c_str());
    string strBuffer;
    string section;
    string key;
    string value;
    int iRet;
    while(getline(fsReadFile, strBuffer))
    {
        if (strBuffer.length() == 0)
        {
            continue;
        }
        if (strBuffer.at(strBuffer.length() - 1) == '\r')
        {
            strBuffer.erase(strBuffer.length() - 1);
        }
        if ((iRet = parseLine(strBuffer, section, key, value)) == -1)
        {
            cerr << "Bad format ini file" << endl;
            fsReadFile.close();
            return -1;
        }
        else if (iRet == 0)
        {
        }
        else if (iRet == 1)
        {
            setValue(section, key, value);
        }
        else if (iRet == 2)
        {
            setValue(section, key, value);
        }
    }
    fsReadFile.close();
    return 0;
}

int IniFileOperator::writeFile(const string &filename)
{
    IniFileFormat::iterator itSections;
    IniFileSettings::iterator itSettings;
    ofstream fsWriteFile(filename.c_str());
    for (itSections = m_lFileContent.begin(); itSections != m_lFileContent.end(); itSections++)
    {
        fsWriteFile << '[' << itSections->section << ']' << endl;
        for (itSettings = itSections->settings.begin(); itSettings != itSections->settings.end(); itSettings++)
        {
            fsWriteFile << itSettings->key << '=' << itSettings->value << endl;
        }
    }
    fsWriteFile.close();
    return 0;
}

int IniFileOperator::parseLine(string &buffer, string &section, string &key, string &value)
{
    int iIndex;
    if (buffer.length() == 0)
    {
        return 0;
    }
    else if (buffer.at(0) == '[' && (buffer.at(buffer.length() - 1)) == ']')
    {
        section = buffer.substr(1, buffer.length() - 2);
        key = "";
        value = "";
        return 1;
    }
    else if ((iIndex = buffer.find('=', 0)) != string::npos) 
    {
        key = buffer.substr(0, iIndex);
        value = buffer.substr(iIndex + 1);
        return 2;
    }
    else
    {
        cerr << "0:" << buffer.at(0) << " " << buffer.length() - 1 << ":" << buffer.at(buffer.length() - 1) << "__" << endl;
        return -1;
    }
}

int IniFileOperator::readFile()
{
    return readFile(m_strFileName);
}

int IniFileOperator::writeFile()
{
    return writeFile(m_strFileName);
}

int IniFileOperator::printContent()
{
    IniFileFormat::iterator itSections;
    IniFileSettings::iterator itSettings;
    for (itSections = m_lFileContent.begin(); itSections != m_lFileContent.end(); itSections++)
    {
        cout << '[' << itSections->section << ']' << endl;
        for (itSettings = itSections->settings.begin(); itSettings != itSections->settings.end(); itSettings++)
        {
            cout << itSettings->key << '=' << itSettings->value << endl;
        }
    }
    return 0;
}
