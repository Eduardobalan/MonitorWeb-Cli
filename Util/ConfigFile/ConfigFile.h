/*
 * Created by Kleber Kruger on 21/07/16.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef KRUGERLIBS_CONFIGFILE_H
#define KRUGERLIBS_CONFIGFILE_H


#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <iostream>
#include <map>
#include "Exceptions.h"
#include "../SystemLog.h"

using namespace std;

class ConfigFile {
private:

    std::string filePath;
    std::string symbol;
    std::map<const std::string, std::string> configMap;
    bool loaded;

    inline bool containsInvalidChar(const std::string &property) {
        return property.find(symbol.c_str()) != std::string::npos;
    }

    template<typename T, typename R = T>
    inline T getNumber(const std::string &property, R (*fptr)(const char *, char **, int)) {
        const char *val = loadValueFromFile(property);
        char *end = nullptr;
        T value = fptr(val, &end, 10);
        if (*end != 0) {
            NumberFormatException ex(val);
            throw ex;
        }
        return value;
    }

    template<typename T>
    inline T getNumber(const std::string &property, T (*fptr)(const char *, char **)) {
        const char *val = loadValueFromFile(property);
        char *end = nullptr;
        T value = fptr(val, &end);
        if (*end != 0) {
            NumberFormatException ex(val);
            throw ex;
        }
        return value;
    }

    inline void saveBool(const std::string &property, const bool value) {
        if (containsInvalidChar(property)) {
            InvalidPropertyName ex(property);
            throw ex;
        }
        configMap[property] = static_cast<const std::string>(value == 0 ? "false" : "true");
    }

    template<typename T>
    inline void saveNumber(const std::string &property, const T value) {
        if (containsInvalidChar(property)) {
            InvalidPropertyName ex(property);
            throw ex;
        }
        configMap[property] = std::to_string(value);
    }

    template<typename T>
    inline void saveCharOrString(const std::string &property, const T value) {
        if (containsInvalidChar(property)) {
            InvalidPropertyName ex(property);
            throw ex;
        }
        configMap[property] = value;
    }

public:

    /**
	 * Creates a ConfigFile object.
     *
     * @param filePath
	 */
    ConfigFile(const std::string &filePath, const std::string &symbol = "=")
            : filePath(filePath), symbol(symbol), loaded(false) {}

    /**
	 * Creates a copy of the ConfigFile object.
     *
     * @param orig
	 */
    ConfigFile(const ConfigFile &orig)
            : filePath(orig.filePath), symbol(orig.symbol), configMap(orig.configMap), loaded(orig.loaded) {}

    /**
	 * Destroys this object.
	 */
    virtual ~ConfigFile() {}

    /**
	 * Loads configurations saved in file.
	 */
    void load();

    /**
	 * Commits (save/serialize) configurations in the file.
	 */
    void commit();

    /**
	 * Gets the file path of this ConfigFile.
	 */
    const std::string &getFilePath() const {
        return filePath;
    }

    const char *getPropertyValue(const std::string &property) {
        std::map<const std::string, std::string>::iterator it = configMap.find(property);
        return it == configMap.end() ? nullptr : it->second.c_str();
    }

    inline const char *loadValueFromFile(const std::string &property) {
        if (!loaded) {
            FileNotLoadedException ex(filePath);
            throw ex;
        }

        const char *value = getPropertyValue(property);

        if (value == nullptr) {
            value = "";
            SystemLog::execLog('w',"ConfigFile: property '"+property+"' não encontrada no arquivo ou linha comentada.");
//            PropertyNotFoundException ex(property);
//            throw ex;
        }

        return value;
    }

    bool getBool(const std::string &property) {
        //bool getBool(const std::string &property, bool &value) {
        const char *val = loadValueFromFile(property);

        if (strcasecmp(val, "true") == 0) {
            return true;
        } else if (strcasecmp(val, "false") == 0) {
            return false;
        }

        InvalidArgumentException<const std::string> ex(val);
        throw ex;
    }

    short getShort(const std::string &property) {
        return getNumber<short>(property, &strtol);
    }

    unsigned short getUShort(const std::string &property) {
        return getNumber<unsigned short>(property, &strtoul);
    }

    int getInt(const std::string &property) {
        return getNumber<int>(property, &strtol);
    }

    unsigned int getUInt(const std::string &property) {
        return getNumber<unsigned int>(property, &strtoul);
    }

    long getLong(const std::string &property) {
        return getNumber<long>(property, &strtol);
    }

    unsigned long getULong(const std::string &property) {
        return getNumber<unsigned long>(property, &strtoul);
    }

    long long getLLong(const std::string &property) {
        return getNumber<long long>(property, &strtoll);
    }

    unsigned long long getULLong(const std::string &property) {
        return getNumber<unsigned long long>(property, &strtoull);
    }

    float getFloat(const std::string &property) {
        return getNumber<float>(property, &strtof);
    }

    double getDouble(const std::string &property) {
        return getNumber<double>(property, &strtod);
    }

    long double getLDouble(const std::string &property) {
        return getNumber<long double>(property, &strtold);
    }

    char getChar(const std::string &property) {
        const char *value = loadValueFromFile(property);
        return value[0];
    }

    unsigned char getUChar(const std::string &property) {
        const char *value = loadValueFromFile(property);
        return static_cast<unsigned char>(value[0]);
    }

    const char *getString(const std::string &property) {
        return loadValueFromFile(property);
    }

//    void load(const std::string &property, bool &value);
//    void load(const std::string &property, short &value);
//    void load(const std::string &property, unsigned short &value);
//    void load(const std::string &property, int &value);
//    void load(const std::string &property, unsigned int &value);
//    void load(const std::string &property, long &value);
//    void load(const std::string &property, unsigned long &value);
//    void load(const std::string &property, long long &value);
//    void load(const std::string &property, unsigned long long &value);
//    void load(const std::string &property, float &value);
//    void load(const std::string &property, double &value);
//    void load(const std::string &property, long double &value);
//    void load(const std::string &property, char &value);
//    void load(const std::string &property, unsigned char &value);
//    void load(const std::string &property, const char *value);
//    void load(const std::string &property, std::string &value);

    void save(const std::string &property, const bool value) { saveBool(property, value); }

    void save(const std::string &property, const short value) { saveNumber(property, value); }

    void save(const std::string &property, const unsigned short value) { saveNumber(property, value); }

    void save(const std::string &property, const int value) { saveNumber(property, value); }

    void save(const std::string &property, const unsigned int value) { saveNumber(property, value); }

    void save(const std::string &property, const long value) { saveNumber(property, value); }

    void save(const std::string &property, const unsigned long value) { saveNumber(property, value); }

    void save(const std::string &property, const long long value) { saveNumber(property, value); }

    void save(const std::string &property, const unsigned long long value) { saveNumber(property, value); }

    void save(const std::string &property, const float value) { saveNumber(property, value); }

    void save(const std::string &property, const double value) { saveNumber(property, value); }

    void save(const std::string &property, const long double value) { saveNumber(property, value); }

    void save(const std::string &property, const char value) { saveCharOrString(property, value); }

    void save(const std::string &property, const unsigned char value) { saveCharOrString(property, value); }

    void save(const std::string &property, const std::string &value) { saveCharOrString(property, value); }
};


#endif //KRUGERLIBS_CONFIGFILE_H
