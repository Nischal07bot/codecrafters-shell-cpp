#include <iostream>
#include <string>
#include <vector>
int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  //TODO: Uncomment the code below to pass the first stage
  std::vector<std::string> builtin={"exit","echo","type"};
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
      if(!flag)
      {
        std::cout<<check<<": not found"<<std::endl;
      }
      continue;
    }
    std::cout << command << ": command not found" << std::endl;
  }

}
