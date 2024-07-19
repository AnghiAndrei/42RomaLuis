#include"webserv.hpp"

void handle_alarm(int sig){
	(void)sig;
	kill(-1,SIGKILL);
}

t_master execute(std::string &locate, int fdc, server &server, const std::string &request, char **env, std::string &get_query, std::string &post_query) {
    t_master ris;
    int read_fd[2];
    int write_fd[2];

    if (pipe(read_fd) == -1 || pipe(write_fd) == -1) {
        std::cout << "Marshal: pipe" << std::endl;
        ris.status = -1;
        ris.content = "Execute error: <br>Pipe error";
        return ris;
    }
    pid_t pid = fork();
    if (pid == -1) {
        close(read_fd[0]);
        close(read_fd[1]);
        close(write_fd[0]);
        close(write_fd[1]);
        std::cout << "Marshal: Fork error" << std::endl;
        ris.status = -1;
        ris.content = "Execute error: <br>Fork error";
        return ris;
    }

    if (pid == 0){
		std::string extension = ExtensionFile(request);
		std::string cmdexe = server.locations[locate].gci[extension];

        close(write_fd[1]);
        close(read_fd[0]);
        dup2(write_fd[0], STDIN_FILENO);
        dup2(read_fd[1], STDOUT_FILENO);
        dup2(read_fd[1], STDERR_FILENO);
        close(write_fd[0]);
        close(read_fd[1]);
        signal(SIGALRM, handle_alarm);
        alarm(EXECUTION_TIME_LIMIT);
        std::vector<const char *> args;
        args.push_back(ExtractFile(cmdexe).c_str());
        args.push_back(request.c_str());
        args.push_back(NULL);

        std::vector<const char *> envs;
        for (size_t i = 0; env[i] != NULL; i++)
            envs.push_back(env[i]);

		std::ostringstream convertitore;
		convertitore << "CONTENT_LENGTH=" << post_query.size();
		envs.push_back(strdup(convertitore.str().c_str()));

		std::ostringstream convertitore2;
		convertitore2 << "SERVER_PORT=" << server.get_port();
		envs.push_back(strdup(convertitore2.str().c_str()));

		std::ostringstream convertitore3;
		convertitore3 << "REMOTE_ADDR=" << fdc;
		envs.push_back(strdup(convertitore3.str().c_str()));

		envs.push_back(strdup(("SCRIPT_FILENAME=" + request).c_str()));
		envs.push_back(strdup(("SCRIPT_NAME=" + request).c_str()));
		envs.push_back(strdup(("REQUEST_URI=" + request).c_str()));
		envs.push_back(strdup(("PATH_TRANSLATED=" + request).c_str()));
		envs.push_back(strdup(("PATH_INFO=" + request).c_str()));
		envs.push_back(strdup(("QUERY_STRING=" + get_query).c_str()));
		envs.push_back(strdup(("SERVER_NAME=" + server.get_host()).c_str()));
		envs.push_back(strdup(("REMOTE_HOST=" + server.get_host()).c_str()));
		envs.push_back(strdup("CONTENT_TYPE=application/x-www-form-urlencoded"));
		envs.push_back(strdup("REQUEST_METHOD=POST"));
		envs.push_back(strdup("GATEWAY_INTERFACE=CGI/1.1"));
		envs.push_back(strdup("SERVER_PROTOCOL=HTTP/1.1"));
		envs.push_back(strdup("SERVER_SOFTWARE=webserv/1.0"));
		envs.push_back(strdup("REDIRECT_STATUS=false"));
		envs.push_back(strdup("REMOTE_USER="));
		envs.push_back(strdup("REMOTE_IDENT="));
		envs.push_back(strdup("AUTH_TYPE="));

        envs.push_back(NULL);

        execve(cmdexe.c_str(), const_cast<char **>(args.data()), const_cast<char **>(envs.data()));
        std::cout << "Marshal: Execute error" << std::endl;
        exit(-1);
    }else{
        close(write_fd[0]);
        close(read_fd[1]);

        if (!post_query.empty())
            write(write_fd[1], post_query.c_str(), post_query.size());
        close(write_fd[1]);
        int status;
        while (waitpid(pid, &status, 0) > 0) {
            if (WIFSIGNALED(status) && WTERMSIG(status) == SIGALRM) {
                ris.status = -1;
                ris.content = "Execute error: <br>Execution timed out";
                break;
            }
        }
        alarm(0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            ssize_t bytesRead;
            char buffer[BUFFER_SIZE];
            while ((bytesRead = read(read_fd[0], buffer, BUFFER_SIZE)) > 0) {
                ris.content.append(buffer, bytesRead);
            }
            ris.status = 0;
        } else if (!(WIFSIGNALED(status) && WTERMSIG(status) == SIGALRM)) {
            ris.status = -1;
            ris.content = "Execute error: <br>";
            ssize_t bytesRead;
            char buffer[BUFFER_SIZE];
            while ((bytesRead = read(read_fd[0], buffer, BUFFER_SIZE)) > 0) {
                ris.content.append(buffer, bytesRead);
            }
        }
        close(read_fd[0]);
    }
    return ris;
}