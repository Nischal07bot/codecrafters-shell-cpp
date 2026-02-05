#include <iostream>
#include <string>

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  //TODO: Uncomment the code below to pass the first stage
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
    std::cout << command << ": command not found" << std::endl;
  }

}
