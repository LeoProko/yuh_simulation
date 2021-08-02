#include "bot.h"

Bot::Bot(int map_size)
    : position_(std::rand() % map_size, std::rand() % map_size) {
  fill_genes_iter();
  calibrate();
}

Bot::Bot(const Bot& mother, const Bot& father)
    : position_(mother.position_.x, mother.position_.y)
    , health_((mother.health_ + father.health_) / 2) {
  fill_genes_iter();
  for (int i = 0; i < genes_amount_; ++i) {
    *genes_iter_[i] = (*mother.genes_iter_[i] + *father.genes_iter_[i]) / 2;
  }
  calibrate();
}

void Bot::fill_genes_iter() {
  genes_iter_.push_back(&militancy_);
  genes_iter_.push_back(&attractiveness_);
  genes_iter_.push_back(&intelligence_);
  genes_iter_.push_back(&childern_amount_);
  genes_iter_.push_back(&children_health_);
}

void Bot::calibrate() {
  float coeff = 50. * genes_amount_ /
                (militancy_ + intelligence_ + attractiveness_ +
                 childern_amount_ + children_health_);
  for (int i = 0; i < genes_amount_; ++i) {
    *genes_iter_[i] *= coeff;
    *genes_iter_[i] = std::min(std::max(*genes_iter_[i], 0), 99);
  }
}

bool operator<(const Bot& first, const Bot& second) {
  return first.attractiveness_ < second.attractiveness_;
}
