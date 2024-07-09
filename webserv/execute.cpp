#include"webserv.hpp"

void handle_alarm(int sig){
	(void)sig;
	exit(-1);
}

t_master executePHP(const std::string &request, char **env, std::string &get_query, std::string &post_query) {
    t_master ris;
    int fd[2];

    if (pipe(fd) == -1) {
        std::cout << "Marshal: pipe" << std::endl;
        ris.status = -1;
        ris.content = "Pipe error";
        return ris;
    }
    pid_t pid = fork();
    if (pid == -1) {
        close(fd[0]);
        close(fd[1]);
        std::cout << "Marshal: Fork error" << std::endl;
        ris.status = -1;
        ris.content = "Fork error";
        return ris;
    }
    if(pid == 0){
        struct sigaction sa;
        sa.sa_handler = handle_alarm;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;
        sigaction(SIGALRM, &sa, NULL);
        alarm(EXECUTION_TIME_LIMIT);
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        std::vector<const char *> args;
        args.push_back("php-cgi");
        args.push_back("-q");
        args.push_back(request.c_str());
        args.push_back(get_query.c_str());
        args.push_back(NULL);
		(void)post_query;
		std::vector<const char *> envs;
        std::cout<<"Request: "<<request<<std::endl;
		for (size_t i=0;env[i]!=NULL;i++)
	        envs.push_back(env[i]);

        if(!post_query.empty()){
            std::ostringstream convertitore;
            convertitore << "CONTENT_LENGTH=" << post_query.size();
            envs.push_back((convertitore.str()).c_str());

            envs.push_back(("SCRIPT_FILENAME="+request).c_str());
            envs.push_back("AUTH_TYPE=".c_str());
            envs.push_back(("SCRIPT_NAME="+request).c_str());
            envs.push_back(("REQUEST_URI="+request).c_str());
            envs.push_back(("PATH_INFO="+request).c_str());
            envs.push_back(("PATH_TRANSLATED=").c_str());
            envs.push_back(("QUERY_STRING="+get_query).c_str());
            envs.push_back("CONTENT_TYPE=application/x-www-form-urlencoded");
            envs.push_back("REQUEST_METHOD=POST");
            envs.push_back("GATEWAY_INTERFACE=CGI/1.1");
            envs.push_back("SERVER_PROTOCOL=HTTP/1.1");
            envs.push_back("SERVER_SOFTWARE=webserv/1.0");
            envs.push_back("REDIRECT_STATUS=false");
            envs.push_back("REMOTE_USER=");
            envs.push_back("REMOTE_IDENT=");
            envs.push_back("REMOTE_HOST=");
            envs.push_back("REMOTE_ADDR=");
            envs.push_back("SERVER_NAME=");
            envs.push_back("SERVER_PORT=");
        }
        envs.push_back(NULL);
        execve("/usr/bin/php-cgi", const_cast<char **>(args.data()), const_cast<char **>(envs.data()));
        std::cout<<"Marshal: Execute error"<<std::endl;
        exit(-1);
    }else{
        close(fd[1]);
        int status;
        while (waitpid(pid, &status, 0) > 0) {
            if (WIFSIGNALED(status) && WTERMSIG(status) == SIGALRM) {
                ris.status = -1;
                ris.content = "Execution timed out";
                break;
            }
        }
        alarm(0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            ssize_t bytesRead;
            char buffer[BUFFER_SIZE];
            while ((bytesRead = read(fd[0], buffer, BUFFER_SIZE)) > 0)
                ris.content.append(buffer, bytesRead);
            ris.status = 0;
        }else if(!(WIFSIGNALED(status) && WTERMSIG(status) == SIGALRM)){
            ris.status = -1;
            ris.content = "Execute error: <br>";
            ssize_t bytesRead;
            char buffer[BUFFER_SIZE];
            while ((bytesRead = read(fd[0], buffer, BUFFER_SIZE)) > 0) {
                ris.content.append(buffer, bytesRead);
            }
        }
        close(fd[0]);
    }
    return ris;
}

