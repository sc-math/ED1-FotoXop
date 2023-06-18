#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Imagem.h"
#include "Filtros.h"

void escurecerImagem(Imagem *img){
    int v;
    printf("Digite o fator de escurecimento: ");
    scanf("%d", &v);

    if(v < 0){
        printf("Informe um valor positivo\n");
        return;
    }

    for (int h = 0; h < obtemAltura(img); h++) {
        for (int w = 0; w < obtemLargura(img); w++) {
            Pixel pixel = obtemPixel(img, h, w);
            pixel.cor[RED]   = (((int)pixel.cor[RED]   - v) >= 0 ? (pixel.cor[RED]   - v) : 0);
            pixel.cor[GREEN] = (((int)pixel.cor[GREEN] - v) >= 0 ? (pixel.cor[GREEN] - v) : 0);
            pixel.cor[BLUE]  = (((int)pixel.cor[BLUE]  - v) >= 0 ? (pixel.cor[BLUE]  - v) : 0);
            recolorePixel(img, h, w, pixel);
        }
    }
}

void clarearImagem(Imagem *img){
    //AVISO(Filtros.c: Ainda nao implementei a funcao 'clarearImagem'); //Retire esssa mensagem ao implementar a fução
    int v;
    printf("Digite o fator de clareamento: ");
    scanf("%d", &v);

    if(v < 0){
        printf("Informe um valor positivo\n");
        return;
    }

    for (int h = 0; h < obtemAltura(img); h++) {
        for (int w = 0; w < obtemLargura(img); w++) {
            Pixel pixel = obtemPixel(img, h, w);
            pixel.cor[RED]   = (((int)pixel.cor[RED]   + v) <= 255 ? (pixel.cor[RED]   + v) : 255);
            pixel.cor[GREEN] = (((int)pixel.cor[GREEN] + v) <= 255 ? (pixel.cor[GREEN] + v) : 255);
            pixel.cor[BLUE]  = (((int)pixel.cor[BLUE]  + v) <= 255 ? (pixel.cor[BLUE]  + v) : 255);
            recolorePixel(img, h, w, pixel);
        }
    }
}

void escalaDeCinzaImagem(Imagem *img){
    //AVISO(Filtros.c: Ainda nao implementei a funcao 'escalaDeCinzaImagem'); //Retire esssa mensagem ao implementar a fução
    int grey;

    for (int h = 0; h < obtemAltura(img); h++) {
        for (int w = 0; w < obtemLargura(img); w++) {
            Pixel pixel = obtemPixel(img, h, w);
            grey = (0.3 * (int)pixel.cor[RED] + 0.59 * (int)pixel.cor[GREEN] + 0.11 * (int)pixel.cor[BLUE]);
            pixel.cor[RED]   = grey;
            pixel.cor[GREEN] = grey;
            pixel.cor[BLUE]  = grey;
            recolorePixel(img, h, w, pixel);
        }
    }
}

void filtroSobel(Imagem *img){
    //AVISO(Filtros.c: Ainda nao implementei a funcao 'filtroSobel'); //Retire esssa mensagem ao implementar a fução

    /* Dicas:
     * 1) Se quiser, pode ignorar as bordas das imagens
     * 2) Para o pixel na posição (h, w), obtenha os outros 8 pixels vizinhos e aplique a matriz gx e gy
     *    em cada banda de cor do pixel. Combine o valor obtido por gx e gy e modifique o pixel de img.
     *    Lembre-se que a obtenção dos pixels deve ser a partir de uma cópia da imagem.
     * 3) Verifique se o novo valor obtido para a banda de cor é um valor válido (entre 0 e 255).
    */
    int Gy[3][3] = {
        {1, 2, 1},
        {0, 0, 0},
        {-1, -2, -1}
    };
    int Gx[3][3] = {
        {1, 0, -1},
        {2, 0, -2},
        {1, 0, -1}
    };
    int Ry = 0;
    int Rx = 0;
    Imagem *CopiaGY = copiaImagem(img);
    Pixel pixel;


    for(int k = 0; k < 3; k++){
        for (int a = 1; a < obtemAltura(img)-1; a++) {
            for (int l = 1; l < obtemLargura(img)-1; l++) {
                //primeira coluna GY
                pixel = obtemPixel(CopiaGY, a-1, l-1);
                Ry = (int)pixel.cor[k] * Gy[0][0];
                pixel = obtemPixel(CopiaGY, a+1, l-1);
                Ry = Ry + ((int)pixel.cor[k] * Gy[2][0]);
                //segunda coluna GY
                pixel = obtemPixel(CopiaGY, a-1, l);
                Ry = Ry + ((int)pixel.cor[k] * Gy[0][1]);
                pixel = obtemPixel(CopiaGY, a+1, l);
                Ry = Ry + ((int)pixel.cor[k] * Gy[2][1]);
                //terceira coluna GY
                pixel = obtemPixel(CopiaGY, a-1, l+1);
                Ry = Ry + ((int)pixel.cor[k] * Gy[0][2]);
                pixel = obtemPixel(CopiaGY, a+1, l+1);
                Ry = Ry + ((int)pixel.cor[k] * Gy[2][2]);
                //primeira coluna GX
                pixel = obtemPixel(CopiaGY, a-1, l-1);
                Rx = (int)pixel.cor[k] * Gx[0][0];
                pixel = obtemPixel(CopiaGY, a, l-1);
                Rx += (int)pixel.cor[k] * Gx[1][0];
                pixel = obtemPixel(CopiaGY, a+1, l-1);
                Rx += (int)pixel.cor[k] * Gx[2][0];
                //terceira coluna GX
                pixel = obtemPixel(CopiaGY, a-1, l+1);
                Rx += (int)pixel.cor[k] * Gx[0][2];
                pixel = obtemPixel(CopiaGY, a, l+1);
                Rx += (int)pixel.cor[k] * Gx[1][2];
                pixel = obtemPixel(CopiaGY, a+1, l+1);
                Rx += (int)pixel.cor[k] * Gx[2][2];
                if(Ry < 0){
                    Ry = 0;
                }
                if(Rx < 0){
                    Rx = 0;
                }
                if(Ry > 255){
                    Ry = 255;
                }
                if(Rx > 255){
                    Rx = 255;
                }

                pixel.cor[k] = (Byte)(Ry + Rx)/2;
                mudaUmaCor(img, a, l, pixel, k);
            }
        }
    }
    liberaImagem(CopiaGY);
}

