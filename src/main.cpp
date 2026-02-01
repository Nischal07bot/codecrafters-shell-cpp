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
        std::string path=getenv("PATH");
        int sz=path.size();
        std::string dir="";
        int j=0;
        while(j<sz)
        {
          if(path[j]==':')
          {
            std::string full_path=dir+"/"+check;
            FILE *file;
            if((file=fopen(full_path.c_str(),"r"))!=NULL)
            {
              std::cout << check << " is " << full_path << std::endl;
              fclose(file);
              break;
            }
            dir="";
          }
          else
          {
            dir+=path[j];
          }
          j++;

      }
      if (!dir.empty()) 
      {
        std::string full_path = dir + "/" + check;
        FILE *file;
        if ((file = fopen(full_path.c_str(), "r")) != NULL) 
        {
        std::cout << check << " is " << full_path << std::endl;
        fclose(file);
        }
      }
      continue;
    }
    std::cout << command << ": command not found" << std::endl;
  }

}
