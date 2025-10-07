#include <stdio.h>
#include <stdlib.h>
int read_file_to_buffer(const char *path, char **out_buf, size_t *out_len)
{
    FILE *fp =fopen(path,"r");  
    if (fp == NULL) 
    {
        printf("Error: cannot open \n", path);
        return 0;
    }
    //MOVING END OF THE FILE
    fseek(fp, 0, SEEK_END);
    long size=ftell(fp);
    rewind(fp);  
    char *buffer=malloc(size + 1);  //ALLOCATING MEMORY
    if (buffer==NULL) 
    {
        printf("Error: memory not allocated\n");
        fclose(fp);
        return 0;
    }
    //READ FILE CONTENT FROM BUFFER
    size_t bytesRead=fread(buffer, 1, size, fp);
    buffer[bytesRead]='\0';  // add null character at the end
    fclose(fp);

    *out_buf=buffer;
    if (out_len)
    {
        *out_len=bytesRead;
    }
    return 1; 
}
void free_buffer(char *buf)
{
    if (buf != NULL)
    {
        free(buf);
    }
}