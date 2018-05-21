#pragma once

#include <data_types.h>

class clustering
{
  public:
    clustering(int cluster_count, const std::string& model_path);
    void read_data();
    void do_work();

  private:
    realty_offer_t make_offer(const std::string& offer_raw_data);

  private:
    int m_cluster_count;
    std::string m_model_fname;
    std::vector<realty_offer_t> m_offers;
    std::vector<double> m_labels;
};
