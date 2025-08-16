#include<iostream>
#include<fstream>
#include"bvh_parser.h"

using std::ofstream;

// print the result
// we should process diffetent cases
void processType(ofstream &outfile, joint p){
    outfile << '"' << "type" << '"' << ": " << '"' << p.joint_type << '"' << ',' << '\n';
}

void processName(ofstream &outfile, joint p){
    // the length of p.name is always the real size of p.name plus one
    if (p.joint_type == "JOINT" || p.joint_type == "ROOT"){
        outfile << '"' << "name" << '"' << ": " << '"' << p.name << '"' << "," << '\n';
    }
    else if (p.joint_type == "End"){
        outfile << '"' << "name" << '"' << ": " << '"' << p.name << '"' << "," << '\n';
    }
}

void processOffset(ofstream &outfile, joint p){
    outfile << '"' << "offset" << '"' << ": " << '[' << p.offset_x << ", "\
    << p.offset_y << ", " << p.offset_z << ']' << ',' << '\n';
}

void processChannels(ofstream &outfile, joint p){
    outfile << '"' << "channels" << '"' << ": " << '[' ;
    if (p.joint_type != "End"){
        for (int i = 0; i < p.channels.size() - 1; i++){
            outfile << '"' << p.channels[i] << '"' << ", ";
        }
        outfile << '"' << p.channels[p.channels.size()-1] << '"' << ']' << ',' << '\n';
    }
    else if (p.joint_type == "End"){
        outfile << ']' << ',' << '\n';
    }
}

void processMotion(ofstream &outfile, joint p, META meta_data){
    outfile << '"' << "motion" << '"' << ": " << '[';
    if (p.joint_type != "End"){
        for (int i = 0; i < p.motion.size()-1; i++){
            outfile << '[';
            for (int j = 0; j < p.motion[0].size() - 1; j++){
                outfile << p.motion[i][j] << ", ";
            }
            outfile << p.motion[i][p.motion[0].size() - 1] << ']' << ',' << '\n';
        }

        outfile << '[';
        for (int j = 0; j < p.motion[0].size() - 1; j++){
            outfile << p.motion[p.motion.size()-1][j] << ", ";
        }
        outfile << p.motion[p.motion.size()-1][p.motion[0].size() - 1] << ']' << '\n';
    }
    else if(p.joint_type == "End"){
        for (int i = 0; i < p.motion.size()-1; i++){
            outfile << "[]," << '\n';
        }
        outfile << "[]" << '\n';
    }
    outfile << ']' << ',' << '\n';
}

void processNode(ofstream &outfile, joint p, META meta_data){
    outfile << '{';
    processType(outfile, p);
    processName(outfile, p);
    processOffset(outfile, p);
    processChannels(outfile, p);
    processMotion(outfile, p, meta_data);
    outfile << '"' << "children" << '"' << ": [" << '\n';
    if (p.children.size() > 1){
        for (int i = 0; i < p.children.size() - 1; i++){
            processNode(outfile, *p.children[i], meta_data);
            outfile << ',';
        }
    }
    if (p.children.size() > 0){
        processNode(outfile, *p.children[p.children.size() - 1], meta_data);
    }
    outfile << ']' << '\n';
    outfile << '}';
}

void jsonify(joint root, META meta_data) {
    ofstream outfile;
    outfile.open("output.json");
    outfile << '{' << '\n';
    outfile << '"' << "frame" << '"' << ':' << ' ' << meta_data.frame << ',' << '\n';
    outfile << '"' << "frame_time" << '"' << ':' << ' ' << meta_data.frame_time << ',' << '\n';
    outfile << '"' << "joint" << '"' << ':' << '\n';
    processNode(outfile, root, meta_data);
    outfile << '}' << '\n';

    // output the root and meta_data

    outfile.close();
}