#include <iostream>
#include <fstream>
#include "json/json.h"

using namespace std;

struct InVert {
    double x;
    double y;
    double z;
    };

struct OutVert {
    double x;
    double y;
    double z;
    double u;
    double v;

    bool operator==(const OutVert& r) const {
        return r.u==u && r.v==v && r.x==x && r.y==y && r.z==z;
        }
    };

struct InFace {
    OutVert v[3];
    };

void vertToOutVert(OutVert& out, const InVert& in) {
    out.x = in.x;
    out.y = in.y;
    out.z = in.z;
    }

int main(int argc, char *argv[]) {
    try {
        string tempStr, filename;
        string mat;
        int tempInt;
        double tempDbl;
        int groupCnt;
        cout<<"Input file?";
        cin>>filename;
        ifstream file((filename+".txt").c_str());
        if(!file.good()) cout<<"FAIL";
        file>>tempStr;
        file>>tempInt;
        file>>groupCnt;

        cout<<"Pocet grup: "<<groupCnt<<endl;

        vector< vector<InVert> > verts = vector< vector<InVert> >();
        vector< vector<InFace> > faces = vector< vector<InFace> >();

        verts.resize(groupCnt);
        faces.resize(groupCnt);


        json::mArray parts;

        for(int g=0; g<groupCnt; ++g) {
            cout<<"Zacinam grupu "<<g<<endl;
            file>>mat;
            cout<<mat<<endl;

            int vertCnt;
            file>>vertCnt;
            cout<<"Pocet vertexu: "<<vertCnt<<endl;
            verts[g].resize(vertCnt);

            for(int v=0; v<vertCnt; ++v) {
                file>>verts[g][v].x;
                file>>verts[g][v].y;
                file>>verts[g][v].z;
                }

            int faceCnt;
            file>>faceCnt;
            cout<<"Pocet faceu: "<<faceCnt<<endl;
            faces[g].resize(faceCnt);

            for(int f=0; f < faceCnt; ++f) {
                file>>tempInt;

                for(int i = 0; i < 3; ++i) {
                    file>>tempInt;
                    vertToOutVert(faces[g][f].v[i], verts[g][tempInt]);
                    }

                for(int i = 0; i < 9; ++i) {
                    file>>tempDbl;
                    }

                for(int i = 0; i < 3; ++i) {
                    file>>faces[g][f].v[i].u;
                    file>>faces[g][f].v[i].v;
                    faces[g][f].v[i].v = 1 - faces[g][f].v[i].v;
                    }
                }

            vector<OutVert> vertVec;
            json::mArray indices;


            for(int f = 0; f < faceCnt; ++f) {
                for(int i = 0; i < 3; ++i) {
                    vector<OutVert>::iterator it = find(vertVec.begin(), vertVec.end(), faces[g][f].v[i]);
                    if(it != vertVec.end()) {
                        indices.push_back(it - vertVec.begin());
                        }
                    else {
                        indices.push_back((int)vertVec.size());
                        vertVec.push_back(faces[g][f].v[i]);
                        }
                    }
                }
            json::mObject part;
            json::mArray vertices;

            for(vector<OutVert>::iterator it = vertVec.begin(); it != vertVec.end(); ++it) {
                json::mObject vertex;
                json::mArray position;
                json::mArray texCoord;
                position.push_back(it->x);
                position.push_back(it->y);
                position.push_back(it->z);
                texCoord.push_back(it->u);
                texCoord.push_back(it->v);
                vertex["position"]=position;
                vertex["texCoord"]=texCoord;
                vertices.push_back(vertex);
                }
            part["material"]=mat;
            part["vertices"]=vertices;
            part["indices"]=indices;
            parts.push_back(part);
            }
        json::mObject obj;
        obj["type"]="static";
        obj["parts"]=parts;
        ofstream output((filename+".json").c_str());
        write(obj, output);
        output.close();
        file.close();
        }
    catch(exception e) {
        cout<<"FAIL: "<<e.what();
        }
    catch(...) {
        cout<<"Something failed...";
        }
    }


