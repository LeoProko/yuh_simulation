# yuh_simulation
*Study of the influence of different genes on development*

The goal of the project is to understand which genes contribute to the survival and development of bots.
What will be the main competitive advantage in such a harsh struggle for life

# Simulation structure
Simulation parameters are set in the main `main/main.cpp `

## Population
Each step of the simulation will consist of one virtual day.
In one day, the bots will walk, interact
with each other, fight for food and among themselves, beware of predators and
notify others of the approaching danger

## Bot
Each bot will consist of two types of fields
- Genome: hereditary genes that affect the behavior of the bot and its offspring
    - collect -- responsible for how much food the bot will collect from the cage
- militancy -- the belligerence gene that determines the winner in a fight
    - vision -- vision: for example, if this gene is equal to two, then the bot chooses where to go from the cells that are within a radius of two from it.
    - intelligence -- the gene that is responsible for which cell the bot will go to: if it is large, then the bot will go to a cell with a lot of food
    - children_amount -- the gene for the number of children who will be born when mating with another bot
- children_health -- the gene for children's health
- is_altruist -- the gene for altruism
    - is_greenbeared -- the green beard gene
- Current stats: health, life time and protection from the enemy
    - health - current health, which is also associated with capital, that is, it can be more than a hundred
    - lifetime - the lifetime of the bot, with each iteration of the simulation, it increases by one
    - is_protected -- whether the bot is protected from the enemy for the current turn. More about this will be in the chapter about altruists

### Bot Replication
If there are more than two bots in some cell, then the two best ones are selected from them according to this bot comparison operator

```cpp
bool operator<(const Bot& first, const Bot& second) {
    return 
        first.collect_ + 
        first.militancy_ + 
        first.intelligence_ + 
        first.health_ -
        3 * first.lifetime_
        <
        second.collect_ + 
        second.militancy_ + 
        second.intelligence_ + 
}
```

This operator was formed from the considerations that the coolness of the bot is collectivity, belligerence, intelligence and health.
However, age is a negative trait, just like in real life: everyone is interested in younger people. The age still goes
with a factor of three, since all other genes range from 0 to 100 and on average they are quite large, and the life
time, depending on the launch parameters, on average reaches from 10 to 25.

Thus, we have identified the two most attractive bots, now we need to somehow give birth to children. They inherit all the genes,
like the arithmetic mean between mom and dad, except for health. It is calculated by the following formula

```cpp
health_(
    (
        mother->health_ + father->health_ +
        2 * mother->children_health_ + 2 * father->children_health_
    ) / (
        6 + std::max(0, (mother->children_amount_ + father->children_amount_) / 20)
    )
)
```

This is due to reducing `children_amount` to reasonable limits. Here, as we can see, the health of children is calculated
as the average between the health of parents and the hereditary gene of children's health with a factor of two, but additionally
it is divided by the total number of children born. Note that we divide not by 2, but by 20, since here we are still normalizing
the gene for the number of children and lead to a range of values from 0 to 10, not from 0 to 100. Now, in more detail, why this is so.

## The problem of rebirth
At the first runs of the simulation, we were amazed that `children_amount` and `children_health` were pumped to the maximum,
and `lifetime` was consistently zero. That is, the bots decided that for a decent life it is better for them to reproduce than to live themselves.

The solution to this problem was as follows
- Normalization of `children_amount` with a maximum value of 10
- Parents` damag according to `children_amount', that is, the more they give birth, the more they themselves will damage
- Taking into account the current health of parents during reproduction, as shown in the code above, that is, now even if the children's health gene is very large, but the parents themselves are all crippled, then they cannot have a perfectly healthy child
- Removing the maximum limit from the current health of bots, that is, now they can save and take care of their capital.

About the results, what this led to, will be later in the analysis of all simulations.

### Food sharing
Food is distributed among all bots in direct proportion to all bots in the cell according to the `collect` gene

