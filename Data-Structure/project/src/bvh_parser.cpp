#include<fstream>
#include"bvh_parser.h"
////////////////////
#include <iostream>
#include <iomanip>
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
////////////////////
// a naive bvh parser
using std::ifstream;

//////////////////////////////////////////////////////////////////
void Split(const string& src, vector<string>& dest)
{
	string str = src;
	// string::size_type start = 0, index;
	dest.clear();
    for (int i = 0; i < str.size(); i++){
        string substring = "";
        while (i < str.size() && str[i] != ' ' && str[i] != '\t' && str[i] != '\n'){
            substring.push_back(str[i]);
            i++;
        }
        if (substring != ""){
            dest.push_back(substring);
        }    
    }
}

int FIND(vector<string> Data, string key){
    for (int i = 0; i < Data.size(); i++){
        if (Data[i] == key){
            return i;
        }
    }
    return -1;
}

char PROCESS(string s){
    if (s.find("ROOT") != s.npos || s.find("JOINT") != s.npos || \
    s.find("End") != s.npos){
        return 'Y';
    }
    else if (s.find("}") != s.npos){
        return '}';
    }
}

// be similar to the process of building a binary tree
void parse(ifstream &file, joint &node, META meta_data, vector<vector<double> > motion_tmp){  
    stack<joint*> s;
    s.push(&node);
    string line;
    // determine parent
    string parent_name;
    // determine column
    int col = 0; 

    // the processs of root
    getline(file, line);
    // the info of line 1
    getline(file, line);
    if(line.find("ROOT") != line.npos){
        node.joint_type = "ROOT";
        vector<string> Data;
        Split(line, Data);
        node.name = Data[Data.size()-1].substr(0, Data[Data.size()-1].size()-1);
    }
    // the info of line 2: '{'
    getline(file, line);
    // the info of line 3
    getline(file, line);
    if (line.find("OFFSET") != line.npos){
        vector<string> Data;
        Split(line, Data);
        node.offset_x = stod(Data[Data.size()-3].c_str());
        node.offset_y = stod(Data[Data.size()-2].c_str());
        node.offset_z = stod(Data[Data.size()-1].c_str());
    }

    // the info of line 4
    getline(file, line);
    if (line.find("CHANNELS") != line.npos){
        vector<string> Data;
        Split(line, Data);
        // we should find the order that "CHANNELS" appears
        // CHANNELS num
        int len = stoi(Data[1].c_str());
        for (int i = 2; i < Data.size(); i++){
            if (i == Data.size() - 1){
                node.channels.push_back(Data[i].substr(0,Data[i].size()-1));
            }
            else{
                node.channels.push_back(Data[i]);
            }
        }
        // initialize node.motion
        node.motion = vector<vector<double> > (meta_data.frame, vector<double>(len));
        // get the data of motion
        for (int i = 0; i < meta_data.frame; i++){
            for (int j = 0; j < len; j++){
                node.motion[i][j] = motion_tmp[i][col + j];
            }
        } 
        col += len;    
    }
    
    getline(file, line);
    while (line.find("MOTION") == line.npos){
        switch (PROCESS(line))
        {
        case 'Y':
            if (line.find("JOINT") != line.npos || line.find("End") != line.npos){
                joint *p = new joint;
                s.top()->children.push_back(p);
                s.push(p);
                if (line.find("JOINT") != line.npos){
                    // the info of line 1
                    p->joint_type = "JOINT";
                    vector<string> Data;
                    Split(line, Data);
                    p->name = Data[Data.size()-1].substr(0, Data[Data.size()-1].size()-1);
                    parent_name = p->name.substr(0,p->name.size()-1);

                    // the info of line 2
                    // '{'
                    getline(file, line);

                    // the info of line 3
                    getline(file, line);
                    if (line.find("OFFSET") != line.npos){
                        vector<string> Data;
                        Split(line, Data);
                        p->offset_x = stod(Data[Data.size()-3].c_str());
                        p->offset_y = stod(Data[Data.size()-2].c_str());
                        p->offset_z = stod(Data[Data.size()-1].c_str());
                    }

                    // the info of line 4
                    getline(file, line);
                    if (line.find("CHANNELS") != line.npos){
                        vector<string> Data;
                        Split(line, Data);
                        // we should find the order that "CHANNELS" appears
                        // CHANNELS num
                        int len = stoi(Data[1].c_str());
                        for (int i = 2; i < Data.size(); i++){
                            if (i == Data.size() - 1){
                                p->channels.push_back(Data[i].substr(0,Data[i].size()-1));
                            }
                            else{
                                p->channels.push_back(Data[i]);
                            }
                        }
                        // initialize node.motion
                        p->motion = vector<vector<double> > (meta_data.frame, vector<double>(len));
                        // get the data of motion
                        for (int i = 0; i < meta_data.frame; i++){
                            for (int j = 0; j < len; j++){
                                p->motion[i][j] = motion_tmp[i][col + j];
                            }
                        } 
                        col += len;    
                    }
                }
                else if (line.find("End") != line.npos){
                    p->joint_type = "End";
                    p->name = parent_name + "_End"; 
                    getline(file, line);
                    getline(file, line);
                    if (line.find("OFFSET") != line.npos){
                        vector<string> Data;
                        Split(line, Data);
                        p->offset_x = stod(Data[Data.size()-3].c_str());
                        p->offset_y = stod(Data[Data.size()-2].c_str());
                        p->offset_z = stod(Data[Data.size()-1].c_str());
                    }
                    p->motion = vector<vector<double> > (meta_data.frame);
                }
            }
            break;
        
        case '}':
            s.pop();
            break;

        default:
            // create another new joint p and link it to the previous node
            break;
        }
        getline(file, line);
    }
}

//////////////////////////////////////////////////////////////////

int main(int argc, char** argv) {
    joint root;
    META meta_data;
    ifstream file(argv[1]);

    // do something
    ///////////////////////////////////////////////////////////////     
    // find the info of frame and frame_time in .bvh
    if (!file){
        cout << "the file doesn't exist!" << endl;
        return -1;
    }
    string line;
    getline(file, line);
    while (file){
        if (line.find("Frames") != line.npos){
            vector<string> Data;
            Split(line, Data);
            meta_data.frame = atoi(Data[1].c_str());
        }
        else if (line.find("Frame Time") != line.npos){
            vector<string> Data;
            Split(line, Data);
            meta_data.frame_time= stod(Data[2]);
            getline(file, line);
            break;
        }
        getline(file, line);
    }

    // get motion data
    vector<vector<double> > motion_tmp(meta_data.frame);
    for (int i = 0; i < meta_data.frame; i++){
        vector<string> Data;
        Split(line, Data);
        // the last element of Data is NULL
        for (int j = 0; j < Data.size() - 1; j++){
            motion_tmp[i].push_back(stod(Data[j].c_str()));
        }
        getline(file, line);
    }

    file.close();

    // bulid tree
    // type, name, offset, channels can be directly get.
    // use recursive structure to save chlidern
    // motion array need to be cut
    // preorder
    ifstream file_n(argv[1]);

    parse(file_n, root, meta_data, motion_tmp);  
    ///////////////////////////////////////////////////////////////
    jsonify(root, meta_data);
    file.close();
    return 0;
}