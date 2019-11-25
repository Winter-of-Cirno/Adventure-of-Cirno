#include "SDL/SDL.h" 
#define isChs(c)    ((c) & 0x80)
#define FONT_WIDTH      12
#define FONT_HEIGHT     12
void Font_DrawString    (SDL_Surface * surface,int x,int y,const char * str,Uint32 color);
void Font_DrawChar      (SDL_Surface * surface,int x,int y,unsigned char c1,unsigned char c2,Uint32 color);
void Font_Init          ();
void Font_Close			(void);
int  Font_GetDrawWidth  (const char *);
#define FONT_12_SIZE    (16*12/8)
extern FILE * fileFont;
void Graph_SetPixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;

    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = (Uint8)pixel;
        break;

    case 2:
        *(Uint16 *)p = (Uint16)pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (Uint8)((pixel >> 16) & 0xff);
            p[1] = (Uint8)((pixel >> 8) & 0xff);
            p[2] = (Uint8)(pixel & 0xff);
        } else {
            p[0] = (Uint8)(pixel & 0xff);
            p[1] = (Uint8)((pixel >> 8) & 0xff);
            p[2] = (Uint8)((pixel >> 16) & 0xff);
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}

void Graph_WriteGraph (SDL_Surface * surface,int x,int y,int w,int h,unsigned char * pimage,Uint32 color) {
    unsigned char p;
    int i,j,k,pixel,rx=0,ry=0;
    int iwidth = w/8 + (w % 8 ? 1:0);

    for (i = 0;i < h; ++i, pimage += iwidth) {
        ry = y + i;
        if (ry >= 240)
            return;
        else if (ry < 0)
            continue;
        for (j = 0;j < iwidth; ++j) {
            p = pimage[j];
            for (k = 0;k < 8; ++k) {
                rx = x + (8 - k) + (j << 3); /* j * 8 */
                if (rx < 0 || rx > 320) 
                    continue;
                pixel = p & 1;
                p >>= 1;
                if (pixel) {
                    Graph_SetPixel(surface,rx,ry,color);
                }
            }
        }
    }
}
 
 
void Font_DrawChar (SDL_Surface * surface,int x,int y,unsigned char c1,unsigned char c2,Uint32 color) {
    
    
    
    unsigned char mat[FONT_12_SIZE];

    fseek(fileFont,(94*(c1-0xa1)+(c2-0xa1))*FONT_12_SIZE,SEEK_SET);
    fread(mat,FONT_12_SIZE,1,fileFont);
    Graph_WriteGraph(surface,x,y,12,12,mat,color);
    
   
}

int Font_GetDrawWidth (const char * str) {
    int width = 0;
    while (*str) {
        if (isChs(*str)) {
            str++,str++;
            width += FONT_WIDTH + 1;
        }
        else {
            str++;
            width += FONT_WIDTH;
            continue;
        }
    }
    return width;
}

void Font_DrawString (SDL_Surface * surface,int x,int y,const char * str,Uint32 color) {
    while (*str) {
        if (isChs(*str)) {
            Font_DrawChar(surface,x,y,*str,*(str+1),color);
            str++,str++;
            x += FONT_WIDTH + 1;
        }
        else {
            unsigned char c1,c2;
            c1 = 0xA3;
            c2 = 0x80 + *str;
            Font_DrawChar(surface,x,y,c1,c2,color);
            x += FONT_WIDTH;
            str++;
        }
    }
}

void put_chs(SDL_Surface * surface,int x,int y,const char * str)
{
	Font_DrawString (surface,x,y,str,SDL_MapRGB(surface->format,0,0,0));
}