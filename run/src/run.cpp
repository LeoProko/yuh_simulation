#include "run.h"

void Run::init() {
    std::cout << "INITIALIZATION BEGIN\n";
    progress_ = 0.;
    progress_scale_ = 1. / parameters::days_amount;
    map_ = Map();
    threads_.resize(parameters::threads_amount);
    all_bots_.resize(parameters::threads_amount);
    bots_amount_ = parameters::bots_amount;
    int thread_block_size = parameters::bots_amount / parameters::threads_amount;
    int thread_block_size_reminder = parameters::bots_amount % parameters::threads_amount;
    for (int thread_num = 0; thread_num < parameters::threads_amount; ++thread_num) {
        if (thread_num != parameters::threads_amount - 1) {
            for (int i = 0; i < thread_block_size; ++i) {
                all_bots_[thread_num].emplace_back();
            }
            continue;
        }
        for (int i = 0; i < thread_block_size + thread_block_size_reminder; ++i) {
            all_bots_[thread_num].emplace_back();
        }
    }
    bots_amount_file_ = File("visualization/json/bots_amount.json");
    parameters_file_ = File("visualization/json/parameters.json");
    parameters_file_.print(std::string("bots_amount "));
    parameters_file_.print(std::string("collect "));
    parameters_file_.print(std::string("militancy "));
    parameters_file_.print(std::string("intelligence "));
    parameters_file_.print(std::string("vision "));
    parameters_file_.print(std::string("share "));
    parameters_file_.print(std::string("children_amount "));
    parameters_file_.print(std::string("children_health "));
    parameters_file_.print(std::string("health "));
    parameters_file_.print(std::string("lifetime "));
    parameters_file_.print(std::string("altruists_amount "));
    parameters_file_.print(std::string("greenbeared_amount "));
    parameters_file_.print(std::string("greenbeared_altruists_amount\n"));
    std::cout << "INITIALIZATION COMPLETED\n";
}

void Run::print_average() {
    int avg_collect = 0;
    int avg_militancy = 0;
    int avg_intelligence = 0;
    int avg_children_amount = 0;
    int avg_children_health = 0;
    int avg_vision = 0;
    int64_t avg_share = 0;
    int64_t avg_health = 0;
    int avg_lifetime = 0;
    int altruists_amount = 0;
    int greenbeared_amount = 0;
    int greenbeared_altruists_amount = 0;
    for (int thread_num = 0; thread_num != parameters::threads_amount; ++thread_num) {
        for (const auto& bot : all_bots_[thread_num]) {
            avg_collect += bot.collect_;
            avg_militancy += bot.militancy_;
            avg_intelligence += bot.intelligence_;
            avg_children_amount += bot.children_amount_;
            avg_children_health += bot.children_health_;
            avg_vision += bot.vision_;
            avg_share += bot.share_;
            avg_health += bot.health_;
            avg_lifetime += bot.lifetime_;
            if (bot.is_altruist_ && bot.is_greenbeared_) {
                greenbeared_altruists_amount += bot.is_altruist_ && bot.is_greenbeared_;
            } else {
                altruists_amount += bot.is_altruist_;
                greenbeared_amount += bot.is_greenbeared_;
            }
        }
    }
    avg_collect /= bots_amount_;
    avg_militancy /= bots_amount_;
    avg_intelligence /= bots_amount_;
    avg_children_amount /= bots_amount_;
    avg_children_health /= bots_amount_;
    avg_vision /= bots_amount_;
    avg_share /= static_cast<int64_t>(bots_amount_);
    avg_health /= static_cast<int64_t>(bots_amount_);
    avg_lifetime /= bots_amount_;
    std::cout << "Average collect..............." << avg_collect << "\n";
    std::cout << "Average militancy............." << avg_militancy << "\n";
    std::cout << "Average intelligence.........." << avg_intelligence << "\n";
    std::cout << "Average vision................" << avg_vision / 10 << " \n";
    std::cout << "Average share................." << avg_share << " \n";
    std::cout << "Average children amount......." << avg_children_amount / 10 << "\n";
    std::cout << "Average children health......." << avg_children_health << "\n";
    std::cout << "Average health................" << avg_health << "\n";
    std::cout << "Average lifetime.............." << avg_lifetime << "\n";
    std::cout << "Altruists amount.............." << altruists_amount << "\n";
    std::cout << "Greenbeared amount............" << greenbeared_amount << "\n";
    std::cout << "Greenbeared altruists amount.." << greenbeared_altruists_amount << "\n";
    nlohmann::json json_parameters;
    json_parameters["bots_amount"] = bots_amount_;
    json_parameters["collect"] = avg_collect;
    json_parameters["militancy"] = avg_militancy;
    json_parameters["intelligence"] = avg_intelligence;
    json_parameters["vision"] = avg_vision;
    json_parameters["share"] = avg_share;
    json_parameters["children_amount"] = avg_children_amount;
    json_parameters["children_health"] = avg_children_health;
    json_parameters["health"] = avg_health;
    json_parameters["lifetime"] = avg_lifetime;
    json_parameters["altruists_amount"] = altruists_amount;
    json_parameters["greenbeared_amount"] = greenbeared_amount;
    json_parameters["greenbeared_altruists_amount"] = greenbeared_altruists_amount;
    parameters_file_.print(json_parameters);
}

