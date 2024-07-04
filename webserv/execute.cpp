#include"webserv.hpp"

std::string executePHP(const std::string &request, char **env){
	int fd_out=dup(STDOUT_FILENO);
	std::string output="";
	int fd[2];
    if (pipe(fd)==-1){
        std::cout<<"Marshal: pipe"<<std::endl;
        exit(-1);
    }
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	close(fd[0]);
	pid_t	pid=fork();
	if (pid==-1){
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
		std::cout<<"Marshal: Fork error"<<std::endl;
		exit(-1);
	}
	if (pid == 0){
		std::vector<const char *> args;
		args.push_back("php-cgi");
		args.push_back("-f");
		args.push_back(request.c_str());
		args.push_back(NULL);
		execve("/usr/bin/php-cgi", const_cast<char **>(args.data()), env);
		// execve("/usr/local/bin/php-cgi", const_cast<char **>(args.data()), env);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
		std::cout<<"Marshal: Execute error"<<std::endl;
		exit(-1);
	}else{
		waitpid(pid, NULL, 0);
		ssize_t bytesRead;
		char buffer[BUFFER_SIZE];
        while ((bytesRead = read(fd[0], buffer, BUFFER_SIZE)) > 0){
	    	output.append(buffer, bytesRead);
		}
	}
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	return output;
}
