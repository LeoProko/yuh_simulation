#include "run.h"

void Run::init() {
    std::cout << "INITIALIZATION BEGIN\n";
    progress = 0.;
    progress_scale = 1. / parameters::days_amount;
    map_ = Map();
    threads_amount = 8;
    threads.resize(threads_amount);
    all_bots.resize(threads_amount);
    for (int i = 0; i < threads_amount; ++i) {
        if (i != threads_amount - 1) {
            all_bots[i].resize(parameters::bots_amount / threads_amount);
            continue;
        }
        all_bots[i].resize((parameters::bots_amount / threads_amount) + (parameters::bots_amount % threads_amount));
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
    for (int i = 0; i != threads_amount; ++i) {
        for (auto &bot : all_bots[i]) {
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
    avg_collect /= all_bots.size();
    avg_militancy /= all_bots.size();
    avg_intelligence /= all_bots.size();
    avg_children_amount /= all_bots.size();
    avg_children_health /= all_bots.size();
    avg_vision /= all_bots.size();
    avg_share /= static_cast<int64_t>(all_bots.size());
    avg_health /= static_cast<int64_t>(all_bots.size());
    avg_lifetime /= all_bots.size();
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
    json_parameters["bots_amount"] = all_bots.size();
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
    if (progress - 0. >= 1e-6) {
        for (int i = 0; i < 15; ++i) {
            std::cout << "\033[F\x1b[2K";
            std::cout.flush();
        }
    }
    progress += progress_scale;
    std::cout << "[";
    int position = bar_width * progress;
    for (int i = 0; i < bar_width; ++i) {
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
    std::cout << "] " << static_cast<int>(progress * 100.0) << "%\n";
    std::cout << "Day number " << today << "\n";
    std::cout << "Bots amount: " << all_bots.size() << " \n";
    print_average();
}

void Run::run() {
    std::cout << "START SIMULATION WITH PARAMETERS:\n";
    parameters::print();
    init();
    int end_of_day_bots_amount ;
    for (int today = 0; today <= parameters::days_amount; ++today) {
        end_of_day_bots_amount = 0;
        print_progress(today);
        for (int threads_cnt = 0; threads_cnt != threads_amount; ++threads_cnt) {
            threads[threads_cnt] = std::thread([threads_cnt,
                                                &all_bots = all_bots,
                                                &map_ = map_] {
                for (auto bot_iter = all_bots[threads_cnt].begin(); bot_iter != all_bots[threads_cnt].end(); ++bot_iter) {
                    if (bot_iter->health_ > parameters::damage) {
                        move(*bot_iter, map_);
                    }
                }
            });
        }
        for (auto& thread : threads) {
            thread.join();
        }
        std::list<Bot> new_bots;
        int block_sz = parameters::map_size / threads_amount;
        int last_block_extra = parameters::map_size % threads_amount;
        for (int threads_cnt = 0; threads_cnt != threads_amount; ++threads_cnt) {
            threads[threads_cnt] = std::thread([threads_cnt,
                                                last_block_extra,
                                                threads_amount = threads_amount,
                                                block_sz,
                                                &reproduce_mutex = reproduce_mutex,
                                                &map_ = map_,
                                                &new_bots = new_bots] {
                int from = threads_cnt * block_sz;
                int to = threads_cnt * block_sz + block_sz + (threads_cnt == (threads_amount - 1)) * last_block_extra;
                for (int i = from; i != to; ++i) {
                    for (int j = from; j != to; ++j) {
                        map_[Position{i, j}].do_all(new_bots, reproduce_mutex);
                    }
                }
            });
        }
        for (auto& thread : threads) {
            thread.join();
        }
        nlohmann::json json_map = map_;
        bots_amount_file_.print(json_map);
        for (int threads_cnt = 0; threads_cnt != threads_amount; ++threads_cnt) {
            threads[threads_cnt] = std::thread([threads_cnt,
                                                &all_bots = all_bots] {
                for (auto bot_iter = all_bots[threads_cnt].begin(); bot_iter != all_bots[threads_cnt].end();) {
                    if (bot_iter->health_ <= parameters::damage) {
                        auto bot_iter_to_erase = bot_iter++;
                        all_bots[threads_cnt].erase(bot_iter_to_erase);
                    } else {
                        ++bot_iter;
                    }
                }
            });
        }
        for (auto& thread : threads) {
            thread.join();
        }
        auto new_bots_it_from = new_bots.begin();
        auto new_bots_it_to = new_bots.begin();
        block_sz = (threads_amount / int(new_bots.size()));
        last_block_extra = (threads_amount % int(new_bots.size()));
        for (int i = 0; i != threads_amount; ++i) {
            int from = block_sz * i;
            int to = block_sz * i + block_sz + (i == threads_amount - 1) * last_block_extra;
            std::advance(new_bots_it_to, from - to);
            all_bots[i].splice(all_bots[i].begin(), new_bots, new_bots_it_from, new_bots_it_to);
            new_bots_it_from = new_bots_it_to;
        }
        map_.clean_and_respawn();
        for (int i = 0; i != threads_amount; ++i) {
            end_of_day_bots_amount += all_bots[i].size();
        }
        if (end_of_day_bots_amount == 0) {
            break;
        }
    }
    if (end_of_day_bots_amount == 0) {
        std::cout << "SIMULATION FAILED. ALL BOTS DEAD!\n";
    } else {
        std::cout << "SUCCESSFUL SIMULATION. CONGRATULAIONS!\n";
    }
}
