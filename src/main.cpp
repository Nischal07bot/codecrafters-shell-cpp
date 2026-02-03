#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sstream>
#include <sys/wait.h>
#define BUFFER_SIZE 1024
int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  //TODO: Uncomment the code below to pass the first stage
  std::vector<std::string> builtin={"exit","echo","type","pwd","cd"};
  while(true){
    start:std::cout << "$ ";
  
    std::string command;
    std::getline(std::cin, command);
    if(command == "exit") return 0;
    else if(command.substr(0, 5) == "echo ")
    {
      std::string echo_text;
      echo_text = command.substr(5);
      std::cout << echo_text << std::endl;
      continue;
    }
    else if(command.substr(0, 5) == "type ")
    {
      //heck for builtin commands
      std::string check=command.substr(5);
      bool flag=false;
      for(int i=0;i<builtin.size();i++)
      {
        if(check==builtin[i])
        {
          std::cout << check << " is a shell builtin" << std::endl;
          flag=true;
          break;
        }
      }
      if (!flag) 
      {
      char* env = getenv("PATH");
      if (!env) continue;

      std::string path(env);
      std::string dir = "";

      for (int j = 0; j < path.size(); j++) 
      {
        if (path[j] == ':') {
            std::string full_path = dir + "/" + check;
            if (access(full_path.c_str(), X_OK) == 0) 
            {
                std::cout << check << " is " << full_path << std::endl;
                flag = true;
                break;
            }
            dir.clear();
        } else {
            dir += path[j];
        }
      }
      if (!flag && !dir.empty()) 
      {
          std::string full_path = dir + "/" + check;
          if (access(full_path.c_str(), X_OK) == 0) {
              std::cout << check << " is " << full_path << std::endl;
              flag=true;
          }
      }
      if(!flag)
      {
        std::cout << check << ": not found" << std::endl;
      }
    }
      continue;
  }
  else if(command.substr(0,3)=="pwd")
  {
    char cwd[BUFFER_SIZE];
    if (getcwd(cwd, sizeof(cwd)) != nullptr) {
        std::cout << cwd << std::endl;
    } else {
        std::cerr << "pwd: error retrieving current directory" << std::endl;
    }
    continue;
  }
  else if(command.substr(0,3)=="cd ")
  {
    std::string path=command.substr(3);
    char *home=getenv("HOME");
    if(path=="~")
    {
      if(chdir(home)!=0)
      {
        std::cout<<"cd: "<<path<<": No such file or directory"<<std::endl;
      }
      continue;
    }
    if(chdir(path.c_str())!=0)
    {
      std::cout<<"cd: "<<path<<": No such file or directory"<<std::endl;
    }
    continue;
  }

    //std::cout << command << ": command not found" << std::endl;
    pid_t pid=fork();
    std::vector<std::string> args;
    std::stringstream iss(command);
    std::string token;
    while(iss >> token)
    {
      args.push_back(token);
    }
    if (args.empty()) continue;
    std::vector<char*> argv;
    for (auto &s : args) {
      argv.push_back(const_cast<char*>(s.c_str()));
    }
    argv.push_back(nullptr);
    if(pid==0)
    {
      //child process
      execvp(argv[0], argv.data());
      std::cout << argv[0] << ": command not found" << std::endl;
      _exit(1);
    }
    else{
      //parent process
      waitpid(pid, nullptr, 0);
    }

  }

}
