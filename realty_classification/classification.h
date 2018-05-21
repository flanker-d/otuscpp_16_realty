#pragma once

#include <data_types.h>

class classification
{
  public:
    classification(const std::string &modelfname);
    void do_work();

  private:
    realty_offer_t make_offer(const std::string &offer_raw_data);

  private:
    dlib::one_vs_one_decision_function<ovo_trainer_t, dlib::decision_function<kernel_type_t>> m_df;
    realty_offer_map_t m_offer_map;
};
