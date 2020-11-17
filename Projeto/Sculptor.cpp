#include "Sculptor.h"
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>


Sculptor::Sculptor(int _nx, int _ny, int _nz){
    nx = _nx;
    ny = _ny;
    nz = _nz;

    v=new Voxel **[nx];
    for(int xs=0; xs<nx; xs++){
        v[xs]= new Voxel*[_ny];
    }
    for(int xs=0; xs<nx; xs++){
        for(int ys=0; ys<ny; ys++){
            v[xs][ys]= new Voxel[nz];
        }
    }

    for(int xs=0; xs<nx; xs++){
        for(int ys=0; ys<ny; ys++){
            for(int zs=0; zs<nz; zs++){
               v[xs][ys][zs].isOn=false;
               v[xs][ys][zs].r=r;
               v[xs][ys][zs].g=g;
               v[xs][ys][zs].b=b;
               v[xs][ys][zs].a=a;
            }
        }
    }
}

Sculptor::~Sculptor()
{
    int ax, ay;
    ax=nx;
    ay=ny;
    for(int as=0; as<ax; as++){
        for(int ass=0; ass<ay; ass++){
            delete[] v[as][ay];
        }
    }
    for(int as=0; as<ax; as++){
        delete [] v[as];
    }
    delete [] v;
}


 void Sculptor::setColor(float r, float g, float b, float alpha){
    this->r = r; //cor vermelha.
    this->g = g; //cor verde.
    this->b = b; //cor azul.
    this->a = alpha; //opacidade.
 }

 void Sculptor::putVoxel(int x, int y, int z){
    v[x][y][z].isOn = true;
    v[x][y][z].r = r;
    v[x][y][z].g = g;
    v[x][y][z].b = b;
    v[x][y][z].a = a;
 }

void Sculptor::cutVoxel(int x, int y, int z){
    v[x][y][z].isOn = false;
}

void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1){
    int i,j,k;
    for(i=x0; i<=x1; i++){
        for(j=y0; j<=y1; j++){
            for(k=z0; k<=z1; k++){
                putVoxel(i,j,k);
            }
        }
    }
}

void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1){
    int i,j,k;
    for(i=x0; i<=x1; i++){
        for(j=y0; j<=y1; j++){
            for(k=z0; k<=z1; k++){
                cutVoxel(i,j,k);
            }
        }
    }
}

void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius){
   int i, j, k;

    for(i=0; i<2*xcenter; i++){
        for(j=0; j<2*ycenter; j++){
            for(k=0; k<2*zcenter; k++){
                if(((i-xcenter)*(i-xcenter) + (j-ycenter)*(j-ycenter) + (k-zcenter)*(k-zcenter)) <=(radius*radius)){
                    putVoxel(i, j, k);
                }
            }
        }
    }
}

void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius){
   int i, j ,k;

   for(i=0; i<2*xcenter; i++){
       for(j=0; j<2*ycenter; j++){
           for(k=0; k<2*zcenter; k++){
               if(((i-xcenter)*(i-xcenter) + (j-ycenter)*(j-ycenter) + (k-zcenter)*(k-zcenter)) <=(radius*radius)){
                   putVoxel(i, j, k);
               }
           }
       }
   }
}

void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    int i,j,k;

    for(i=xcenter-rx; i<xcenter+rx; i++){
        for(j=ycenter-ry; j<ycenter+ry; j++){
            for(k=zcenter-rz; k<zcenter+rz; k++){
                if((pow(i-xcenter,2)/pow(rx,2)) + (pow(j-ycenter,2)/pow(ry,2)) + (pow(k-zcenter,2)/pow(rz,2)) <= 1){
                    putVoxel(i,j,k);
                }
            }
        }
    }
}

void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    int i,j,k;

    for(i=xcenter-rx; i<xcenter+rx; i++){
        for(j=ycenter-ry; j<ycenter+ry; j++){
            for(k=zcenter-rz; k<zcenter+rz; k++){
                if((pow(i-xcenter,2)/pow(rx,2)) + (pow(j-ycenter,2)/pow(ry,2)) + (pow(k-zcenter,2)/pow(rz,2)) <= 1){
                    cutVoxel(i,j,k);
                }
            }
        }
    }
}

void Sculptor::writeOFF(char *filename){
    int i=0, j=0, k=0;
    putVoxel(i,j,k);

    std::ofstream arquivo;
    int total=0;

    for(i=0; i<nz; i++){
        for(j=0; j<ny; j++){
            for(k=0; k<nx; k++){
                if(v[i][j][k].isOn==true){
                    total++;
                }
            }
        }
    }

    int NVertices=total*8, NFaces=total*6;
    arquivo.open(filename);

    if (!arquivo.is_open()){
       std::cout<< "Não foi possivel gravar no arquivo";
     exit(1);
    }
    arquivo << "OFF \n";

    arquivo << NVertices << " " << NFaces << " " << 0 << std::endl;

    for(int i=0; i<nz; i++){
        for(int j=0; j<ny; j++){
            for(int k=0; k<nx; k++){
                if(v[i][j][k].isOn==true){
                    arquivo << i-0.5 << " " << j+0.5 << " " << k-0.5 << std::endl
                         << i-0.5 << " " << j-0.5 << " " << k-0.5 << std::endl
                         << i+0.5 << " " << j-0.5 << " " << k-0.5 << std::endl
                         << i+0.5 << " " << j+0.5 << " " << k-0.5 << std::endl
                         << i-0.5 << " " << j+0.5 << " " << k+0.5 << std::endl
                         << i-0.5 << " " << j-0.5 << " " << k+0.5 << std::endl
                         << i+0.5 << " " << j-0.5 << " " << k+0.5 << std::endl
                         << i+0.5 << " " << j+0.5 << " " << k+0.5 << std::endl;
                 }
            }
        }
    }

    int faces=0;
    //Faces do cubo sendo inseridos no arquivo OFF
    for(int i=0; i<nx; i++){
        for(int j=0; j<ny; j++){
            for(int k=0; k<nz; k++){
                if(v[i][j][k].isOn==true){
                    int vvv=faces*8;
                                       arquivo<<"4 "<<vvv<< " "<< vvv+3<<" "<< vvv+2 <<" "<< vvv+1;
                                       arquivo<<" "<< v[i][j][k].r <<" "<< v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<std::endl;
                                       arquivo<<"4 "<< vvv+4<< " "<< vvv +5<<" "<< vvv+6 <<" "<< vvv+7;
                                       arquivo<<" "<< v[i][j][k].r <<" "<< v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<std::endl;
                                       arquivo<<"4 "<< vvv<< " " << vvv+1<<" "<< vvv+5 <<" "<< vvv+4;
                                       arquivo<<" "<< v[i][j][k].r <<" "<< v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<std::endl;
                                       arquivo<<"4 "<< vvv<< " " << vvv+4<<" "<< vvv+7 <<" "<< vvv+3;
                                       arquivo<<" "<< v[i][j][k].r <<" "<< v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<std::endl;
                                       arquivo<<"4 "<< vvv+3<<" " << vvv+7<<" "<< vvv+6 <<" "<< vvv+2;
                                       arquivo<<" "<< v[i][j][k].r << " "<< v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<std::endl;
                                       arquivo<<"4 "<< vvv+1 <<" "<< vvv +2<<" "<< vvv+6 <<" "<< vvv+5;
                                       arquivo<<" "<<v[i][j][k].r << " "<< v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].a<<std::endl;
                    faces++;

                 }
            }
        }
    }

    arquivo.close();
}
