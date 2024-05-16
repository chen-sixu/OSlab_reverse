#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include <string.h>

char** parse_input(FILE *input_file,int* line_cnt)
{
    char **text = NULL;
    size_t text_size = 0;
    char *line = NULL;
    ssize_t line_len;

    while ((line_len = getline(&line, &text_size, input_file)) != -1) 
    {
        if (line[line_len - 1] == '\n') 
        {
            line[line_len - 1] = '\0';
            line_len--;
        }
        text = (char**)realloc(text, sizeof(char*) * (*line_cnt+1));
        if (text == NULL) 
        {
            fprintf(stderr, "malloc failed\n");
            free(line);
            exit(1);
        }

        text[*line_cnt] = strdup(line);
        if (text[*line_cnt] == NULL) 
        {
            fprintf(stderr, "malloc failed\n");
            for (int i = 0; i < *line_cnt; i++) 
            {
                free(text[i]);
            }
            free(text);
            free(line);
            exit(1);
        }

        (*line_cnt)++;
    }
    free(line);
    return text;


    // char** text = (char**)malloc(sizeof(char*)*100);
    // if (text == NULL)
    // {
    //     fprintf(stderr, "malloc failed\n");
    //     exit(1);
    // }
    // for (int i = 0; i < 100; i++)
    // {
    //     text[i] = (char*)malloc(sizeof(char)*100);
    //     if (text == NULL)
    //     {
    //         fprintf(stderr, "malloc failed\n");
    //         exit(1);
    //     }
    // }
    // int temp = 0;
    // while (fscanf(input_file,"%s",text[temp])!=-1)
    // {
    //     temp++;
    // }
    // *line_cnt = temp;
    // if (line_cnt == 0)
    //     exit(1);
    // return text;
}

char** reverse_text(char** text, int line_count)
{
    char** ret = (char**)malloc(sizeof(char*)*line_count);
    if(ret == NULL) 
    {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }
    for (int i = 0; i < line_count; i++) 
    {
        ret[i] = text[line_count - i - 1];
    }
    return ret;
}
void output(FILE* file, char** text, int line_count)
{
    for (int i = 0; i < line_count; ++i) 
    {
        fprintf(file, "%s\n", text[i]);
    }
}

int main(int argc,char *argv[])
{
    char *input_file_path = NULL;
    char *output_file_path = NULL;
    FILE* input_file  = stdin;
    FILE* output_file = stdout;

    if (argc == 2) //input file -> cmdline
    {
        input_file_path = argv[1]; //argv[0] is the exctable program name
    }
    if (argc ==3) //input file -> output file
    {
        input_file_path = argv[1];
        output_file_path = argv[2];
    }
    if (argc > 3) //too many arguments
    {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }

    if (input_file_path != NULL) //read from input_file
    {
        input_file = fopen(input_file_path, "r");
        if (input_file == NULL) 
        {
            fprintf(stderr, "reverse: cannot open file '%s'\n",input_file_path);
            exit(1);
        }
    }

    if (output_file_path != NULL) //write to output_file
    {
        output_file = fopen(output_file_path, "w");
        if (output_file == NULL) 
        {
            fprintf(stderr, "reverse: cannot open file '%s'\n",output_file_path);
            exit(1);
        }
    }

    if (input_file_path != NULL && output_file_path != NULL) //input is the same as output
    {
        struct stat input_file_stat, output_file_stat;
        stat(input_file_path, &input_file_stat);
        stat(output_file_path, &output_file_stat);

        if(input_file_stat.st_ino == output_file_stat.st_ino) 
        // unique for a file
        {
            fprintf(stderr, "reverse: input and output file must differ\n");
            exit(1);
        }
    }
    
    int line_cnt = 0;
    /*
    char** parse_input():return text_array
    char** reverse_text(char** text_array):return reversed text
    void output():write to command line or file
    */
    char** original_text = parse_input(input_file,&line_cnt);
    char** reversed_text = reverse_text(original_text,line_cnt);
    output(output_file,reversed_text,line_cnt);
    fclose(input_file);
    fclose(output_file);
}