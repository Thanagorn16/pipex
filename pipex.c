#include "pipex.h"

int main(int ac, char **av, char **envp)
{
    int i;
    char    *path;
    char    **path_env;
    // char    *path = "/bin/ls";
    char    *args[] = {"ls", "-l", NULL};

    // execve(path, args, NULL);
    // printf(envp[i]);
    i = 0;
    while (envp[i]) // get the path index
    {
        if (envp[i][0] == 'P' && envp[i][1] == 'A' 
            && envp[i][2] == 'T' && envp[i][3] == 'H')
            break;
        i++;
    }
    path = ft_strdup(envp[i]); // copy to path variable
    path_env = ft_split(path, ':'); // split them with :
    i = 0;
    path_env[i] = ft_strtrim(path_env[i], "PATH="); // trim PATH=
    while (path_env[i])
    {
        printf("%s\n", path_env[i++]);
    }
    // printf("%s\n", path);
    // printf("len:%zu\n", ft_strlen(path));
}