#include "clustering.h"

clustering::clustering(int cluster_count, const std::string &model_path)
  : m_cluster_count(cluster_count)
  , m_model_fname(model_path)
{
}

void clustering::read_data()
{
  std::string offer_raw_data;

  std::fstream file("../data.csv");
  //while(std::getline(std::cin, offer_raw_data))
  while(std::getline(file, offer_raw_data))
  {
    m_offers.push_back(make_offer(offer_raw_data));
  }
  std::cout << "read done" << std::endl;
}

void clustering::do_work()
{
  dlib::kcentroid<kernel_type_t> kc(kernel_type_t(0.01), 8, m_cluster_count);
  dlib::kkmeans<kernel_type_t> kkmeans(kc);
  std::vector<realty_offer_t> initial_centers;

  kkmeans.set_number_of_centers(m_cluster_count);
  pick_initial_centers(m_cluster_count, initial_centers, m_offers, kkmeans.get_kernel());
  find_clusters_using_kmeans(m_offers, initial_centers);
  kkmeans.train(m_offers, initial_centers);

  for (const auto &offer : m_offers)
  {
    m_labels.push_back(kkmeans(offer));
  }

  ovo_trainer_t ovo_trainer;
  dlib::krr_trainer<kernel_type_t> linear_trainer;
  ovo_trainer.set_trainer(linear_trainer);

  auto df = ovo_trainer.train(m_offers, m_labels);
  std::cout << "serialize begin" << std::endl;
  dlib::serialize(m_model_fname) << m_offers << m_labels;
}

realty_offer_t clustering::make_offer(const std::string &offer_raw_data)
{
  realty_offer_t m;
  std::string item;
  std::stringstream input(offer_raw_data);
  for(int i = 0; i < 6; i++)
  {
    std::getline(input, item, ';');
    (item.size() == 0) ? m(i) = 0 : m(i) = std::stod(item);
  }
  std::getline(input, item, ';');
  double floor = 0;
  (item.size() == 0) ? floor = 0 : floor = std::stoi(item);

  std::getline(input, item, ';');
  double floors_total = 0;
  (item.size() == 0) ? floors_total = 0 : floors_total = std::stoi(item);

  ((floor == floors_total) || (floor == 1)) ? m(6) = 0 : m(6) = 1;

  return m;
}
