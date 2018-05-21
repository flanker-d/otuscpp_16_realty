#include <iostream>
#include <realty_clustering/clustering.h>

int main(int argc, char **argv)
{
  if(argc == 3)
  {
    clustering rclst(std::stoi(argv[1]), argv[2]);
    rclst.read_data();
    rclst.do_work();
  }
  else
    std::cout << "usage: rclst <clusters_count> <modelfname>" << std::endl;

  return 0;
}