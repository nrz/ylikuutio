// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2025 Antti Nuortimo.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <chrono>   // std::chrono
#include <iostream> // std::cout
#include <mutex>    // std::mutex, std::scoped_lock
#include <random>   // std::mt19937, std::random_device
#include <stdint.h> // uint32_t etc.
#include <thread>   // std::thread
#include <vector>   // std::vector

class Messenger
{
    public:
        std::mutex my_mutex;
};

class Random
{
    public:
        Random(std::uniform_real_distribution<float>& distribution, std::mt19937& generator)
            : distribution { distribution },
            generator      { generator }
        {
        }

        float get_random() const
        {
            return this->distribution(this->generator);
        }

        std::mutex my_mutex;

    private:
        std::uniform_real_distribution<float>& distribution;
        std::mt19937& generator;
};

class Fork
{
    public:
        Fork() = default;

        std::mutex my_mutex;
};

class Philosopher
{
    public:
        Philosopher(Messenger& messenger, Random& random, const uint32_t id, Fork& left_fork, Fork& right_fork)
            : messenger { messenger },
            random { random },
            left_fork { left_fork },
            right_fork { right_fork },
            id { id }
        {
            const std::lock_guard<std::mutex> messenger_lock(this->messenger.my_mutex);
            std::cout << "Philosopher " << this->id << " says hello!\n";
        }

        void eat() const
        {
            const std::scoped_lock fork_lock(this->left_fork.my_mutex, this->right_fork.my_mutex);
            float eat_time = 0.0f;
            {
                const std::lock_guard<std::mutex> random_lock(this->random.my_mutex);
                eat_time = this->random.get_random();
            }
            {
                const std::lock_guard<std::mutex> messenger_lock(this->messenger.my_mutex);
                std::cout << "Philosopher " << this->id << " is eating for " << eat_time << " seconds...\n";
            }
            std::this_thread::sleep_for(std::chrono::duration<float>(eat_time));
        }

        void think() const
        {
            float think_time = 0.0f;
            {
                const std::lock_guard<std::mutex> random_lock(this->random.my_mutex);
                think_time = this->random.get_random();
            }
            {
                const std::lock_guard<std::mutex> messenger_lock(this->messenger.my_mutex);
                std::cout << "Philosopher " << this->id << " is thinking for " << think_time << " seconds...\n";
            }
            std::this_thread::sleep_for(std::chrono::duration<float>(think_time));
        }

        void philosophize() const
        {
            while (true)
            {
                eat();
                think();
            }
        }

    private:
        Messenger& messenger;
        Random& random;
        Fork& left_fork;
        Fork& right_fork;
        const uint32_t id;
};

class Table
{
    public:
        Table(const uint32_t n_philosophers, Messenger& messenger, Random& random)
            : n_philosophers { n_philosophers },
            messenger { messenger },
            random { random },
            forks(n_philosophers)
        {
            this->philosophers.reserve(this->n_philosophers);

            if (this->n_philosophers > 0)
            {
                this->philosophers.emplace_back(this->messenger, this->random, 0, this->forks.back(), this->forks.front());
            }

            for (uint32_t id = 1; id < this->n_philosophers; id++)
            {
                this->philosophers.emplace_back(this->messenger, this->random, id, this->forks.at(id - 1), this->forks.at(id));
            }

            this->threads.resize(this->n_philosophers);
        }

        void dine()
        {
            for (uint32_t i = 0; i < this->n_philosophers; i++)
            {
                this->threads.at(i) = std::thread { &Philosopher::philosophize, this->philosophers.at(i) };
            }
        }

        void cleanup()
        {
            for (std::thread& my_thread : this->threads)
            {
                my_thread.join();
            }
        }

        const uint32_t n_philosophers;
        Messenger& messenger;
        Random& random;
        std::vector<Fork> forks;
        std::vector<Philosopher> philosophers;
        std::vector<std::thread> threads;
};

int main()
{
    std::random_device random_device;
    std::uniform_real_distribution<float> distribution(0.0f, 0.1f);
    std::mt19937 generator(random_device());
    Messenger messenger;
    Random random(distribution, generator);
    Table table(5, messenger, random);
    table.dine();
    table.cleanup();
}