void deteccaoBordasLaplace(Imagem *img) {
    //AVISO(Filtros.c: Ainda nao implementei a funcao 'deteccaoBordasLaplace'); //Retire esssa mensagem ao implementar a fução

    /* Siga as mesmas dicas do filtro de Sobel */
    int LP[3][3] = {
        {0, -1, 0},
        {-1, 4, -1},
        {0, -1, 0}
    };
    int Res = 0;
    Imagem *CopiaGY = copiaImagem(img);
    Pixel pixel;


    for(int k = 0; k < 3; k++){
        for (int a = 1; a < obtemAltura(img)-1; a++) {
            for (int l = 1; l < obtemLargura(img)-1; l++) {
                //primeira coluna
                pixel = obtemPixel(CopiaGY, a-1, l-1);
                Res = (int)pixel.cor[k] * LP[0][0];
                pixel = obtemPixel(CopiaGY, a, l-1);
                Res = Res + ((int)pixel.cor[k] * LP[1][0]);
                pixel = obtemPixel(CopiaGY, a+1, l-1);
                Res = Res + ((int)pixel.cor[k] * LP[2][0]);
                //segunda coluna
                pixel = obtemPixel(CopiaGY, a-1, l);
                Res = Res + ((int)pixel.cor[k] * LP[0][1]);
                pixel = obtemPixel(CopiaGY, a, l);
                Res = Res + ((int)pixel.cor[k] * LP[1][1]);
                pixel = obtemPixel(CopiaGY, a+1, l);
                Res = Res + ((int)pixel.cor[k] * LP[2][1]);
                //terceira coluna
                pixel = obtemPixel(CopiaGY, a-1, l+1);
                Res = Res + ((int)pixel.cor[k] * LP[0][2]);
                pixel = obtemPixel(CopiaGY, a, l+1);
                Res = Res + ((int)pixel.cor[k] * LP[1][2]);
                pixel = obtemPixel(CopiaGY, a+1, l+1);
                Res = Res + ((int)pixel.cor[k] * LP[2][2]);

                if(Res < 0){
                    Res = 0;
                }
                if(Res > 255){
                    Res = 255;
                }

                pixel.cor[k] = (Byte)Res;
                mudaUmaCor(img, a, l, pixel, k);
            }
        }
    }
    liberaImagem(CopiaGY);
}

void meuFiltro(Imagem *img){
    //AVISO(Filtros.c: Ainda nao implementei a funcao 'meuFiltro'); //Retire esssa mensagem ao implementar a fução
    int aux1, aux2 ;
    for (int h = 0; h < obtemAltura(img); h++) {
        for (int w = 0; w < obtemLargura(img); w++) {
            Pixel pixel = obtemPixel(img, h, w);

            aux1 = pixel.cor[RED];
            aux2 = pixel.cor[BLUE];

            pixel.cor[RED]   = pixel.cor[GREEN];
            pixel.cor[BLUE] = aux1;
            pixel.cor[GREEN] = aux2;
            recolorePixel(img, h, w, pixel);
        }
    }
}

