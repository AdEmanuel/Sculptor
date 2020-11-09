#include "sculptor.h"


Sculptor::Sculptor(int _nx, int _ny, int _nz){
    nx = _nx;
    ny = _ny;
    nz = _nz;
}

 void Sculptor::setColor(float r, float g, float b, float alpha){
    v[nx][ny][nz].r = r;
    v[nx][ny][nz].g = g;
    v[nx][ny][nz].b = b;
    v[nx][ny][nz].a = alpha;
 }

 void Sculptor::putVoxel(int x, int y, int z){
    v[x][y][z].isOn = true;
 }

void Sculptor::cutVoxel(int x, int y, int z){
    v[x][y][z].isOn = false;
}

void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1){
    int i,j,k;
    for(i=x0;i<x1;i++){
        for(j=y0;j<y1;j++){
            for(k=z0;k<z1;k++){
                //a ideia seria atribuir novamente os métodos set color e o putVoxel para iniciar a caixa. O problema é como definir a entidade caixa.
            }
        }
    }
}



