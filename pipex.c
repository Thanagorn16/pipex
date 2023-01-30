#include "pipex.h"

char    **find_path(char **envp)
{
    int i;
    char    *path;
    char    **path_env;

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
    return (path_env);
}

int main(int ac, char **av, char **envp)
{
    char    **path_env;
    char    *test_path = "/bin/ls"; //* this is the correct path for "ls". The others are fault.
    // char    *test_path2 = "/bin/ls"; 
    char    *temp_path;
    char    **cmd;
    char    *args[] = {"ls", "-l", NULL};
    int fd[2];
    int pid;

    path_env = find_path(envp);
    if (pipe == -1)
        return (1);
    pid = fork;
    if (pid < 0)
        return (2);
    if (pid == 0)
    {
        // child process
        
    }
    // *test
    // cmd = ft_split(av[1], ' '); // split command and argument to the commnad from each other
    // temp_path = ft_strjoin_path(path_env[i], cmd[0]);
    // printf("%s\n", temp_path);
    // printf("%s\n", path_env[0]);
    // execve(test_path, cmd, NULL);
    // while (path_env[i])
    // {
    //     printf("%s\n", path_env[i++]);
    // }
    
}