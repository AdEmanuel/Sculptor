#include "sculptor.h"


Sculptor::Sculptor(int _nx, int _ny, int _nz){
    // aloca uma matriz voxel com tamanho especificado.
    nx = _nx;
    ny = _ny; 
    nz = _nz;
}

 void Sculptor::setColor(float r, float g, float b, float alpha){
    v[nx][ny][nz].r = r; //componente correspondente à cor vermelha.
    v[nx][ny][nz].g = g; //componente correspondente à cor verde.
    v[nx][ny][nz].b = b; //componente correspondente à cor azul.
    v[nx][ny][nz].a = alpha; //componente correspondente à opacidade.
 }

 void Sculptor::putVoxel(int x, int y, int z){
    v[x][y][z].isOn = true; //o voxel será exibido no escultor.
 }

void Sculptor::cutVoxel(int x, int y, int z){
    v[x][y][z].isOn = false;//o voxel não será exibido no escultor.
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



