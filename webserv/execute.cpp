#include"webserv.hpp"

t_master executePHP(const std::string &request, char **env){
	t_master ris;
	int fd_out=dup(STDOUT_FILENO);
	int fd[2];
    if (pipe(fd)==-1){
        std::cout<<"Marshal: pipe"<<std::endl;
        ris.status=-1;
		ris.content="Pipe error";
    }
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	close(fd[0]);
	pid_t	pid=fork();
	if (pid==-1){
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
		std::cout<<"Marshal: Fork error"<<std::endl;
		ris.status=-1;
		ris.content="Fork error";
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
		int status;
		while (waitpid(-1, &status, 0) > 0){;}
		if(status==0){
			ssize_t bytesRead;
			char buffer[BUFFER_SIZE];
			while ((bytesRead = read(fd[0], buffer, BUFFER_SIZE)) > 0){
				ris.content.append(buffer, bytesRead);
			}
			ris.status=0;
		}else{
			ris.status=-1;
			ris.content="Execute error";
		}
	}
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	return ris;
}
