#include <realty_classification/classification.h>
#include <iostream>

int main(int argc, char **argv)
{
  if(argc == 2)
  {
    classification rclss(argv[1]);
    rclss.do_work();
  }
  else
    std::cout << "Usage: rclss <modelfname>" << std::endl;

  return 0;
}