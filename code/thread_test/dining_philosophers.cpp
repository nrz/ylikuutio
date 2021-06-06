// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2021 Antti Nuortimo.
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
#include <cstdlib>  // std::rand, std::srand
#include <iostream> // std::cout, std::cin, std::cerr
#include <mutex>    // std::mutex, std::scoped_lock
#include <stdint.h> // uint32_t etc.
#include <thread>   // std::thread
#include <ctime>    // std::time
#include <vector>   // std::vector

class Messenger
{
    public:
        std::mutex my_mutex;
};

class Random
{
    public:
        Random()
        {
            // constructor.
            std::srand(std::time(nullptr)); // Use current time as seed.
        }

        float get_random()
        {
            float dividend = static_cast<float>(std::rand() % 10000);
            float divisor = static_cast<float>(std::rand() % 10000);
            return dividend / divisor / 10000.0f;;
        }

        std::mutex my_mutex;
};

class Fork
{
    public:
        Fork()
        {
            // constructor.
        }

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
            // constructor.
            const std::lock_guard<std::mutex> lock(this->messenger.my_mutex);
            std::cout << "Philosopher " << this->id << " says hello!\n";
        }

        void eat()
        {
            std::scoped_lock fork_lock(this->left_fork.my_mutex, this->right_fork.my_mutex);
            float eat_time = 0.0f;
            {
                const std::lock_guard<std::mutex> random_lock(this->random.my_mutex);
                eat_time = this->random.get_random();
            }
            {
                const std::lock_guard<std::mutex> lock(this->messenger.my_mutex);
                std::cout << "Philosopher " << this->id << " is eating for " << eat_time << " seconds...\n";
            }
            std::this_thread::sleep_for(std::chrono::duration<float>(eat_time));
        }

        void think()
        {
            float think_time = 0.0f;
            {
                const std::lock_guard<std::mutex> random_lock(this->random.my_mutex);
                think_time = this->random.get_random();
            }
            {
                const std::lock_guard<std::mutex> lock(this->messenger.my_mutex);
                std::cout << "Philosopher " << this->id << " is thinking for " << think_time << " seconds...\n";
            }
            std::this_thread::sleep_for(std::chrono::duration<float>(think_time));
        }

        void philosophize()
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
            // constructor.

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

        std::vector<Fork> forks;
        std::vector<Philosopher> philosophers;
        std::vector<std::thread> threads;
        const uint32_t n_philosophers;
        Messenger& messenger;
        Random& random;
};

int main()
{
    Messenger messenger;
    Random random;
    Table table(5, messenger, random);
    table.dine();
    table.cleanup();
}
