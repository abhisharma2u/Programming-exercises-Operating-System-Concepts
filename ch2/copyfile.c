#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#define BUF_SIZE 8192

int main() {
 
    int input_fd, output_fd;    /* Input and output file descriptors */
    ssize_t ret_in, ret_out;    /* Number of bytes returned by read() and write() */
    char buffer[BUF_SIZE];      /* Character buffer */
    char *input=NULL;
    char *output=NULL;
    size_t len = 0;
    size_t len1 = 0;

/*asking for input file*/    
    printf("Enter the input filename: \n");
    getline(&input, &len, stdin);

/*stripping off the last character of input string as null character */
    int size = strlen(input); //Total size of string
    input[size-1] = '\0';
    
/* Create input file descriptor */
   input_fd = open (input, O_RDONLY);
    if (input_fd == -1) {
          perror ("opening input file");
        return 2;
   }
  
/*asking for output filename*/  
  printf("Enter the output filename: \n");
  getline(&output, &len1, stdin);

/*stripping off the last character of input string */
    int size1 = strlen(output); //Total size of string
    output[size1-1] = '\0';
   
/* Create output file descriptor */
    output_fd = open(output, O_WRONLY | O_CREAT, 0644);
    if(output_fd == -1){
        perror("opening output file");
        return 3;
    }

/* Copy process */
    while((ret_in = read (input_fd, &buffer, BUF_SIZE)) > 0){
            ret_out = write (output_fd, &buffer, (ssize_t) ret_in);
            if(ret_out != ret_in){
                /* Write error */
                perror("write");
                return 4;
            }
printf("file %s copied successfully into file %s\n",input,output);
    }
/* Close file descriptors */
    close (input_fd);
    close (output_fd);
    return (EXIT_SUCCESS);
}
