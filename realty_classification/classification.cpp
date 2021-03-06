#include "classification.h"
#include <cmath>

classification::classification(const std::string &modelfname)
{
  std::vector<double> labels;
  std::vector<realty_offer_t> offers;

  dlib::deserialize(modelfname) >> offers >> labels >> m_df;

  for(std::size_t idx = 0; idx < labels.size(); idx++)
  {
    m_offer_map[labels.at(idx)].emplace_back(offers.at(idx));
  }
}

void classification::do_work()
{
  std::string offer_raw_data;
  while(std::getline(std::cin, offer_raw_data))
  {
    realty_offer_t offer = make_offer(offer_raw_data);
    double label = m_df(offer);
    auto offers_it = m_offer_map.find(label);
    if(offers_it != m_offer_map.end())
    {
      auto& off_vect = offers_it->second;
      std::sort(off_vect.begin(), off_vect.end(), [offer](auto &lhs, auto &rhs){
        return (std::sqrt(std::pow(offer(0) - lhs(0), 2) + std::pow(offer(1) - lhs(1), 2))) <
               (std::sqrt(std::pow(offer(0) - rhs(0), 2) + std::pow(offer(1) - rhs(1), 2)));
      });

      for(auto &it : off_vect)
      {
        for(int i = 0; i < 7; i++)
          std::cout << std::setprecision(10) << it(i) << ";";
        std::cout << std::endl;
      }
    }
  }
}

realty_offer_t classification::make_offer(const std::string &offer_raw_data)
{
  realty_offer_t m;
  std::string item;
  std::stringstream input(offer_raw_data);
  for(int i = 0; i < 7; i++)
  {
    std::getline(input, item, ';');
    if(i != 6)
      (item.size() == 0) ? m(i) = 0 : m(i) = std::stod(item);
    else
      (item.size() == 0) ? m(i) = 0 : ((std::stod(item) > 1) ? m(i) = 1 : m(i) = 0);
  }
  return m;
}
