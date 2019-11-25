#ifndef __puts_h_
#define __puts_h_
void Graph_SetPixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
void Graph_WriteGraph (SDL_Surface * surface,int x,int y,int w,int h,unsigned char * pimage,Uint32 color);
void Font_DrawChar (SDL_Surface * surface,int x,int y,unsigned char c1,unsigned char c2,Uint32 color);
int Font_GetDrawWidth (const char * str);
void Font_DrawString (SDL_Surface * surface,int x,int y,const char * str,Uint32 color);
void put_chs(SDL_Surface * surface,int x,int y,const char * str);
#endif