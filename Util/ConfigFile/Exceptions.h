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

#ifndef KRUGERLIBS_EXCEPTIONS_H
#define KRUGERLIBS_EXCEPTIONS_H


#include <exception>

using namespace std;

class FileNotFoundException : public exception {
public:

    FileNotFoundException(const std::string &filePath) : filePath(filePath) { }

    virtual const char *what() const throw() {
        std::string msg("File " + filePath + " not found");
        return msg.c_str();
    }

private:

    const std::string filePath;
};

class FileNotLoadedException : public exception {
public:

    FileNotLoadedException(const std::string &filePath) : filePath(filePath) { }

    virtual const char *what() const throw() {
        std::string msg("File " + filePath + " not loaded");
        return msg.c_str();
    }

private:

    const std::string filePath;
};

template <typename T>
class InvalidArgumentException : public exception {
public:

    InvalidArgumentException(const T &arg) : arg(arg) { }

    virtual const char *what() const throw() {
        std::string msg("Invalid argument: " + arg);
        return msg.c_str();
    }

protected:

    const T arg;
};

class InvalidPropertyName : public InvalidArgumentException<const std::string> {
public:

    InvalidPropertyName(const std::string &arg) : InvalidArgumentException(arg) { }

    virtual const char *what() const throw() {
        std::string msg("Invalid property name: " + arg);
        return msg.c_str();
    }
};

class PropertyNotFoundException : public InvalidArgumentException<const std::string> {
public:

    PropertyNotFoundException(const std::string &arg) : InvalidArgumentException(arg) { }

    virtual const char *what() const throw() {
        std::string msg("Property not found: " + arg);
        return msg.c_str();
    }
};

class NumberFormatException : public exception {
public:

    NumberFormatException(const std::string &arg) : arg(arg) { }

    virtual const char *what() const throw() {
        std::string msg("Number format error: " + arg);
        return msg.c_str();
    }

protected:

    const std::string arg;
};



#endif //KRUGERLIBS_EXCEPTIONS_H
