#include <gba.h>
extern int sinus[];
void createpal()
{
    int i=0;
    for(;i<32;i++)
    {
        pal_bg_mem[i+0*32]=RGB15(31-i,i,0);
        pal_bg_mem[i+1*32]=RGB15(0,31-i,i);
        pal_bg_mem[i+2*32]=RGB15(i,0,31-i);
        pal_bg_mem[i+3*32]=RGB15(31-i,i,i);
        
        pal_bg_mem[i+4*32]=RGB15(i,31,31-i);
        pal_bg_mem[i+5*32]=RGB15(31,31-i,0);
        pal_bg_mem[i+6*32]=RGB15(31-i,i,0);
        pal_bg_mem[i+7*32]=RGB15(i,31-i,0);
    }
}

INLINE void palrotate()
{
    u32* dst=(u32*)pal_bg_mem;
    int i=0,temp=*dst;
    for(;i<127;i++)
    {
        *(dst+i)=*(dst+i+1);
    }
    *(dst+127)=temp;
}

void __attribute__((section(".iwram"),long_call)) plasma()
{
    int x,y;
    int a=0;
    int b=32;
    int c=64;
    int d=128;
    int value;
    u32 color;
    u32 *dst;
    while(1)
    {
        dst=vid_screen.pixel;
        for(y=0;y<SCREEN_HEIGHT;y++)
        {
            value=*(sinus+((y+a)&255))+*(sinus+((y-d)&255));
            for(x=0;x<SCREEN_WIDTH;x++)
            {
                color=value+*(sinus+((x-b)&255))+*(sinus+((c+x)&255))+*(sinus+((y+x)&255));
                x++;
                color=color|(value+*(sinus+((x-b)&255))+*(sinus+((c+x)&255))+*(sinus+((y+x)&255))<<8);
                x++;
                color=color|(value+*(sinus+((x-b)&255))+*(sinus+((c+x)&255))+*(sinus+((y+x)&255))<<16);
                x++;
                color=color|(value+*(sinus+((x-b)&255))+*(sinus+((c+x)&255))+*(sinus+((y+x)&255))<<24);
                *dst++=color;
            }
        }
        a++;
        b++;
        b++;
        
        c++;
        c++;
        c++;
        
        d++;
        d++;
        d++;
        d++;
        
        vid_vsync();
        palrotate();
        vid_flip();   
    }
}

int main()
{
    m4_init();
    createpal();
    plasma();

    return 0;
}


