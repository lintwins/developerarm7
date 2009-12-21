/*******************************************************************************
  JPG2Data.c:
  Convert jpg data to a head file.
  Norman,2009-12-21
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/******************************************************************************/
int main(int argc,char **argv)
{
  int i,fsize;
  FILE *fp;
  unsigned char *DataBuf;
  char Prefix[16] = "jpg";

  if(argc < 2)
  {
    printf("Useage %s *.jpg [Prefix]\n",argv[0]);
    return 1;
  }

  if(argc > 2) // copy data prifix
    strcpy(Prefix,argv[2]);

  fp = fopen(argv[1],"rb");
  if(fp == NULL)
  {
    printf("Open file \"%s\" error\n",argv[1]);
    return 2;
  }

  /* Get file size */
  fseek(fp,0,SEEK_END);
  fsize = ftell(fp);
  fseek(fp,0,SEEK_SET);

  DataBuf = (unsigned char *) malloc (fsize * sizeof(unsigned char));
  if(!DataBuf)
  {
    printf("Error:could not allocate memory\n");
    fclose(fp);
    return 3;
  }

  if(fread(DataBuf,1,fsize,fp) != fsize)
  {
    printf("Error: could not read Bin file .\n");
    fclose(fp);
    free(DataBuf);
    return 4;
  }
  
  fclose(fp);

  /* Write head file */
  printf("/*******************************************************************************\n");
  printf("%s.h:\n      data of a jpg file.\n",Prefix);
  printf("*******************************************************************************/\n");

  printf("\n#ifndef _%s_GLOBAL_\n",_strupr(_strdup(Prefix)));
  printf("extern const unsigned int %s_size;\n",Prefix);
  printf("extern const unsigned char %s_data[];\n",Prefix);
  printf("#else\n");
  printf("const unsigned int %s_size = 0x%x;\n",Prefix,fsize);
  printf("const unsigned char %s_data[] =\n{",Prefix);
  for(i=0;i<fsize;i++)
  {
    if(i%32 == 0)
      printf("\n  ");
    printf("0x%02x",DataBuf[i]);
    if(i != fsize - 1)
      printf(",");
  }
  printf("\n};\n");
  printf("\n#endif\n");

  free(DataBuf);
  return 0;
}
