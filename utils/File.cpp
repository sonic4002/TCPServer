//
// Created by omrih on 21-Jun-17.
//

#include "File.h"

using namespace npl;

File::File(char* path) {
    // TODO Auto-generated constructor stub

    file.open(path, ifstream::in | ifstream::out | ifstream::app);
    this->path = path;
}

string File::getpath() {
    return path;
}

int File::read(char* buffer, int length) {

    if (file.is_open())
    {
        length = file.tellg();
        buffer = new char [length];
        file.seekg (0, ios::beg);
        file.read(buffer ,length);
        while (!file.eof()) {
            file >> this->buffer;
            //cout<<buffer;
        }

    }
//    puts("\n");

    return 0;
}

int File::write(const string& msg) {
    char* buff = new char[msg.length()+1];
    strcpy(buff,msg.c_str());
    long size = msg.size();
    file.write(buff, size);
    file.flush();
    return 0;
}

void File::close() {
    file.close();
}

File::~File() {
    // TODO Auto-generated destructor stub
}


bool File::find_user_and_pass(string user, string pass){
    string f_user, f_pass, f_points;
    ifstream file(this->path);

    while (file >> f_user >> f_pass >> f_points){
        if((f_user.compare(user) == 0 ) && (f_pass.compare(pass) == 0)){
            return true;
        }
    }
    return false;
}

bool File::find_user(string user){
    string f_user, f_pass, f_points;
    ifstream file(this->path);

    while (file >> f_user >> f_pass >> f_points){
        if(f_user.compare(user) == 0 ){
            return true;
        }
    }
    return false;
}