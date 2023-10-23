#include "../includes/Visualizer.hpp"
#include <algorithm>
#include <numeric>
#include <random>

Visualizer::Visualizer() : m_arr(std::vector<int>(100)) {}

// The first window has 22 frames for some reason
// Dummy instance is used to fix this problem
void Visualizer::run_dummy_instance() 
{
    m_window.create(sf::VideoMode(1, 1), "");
    m_window.setPosition(sf::Vector2i(-10000, -10000));
    m_window.setVisible(false);
    m_window.close();
    m_window.setVisible(true);
}

void Visualizer::set_window_name(const std::string& a_name)
{
    m_window.create(sf::VideoMode(1200, 800), a_name);
}

void Visualizer::set_array_size(int a_size)
{
    m_arr.resize(a_size);
}

void Visualizer::set_algorithm(std::shared_ptr<Sort> a_algorithm)
{
    m_algorithm = a_algorithm;
}

void Visualizer::draw(int a_active1, int a_active2, int a_pivot)
{
    m_algorithm->draw(m_window, m_arr, a_active1, a_active2, a_pivot);
}

void Visualizer::perform_sorting()
{
    std::random_device rd{};
    std::mt19937 g(rd());
    std::shuffle(m_arr.begin(), m_arr.end(), g);
    m_algorithm->sort(m_window, m_arr);
    draw(-1, -1, -1);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

void Visualizer::run()
{
    m_window.setVerticalSyncEnabled(false);
    m_window.setFramerateLimit(144);
    std::iota(m_arr.begin(), m_arr.end(), 1);
    perform_sorting();
    while (m_window.isOpen())
    {
        sf::Event event{};
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || 
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            {
                m_window.close();
            }
        }
    }
}