t_master executePython(const std::string &request, char **env) {
    t_master ris;
    int fd[2];

    if (pipe(fd) == -1) {
        std::cout << "Marshal: pipe" << std::endl;
        ris.status = -1;
        ris.content = "Pipe error";
        return ris;
    }
    pid_t pid = fork();
    if (pid == -1) {
        close(fd[0]);
        close(fd[1]);
        std::cout << "Marshal: Fork error" << std::endl;
        ris.status = -1;
        ris.content = "Fork error";
        return ris;
    }
    if(pid == 0){
        struct sigaction sa;
        sa.sa_handler = handle_alarm;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;
        sigaction(SIGALRM, &sa, NULL);
        alarm(EXECUTION_TIME_LIMIT);
        close(fd[0]);
        dup2(fd[1], STDERR_FILENO);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        std::vector<const char *> args;
        args.push_back("python3");
        args.push_back(request.c_str());
        args.push_back(NULL);
        execve("/usr/bin/python3", const_cast<char **>(args.data()), env);
        std::cout<<"Marshal: Execute error"<<std::endl;
        exit(-1);
    }else{
        close(fd[1]);
        int status;
        while (waitpid(pid, &status, 0) > 0) {
            if (WIFSIGNALED(status) && WTERMSIG(status) == SIGALRM) {
                ris.status = -1;
                ris.content = "Execution timed out";
                break;
            }
        }
        alarm(0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            ssize_t bytesRead;
            char buffer[BUFFER_SIZE];
            while ((bytesRead = read(fd[0], buffer, BUFFER_SIZE)) > 0)
                ris.content.append(buffer, bytesRead);
            ris.status = 0;
        }else if(!(WIFSIGNALED(status) && WTERMSIG(status) == SIGALRM)){
            ris.status = -1;
            ris.content = "Execute error: <br>";
            ssize_t bytesRead;
            char buffer[BUFFER_SIZE];
            while ((bytesRead = read(fd[0], buffer, BUFFER_SIZE)) > 0) {
                ris.content.append(buffer, bytesRead);
            }
        }
        close(fd[0]);
    }
    return ris;
}

t_master executeShell(const std::string &request, char **env) {
    t_master ris;
    int fd[2];

    if (pipe(fd) == -1) {
        std::cout << "Marshal: pipe" << std::endl;
        ris.status = -1;
        ris.content = "Pipe error";
        return ris;
    }
    pid_t pid = fork();
    if (pid == -1) {
        close(fd[0]);
        close(fd[1]);
        std::cout << "Marshal: Fork error" << std::endl;
        ris.status = -1;
        ris.content = "Fork error";
        return ris;
    }
    if(pid == 0){
        struct sigaction sa;
        sa.sa_handler = handle_alarm;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;
        sigaction(SIGALRM, &sa, NULL);
        alarm(EXECUTION_TIME_LIMIT);
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        std::vector<const char *> args;
        args.push_back("bash");
        args.push_back(request.c_str());
        args.push_back(NULL);
        execve("/bin/bash", const_cast<char **>(args.data()), env);
        std::cout<<"Marshal: Execute error"<<std::endl;
        exit(-1);
    }else{
        close(fd[1]);
        int status;
        while (waitpid(pid, &status, 0) > 0) {
            if (WIFSIGNALED(status) && WTERMSIG(status) == SIGALRM) {
                ris.status = -1;
                ris.content = "Execution timed out";
                break;
            }
        }
        alarm(0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            ssize_t bytesRead;
            char buffer[BUFFER_SIZE];
            while ((bytesRead = read(fd[0], buffer, BUFFER_SIZE)) > 0)
                ris.content.append(buffer, bytesRead);
            ris.status = 0;
        }else if(!(WIFSIGNALED(status) && WTERMSIG(status) == SIGALRM)){
            ris.status = -1;
            ris.content = "Execute error: <br>";
            ssize_t bytesRead;
            char buffer[BUFFER_SIZE];
            while ((bytesRead = read(fd[0], buffer, BUFFER_SIZE)) > 0) {
                ris.content.append(buffer, bytesRead);
            }
        }
        close(fd[0]);
    }
    return ris;
}