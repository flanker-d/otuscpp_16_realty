#pragma once

#include <dlib/clustering.h>
#include <dlib/matrix.h>
#include <dlib/svm_threaded.h>

using realty_offer_t = dlib::matrix<double, 7, 1>;
using kernel_type_t = dlib::radial_basis_kernel<realty_offer_t>;
using ovo_trainer_t = dlib::one_vs_one_trainer<dlib::any_trainer<realty_offer_t>> ;
using ovo_df_t = dlib::one_vs_one_decision_function<ovo_trainer_t>;
using realty_offer_map_t = std::map<double, std::vector<realty_offer_t>>;