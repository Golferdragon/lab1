#include <SFML/Graphics.hpp>
#include "rand.h"
#include "Config.h"

void render(sf::RenderWindow & window, const std::vector<sf::CircleShape> & shapes) {
  // always clear!
  window.clear();

  // drawing happens here (off-screen)
  for (const auto & shape : shapes) {
    window.draw(shape);
  }

  // swap the display buffer (double-buffering)
  window.display();
}

void processEvents(sf::RenderWindow & window, std::vector<sf::CircleShape> & shapes) {
  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window.close();
    }
  }
}

// Update Circle logic to be aware of wall collision - bounce, warp, teleport the ball if
// collision should happen - NEED TO DO (LAB 1)

void update(sf::Time dt, std::vector<sf::CircleShape> & shapes, sf::RenderWindow& window) {
  float s = dt.asSeconds();
  for (auto & shape : shapes) {
      auto size = window.getSize();
      if(shape.getPosition().y < size.y)
          shape.move(20.0f * s, 20.0f * s);
      if (shape.getPosition().y >= (size.y - 22)) {
          shape.setPosition(rand(22, size.x - 22), rand(22, size.y - 22));
          shape.move(20.0f * s, 20.0f * s);
      }
      if (shape.getPosition().x < size.x)
          shape.move(20.0f * s, 20.0f * s);
      if (shape.getPosition().x >= (size.x - 22)) {
          shape.setPosition(rand(22, size.x - 22), rand(22, size.y - 22));
          shape.move(20.0f * s, 20.0f * s);
      }
  }
}

int main(int argc, char* argv[]) {

  std::string temp = argv[1];
  Config& graphSet = Config::getInstance(temp);

  sf::RenderWindow window{sf::VideoMode{graphSet.width, graphSet.height}, "Lab1"};

  std::vector<sf::CircleShape> shapes{};

  for (int i{}; i < 10; ++i) {
    sf::CircleShape shape{graphSet.radius, 100};
    shape.setFillColor(sf::Color::Blue);
    shape.setOutlineColor(sf::Color::White);
    shape.setPosition(rand(graphSet.radius, graphSet.width - graphSet.radius), rand(graphSet.radius, graphSet.height - graphSet.radius));
    shapes.push_back(shape);
  }

  // for info on game loops:
  //   https://subscription.packtpub.com/book/game+development/9781849696845/1/ch01lvl1sec11/game-loops-and-frames
  sf::Clock clock;

  sf::Time t{sf::Time::Zero}; // time
  sf::Time dt{sf::seconds(1.0f / 60.0f)}; // delta time (fixed to 60fps)

  while (window.isOpen()) {
    processEvents(window, shapes);
    t += clock.restart();

    while (t > dt) {
      t -= dt;
      processEvents(window, shapes);
      update(dt, shapes, window);
    }

    render(window, shapes);
  }
}
