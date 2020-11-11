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
                putVoxel(i,j,k);
            }
        }
    }
}

void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1){
    int i,j,k;
    for(i=x0;i<x1;i++){
        for(j=y0;j<y1;j++){
            for(k=z0;k<z1;k++){
                cutVoxel(i,j,k);
                v[i][j][k].r = r;
                v[i][j][k].g = g;
                v[i][j][k].b = b;
                v[i][j][k].a = a;
            }
        }
    }

}

void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius){
    
//CABE COLOCAR UMA VERIIFCAÇÃO AQUI, EX.: CASO OS PONTOS SEJAM INVÁLIDOS (PONTOS QUE NÃO SATISFAÇAM A EQUAÇÃO DA ESFERA, AVISAR "VALORES INVÁLIDOS, POR FAVOR DIGITE NOVAMENTE")
    
    int i,j,k; // Variáveis contadores
    int distX, distY, distZ; // Variáveis que representam a distânica do centro da esfera para o ponto.
    
    for(i=0; i<nx; i++){
        distX = static_cast<float>(((i-xcenter)/radius));
        for(j=0; j<ny; j++){
            distY = static_cast<float>(((j-ycenter)/radius));
            for(k=0; k<nz; k++){
                distZ = static_cast<float>(((k-zcenter)/radius));
                
               float dist = (distX*distX) + (distY*distY) + (distZ*distZ) // Todas as distâncias somadas.
                   
                   if(dist<=1.00){
                       putVoxel(i,j,k); // Caso a distância seja menor que 1, isso significa que a equação é respeitada e os valores são coerentes, portanto é criado um Voxel no local.
                   }
            }
        }
    }
}
            
void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius){
    //Seguindo a mesma lógica do putSphere, porém agora ao invés de chamar putVoxel será chamado a função cutVoxel, para retirar um voxel.
    
    int i,j,k; // Variáveis contadores
    float distX, distY, distZ; // Variáveis que representam a distânica do centro da esfera para o ponto.
    
    for(i=0; i<nx; i++){
        distX = static_cast<float>(((i-xcenter)/radius));
        for(j=0; j<ny; j++){
            distY = static_cast<float>(((j-ycenter)/radius));
            for(k=0; k<nz; k++){
                distZ = static_cast<float>(((k-zcenter)/radius));
                
               float dist = (distX*distX) + (distY*distY) + (distZ*distZ);
                   
                   if(dist<=1.00){
                       cutVoxel(i,j,k); // Como a distância foi menor que 1, a equação foi satisfeita, e o voxel é retirado.
                       v[i][j][k].r = r;
                       v[i][j][k].g = g;
                       v[i][j][k].b = b;
                       v[i][j][k].a = a;
                   }
            }
        }
    }
}

void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int int rx, int ry, int rz){
    //Para a função do putEllipsoid, a mesma equação da função putSphere pode ser utilizada, mas com a diferença que no cálcul das distâncias o valor dos raios em cada eixo é utilizado, ao invés de um único raio geral.
    int i,j,k; // Variáveis contadores
    float distX, distY, distZ; // Variáveis que representam a distânica do centro da esfera para o ponto.
    
    for(i=0; i<nx; i++){
        distX = static_cast<float>(((i-xcenter)/rx));
        for(j=0; j<ny; j++){
            distY = static_cast<float>(((j-ycenter)/ry));
            for(k=0; k<nz; k++){
                distZ = static_cast<float>(((k-zcenter)/rz));
                
               float dist = (distX*distX) + (distY*distY) + (distZ*distZ) // Todas as distâncias somadas.
                   
                   if(dist<=1.00){
                       putVoxel(i,j,k);
                   }
            }
        }
    }
}

void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int int rx, int ry, int rz){
    int i,j,k; // Variáveis contadores
    float distX, distY, distZ; // Variáveis que representam a distânica do centro da esfera para o ponto.
    
    for(i=0; i<nx; i++){
        distX = static_cast<float>(((i-xcenter)/rx));
        for(j=0; j<ny; j++){
            distY = static_cast<float>(((j-ycenter)/ry));
            for(k=0; k<nz; k++){
                distZ = static_cast<float>(((k-zcenter)/rz));
                
               float dist = (distX*distX) + (distY*distY) + (distZ*distZ) // Todas as distâncias somadas.
                   
                   if(dist<=1.00){
                       cutVoxel(i,j,k);
                       v[i][j][k].r = r;
                       v[i][j][k].g = g;
                       v[i][j][k].b = b;
                       v[i][j][k].a = a;
                   }
            }
        }
    }
}
