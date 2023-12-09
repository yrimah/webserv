// #include <iostream>
// #include <unistd.h>
// #include <stdlib.h>
// #include <limits.h>

// int main()
// {
//     // char buff[PATH_MAX + 1];
//     char *path;
//     path = getcwd(NULL, 0);
//     if (path != NULL)
//         std::cout << path << std::endl;

//     pid_t id;

//     id = fork();
//     if (id < 0)
//         std::cerr << "Error: \n";
//     else if (id == 0)
//     {
//         std::cout << "Child proccess\n";
        
//     }
//     int i = 0;
//     while(1){i++;};
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <limits.h>

// int main( void )
// {
//     char* cwd;
//     char buff[PATH_MAX + 1];

//     cwd = getcwd( buff, PATH_MAX + 1 );
//     if( cwd != NULL ) {
//         printf( "My working directory is %s.\n", cwd );
//     }

//     return EXIT_SUCCESS;
// }

#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv, char **env)
{
    pid_t p_id;

    p_id = fork();
    if (p_id < 0)
        perror("Error: ");
    else if (p_id == 0)
    {
        execve("webserv", argv, env);
    }
    // while (1);
}