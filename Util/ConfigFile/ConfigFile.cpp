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

#include "ConfigFile.h"

static const std::string pattern = " \f\n\r\t\v";

std::string trim_left(const std::string &str) {
    std::size_t pos = str.find_first_not_of(pattern);
    return (pos != std::string::npos) ? str.substr(pos) : "";
}

std::string trim_right(const std::string &str) {
    std::size_t pos = str.find_last_not_of(pattern);
    return (pos != std::string::npos) ? str.substr(0, pos + 1) : "";
}

std::string trim(const std::string &str) {
    return trim_left(trim_right(str));
}

void ConfigFile::load() {

    ifstream file(filePath, ios::in);
    if (!file.good()) {
        FileNotFoundException ex(filePath);
        throw ex;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::size_t pos = line.find("#");
        if (pos != std::string::npos) {
            line = line.substr(0, pos);
        }
        pos = line.find(symbol.c_str());
        if (pos != std::string::npos) {
            std::string property = trim(line.substr(0, pos));
            std::string value = trim(line.substr(pos + 1, line.size() - pos - 1));
            //cout << "Adicionado: [" << property << "=" << value << "]" << endl;
            save(property, value);
            loaded = true;
            //cout << "ahsuahsuhas : " << getString(property) << endl;
        }
    }
    file.close();
    loaded = true;
}

void ConfigFile::commit() {
    ofstream file(filePath, ios::ate | ios::out);
    if (!file.good()) {
        FileNotFoundException ex(filePath);
        throw ex;
    }
    for (auto const &x : configMap) {
        file << x.first << symbol.c_str() << x.second << std::endl;
    }
    file.close();
}