### War
The bots in each cell are sorted by `militancy` and everyone starts fighting in pairs: the first with the second, the third with the fourth, etc.

The winner is the one who has more `militancy` and gets himself `damage` health, which is set by the simulation parameters, and the loser accordingly loses so much health

## Altruists and predators
Food and predators are randomly generated all over the map every day. Their number is set by the simulation parameters.

If there is a predator in the cage, then it kills all the unprotected ones. Protection is distributed by an altruist, and only to those who have a green beard.
About why this is so, and why it is necessary, you can read [here](https://www.youtube.com/watch?v=goePYJ74Ydg ).

# Simulation results
## Population
![visualization/charts/bots_amount.jpg](visualization/charts/bots_amount.jpg)

As we can see, immediately after initialization in 50'000 bots, there is a sharp reduction to 6'000, and in just a couple of days
the same jump occurs, but already up to 75'000 and stays at the level of 55'000-60'000 for the rest of the time.

As for altruists and greensbeards, we can say that those who own both genes are about 22,000, that is, about 40% of the total population.

In second place are exclusively greybeards, there are about 16'000 of them. And in third place are exclusively altruists, there are about 10,000 of them

## Genes and characteristics
![visualization/charts/parameters.jpg](visualization/charts/parameters.jpg)

## Video visualization
[![Video visualization](https://img.youtube.com/vi/Ydg23d_g6O0/0.jpg)](https://www.youtube.com/watch?v=Ydg23d_g6O0)

# Working with the repository
The first step is to clone the repository
```bash
git clone https://github.com/LeoProko/huy_simulation.git
```

## Build and launch
### Remark
The project takes several minutes to build due to downloading the library for working with `json`,
and the code execution itself can take from several minutes to several hours,
so if you are only interested in the results, they are given above, you can also
view them in the `visualization` folder. When running the simulation, files from this folder may
be lost, so be careful.

### Automatic assembly and visualization
Run the file `make_run_visualize.sh `
``bash
./make_run_visualize.sh
``
You will have a project assembled and launched, and upon completion, visualization will automatically begin

### Manual assembly and visualization

Run the file assembly.sh
``bash
./assembly.sh
``

This file consists of commands

```bash
mkdir build
cd build
cmake ..
make -j
cd ..
```

## Launch
Run the file start_simulation.sh
``bash
./start_simulation.sh
``

This file consists of commands

```bash
./build/main/bin/main
```

## Visualization
Run the simulation and when finished, go to the `visualization' directory.
There will be a file `results.json` with all the necessary data
for visualization and executable files `make_charts.sh ` and `make_vieo.sh `.
Run them accordingly in turn.
At the output you will get a video with a simulation.

---
*Information for collaborators*
After you have been added to the collaborators, create a brunch for yourself for the task

```bash
git checkout master
git pull
git checkout -b branch_name
```

Now you can do whatever you want in your brunch, it won't affect the rest.
After you have finished the work, you need to add changes to the brunch

```bash
git add file_name_or_directory_name
```

And commit everything

```bash
git commit -m "[folder_name] change description"
```

Now we need to push the changes to github

```bash
git push
```

The first time you will have an error. It will indicate the command
that you need to write to solve

Now we go to the repository on github and asks someone to review your brunch

After you and the reviewer have come to a joint agreement, you can
hold your brunch in the master

### Amenities

First of all, configure git. If you have already done this, then you do not need to set it up again
```bash
git config --global user.name "Vasya Pupkin"
git config --global user.email vasya@pupkin.ru
```

For convenience, you can create a file on your computer in the folder `/home/username/`
`.gitconfig`. Insert the following data into it

```bash
[user]
    name = github_username
    email = github_email

[alias]
    co = checkout
    cm = commit
    st = status
```

Replace `github_username` with your nickname on github, and `github_email` to your email address,
which you have linked to github

Now you can write just `co` instead of the cumbersome `checkout`,
instead of `status` `st`, and instead of `commit` `cm`
