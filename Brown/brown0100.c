#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int ResH;
int ResV;

char * * tab;

void init_tab(void)
{
 int h, v;

 tab = (char * *) malloc(ResH*sizeof(char *));

 for (h=0; h<ResH; h++)
  {
   tab[h] = (char *) malloc(ResV * sizeof(char));
  } 

 for (h=0; h<ResH; h++)
  {
   for (v=0; v<ResV; v++)
    {
     tab[h][v] = ' ';
    }   
  } 

 for (h=0; h<ResH; h++)
  tab[h][0] = (char) ('A'+h%26);
}

char collision(int hc, int vc)
{
 int i,j;
 int h,v;
 char last_c;

 last_c = ' ';
 for (i=-1; i<=1; i+=1)
  {
   h = hc+i;
   if (h<0)
    h = h+ResH;
   if (h>=ResH)
    h = h-ResH;
   for (j=-1; j<=1; j+=1)
    {
     v = vc+j;
     if ( (v>=0) && (v<ResV))
      if (tab[h][v]!=' ')
       last_c = tab[h][v];
    }
  }
 return(last_c);
}

void go(void)
{
 int encore, full;
 int h,v;
 char c;

 printf("debut de go\n"); 
 full = 0;
 while (!full)
  {
   v = ResV-1;
   h = (int) floor(drand48() * ResH);
   encore = 1;
   while (encore)
    {
     c = collision(h,v);
     encore = (c==' ');
     if (encore)
      {
       if (drand48()<0.5)
        h--;
       else
        h++;
       if (h<0)
        h = ResH-1;
       if (h>=ResH)
        h=0; 
       if (drand48()<0.51)
        v--;
       else
        v++;
       if (v>=ResV)
        v= ResV-1;
      }
    }
   tab[h][v] = c;
   full = (v >= (ResV - 2));
  }
}

void dump(void)
{
 int h, v;
 for (v=ResV-1; v>=0; v--)
  {
   printf("\n");
   for (h=0; h<ResH; h++)
    {
     printf("%c",tab[h][v]);
    }   
  } 
 printf("\n");
}

int main(int argc, char * * argv)
{
 int seed;

 if (argc == 1)
 { 
  printf ("usage: %s graine resolution_horizontale resolution_verticale\n",argv[0]);
  printf ("par exemple %s 12345 700 220\n",argv[0]);
 }

 seed = 90466;
 if (argc>1)
  sscanf(argv[1],"%i",&seed);
 srand48(seed);

 ResH=182;
 ResV=60;

 if (argc>2)
  sscanf(argv[2],"%i",&ResH);

 if (argc>3)
  sscanf(argv[3],"%i",&ResV);

 init_tab();
 go();
 dump();
 return(0);
}