void Run::print_progress(int today) {
    if (progress_ - 0. >= 1e-6) {
        for (int i = 0; i < 15; ++i) {
            std::cout << "\033[F\x1b[2K";
            std::cout.flush();
        }
    }
    progress_ += progress_scale_;
    std::cout << "[";
    int position = bar_width_ * progress_;
    for (int i = 0; i < bar_width_; ++i) {
        if (i < position) {
            std::cout << "=";
        }
        else if (i == position) {
            std::cout << ">";
        }
        else {
            std::cout << " ";
        }
    }
    std::cout << "] " << static_cast<int>(progress_ * 100.0) << "%\n";
    std::cout << "Day number " << today << "\n";
    std::cout << "Bots amount: " << bots_amount_ << " \n";
    print_average();
}

void Run::thread_move(int thread_num) {
    for (auto bot_iter = all_bots_[thread_num].begin(); bot_iter != all_bots_[thread_num].end(); ++bot_iter) {
        if (bot_iter->health_ > parameters::damage) {
            move(*bot_iter, map_);
        }
    }
}

void Run::thread_do_all(int thread_num, std::list<Bot>& bots) {
    int thread_block_size = parameters::map_size /
        parameters::threads_amount;
    int thread_block_size_reminder = parameters::map_size %
        parameters::threads_amount;
    int from = thread_num * thread_block_size;
    int to = (1 + thread_num) * thread_block_size + 
        (thread_num == (parameters::threads_amount - 1)) *
        thread_block_size_reminder;
    for (int x = 0; x != parameters::map_size; ++x) {
        for (int y = from; y != to; ++y) {
            map_[Position(x, y)].do_all(bots);
        }
    }
}

void Run::thread_bot_erase(int thread_num) {
    for (auto bot_iter = all_bots_[thread_num].begin(); bot_iter != all_bots_[thread_num].end();) {
        if (bot_iter->health_ <= parameters::damage) {
            auto bot_iter_to_erase = bot_iter++;
            all_bots_[thread_num].erase(bot_iter_to_erase);
        } else {
            ++bot_iter;
        }
    }
}

void Run::add_bots(std::list<Bot>& bots) {
    auto bots_it_from = bots.begin();
    auto bots_it_to = bots.begin();
    int thread_block_size = static_cast<int>(bots.size()) /
        parameters::threads_amount;
    int thread_block_size_reminder = static_cast<int>(bots.size()) %
        parameters::threads_amount;
    for (int thread_num = 0; thread_num != parameters::threads_amount; ++thread_num) {
        int distance = thread_block_size + 
            (thread_num == parameters::threads_amount - 1) *
            thread_block_size_reminder;
        std::advance(bots_it_to, distance);
        all_bots_[thread_num].splice(
            all_bots_[thread_num].end(),
            bots,
            bots_it_from,
            bots_it_to
        );
        bots_it_from = bots_it_to;
    }
}

void Run::update_bots_amount() {
    bots_amount_ = 0;
    for (int thread_num = 0; thread_num != parameters::threads_amount; ++thread_num) {
        bots_amount_ += all_bots_[thread_num].size();
    }
}

void Run::run() {
    std::cout << "START SIMULATION WITH PARAMETERS:\n";

    parameters::print();
    init();

    for (int today = 0; today <= parameters::days_amount; ++today) {
        print_progress(today);

        for (int thread_num = 0; thread_num != parameters::threads_amount; ++thread_num) {
            threads_[thread_num] = std::thread(&Run::thread_move, this, thread_num);
        }
        for (auto& thread : threads_) {
            thread.join();
        }

        std::list<Bot> new_bots;
        for (int thread_num = 0; thread_num != parameters::threads_amount; ++thread_num) {
            threads_[thread_num] = std::thread(&Run::thread_do_all, this, thread_num, std::ref(new_bots));
        }
        for (auto& thread : threads_) {
            thread.join();
        }

        nlohmann::json json_map = map_;
        bots_amount_file_.print(json_map);

        for (int thread_num = 0; thread_num != parameters::threads_amount; ++thread_num) {
            threads_[thread_num] = std::thread(&Run::thread_bot_erase, this, thread_num);
        }
        for (auto& thread : threads_) {
            thread.join();
        }

        add_bots(new_bots);
        map_.food_amount_ = 0;
        for (int thread_num = 0; thread_num != parameters::threads_amount; ++thread_num) {
            threads_[thread_num] = std::thread(&Map::clean_and_respawn, std::ref(map_), thread_num);
        }
        for (auto& thread : threads_) {
            thread.join();
        }
        update_bots_amount();

        if (bots_amount_ == 0) {
            break;
        }
    }
    if (bots_amount_ == 0) {
        std::cout << "SIMULATION FAILED. ALL BOTS DEAD!\n";
    } else {
        std::cout << "SUCCESSFUL SIMULATION. CONGRATULAIONS!\n";
    }
}
