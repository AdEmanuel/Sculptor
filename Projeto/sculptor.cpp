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
    v[x][y][z].r = r; 
    v[x][y][z].g = g;
    v[x][y][z].b = b;
    v[x][y][z].a = a;
 }

void Sculptor::cutVoxel(int x, int y, int z){
    v[x][y][z].isOn = false;//o voxel não será exibido no escultor.
}

void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1){
    int i,j,k;
    for(i=x0;i<x1;i++){
        for(j=y0;j<y1;j++){
            for(k=z0;k<z1;k++){
                v[i][j][k].isOn = true;
                v[i][i][j].r = r;
                v[i][i][j].g = g;
                v[i][i][j].b = b;
                v[i][i][j].a = a;
            }
        }
    }
}

void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1){
    int i,j,k;
    for(i=x0;i<x1;i++){
        for(j=y0;j<y1;j++){
            for(k=z0;k<z1;k++){
                v[i][j][k].isOn = false;
                v[i][i][j].r = r;
                v[i][i][j].g = g;
                v[i][i][j].b = b;
                v[i][i][j].a = a;
            }
        }
    }

}

void Sculptor::putSphere(int xcentro, int ycentro, int zcentro, int raio){
    
//CABE COLOCAR UMA VERIIFCAÇÃO AQUI, EX.: CASO OS PONTOS SEJAM INVÁLIDOS (PONTOS QUE NÃO SATISFAÇAM A EQUAÇÃO DA ESFERA, AVISAR "VALORES INVÁLIDOS, POR FAVOR DIGITE NOVAMENTE")
    
    int i,j,k; // Variáveis contadores
    int distX, distY, distZ; // Variáveis que representam a distânica do centro da esfera para o ponto.
    
    for(i=0; i<nx; i++){
        distX = static_cast<float>(((i-xcentro)/raio));
        for(j=0; j<ny; j++){
            distY = static_cast<float>(((j-ycentro)/raio));
            for(k=0; k<nz; k++){
                distZ = static_cast<float>(((k-zcentro)/raio));
                
               float dist = (distX*distX) + (distY*distY) + (distZ*distZ) // Todas as distâncias somadas.
                   
                   if(dist<=1.00){
                       putVoxel(i,j,k); // Caso a distância seja menor que 1, isso significa que a equação é respeitada e os valores são coerentes, portanto é criado um Voxel no local.
                   }
            }
        }
    }
}
            
void Sculptor::cutSphere(int xcentro, int ycentro, int zcentro, int raio){
    //Seguindo a mesma lógica do putSphere, porém agora ao invés de chamar putVoxel será chamado a função cutVoxel, para retirar um voxel.
    
    int i,j,k; // Variáveis contadores
    int distX, distY, distZ; // Variáveis que representam a distânica do centro da esfera para o ponto.
    
    for(i=0; i<nx; i++){
        distX = static_cast<float>(((i-xcentro)/raio));
        for(j=0; j<ny; j++){
            distY = static_cast<float>(((j-ycentro)/raio));
            for(k=0; k<nz; k++){
                distZ = static_cast<float>(((k-zcentro)/raio));
                
               float dist = (distX*distX) + (distY*distY) + (distZ*distZ);
                   
                   if(dist<=1.00){
                       cutVoxel(i,j,k); // Como a distância foi menor que 1, a equação foi satisfeita, e o voxel é retirado.
                   }
            }
        }
    }
}
