#include<stdio.h>
#include <cstdlib>
#include<sys/stat.h>

char** reverse_text()
{

}
char** parse_input()
{

}
void output()
{

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
    char** reverse_text(char** text_array):return reversed text
    char** parse_input():return text_array
    void output():write to command line or file
    */
    char** original_text = parse_input();

}