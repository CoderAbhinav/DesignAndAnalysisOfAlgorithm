#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

#define NUM_PHILOSOPHERS 5

std::mutex forks[NUM_PHILOSOPHERS];
std::mutex output_mutex; // Mutex to lock output

void philosopher(int id) {
    int left_fork = id;
    int right_fork = (id + 1) % NUM_PHILOSOPHERS;

    std::unique_lock<std::mutex> left_lock(forks[left_fork]);
    std::unique_lock<std::mutex> right_lock(forks[right_fork]);

    {
        std::lock_guard<std::mutex> lock(output_mutex);
        std::cout << "Philosopher " << id << " is eating. Generated at " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() << std::endl;
    }

    // Simulate eating
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    {
        std::lock_guard<std::mutex> lock(output_mutex);
        std::cout << "Philosopher " << id << " finished eating. Generated at " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() << std::endl;
    }


    // Unlock the forks
    left_lock.unlock();
    right_lock.unlock();
}

int main() {
    std::thread philosophers[NUM_PHILOSOPHERS];

    // Start philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        philosophers[i] = std::thread(philosopher, i);
    }

    // Wait for philosopher threads to finish
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        philosophers[i].join();
    }

    return 0;
}
