/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mich <lde-mich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:09:51 by lde-mich          #+#    #+#             */
/*   Updated: 2024/04/30 00:29:48 by lde-mich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cgi.hpp"


Cgi::Cgi()
{
	
}

Cgi::~Cgi()
{
	
}

// funzione che trova l'estensione del programma passato come argomento
std::string Cgi::getFileExtension(const std::string& fileName)
{
    size_t dotPosition = fileName.find_last_of(".");
    if (dotPosition != std::string::npos)
        return fileName.substr(dotPosition + 1);

    return ""; // Se non c'è estensione
}


int Cgi::exeScript(std::string path)
{
    pid_t pid = fork();

    std::string fileExtension = getFileExtension(path);
        
    //nullptr
    const char* args[] = {path.c_str(), NULL};
    
    clock_t start_time = clock();
    
    if (pid == -1)
        throw Cgi::ForkException();
    else if (pid == 0)
    {
            
        //mettere i permessi per eseguire il file 
        int result = chmod(path.c_str(), S_IRWXU);
        if (result != 0)
            throw Cgi::PermissionFileException();
        
        int outputFile = open("temp.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
        if (outputFile == -1)
            throw Cgi::OpenFileException();
        
        // Duplica il file descriptor per stdout
        if (dup2(outputFile, STDOUT_FILENO) == -1)
            throw Cgi::DupException();
        
        // Chiudi il file descriptor superfluo
        close(outputFile);
        
        if (fileExtension == "py")
            execlp("python3", "python3", path.c_str(), NULL);
        else if (fileExtension == "sh" || fileExtension == "out")
            execvp(path.c_str(), const_cast<char**>(args));
        
        throw Cgi::ExecuteFileException();
            
    }
    
    //gestisce quanto tempo ci sta mettendo il processo figlio ad eseguire il file se supera il tempo(in secondi) definito nella funzione, stoppa il processo
    alarm(TIMEOUT);
    //aspetta che finisce il processo figlio per poi continuare ad eseguire il processo padre
    waitpid(pid, NULL, 0);
    //reset del tempo
    alarm(0);
    
    clock_t end_time = clock();
    double time = (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000000; //millisecondi * 1000 -- microsecondi * 1000000
    std::cout << "Fine programma in → " << time << " us" << std::endl;
    
    return (0);
}




//DOC sulla funzione "open"

// Apri un file per l'output
// O_WRONLY: Questo flag indica che il file deve essere aperto solo in modalità scrittura.
// Il file verrà aperto per la scrittura solamente, quindi non sarà possibile leggere da esso.

// O_CREAT: Questo flag specifica che se il file non esiste, deve essere creato. Se il file esiste già,
// questa opzione non ha effetto.

// O_TRUNC: Questo flag indica che, se il file esiste già e viene aperto in modalità scrittura,
// il suo contenuto deve essere troncato (azzerato) prima di scrivere in esso. In altre parole,
// il file viene "svuotato".

// S_IRWXU: Questo non è un flag per la funzione open(), ma è un argomento separato che indica i permessi di accesso
// per il file che verrà creato. In questo caso, S_IRWXU indica che il proprietario del file (utente) avrà i permessi
// di lettura, scrittura e esecuzione sul file.
